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

#ifndef SRC_PHYLAYER80211PMETRICS_H_
#define SRC_PHYLAYER80211PMETRICS_H_

#include <../../veins/src/veins/modules/phy/PhyLayer80211p.h>

class PhyLayer80211pMetrics : public PhyLayer80211p {
public:
    PhyLayer80211pMetrics();
    void initialize(int stage);
protected:
    virtual AnalogueModel* getAnalogueModelFromName(std::string name, ParameterMap& params);
    virtual AnalogueModel* initializeBreakpointPathlossModel(ParameterMap& params);
    virtual AnalogueModel* initializePERModel(ParameterMap& params);
    virtual Decider* getDeciderFromName(std::string name, ParameterMap& params);
    virtual Decider* initializeDecider80211p(ParameterMap& params);
    virtual AirFrame *encapsMsg(cPacket *msg);
    virtual void changeListeningFrequency(double freq);
    virtual void handleSelfMessage(cMessage* msg);
    virtual int getRadioState();
    virtual simtime_t setRadioState(int rs);
    virtual ~PhyLayer80211pMetrics();
};

#endif /* SRC_PHYLAYER80211PMETRICS_H_ */
