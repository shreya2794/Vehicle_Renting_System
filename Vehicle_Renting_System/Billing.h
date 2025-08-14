#pragma once
#include <string>
#include "Vehicle.h"
#include "Customer.h"

class Billing {
public:
    static void generateFinalBill(Customer& cust, Vehicle* vehicle, int actualDays);

private:
    static std::string formatBill(const std::string& customerName, const std::string& phone,
        const std::string& vehicleID, int expectedDays,
        int actualDays, float rentPerDay,
        int baseRent, int lateFee, int earlyPenalty, int totalBill);

    static void logBill(const std::string& formattedBill);
};

// Global constants
const float LATE_FEE_RATE = 0.5f;        // 50% of rent/day for late return
const float EARLY_PENALTY_RATE = 0.5f;   // 50% of one day rent for early return
