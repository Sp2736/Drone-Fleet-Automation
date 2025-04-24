#ifndef DELIVERY_DRONE_H
#define DELIVERY_DRONE_H

#include "Drone.h"

class DeliveryDrone : public Drone
{
public:
    DeliveryDrone();
    void executeMission(float N, float E, const std::string &address, int &minutesTaken) override;
};

#endif