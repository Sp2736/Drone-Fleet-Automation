#include "SurveyDrone.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

// constructor initializing drone with id "SD-1"
SurveyDrone::SurveyDrone() : Drone("SD-1") {}

// executes a survey mission and updates drone's status and log
void SurveyDrone::executeMission(float N, float E, const string &address, int &minutesTaken)
{
    // check if drone is currently in maintenance
    if (!isAvailable())
    {
        cout << id << ": Under maintenance.\n";
        return;
    }

    // continue charging if drone is in charging mode
    if (isCharging)
    {
        chargeCycle();
        return;
    }

    // throw exception if battery is empty
    if (battery <= 0)
        throw SimpleException(id + " battery depleted!");

    // print mission header and coordinates
    cout << "\n--- SURVEY MISSION (" << id << ") ---\n";
    cout << "Location: " << N << "N, " << E << "E\n";
    cout << "Address: " << address << "\n";
    cout << "Battery Start: " << battery << "%\n";

    // simulate mission duration and reduce battery level
    usleep(200000);
    battery = max(0, battery - 30);

    // initiate charging if battery falls below threshold
    if (battery < 30)
        startCharging();

    // assign mission time randomly between 10 to 14 minutes
    minutesTaken = 10 + rand() % 5;
    cout << "Duration: " << minutesTaken << " min\n";
    cout << "Battery End: " << battery << "%\n";

    // increment completed missions and send for maintenance if needed
    missionsCompleted++;
    if (missionsCompleted >= 10)
    {
        inService = true;
        lastServicedTime = time(nullptr);
        cout << id << ": Sent for servicing.\n";
    }

    // append mission details to drone's log file
    ofstream log(id + "_log.txt", ios::app);
    log << "Survey | " << id << " | Time:" << minutesTaken << "m | EndBat:" << battery << "%\n";
}