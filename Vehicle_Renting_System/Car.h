#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
    int numSeats;

public:
    // Constructors
    Car(); // Default constructor
    Car(std::string id, std::string brand, float rent, int seats); // Parameterized constructor

    // Overridden methods
    void displayDetails() const override;
    int calculateRent(int days) const override;

    // Getter
    int getSeats() const;
};
