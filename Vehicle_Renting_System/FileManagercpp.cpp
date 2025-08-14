#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void FileManager::saveVehiclesToFile(const vector<Vehicle*>& vehicles, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& v : vehicles) {
        if (Car* car = dynamic_cast<Car*>(v)) {
            outFile << "Car," << car->getID() << "," << car->getBrand() << ","
                << car->getRentPerDay() << "," << car->getAvailability() << ","
                << car->getSeats() << "\n";
        }
        else if (Bike* bike = dynamic_cast<Bike*>(v)) {
            outFile << "Bike," << bike->getID() << "," << bike->getBrand() << ","
                << bike->getRentPerDay() << "," << bike->getAvailability() << ","
                << bike->hasCarrierFn() << "\n";
        }
    }

    outFile.close();
}

void FileManager::loadVehiclesFromFile(vector<Vehicle*>& vehicles, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No vehicle file found. Starting with empty list.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string type, id, brand;
        float rent;
        bool avail;

        getline(ss, type, ',');
        getline(ss, id, ',');
        getline(ss, brand, ',');
        ss >> rent;
        ss.ignore();
        ss >> avail;
        ss.ignore();

        if (type == "Car") {
            int seats;
            ss >> seats;
            auto* car = new Car(id, brand, rent, seats);
            car->setAvailability(avail);
            vehicles.push_back(car);
        }
        else if (type == "Bike") {
            bool carrier;
            ss >> carrier;
            auto* bike = new Bike(id, brand, rent, carrier);
            bike->setAvailability(avail);
            vehicles.push_back(bike);
        }
    }

    inFile.close();
}

void FileManager::resetSystemData() {
    vector<string> files = {
        "vehicles.txt",
        "current_rentals.txt",
        "rental_history.txt",
        "bill_log.txt"
    };

    for (const auto& file : files) {
        ofstream out(file); // Truncates by default
        if (out) {
            cout << "Cleared: " << file << endl;
        }
        else {
            cerr << "Failed to clear: " << file << endl;
        }
    }
}
