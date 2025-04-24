#include "DeliveryDrone.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// constructor initializing drone with id "DD-1"
DeliveryDrone::DeliveryDrone() : Drone("DD-1") {}

// executes a delivery mission and updates drone status accordingly
void DeliveryDrone::executeMission(float N, float E, const string &address, int &minutesTaken)
{
    // check if drone is unavailable due to maintenance
    if (!isAvailable())
    {
        cout << id << ": Under maintenance.\n";
        return;
    }

    // if drone is currently charging, continue charging
    if (isCharging)
    {
        chargeCycle();
        return;
    }

    // throw exception if battery is completely drained
    if (battery <= 0)
        throw SimpleException(id + " battery depleted!");

    // display mission header and location details
    cout << "\n--- DELIVERY MISSION (" << id << ") ---\n";
    cout << "Location: " << N << "N, " << E << "E\n";
    cout << "Address: " << address << "\n";
    cout << "Battery Start: " << battery << "%\n";

    // simulate delivery time and battery usage
    usleep(200000);
    battery = max(0, battery - 40);

    // if battery is low after mission, initiate charging
    if (battery < 40)
        startCharging();

    // generate random delivery duration between 15 to 18 minutes
    minutesTaken = 15 + rand() % 4;
    cout << "Duration: " << minutesTaken << " min\n";
    cout << "Battery End: " << battery << "%\n";

    // increment mission count and send for service after 10 missions
    missionsCompleted++;
    if (missionsCompleted >= 10)
    {
        inService = true;
        lastServicedTime = time(nullptr);
        cout << id << ": Sent for servicing.\n";
    }

    // log mission details to a file
    ofstream log(id + "_log.txt", ios::app);
    log << "Delivery | " << id << " | Time:" << minutesTaken << "m | EndBat:" << battery << "%\n";
}