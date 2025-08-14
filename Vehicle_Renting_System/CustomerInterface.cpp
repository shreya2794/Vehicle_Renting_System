#include "CustomerInterface.h"
#include "Car.h"
#include "Bike.h"
#include "Customer.h"
#include "FileManager.h"
#include "Billing.h"
#include "RentalManager.h"

#include <iostream>
#include <limits>

using namespace std;

void CustomerInterface::showMenu(vector<Vehicle*>& vehicles) {
    string customerName, phone;
    cin.ignore();
    cout << "\nEnter your name: ";
    getline(cin, customerName);
    cout << "Enter your phone number: ";
    getline(cin, phone);

    Customer cust(customerName, phone);
    RentalManager::loadCurrentRental(cust);  // Try to load existing rental

    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Available Vehicles\n2. Rent Vehicle\n3. Return Vehicle\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAvailableVehicles(vehicles); break;
        case 2: rentVehicle(cust, vehicles); break;
        case 3: returnVehicle(cust, vehicles); break;
        case 0: cout << "Exiting Customer Menu.\n"; break;
        default:
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

void CustomerInterface::viewAvailableVehicles(const vector<Vehicle*>& vehicles) {
    displayAllVehicles(vehicles);
}

void CustomerInterface::rentVehicle(Customer& cust, vector<Vehicle*>& vehicles) {
    if (cust.hasRented()) {
        cout << "You already rented vehicle ID: " << cust.getRentedVehicleID() << endl;
        cout << "Please return the current vehicle before renting another.\n";
        return;
    }

    string rentID;
    int days;
    cout << "Enter Vehicle ID to Rent: ";
    cin >> rentID;

    bool found = false;
    for (auto& v : vehicles) {
        if (v->getID() == rentID && v->getAvailability()) {
            cout << "Enter number of days: ";
            cin >> days;

            int totalRent = v->calculateRent(days);
            cout << "Vehicle rented! Total Rent: ₹" << totalRent << endl;

            v->setAvailability(false);
            cust.rentVehicle(rentID, days);

            FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
            RentalManager::logRentalHistory(cust.getName(), cust.getPhone(), rentID, days, "Rented");

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Vehicle not found or unavailable.\n";
    }
}

void CustomerInterface::returnVehicle(Customer& cust, vector<Vehicle*>& vehicles) {
    if (!cust.hasRented()) {
        cout << "No rented vehicle to return.\n";
        return;
    }

    string rentedID = cust.getRentedVehicleID();
    int actualDays;
    cout << "Enter number of days you kept the vehicle: ";
    cin >> actualDays;

    for (auto& v : vehicles) {
        if (v->getID() == rentedID) {
            v->setAvailability(true);
            FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
            Billing::generateFinalBill(cust, v, actualDays);
            break;
        }
    }
}

void CustomerInterface::displayAllVehicles(const vector<Vehicle*>& vehicles) {
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
