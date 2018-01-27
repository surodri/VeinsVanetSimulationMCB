//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <PhyLayer80211pMetrics.h>
#include <Decider80211pMetrics.h>

Define_Module(PhyLayer80211pMetrics);

void PhyLayer80211pMetrics::initialize(int stage) {
    PhyLayer80211p::initialize(stage);
}

AnalogueModel* PhyLayer80211pMetrics::getAnalogueModelFromName(std::string name, ParameterMap& params){
     return PhyLayer80211p::getAnalogueModelFromName(name, params);
}

AnalogueModel* PhyLayer80211pMetrics::initializeBreakpointPathlossModel(ParameterMap& params){
    return PhyLayer80211p::initializeBreakpointPathlossModel(params);
}

AnalogueModel* PhyLayer80211pMetrics::initializePERModel(ParameterMap& params){
    return PhyLayer80211p::initializePERModel(params);
}

Decider* PhyLayer80211pMetrics::getDeciderFromName(std::string name, ParameterMap& params) {
    if(name == "Decider80211pMetrics") {
        protocolId = IEEE_80211;
        return initializeDecider80211p(params);
    }
    return BasePhyLayer::getDeciderFromName(name, params);
}


Decider* PhyLayer80211pMetrics::initializeDecider80211p(ParameterMap& params){
    double centerFreq = params["centerFrequency"];
    Decider80211pMetrics* dec = new Decider80211pMetrics(this, sensitivity, ccaThreshold, allowTxDuringRx, centerFreq, findHost()->getIndex(), collectCollisionStatistics, coreDebug);
    dec->setPath(getParentModule()->getFullPath());
    return dec;
//    return PhyLayer80211p::initializeDecider80211p(params);
}

AirFrame* PhyLayer80211pMetrics::encapsMsg(cPacket *msg){
    return PhyLayer80211p::encapsMsg(msg);
}

void    PhyLayer80211pMetrics::changeListeningFrequency(double freq){
    return PhyLayer80211p::changeListeningFrequency(freq);
}

void PhyLayer80211pMetrics::handleSelfMessage(cMessage* msg){
    return PhyLayer80211p::handleSelfMessage(msg);
}

int PhyLayer80211pMetrics::getRadioState(){
    return PhyLayer80211p::getRadioState();
}

simtime_t PhyLayer80211pMetrics::setRadioState(int rs){
    return PhyLayer80211p::setRadioState(rs);
}

PhyLayer80211pMetrics::~PhyLayer80211pMetrics() {
    // TODO Auto-generated destructor stub
}

