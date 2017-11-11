//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Mac16094Metrics.h"

#include <../../veins/src/veins/modules/phy/DeciderResult80211.h>
#include <../../veins/src/veins/base/phyLayer/PhyToMacControlInfo.h>
#include "veins/modules/messages/PhyControlMessage_m.h"
using namespace std;
#define DBG_MAC EV
Define_Module(Mac16094Metrics);

void Mac16094Metrics::initialize(int i) {
    cout << setiosflags(ios::fixed) << setprecision(10);

    metrics = new Metrics();
    statsReceivedPackets = 0;
    statsMbpsReceived = 0;
    statsControlMbpsReceived = 0;
    throughputMetricMac = 0;
    throughputMbps = 0;
    throughputControlMbps = 0;
    receivedFramesLowerMsg = 0;
    receivedBitsLowerPackets = 0;
    receivedBitsLowerWsm = 0;
    packetsNotForMe = 0;
    statsReceivedBits = 0;
    collisionsPktNonDecoded = 0;

    throughputSignalMac = registerSignal("throughputSignalMac");
    channelUtilization.insert(std::pair<int, double>(Channels::CRIT_SOL, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::SCH1, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::SCH2, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::CCH, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::SCH3, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::SCH4, 0.0));
    channelUtilization.insert(std::pair<int, double>(Channels::HPPS, 0.0));

    Mac1609_4::initialize(i);

    WATCH(throughputMetricMac);
    WATCH(throughputMbps);
    WATCH(throughputControlMbps);
    WATCH(collisionsPktNonDecoded);
}

void Mac16094Metrics::finish() {

    recordScalar("throughputMetricMac", throughputMetricMac);
    recordScalar("throughputMbps", throughputMbps);
    recordScalar("throughputControlMbps", throughputControlMbps);
    recordScalar("receivedFramesLowerMsg", receivedFramesLowerMsg);
    recordScalar("receivedBitsLowerPackets", receivedBitsLowerPackets);
    recordScalar("receivedBitsLoserWsm", receivedBitsLowerPackets);
    recordScalar("packetsNotForMe", packetsNotForMe);
    recordScalar("receivedTotalBits", statsReceivedBits);
    recordScalar("collisionsPktNonDecoded", collisionsPktNonDecoded);
    recordScalar("chUtilizationSCH1", channelUtilization.at(Channels::SCH1));
    recordScalar("chUtilizationSCH2", channelUtilization.at(Channels::SCH2));
    recordScalar("chUtilizationSCH3", channelUtilization.at(Channels::SCH3));
    recordScalar("chUtilizationSCH4", channelUtilization.at(Channels::SCH4));
    recordScalar("chUtilizationCCH", channelUtilization.at(Channels::CCH));
    recordScalar("chUtilizationHPPS", channelUtilization.at(Channels::HPPS));
    recordScalar("chUtilizationCRIT_SOL",channelUtilization.at(Channels::CRIT_SOL));

    Mac1609_4::finish();
}

