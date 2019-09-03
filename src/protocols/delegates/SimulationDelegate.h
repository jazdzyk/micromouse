//
// Created by Kuba Jazdzyk on 9/2/19.
//

#ifndef MICROMOUSE_SIMULATIONDELEGATE_H
#define MICROMOUSE_SIMULATIONDELEGATE_H

/**
 * SimulationDelegate is a protocol delegating methods from Simulation class.
 */
class SimulationDelegate {
public:
    /**
     * A method which delegates work when a simulation's iteration did happen.
     *
     * @param robotId an id of a robot
     * @param msecs elapsed time
     */
    virtual void simulationIterationDidHappen(int robotId, int msecs) = 0;

    /**
     * A method which delegates work when a simulation was reset.
     */
    virtual void simulationDidReset() = 0;

    /**
     * SimulationDelegate class destructor.
     */
    virtual ~SimulationDelegate() = default;
};


#endif //MICROMOUSE_SIMULATIONDELEGATE_H
