#include "Bike.h"
#include <iostream>
using namespace std;

// Default constructor
Bike::Bike() : Vehicle("", "", 0.0), hasCarrier(false) {}

// Parameterized constructor
Bike::Bike(string id, string brand, float rent, bool carrier)
    : Vehicle(id, brand, rent), hasCarrier(carrier) {
}

// Display bike-specific details
void Bike::displayDetails() const {
    Vehicle::displayDetails(); // Call base class method
    cout << "Carrier: " << (hasCarrier ? "Yes" : "No") << endl;
}

// Rent calculation (no booking fee for bikes)
int Bike::calculateRent(int days) const {
    return rentPerDay * days;
}

// Getter for hasCarrier
bool Bike::hasCarrierFn() const {
    return hasCarrier;
}
