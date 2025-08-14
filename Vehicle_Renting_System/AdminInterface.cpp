#include "AdminInterface.h"
#include "Car.h"
#include "Bike.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void AdminInterface::showMenu(vector<Vehicle*>& vehicles) {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Vehicle\n2. View All Vehicles\n3. View Rental History\n4. Reset System (Clear All Data)\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addVehicle(vehicles); break;
        case 2: viewVehicles(vehicles); break;
        case 3: viewRentalHistory(); break;
        case 4: handleSystemReset(vehicles); break;
        case 0: cout << "Exiting Admin Menu.\n"; break;
        default:
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

void AdminInterface::addVehicle(vector<Vehicle*>& vehicles) {
    int typeChoice;
    cout << "Add:\n1. Car\n2. Bike\nEnter choice: ";
    cin >> typeChoice;

    string id, brand;
    float rent;

    while (true) {
        cout << "Enter ID (start with 'C' for Car or 'B' for Bike): ";
        cin >> id;

        if ((typeChoice == 1 && id[0] != 'C') || (typeChoice == 2 && id[0] != 'B')) {
            cout << "Invalid ID prefix. Car ID must start with 'C', Bike with 'B'. Try again.\n";
            continue;
        }

        if (!isUniqueID(vehicles, id)) {
            cout << "Vehicle ID already exists. Try again.\n";
            continue;
        }

        break;
    }

    cout << "Enter Brand: ";
    cin.ignore(); // Clear newline
    getline(cin, brand);
    cout << "Enter Rent per Day: ";
    cin >> rent;

    if (typeChoice == 1) {
        int seats;
        cout << "Enter Number of Seats: ";
        cin >> seats;
        vehicles.push_back(new Car(id, brand, rent, seats));
    }
    else if (typeChoice == 2) {
        bool carrier;
        cout << "Has Carrier (1 for Yes, 0 for No): ";
        cin >> carrier;
        vehicles.push_back(new Bike(id, brand, rent, carrier));
    }

    FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
    cout << "Vehicle added successfully.\n";
}

void AdminInterface::viewVehicles(const vector<Vehicle*>& vehicles) {
    displayAllVehicles(vehicles);
}

void AdminInterface::viewRentalHistory() {
    ifstream logFile("rental_history.txt");
    if (!logFile) {
        cout << "No rental history found.\n";
        return;
    }

    string line;
    cout << "\n--- Rental History ---\n";
    while (getline(logFile, line)) {
        stringstream ss(line);
        string name, phone, id, datetime, days, action;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, id, ',');
        getline(ss, datetime, ',');
        getline(ss, days, ',');
        getline(ss, action);

        cout << "Customer: " << name << ", Phone: " << phone << ", Vehicle ID: " << id
            << ", Date: " << datetime << ", Days: " << days
            << ", Action: " << action << "\n";
    }

    logFile.close();
}

void AdminInterface::handleSystemReset(vector<Vehicle*>& vehicles) {
    char confirm;
    cout << "⚠️  Are you sure you want to reset all system data? (y/n): ";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        FileManager::resetSystemData();
        for (auto v : vehicles) delete v;
        vehicles.clear();
        cout << "✅ System data reset.\n";
    }
    else {
        cout << "❌ Reset cancelled.\n";
    }
}

// Helper to check unique ID
bool AdminInterface::isUniqueID(const vector<Vehicle*>& vehicles, const string& id) {
    for (const auto& v : vehicles) {
        if (v->getID() == id)
            return false;
    }
    return true;
}

// Helper to display all vehicles
void AdminInterface::displayAllVehicles(const vector<Vehicle*>& vehicles) {
    cout << "\n======================== Cars ========================\n";
    for (const auto& v : vehicles) {
        if (auto* car = dynamic_cast<Car*>(v)) {
            cout << car->getID() << " | " << car->getBrand()
                << " | ₹" << car->getRentPerDay()
                << " | Seats: " << car->getSeats()
                << " | " << (car->getAvailability() ? "✅ Available" : "❌ Rented") << endl;
        }
    }

    cout << "\n======================== Bikes =======================\n";
    for (const auto& v : vehicles) {
        if (auto* bike = dynamic_cast<Bike*>(v)) {
            cout << bike->getID() << " | " << bike->getBrand()
                << " | ₹" << bike->getRentPerDay()
                << " | Carrier: " << (bike->hasCarrierFn() ? "Yes" : "No")
                << " | " << (bike->getAvailability() ? "✅ Available" : "❌ Rented") << endl;
        }
    }
}
