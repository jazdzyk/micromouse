//
// Created by Kuba Jazdzyk on 9/2/19.
//

#ifndef MICROMOUSE_SIMULATIONDELEGATE_H
#define MICROMOUSE_SIMULATIONDELEGATE_H


class SimulationDelegate {
public:
    virtual void simulationIterationDidHappen(int robotId, int msecs) = 0;
    virtual void simulationDidReset() = 0;
    virtual ~SimulationDelegate() = default;
};


#endif //MICROMOUSE_SIMULATIONDELEGATE_H
