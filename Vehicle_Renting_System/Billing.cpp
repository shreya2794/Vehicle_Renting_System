#include "Billing.h"
#include "RentalManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // for max

using namespace std;

void Billing::generateFinalBill(Customer& cust, Vehicle* v, int actualDays) {
    int expectedDays = cust.getRentDays();
    int lateDays = max(0, actualDays - expectedDays);
    float rentPerDay = v->getRentPerDay();
    int baseRent = v->calculateRent(actualDays);

    // Late fee and early penalty logic
    int lateFee = (lateDays > 0) ? static_cast<int>(rentPerDay * LATE_FEE_RATE) : 0;
    int earlyPenalty = (actualDays < expectedDays) ? static_cast<int>(rentPerDay * EARLY_PENALTY_RATE) : 0;

    int totalBill = baseRent + lateFee + earlyPenalty;

    // Generate and display formatted bill
    string billText = Billing::formatBill(cust.getName(), cust.getPhone(), v->getID(),
        expectedDays, actualDays, rentPerDay,
        baseRent, lateFee, earlyPenalty, totalBill);

    cout << "\033[1;33m" << billText << "\033[0m\n"; // Yellow color output

    // Log return
    RentalManager::logRentalHistory(cust.getName(), cust.getPhone(), v->getID(),
        actualDays, "Returned", totalBill, lateFee, earlyPenalty);

    // Save bill to file
    Billing::logBill(billText);

    // Cleanup
    RentalManager::removeFromCurrentRentals(cust.getName(), cust.getPhone());
    cust.returnVehicle();
}

string Billing::formatBill(const string& customerName, const string& phone, const string& vehicleID,
    int expectedDays, int actualDays, float rentPerDay,
    int baseRent, int lateFee, int earlyPenalty, int totalBill) {
    stringstream ss;
    ss << "\n--- Final Bill ---\n";
    ss << "Customer       : " << customerName << " | Phone: " << phone << "\n";
    ss << "Vehicle ID     : " << vehicleID << "\n";
    ss << "Days Kept      : " << actualDays << " (Expected: " << expectedDays << ")\n";
    ss << "Rent per Day   : ?" << rentPerDay << "\n";
    ss << "Base Rent      : ?" << baseRent << "\n";

    if (lateFee > 0)
        ss << "Late Fee       : ?" << lateFee << " (?" << rentPerDay << " x " << (actualDays - expectedDays) << " days)\n";
    if (earlyPenalty > 0)
        ss << "Early Penalty  : ?" << earlyPenalty << " (Half-day rent)\n";

    ss << "Total Bill     : ?" << totalBill << "\n";
    ss << "\nNote:\n• Late returns incur " << (LATE_FEE_RATE * 100) << "% rent/day.\n";
    ss << "• Early returns charge " << (EARLY_PENALTY_RATE * 100) << "% penalty of daily rent.\n";
    ss << "• For Cars, an extra ?100 booking fee is already included.\n";

    return ss.str();
}

void Billing::logBill(const string& formattedBill) {
    ofstream billFile("bill_log.txt", ios::app);
    if (!billFile) {
        cerr << "Error opening bill_log.txt\n";
        return;
    }
    billFile << formattedBill << "\n------------------------------------\n";
    billFile.close();
}
