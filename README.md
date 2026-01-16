# Hospital Management System 🏥

A comprehensive console-based Hospital Management System built in C++, demonstrating core Object-Oriented Programming (OOP) principles. This project was developed as a final project for an OOP course.

## 📋 Table of Contents
- [Features](#features)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [File Storage](#file-storage)
- [Screenshots](#screenshots)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

### Patient Management
- Register new patients with medical history
- View all registered patients
- Search patients by ID
- Track assigned doctors
- Monitor current medical conditions

### Doctor Management
- Add doctors with specializations
- View all doctors and their details
- Search doctors by ID
- Track doctor schedules
- Monitor patient assignments per doctor

### Nurse Management
- Register nurses with department information
- Assign nurses to specific wards
- Track shift timings
- View all nursing staff

### Appointment System
- Book appointments between patients and doctors
- View all scheduled appointments
- Cancel appointments
- Track appointment status (Scheduled/Completed/Cancelled)
- Automatic doctor-patient relationship establishment

### Data Persistence
- Save all data to text files
- Load existing data on startup
- Maintain data integrity across sessions

## 🎯 OOP Concepts Demonstrated

### 1. Inheritance
```cpp
Person (Base Class)
├── Patient (Derived)
├── Doctor (Derived)
└── Nurse (Derived)
```

### 2. Polymorphism
- **Virtual Functions**: `displayDetails()`, `getInfo()`, `getType()`
- **Pure Virtual Functions**: Making `Person` an abstract base class
- **Runtime Polymorphism**: Dynamic binding of virtual functions

### 3. Encapsulation
- Private data members with controlled access
- Public getter and setter methods
- Protected members accessible to derived classes

### 4. Abstraction
- Abstract `Person` class cannot be instantiated
- Interface defined through pure virtual functions
- Implementation details hidden from users

### 5. Additional Concepts
- **Composition**: `HospitalSystem` contains vectors of objects
- **File I/O**: Custom serialization and deserialization
- **STL Usage**: Vectors, strings, algorithms
- **Exception Safety**: Input validation and error handling

## 💻 System Requirements

- **Compiler**: Any C++ compiler supporting C++11 or later
  - GCC 4.8+
  - Clang 3.3+
  - MSVC 2013+
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimal (< 50 MB)

## 🚀 Installation

### Linux/macOS

```bash
# Clone the repository
git clone https://github.com/yourusername/hospital-management-system.git

# Navigate to project directory
cd hospital-management-system

# Compile the program
g++ -std=c++11 -o hospital main.cpp

# Run the program
./hospital
```

### Windows

```bash
# Clone the repository
git clone https://github.com/yourusername/hospital-management-system.git

# Navigate to project directory
cd hospital-management-system

# Compile using MinGW
g++ -std=c++11 -o hospital.exe main.cpp

# Run the program
hospital.exe
```

### Using an IDE
1. Open the project in your IDE (Visual Studio, Code::Blocks, etc.)
2. Build and run the project
3. Follow the on-screen menu

## 📖 Usage

### Main Menu Options

```
1.  Add Patient          - Register a new patient
2.  View All Patients    - Display all registered patients
3.  Search Patient       - Find patient by ID
4.  Add Doctor          - Register a new doctor
5.  View All Doctors    - Display all doctors
6.  Search Doctor       - Find doctor by ID
7.  Add Nurse           - Register a new nurse
8.  View All Nurses     - Display all nursing staff
9.  Book Appointment    - Schedule a patient-doctor appointment
10. View All Appointments - Display all appointments
11. Cancel Appointment   - Cancel an existing appointment
12. Save Data           - Save all data to files
13. Exit                - Save and exit the program
```

### Example Workflow

1. **Add a Doctor**
   - Select option 4
   - Enter doctor details (name, age, contact, specialization, schedule)

2. **Register a Patient**
   - Select option 1
   - Enter patient information (name, age, contact, medical history, condition)

3. **Book an Appointment**
   - Select option 9
   - Choose patient ID and doctor ID from the lists
   - Enter date and time

4. **View Appointment**
   - Select option 10
   - Review all scheduled appointments

## 📁 Project Structure

```
hospital-management-system/
│
├── main.cpp                 # Main source file
├── README.md               # Project documentation
│
├── patients.txt            # Patient data (auto-generated)
├── doctors.txt             # Doctor data (auto-generated)
├── nurses.txt              # Nurse data (auto-generated)
├── appointments.txt        # Appointment data (auto-generated)
└── nextids.txt            # ID counters (auto-generated)
```

## 💾 File Storage

The system automatically creates and manages five text files:

### patients.txt
```
ID,Name,Age,Contact,MedicalHistory,CurrentCondition,AssignedDoctorID
```

### doctors.txt
```
ID,Name,Age,Contact,Specialization,Schedule,PatientIDs(colon-separated)
```

### nurses.txt
```
ID,Name,Age,Contact,Department,Shift,AssignedWard
```

### appointments.txt
```
AppointmentID,PatientID,DoctorID,Date,Time,Status
```

### nextids.txt
```
NextPatientID
NextDoctorID
NextNurseID
NextAppointmentID
```

## 🖼️ Screenshots

### Main Menu
```
╔════════════════════════════════════════╗
║   HOSPITAL MANAGEMENT SYSTEM          ║
╚════════════════════════════════════════╝

1.  Add Patient
2.  View All Patients
3.  Search Patient
...
```

### Patient Details Display
```
========== PATIENT DETAILS ==========
ID: 1
Name: John Doe
Age: 35
Contact: +1234567890
Medical History: Diabetes, Hypertension
Current Condition: Stable
Assigned Doctor ID: 2
====================================
```

## 🔮 Future Enhancements

- [ ] Billing and payment system
- [ ] Prescription management
- [ ] Medical test records
- [ ] Emergency queue with priority
- [ ] GUI implementation using Qt or wxWidgets
- [ ] Database integration (MySQL/PostgreSQL)
- [ ] Multi-user authentication system
- [ ] Report generation (PDF/Excel)
- [ ] Email notifications for appointments
- [ ] SMS reminders
- [ ] Search by name functionality
- [ ] Edit/update existing records
- [ ] Medical inventory management
- [ ] Staff attendance tracking

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/improvement`)
3. Make your changes
4. Commit your changes (`git commit -am 'Add new feature'`)
5. Push to the branch (`git push origin feature/improvement`)
6. Create a Pull Request

## 📝 Code Style Guidelines

- Use meaningful variable names
- Comment complex logic
- Follow consistent indentation (4 spaces)
- Keep functions focused and concise
- Use appropriate access specifiers

## 🐛 Known Issues

- Limited input validation for dates and times
- No duplicate ID checking when loading from files
- Limited error handling for file operations
- No data backup mechanism



## 🙏 Acknowledgments

- Thanks to my OOP course instructor for project guidance
- C++ documentation and community resources
- Stack Overflow community for troubleshooting help

## 📞 Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Contact via email
- Check existing issues for solutions

---

⭐ If you found this project helpful, please give it a star!

**Last Updated**: January 2026
