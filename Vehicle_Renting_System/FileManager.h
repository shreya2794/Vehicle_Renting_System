#pragma once
#include <vector>
#include <string>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"

class FileManager {
public:
    static void saveVehiclesToFile(const std::vector<Vehicle*>& vehicles, const std::string& filename);
    static void loadVehiclesFromFile(std::vector<Vehicle*>& vehicles, const std::string& filename);
    static void resetSystemData();  // Clears all vehicle & rental files
};
