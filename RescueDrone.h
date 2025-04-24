#ifndef RESCUE_DRONE_H
#define RESCUE_DRONE_H

#include "Drone.h"

class RescueDrone : public Drone
{
public:
    RescueDrone();
    void executeMission(float N, float E, const std::string &address, int &minutesTaken) override;
};

#endif