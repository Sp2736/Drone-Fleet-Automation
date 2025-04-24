#include "RescueDrone.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

// constructor initializing drone with id "RD-1"
RescueDrone::RescueDrone() : Drone("RD-1") {}

// executes a rescue mission and updates drone state accordingly
void RescueDrone::executeMission(float N, float E, const string &address, int &minutesTaken)
{
    // check if drone is unavailable due to maintenance
    if (!isAvailable())
    {
        cout << id << ": Under maintenance.\n";
        return;
    }

    // continue charging if drone is in charging state
    if (isCharging)
    {
        chargeCycle();
        return;
    }

    // throw exception if battery is depleted
    if (battery <= 0)
        throw SimpleException(id + " battery depleted!");

    // display mission type and coordinates
    cout << "\n--- RESCUE MISSION (" << id << ") ---\n";
    cout << "Location: " << N << "N, " << E << "E\n";
    cout << "Address: " << address << "\n";
    cout << "Battery Start: " << battery << "%\n";

    // simulate mission duration and reduce battery
    usleep(200000);
    battery = max(0, battery - 35);

    // start charging if battery is too low after mission
    if (battery < 35)
        startCharging();

    // randomly generate mission duration between 25 to 30 minutes
    minutesTaken = 25 + rand() % 6;
    cout << "Duration: " << minutesTaken << " min\n";
    cout << "Battery End: " << battery << "%\n";

    // increment mission count and trigger maintenance after 10 missions
    missionsCompleted++;
    if (missionsCompleted >= 10)
    {
        inService = true;
        lastServicedTime = time(nullptr);
        cout << id << ": Sent for servicing.\n";
    }

    // log mission details to a text file
    ofstream log(id + "_log.txt", ios::app);
    log << "Rescue | " << id << " | Time:" << minutesTaken << "m | EndBat:" << battery << "%\n";
}
