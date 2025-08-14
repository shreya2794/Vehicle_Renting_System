#include "Customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Constructor
Customer::Customer(string name, string phone)
    : name(name), phoneNumber(phone), rentedVehicleID(""), rentDays(0) {
    loadRental();
}

// Getters
string Customer::getName() const {
    return name;
}

string Customer::getPhone() const {
    return phoneNumber;
}

string Customer::getRentedVehicleID() const {
    return rentedVehicleID;
}

int Customer::getRentDays() const {
    return rentDays;
}

// Check if customer has rented a vehicle
bool Customer::hasRented() const {
    return !rentedVehicleID.empty();
}

// Rent a vehicle
void Customer::rentVehicle(const string& vid, int days) {
    rentedVehicleID = vid;
    rentDays = days;
    saveRental();
}

// Return a rented vehicle
void Customer::returnVehicle() {
    rentedVehicleID = "";
    rentDays = 0;
    removeRental();
}

// Save current rental to file
void Customer::saveRental() {
    removeRental(); // Remove any existing entry first
    ofstream out("current_rentals.txt", ios::app);
    out << name << "," << phoneNumber << "," << rentedVehicleID << "," << rentDays << "\n";
    out.close();
}

// Load rental from file (if any)
void Customer::loadRental() {
    ifstream in("current_rentals.txt");
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string n, phone, vid, daysStr;
        getline(ss, n, ',');
        getline(ss, phone, ',');
        getline(ss, vid, ',');
        getline(ss, daysStr, ',');

        if (n == name && phone == phoneNumber) {
            rentedVehicleID = vid;
            rentDays = stoi(daysStr);
            break;
        }
    }
    in.close();
}

// Remove rental record for this customer
void Customer::removeRental() {
    ifstream in("current_rentals.txt");
    vector<string> lines;
    string line;
    while (getline(in, line)) {
        if (line.find(name + "," + phoneNumber + "," + rentedVehicleID) != 0) {
            lines.push_back(line);
        }
    }
    in.close();

    ofstream out("current_rentals.txt");
    for (const auto& l : lines)
        out << l << "\n";
    out.close();
}

// Display customer info
void Customer::displayCustomerDetails() const {
    cout << "Name: " << name << "\nPhone: " << phoneNumber
        << "\nRented Vehicle ID: " << rentedVehicleID
        << "\nDays: " << rentDays << endl;
}
