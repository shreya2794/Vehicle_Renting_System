#pragma once
#include <string>

class Vehicle {
protected:
    std::string vehicleID;
    std::string brand;
    float rentPerDay;
    bool isAvailable;

public:
    // Constructors
    Vehicle();
    Vehicle(std::string id, std::string brand, float rent, bool avail = true);

    // Virtual destructor for proper cleanup
    virtual ~Vehicle();

    // Getters
    std::string getID() const;
    std::string getBrand() const;
    float getRentPerDay() const;
    bool getAvailability() const;

    // Setters
    void setAvailability(bool avail);

    // Virtual methods for polymorphism
    virtual void displayDetails() const;
    virtual int calculateRent(int days) const;
};

