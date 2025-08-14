#include "RentalManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

bool RentalManager::loadCurrentRental(Customer& cust) {
    ifstream file("current_rentals.txt");
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, vid, daysStr;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, vid, ',');
        getline(ss, daysStr);

        if (name == cust.getName() && phone == cust.getPhone()) {
            if (!isNumber(daysStr)) {
                cout << "Invalid rental day data for customer: " << name << "\n";
                return false;
            }

            int days = stoi(daysStr);
            cust.rentVehicle(vid, days);
            return true;
        }
    }
    return false;
}

void RentalManager::updateVehicleAvailabilityFromCurrentRentals(vector<Vehicle*>& vehicles) {
    ifstream in("current_rentals.txt");
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, phone, vehicleID, daysStr;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, vehicleID, ',');
        getline(ss, daysStr, ',');

        for (auto& v : vehicles) {
            if (v->getID() == vehicleID) {
                v->setAvailability(false);
                break;
            }
        }
    }

    in.close();
}

void RentalManager::removeFromCurrentRentals(const string& name, const string& phone) {
    ifstream inFile("current_rentals.txt");
    ofstream tempFile("temp.txt");

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileName, filePhone;
        getline(ss, fileName, ',');
        getline(ss, filePhone, ',');

        if (fileName != name || filePhone != phone) {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();
    remove("current_rentals.txt");
    rename("temp.txt", "current_rentals.txt");
}

void RentalManager::logRentalHistory(const string& customerName, const string& phone,
    const string& vehicleID, int days,
    const string& action, int totalBill,
    int lateFee, int earlyPenalty) {
    ofstream logFile("rental_history.txt", ios::app);
    if (!logFile) {
        cerr << "Error opening rental_history.txt\n";
        return;
    }

    string dateStr = "";
    if (action != "Returned") {
        time_t now = time(0);
        tm localtm;
        localtime_s(&localtm, &now);  // Secure version for Visual Studio
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localtm);
        dateStr = buffer;
    }

    logFile << customerName << "," << phone << "," << vehicleID << ",";
    if (!dateStr.empty()) logFile << dateStr;
    logFile << "," << days << "," << action;

    if (action == "Returned") {
        logFile << ", Total: â, Total: \xE2, Total: \xE2\x82¹, Total: \xE2\x82\xB9" << totalBill;  // INR symbol
        if (lateFee > 0)
            logFile << ", Late Fee: â, Late Fee: \xE2, Late Fee: \xE2\x82¹, Late Fee: \xE2\x82\xB9" << lateFee;
        if (earlyPenalty > 0)
            logFile << ", Early Penalty: â, Early Penalty: \xE2, Early Penalty: \xE2\x82¹, Early Penalty: \xE2\x82\xB9" << earlyPenalty;
        logFile << ", Note: 20% extra/day for late, half-day charge for early return";
    }

    logFile << "\n";
    logFile.close();
}

bool RentalManager::isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}
