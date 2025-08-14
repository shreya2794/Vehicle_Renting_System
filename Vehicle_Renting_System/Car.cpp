#include "Car.h"
#include <iostream>
using namespace std;

// Default constructor
Car::Car() : Vehicle("", "", 0.0), numSeats(0) {}

// Parameterized constructor
Car::Car(string id, string brand, float rent, int seats)
    : Vehicle(id, brand, rent), numSeats(seats) {
}

// Display car-specific details
void Car::displayDetails() const {
    Vehicle::displayDetails(); // Call base class display
    cout << "Seats: " << numSeats << endl;
}

// Calculate rent including flat booking fee
int Car::calculateRent(int days) const {
    const int BOOKING_FEE = 100;
    return rentPerDay * days + BOOKING_FEE;
}

// Getter
int Car::getSeats() const {
    return numSeats;
}
