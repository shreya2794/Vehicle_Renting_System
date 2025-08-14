#pragma once
#include <vector>
#include "Vehicle.h"
#include "Customer.h"

class CustomerInterface {
public:
    static void showMenu(std::vector<Vehicle*>& vehicles);

private:
    static void viewAvailableVehicles(const std::vector<Vehicle*>& vehicles);
    static void rentVehicle(Customer& cust, std::vector<Vehicle*>& vehicles);
    static void returnVehicle(Customer& cust, std::vector<Vehicle*>& vehicles);
    static void displayAllVehicles(const std::vector<Vehicle*>& vehicles); // helper
};

