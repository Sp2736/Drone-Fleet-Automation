#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

struct SimpleException
{
    std::string msg;
    SimpleException(const std::string &m) : msg(m) {}
};

class Drone
{
protected:
    std::string id;
    int battery = 100;
    bool isCharging = false;
    int missionsCompleted = 0;
    bool inService = false;
    time_t lastServicedTime = 0;

public:
    Drone(const std::string &i);
    virtual ~Drone() {}
    int &getBattery();
    std::string getId() const;
    void startCharging();
    void chargeCycle(int rate = 20);
    bool isAvailable();
    virtual void executeMission(float N, float E, const std::string &address, int &minutesTaken) = 0;
};

#endif
