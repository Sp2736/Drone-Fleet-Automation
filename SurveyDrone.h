#ifndef SURVEY_DRONE_H
#define SURVEY_DRONE_H

#include "Drone.h"

class SurveyDrone : public Drone
{
public:
    SurveyDrone();
    void executeMission(float N, float E, const std::string &address, int &minutesTaken) override;
};

#endif
