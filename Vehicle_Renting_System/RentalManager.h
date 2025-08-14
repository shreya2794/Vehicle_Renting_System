#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Customer.h"

class RentalManager {
public:
    static bool loadCurrentRental(Customer& cust);
    static void updateVehicleAvailabilityFromCurrentRentals(std::vector<Vehicle*>& vehicles);
    static void removeFromCurrentRentals(const std::string& name, const std::string& phone);
    static void logRentalHistory(const std::string& customerName, const std::string& phone,
        const std::string& vehicleID, int days,
        const std::string& action, int totalBill = 0,
        int lateFee = 0, int earlyPenalty = 0);

private:
    static bool isNumber(const std::string& s);
};