void Mac16094Metrics::handleLowerMsg(cMessage* message) {

    Mac80211Pkt* macPkt = static_cast<Mac80211Pkt*>(message);
    ASSERT(macPkt);

    WaveShortMessage* wsm =
            dynamic_cast<WaveShortMessage*>(macPkt->decapsulate());
    receivedFramesLowerMsg++;

    double macPktBitLength = (macPkt->getBitLength());
    receivedBitsLowerPackets = receivedBitsLowerPackets + macPktBitLength;

    double tempBitLength = (wsm->getWsmLength());
    receivedBitsLowerWsm = receivedBitsLowerWsm + tempBitLength;

    //pass information about received frame to the upper layers
    DeciderResult80211 *macRes =
            dynamic_cast<DeciderResult80211 *>(PhyToMacControlInfo::getDeciderResult(
                    message));
    ASSERT(macRes);
    DeciderResult80211 *res = new DeciderResult80211(*macRes);
    wsm->setControlInfo(new PhyToMacControlInfo(res));

    long dest = macPkt->getDestAddr();

    DBG_MAC << "Received frame name= " << macPkt->getName() << ", myState="
                   << " src=" << macPkt->getSrcAddr() << " dst="
                   << macPkt->getDestAddr() << " myAddr=" << myMacAddress
                   << std::endl;

    if (macPkt->getDestAddr() == myMacAddress) {
        DBG_MAC << "Received a data packet addressed to me." << std::endl;
        statsReceivedPackets++;

        double statsReceivedPacketsDbl = (double) statsReceivedPackets;
        double time = simTime().dbl();

        sendUp(wsm);
    } else if (dest == LAddress::L2BROADCAST()) {

        cout << setiosflags(ios::fixed) << setprecision(16);

        statsReceivedBroadcasts++;
        double statsReceivedBroadcastsDbl = (double) statsReceivedBroadcasts;
        double time = simTime().dbl();

        double messageBits = (double) wsm->getBitLength();
        statsReceivedBits = statsReceivedBits + messageBits;
        computeThroughput(metrics, statsReceivedBroadcastsDbl, time);
        computeThroughputMbps(metrics, messageBits, statsMbpsReceived, time);

        sendUp(wsm);
    } else {
        DBG_MAC << "Packet not for me, deleting..." << std::endl;
        packetsNotForMe++;
        delete wsm;
    }
    delete macPkt;
}

void Mac16094Metrics::handleUpperMsg(cMessage* message) {
    WaveShortMessage* thisMsg;
        if ((thisMsg = dynamic_cast<WaveShortMessage*>(message)) == NULL) {
            error("WaveMac only accepts WaveShortMessages");
        }

        //(1) I = ( 1 − wI ) × P^2 + wI × C^2
        //∆I = I min + ( I max − I min ) × I
        if(std::string(thisMsg->getName())== "beacon") {
            std::cout<<"Received upperLayer message of type: "<< thisMsg->getName() << std::endl;
        }else{
            std::cout<<"MessageType: "<<thisMsg->getName() << std::endl;
        }

        t_access_category ac = mapPriority(thisMsg->getPriority());

        DBG_MAC <<"RECEIVED MESSGE FROM UPPER LAYER"<< std::endl;
        DBG_MAC << "Received a message from upper layer for channel "
                << thisMsg->getChannelNumber() << " Access Category (Priority):  "
                << ac << std::endl;

        t_channel chan;

        //rewrite SCH channel to actual SCH the Mac1609_4 is set to
        if (thisMsg->getChannelNumber() == Channels::SCH1) {
            ASSERT(useSCH);
            thisMsg->setChannelNumber(mySCH);
            chan = type_SCH;
        }


        //put this packet in its queue
        if (thisMsg->getChannelNumber() == Channels::CCH) {
            chan = type_CCH;
        }

        int num = myEDCA[chan]->queuePacket(ac,thisMsg);

        //packet was dropped in Mac
        if (num == -1) {
            statsDroppedPackets++;
            return;
        }

        //if this packet is not at the front of a new queue we dont have to reevaluate times
        DBG_MAC << "sorted packet into queue of EDCA " << chan << " this packet is now at position: " << num << std::endl;

        if (chan == activeChannel) {
            DBG_MAC << "this packet is for the currently active channel" << std::endl;
        }
        else {
            DBG_MAC << "this packet is NOT for the currently active channel" << std::endl;
        }

        if (num == 1 && idleChannel == true && chan == activeChannel) {

            simtime_t nextEvent = myEDCA[chan]->startContent(lastIdle,guardActive());
            DBG_MAC << "Next EVENTE HERE :"<< nextEvent << std::endl;
            if (nextEvent != -1) {
                if ((!useSCH) || (nextEvent <= nextChannelSwitch->getArrivalTime())) {
                    if (nextMacEvent->isScheduled()) {
                        cancelEvent(nextMacEvent);
                    }
                    scheduleAt(nextEvent,nextMacEvent);
                    DBG_MAC << "Updated nextMacEvent:" << nextMacEvent->getArrivalTime().raw() << std::endl;
                }
                else {
                    DBG_MAC << "Too little time in this interval. Will not schedule nextMacEvent" << std::endl;
                    //it is possible that this queue has an txop. we have to revoke it
                    myEDCA[activeChannel]->revokeTxOPs();
                    statsNumTooLittleTime++;
                }
            }
            else {
                cancelEvent(nextMacEvent);
            }
        }
        if (num == 1 && idleChannel == false && myEDCA[chan]->myQueues[ac].currentBackoff == 0 && chan == activeChannel) {
            myEDCA[chan]->backoff(ac);
        }
}

