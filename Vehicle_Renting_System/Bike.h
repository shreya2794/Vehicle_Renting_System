#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
    bool hasCarrier;

public:
    // Constructors
    Bike(); // Default constructor
    Bike(std::string id, std::string brand, float rent, bool carrier); // Parameterized

    // Overridden virtual methods
    void displayDetails() const override;
    int calculateRent(int days) const override;

    // Getter
    bool hasCarrierFn() const;
};
