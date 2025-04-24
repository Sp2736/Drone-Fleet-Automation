#include "SurveyDrone.h"
#include "DeliveryDrone.h"
#include "RescueDrone.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // seed random generator with current time
    srand(static_cast<unsigned>(time(nullptr)));

    // create instances of each drone type
    SurveyDrone sd;
    DeliveryDrone dd;
    RescueDrone rd;

    // store pointers to all drones in a vector
    vector<Drone *> drones = {&sd, &dd, &rd};

    // main simulation loop
    while (true)
    {
        // display menu and get user choice
        std::cout << "\n=== Drone Fleet Simulator ===\n"
                  << "Select mission (0 to exit):\n"
                  << "  1) Survey\n"
                  << "  2) Delivery\n"
                  << "  3) Rescue\n"
                  << "Choice: ";

        int choice;
        cin >> choice;

        // handle non-numeric input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        // exit condition
        if (choice == 0)
            break;

        // check for valid option
        if (choice < 1 || choice > 3)
        {
            cout << "Invalid choice.\n";
            continue;
        }

        // get pointer to selected drone by managing index value
        Drone *selected = drones[choice - 1];

        // check if selected drone is currently available
        if (!selected->isAvailable())
        {
            cout << selected->getId() << " is under service.\n";
            continue;
        }

        // determine minimum battery required for selected mission
        int requiredBattery = (choice == 1 ? 30 : (choice == 2 ? 40 : 35));

        // check if battery is sufficient for the mission
        if (selected->getBattery() < requiredBattery)
        {
            cout << selected->getId() << " battery low. Charging...\n";
            selected->startCharging();
            int dummy;
            try
            {
                // trigger charge cycle through dummy mission call
                selected->executeMission(0, 0, "", dummy);
            }
            catch (SimpleException &e)
            {
                cerr << "Error: " << e.msg << "\n";
            }
            continue;
        }

        // get mission location and address from user
        float N, E;
        cout << "Enter latitude (-90 to +90): ";
        cin >> N;
        if (N > 90 || N < -90)
        {
            cout << "Latitude is not valid\n";
            continue;
        }
        
        cout << "Enter longitude (-180 to +180): ";
        cin >> E;
        if (E > 180 || E < -180)
        {
            cout << "Longitude is not valid\n";
            continue;
        }
        cin.ignore();
        string address;
        cout << "Enter address: ";
        getline(cin, address);
        // code to check for radius not exceeding 10km range
        int radius;
        radius = 5 + rand() % 5;
        if (radius > 10)
            cout << "The distance is out of range! Mission aborted.\n";
        else
            cout << "Proceeding with the mission...\n";

        // generate a simulated air quality index value
        int airIndex = 20 + rand() % 111;
        cout << "Service reports AQI: " << airIndex << " (Safe)\n";

        int minutesTaken = 0;

        // try executing the mission and catch any errors
        try
        {
            selected->executeMission(N, E, address, minutesTaken);
        }
        catch (SimpleException &e)
        {
            cerr << "Mission failed: " << e.msg << "\n";
        }
    }

    // end of simulation message
    cout << "\nSimulation ended. Check logs.\n";
    return 0;
}