void Mac16094Metrics::handleSelfMsg(cMessage* message) {

    if (message == nextChannelSwitch) {
        ASSERT(useSCH);

        scheduleAt(simTime() + SWITCHING_INTERVAL_11P, nextChannelSwitch);

        switch (activeChannel) {
        case type_CCH:
            DBG_MAC << "CCH --> SCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_SCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[mySCH]);
            break;
        case type_SCH:
            DBG_MAC << "SCH --> CCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_CCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[Channels::CCH]);
            break;
        }
        //schedule next channel switch in 50ms

    } else if (message == nextMacEvent) {

        //we actually came to the point where we can send a packet
        channelBusySelf(true);
        WaveShortMessage* pktToSend = myEDCA[activeChannel]->initiateTransmit(
                lastIdle);

        lastAC = mapPriority(pktToSend->getPriority());

        DBG_MAC << "MacEvent received. Trying to send packet with priority"
                       << lastAC << std::endl;

        //send the packet
        Mac80211Pkt *mac = new Mac80211Pkt(pktToSend->getName(), pktToSend->getKind());
        mac->setDestAddr(LAddress::L2BROADCAST());
        mac->setSrcAddr(myMacAddress);
        mac->encapsulate(pktToSend->dup());

        enum PHY_MCS mcs;
        double txPower_mW;
        uint64_t datarate;

        PhyControlMessage *controlInfo = dynamic_cast<PhyControlMessage *>(pktToSend->getControlInfo());
        if (controlInfo) {
            //if MCS is not specified, just use the default one
            mcs = (enum PHY_MCS) controlInfo->getMcs();
            if (mcs != MCS_DEFAULT) {
                datarate = getOfdmDatarate(mcs, BW_OFDM_10_MHZ);
            } else {
                datarate = bitrate;
            }
            //apply the same principle to tx power
            txPower_mW = controlInfo->getTxPower_mW();
            if (txPower_mW < 0) {
                txPower_mW = txPower;
            }
        } else {
            mcs = MCS_DEFAULT;
            txPower_mW = txPower;
            datarate = bitrate;
        }

        simtime_t sendingDuration = RADIODELAY_11P
                + getFrameDuration(mac->getBitLength(), mcs);
        DBG_MAC << "Sending duration will be" << sendingDuration << std::endl;
        if ((!useSCH) || (timeLeftInSlot() > sendingDuration)) {
            if (useSCH)
                DBG_MAC << " Time in this slot left: " << timeLeftInSlot()
                               << std::endl;
            // give time for the radio to be in Tx state before transmitting
            phy->setRadioState(Radio::TX);

            double freq = (activeChannel == type_CCH) ? frequency[Channels::CCH] : frequency[mySCH];

            attachSignal(mac, simTime() + RADIODELAY_11P, freq, datarate,
                    txPower_mW);
            MacToPhyControlInfo* phyInfo =
                    dynamic_cast<MacToPhyControlInfo*>(mac->getControlInfo());
            assert(phyInfo);
            DBG_MAC << "Sending a Packet. Frequency " << freq << " Priority"
                           << lastAC << std::endl;
            sendDelayed(mac, RADIODELAY_11P, lowerLayerOut);
            statsSentPackets++;

            int channelUtilized =
                    (activeChannel == type_CCH) ? Channels::CCH : mySCH;

            channelUtilization[channelUtilized] =
                    channelUtilization[channelUtilized] + sendingDuration;

        } else {   //not enough time left now
            DBG_MAC
                           << "Too little Time left. This packet cannot be send in this slot."
                           << std::endl;
            statsNumTooLittleTime++;
            //revoke TXOP
            myEDCA[activeChannel]->revokeTxOPs();
            delete mac;
            channelIdle();
            //do nothing. contention will automatically start after channel switch
        }
    }
}

