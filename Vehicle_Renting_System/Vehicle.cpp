#include "Vehicle.h"
#include <iostream>
using namespace std;

// Default constructor
Vehicle::Vehicle() : vehicleID(""), brand(""), rentPerDay(0.0), isAvailable(true) {}

// Parameterized constructor
Vehicle::Vehicle(string id, string brand, float rent, bool avail)
    : vehicleID(id), brand(brand), rentPerDay(rent), isAvailable(avail) {
}

// Virtual destructor
Vehicle::~Vehicle() {}

// Getters
string Vehicle::getID() const {
    return vehicleID;
}

string Vehicle::getBrand() const {
    return brand;
}

float Vehicle::getRentPerDay() const {
    return rentPerDay;
}

bool Vehicle::getAvailability() const {
    return isAvailable;
}

// Setter
void Vehicle::setAvailability(bool avail) {
    isAvailable = avail;
}

// Display vehicle info
void Vehicle::displayDetails() const {
    cout << "\n--- Vehicle Info ---\n";
    cout << "ID: " << vehicleID << "\nBrand: " << brand
        << "\nRent/Day: ₹" << rentPerDay
        << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
}

// Calculate base rent
int Vehicle::calculateRent(int days) const {
    return rentPerDay * days;
}
