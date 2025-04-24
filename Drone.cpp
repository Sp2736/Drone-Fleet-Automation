#include "Drone.h"
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

// constructor initializing drone with given id
Drone::Drone(const string &i) : id(i) {}

// returns reference to battery level
int &Drone::getBattery() { return battery; }

// returns drone's id
string Drone::getId() const { return id; }

// sets drone to charging state and prints message
void Drone::startCharging()
{
    isCharging = true;
    cout << id << ": Starting charge\n";
}

// increases battery by rate and prints charging status
void Drone::chargeCycle(int rate)
{
    battery = min(100, battery + rate);
    if (battery == 100)
    {
        isCharging = false;
        cout << id << ": Fully charged\n";
    }
    else
    {
        cout << id << ": Charging... " << battery << "%\n";
    }
}

// checks if drone is available or has completed service time
bool Drone::isAvailable()
{
    if (!inService)
        return true;

    // calculate time since last service
    time_t now = time(nullptr);
    double hours = difftime(now, lastServicedTime) / 3600.0;

    // reset service status if 24 hours have passed
    if (hours >= 24.0)
    {
        inService = false;
        missionsCompleted = 0;
        cout << id << ": Service complete. Drone is back online.\n";
        return true;
    }

    // drone still under service
    return false;
}