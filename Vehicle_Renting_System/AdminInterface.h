#pragma once
#include <vector>
#include "Vehicle.h"

class AdminInterface {
public:
    static void showMenu(std::vector<Vehicle*>& vehicles);

private:
    static void addVehicle(std::vector<Vehicle*>& vehicles);
    static void viewVehicles(const std::vector<Vehicle*>& vehicles);
    static void viewRentalHistory();
    static void handleSystemReset(std::vector<Vehicle*>& vehicles);

    static bool isUniqueID(const std::vector<Vehicle*>& vehicles, const std::string& id);
    static void displayAllVehicles(const std::vector<Vehicle*>& vehicles);  // helper
};
