/*
 * Decider80211pMetrics.cc
 *
 *  Created on: Jan 18, 2018
 *      Author: susanarodriguez
 */

#include <Decider80211pMetrics.h>
#include <../../veins/src/veins/modules/phy/Decider80211p.h>


DeciderResult* Decider80211pMetrics::checkIfSignalOk(AirFrame* frame){
    return Decider80211p::checkIfSignalOk(frame);
}

simtime_t Decider80211pMetrics::processNewSignal(AirFrame* frame){
    return Decider80211p::processNewSignal(frame);
}

simtime_t Decider80211pMetrics::processSignalEnd(AirFrame* frame){
    return Decider80211p::processSignalEnd(frame);
}

void Decider80211pMetrics::switchToTx(){
    Decider80211p::switchToTx();
}

double Decider80211pMetrics::calcChannelSenseRSSI(simtime_t_cref min, simtime_t_cref max){
    return Decider80211p::calcChannelSenseRSSI(min, max);
}

void Decider80211pMetrics::calculateSinrAndSnrMapping(AirFrame* frame, Mapping **sinrMap, Mapping **snrMap){
    Decider80211p::calculateSinrAndSnrMapping(frame, sinrMap, snrMap);
}

void Decider80211pMetrics::finish(){
    Decider80211p::finish();
}
Decider80211pMetrics::~Decider80211pMetrics() {
    Decider80211p::~Decider80211p();
}