void Mac16094Metrics::handleLowerControl(cMessage* message) {
    if (message->getKind() == MacToPhyInterface::TX_OVER) {

        DBG_MAC << "Successfully transmitted a packet on " << lastAC
                       << std::endl;

        phy->setRadioState(Radio::RX);

        //message was sent
        //update EDCA queue. go into post-transmit backoff and set cwCur to cwMin
        myEDCA[activeChannel]->postTransmit(lastAC);
        //channel just turned idle.
        //don't set the chan to idle. the PHY layer decides, not us.

        if (guardActive()) {
            throw cRuntimeError("We shouldnt have sent a packet in guard!");
        }
    } else if (message->getKind() == Mac80211pToPhy11pInterface::CHANNEL_BUSY) {
        channelBusy();
    } else if (message->getKind() == Mac80211pToPhy11pInterface::CHANNEL_IDLE) {
        channelIdle();
    } else if (message->getKind() == Decider80211p::BITERROR
            || message->getKind() == Decider80211p::COLLISION) {
        statsSNIRLostPackets++;
        std::cout<<"handleLowerControl received COLLISIONS + BITERROR : "<< statsSNIRLostPackets<< std::endl;

        DBG_MAC << "A packet was not received due to biterrors" << std::endl;
    } else if (message->getKind() == Decider80211p::NOT_DECODED) {
        collisionsPktNonDecoded++;
        std::cout<<"handleLowerControl received NOT_DECODED : "<< collisionsPktNonDecoded<< std::endl;
        DBG_MAC << "A packet was not received due to NOT_DECODED" << std::endl;

    } else if (message->getKind() == Decider80211p::RECWHILESEND) {
        statsTXRXLostPackets++;
        DBG_MAC
                       << "A packet was not received because we were sending while receiving"
                       << std::endl;
    } else if (message->getKind() == MacToPhyInterface::RADIO_SWITCHING_OVER) {
        DBG_MAC << "Phylayer said radio switching is done" << std::endl;
    } else if (message->getKind() == BaseDecider::PACKET_DROPPED) {
        phy->setRadioState(Radio::RX);
        DBG_MAC << "Phylayer said packet was dropped" << std::endl;
    } else {
        DBG_MAC << "Invalid control message type (type=NOTHING) : name="
                       << message->getName() << " modulesrc="
                       << message->getSenderModule()->getFullPath() << "."
                       << std::endl;
        assert(false);
    }

    if (message->getKind() == Decider80211p::COLLISION) {
        emit(sigCollision, true);
    }

    delete message;

}

void Mac16094Metrics::handleUpperControl(cMessage* message) {
    Mac1609_4::handleUpperControl(message);
}

void Mac16094Metrics::computeThroughput(Metrics* metrics,
        double receivedPackets, double currentSimulationTime) {
    throughputMetricMac = metrics->computeThroughput(receivedPackets,
            currentSimulationTime);
    emit(throughputSignalMac, throughputMetricMac);
    metrics->throughputMetric = throughputMetricMac;
}

void Mac16094Metrics::computeThroughputMbps(Metrics* metrics,
        double messageBits, double currentMbs, double currentTime) {
    //cout<<setiosflags(ios::fixed)<<setprecision(16);

    double messageMbs = (messageBits) / 1000000;
    statsMbpsReceived = currentMbs + messageMbs;

    throughputMbps = metrics->computeThroughput(statsMbpsReceived, currentTime);
}

double Mac16094Metrics::getThroughputMbps() {
    return throughputMbps;
}

double Mac16094Metrics::getCollisionsPktNotDecoded() {
    return collisionsPktNonDecoded;
}

double Mac16094Metrics::getThroughputMetricMac() {
    return throughputMetricMac;
}

Mac16094Metrics::~Mac16094Metrics() {

}
