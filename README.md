# 🚗 Vehicle Rental System (C++ Project)

A modular and object-oriented **Vehicle Rental System** built in C++. It allows customers to rent or return vehicles (cars/bikes), and admins to manage fleet inventory and view rental history. The system uses OOP concepts like inheritance, polymorphism, encapsulation, abstraction, and file handling for persistent data.

---

## 🧠 OOP Principles Used

- **Encapsulation** - All classes keep their data private and expose behavior through public methods (`getID()`, `rentVehicle()`, etc.) 
- **Abstraction** - Users interact with simple admin/customer menus without knowing internal logic; file I/O, billing, and rental logic are abstracted into dedicated classes 
- **Inheritance** - `Car` and `Bike` inherit from base class `Vehicle` 
- **Polymorphism** - Vehicle objects are accessed via base class pointers; virtual functions enable runtime behavior (`calculateRent()`, `displayDetails()`) 
- **Classes & Objects** - Real-world entities like Vehicle, Customer, Billing, and FileManager are modeled as classes 

---

## 🧩 Key Features

### 👤 Customer
- View available vehicles
- Rent vehicle (with unique ID and duration)
- Return rented vehicle and get a final bill
- Early return → half-day penalty
- Late return → extra full-day charges
- Rental automatically saved in `current_rentals.txt`
- System Reset Function → Admins can reset all system data (vehicles, rentals, bills, logs) to start fresh for testing or new deployment.

### 👩‍💼 Admin
- Add new cars or bikes with unique IDs
- View all registered vehicles with status
- View complete rental history from `rental_history.txt`

---

## 🔁 Project Flow Summary

1. Admin loads vehicle data
2. Vehicles are saved to and read from `vehicles.txt`
3. Customers rent/return vehicles → triggers:
   - Update availability
   - Log rental to `rental_history.txt`
   - Track active rentals in `current_rentals.txt`
   - Generate final bill in `bill_log.txt`

---

## 🧾 Billing Logic

- **Base Rent** = rent per day × total days used
- **Late Fee** = ₹rent/day × number of extra days
- **Early Return Penalty** = ₹rent/day ÷ 2 (half-day charge)
- 💾 All bills saved to `bill_log.txt`

---

## 🧪 Final Testing Checklist ✅

- [x] Admin can add cars and bikes with validation
- [x] Duplicated vehicle IDs are rejected
- [x] Customer can rent only if not already renting
- [x] Vehicle availability updates automatically
- [x] Final bill generated with accurate fees
- [x] Rental and return logs are persistent
- [x] Invalid inputs are safely handled
- [x] No memory leaks (manual `delete` on exit)

---

## 🛠 Technologies Used

- Language: **C++**
- Features: **Object-Oriented Programming, File I/O, CLI**
- IDE: **Visual Studio 2022 Preview**
- Platform: Windows

---

## ▶️ How to Run (Visual Studio 2022)

1. Open **Visual Studio 2022 Preview**.
2. Click **File → Open → Project/Solution** and select `Vehicle_Renting_System.sln`.
3. Set the build configuration to **Debug** (or Release) and platform to **x64** if needed.
4. Build the solution: **Build → Build Solution** (`Ctrl + Shift + B`).
5. Run the project: **Debug → Start Without Debugging** (`Ctrl + F5`).
6. Follow the **on-screen menus** for Admin or Customer actions.

💡 Notes:  
- The program will generate and update `vehicles.txt`, `current_rentals.txt`, `rental_history.txt`, and `bill_log.txt` automatically.  
- No extra compilation commands are needed; Visual Studio handles linking all `.cpp` files.  

---
## 📂 Project Structure
```plaintext
Vehicle_Renting_System/
│ Vehicle_Renting_System.sln
│ Vehicle_Renting_System.vcxproj
│ Vehicle_Renting_System.vcxproj.filters
│ bill_log.txt
│ current_rentals.txt
│ rental_history.txt
│ vehicles.txt
│ .gitignore
│
├── AdminInterface.cpp
├── AdminInterface.h
├── Bike.cpp
├── Bike.h
├── Billing.cpp
├── Billing.h
├── Car.cpp
├── Car.h
├── Customer.cpp
├── Customer.h
├── CustomerInterface.cpp
├── CustomerInterface.h
├── FileManagercpp.cpp
├── FileManager.h
├── RentalManager.cpp
├── RentalManager.h
├── Vehicle.cpp
├── Vehicle.h
├── Vehicle_Renting_System.cpp

---

👩‍💻 Developer

Shreya Dandale  
B.Tech in Electronics & Telecommunication, JSPM RSCOE Pune (2026)  
🎯 Passionate about C++, Web Development, and Software Engineering  
