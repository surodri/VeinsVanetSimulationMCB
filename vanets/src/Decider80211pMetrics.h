/*
 * Decider80211pMetrics.h
 *
 *  Created on: Jan 18, 2018
 *      Author: susanarodriguez
 */

#ifndef SRC_DECIDER80211PMETRICS_H_
#define SRC_DECIDER80211PMETRICS_H_

#include <../../veins/src/veins/modules/phy/Decider80211p.h>
class Decider80211pMetrics: public Decider80211p {
public:
    Decider80211pMetrics();
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
