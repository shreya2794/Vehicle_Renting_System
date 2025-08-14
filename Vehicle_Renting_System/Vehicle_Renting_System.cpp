#include "AdminInterface.h"
#include "CustomerInterface.h"
#include "FileManager.h"
#include "RentalManager.h"
#include "Vehicle.h"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Vehicle*> vehicles;

    // Load vehicle data from file
    FileManager::loadVehiclesFromFile(vehicles, "vehicles.txt");

    // Update rented status from current_rentals.txt
    RentalManager::updateVehicleAvailabilityFromCurrentRentals(vehicles);

    // Main login menu loop
    int userType;
    while (true) {
        cout << "\nLogin as:\n1. Admin\n2. Customer\n0. Exit\nEnter choice: ";
        cin >> userType;

        switch (userType) {
        case 1:
            AdminInterface::showMenu(vehicles);
            break;
        case 2:
            CustomerInterface::showMenu(vehicles);
            break;
        case 0:
            cout << "Exiting program.\n";
            FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
            for (auto v : vehicles)
                delete v;
            return 0;
        default:
            cout << "Invalid choice. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return 0;
}
