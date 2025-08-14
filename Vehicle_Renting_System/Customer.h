#pragma once
#include <string>

class Customer {
    std::string name;
    std::string phoneNumber;
    std::string rentedVehicleID;
    int rentDays;

public:
    // Constructor
    Customer(std::string name, std::string phone = "");

    // Getters
    std::string getName() const;
    std::string getPhone() const;
    std::string getRentedVehicleID() const;
    int getRentDays() const;

    // Rental status check
    bool hasRented() const;

    // Renting and returning functions
    void rentVehicle(const std::string& vehicleID, int days);
    void returnVehicle();

    // Display customer info
    void displayCustomerDetails() const;

private:
    void saveRental();
    void loadRental();
    void removeRental();
};
