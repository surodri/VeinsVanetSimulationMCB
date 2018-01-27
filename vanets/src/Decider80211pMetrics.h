/*
 * Decider80211pMetrics.h
 *
 *  Created on: Jan 18, 2018
 *      Author: susanarodriguez
 */

#ifndef SRC_DECIDER80211PMETRICS_H_
#define SRC_DECIDER80211PMETRICS_H_

#include <../../veins/src/veins/modules/phy/Decider80211p.h>
#include <../../veins/src/veins/base/phyLayer/BaseDecider.h>
//#include <../../veins/src/veins/modules/mac/ieee80211p/>

class Decider80211pMetrics: public Decider80211p {
public:
    double ccaThreshold;
    double allowTxDuringRx;
    double centerFrequency;
    double myBusyTime;
    double myStartTime;
    double collectCollisionStats;
    unsigned int collisions;
    unsigned int notDecoded;
    Decider80211pMetrics();
    Decider80211pMetrics(DeciderToPhyInterface* phy,
                  double sensitivity,
                  double ccaThreshold,
                  bool allowTxDuringRx,
                  double centerFrequency,
                  int myIndex = -1,
                  bool collectCollisionStatistics = false,
                  bool debug = false):
        Decider80211p(phy, sensitivity,ccaThreshold, allowTxDuringRx, centerFrequency, myIndex, collectCollisionStatistics, debug),
        ccaThreshold(ccaThreshold),
        allowTxDuringRx(allowTxDuringRx),
        centerFrequency(centerFrequency),
        myBusyTime(0),
        myStartTime(simTime().dbl()),
        collectCollisionStats(collectCollisionStatistics),
        collisions(0),
        notDecoded(0){
        phy11p = dynamic_cast<Decider80211pToPhy80211pInterface*>(phy);
        assert(phy11p);

    }

    virtual ~Decider80211pMetrics();
protected:

    virtual DeciderResult* checkIfSignalOk(AirFrame* frame);
    virtual simtime_t processNewSignal(AirFrame* frame);
    virtual simtime_t processSignalEnd(AirFrame* frame);
    virtual double calcChannelSenseRSSI(simtime_t_cref min, simtime_t_cref max);
    virtual void calculateSinrAndSnrMapping(AirFrame* frame, Mapping **sinrMap, Mapping **snrMap);
    virtual void finish();
    virtual void switchToTx();
};

#endif /* SRC_DECIDER80211PMETRICS_H_ */
