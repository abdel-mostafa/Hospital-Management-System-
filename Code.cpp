#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    int id;
    int age;
    string contact;

public:
    Person() : id(0), age(0) {}
    Person(string n, int i, int a, string c) : name(n), id(i), age(a), contact(c) {}
    
    virtual ~Person() {}
    
    // Pure virtual function - makes this an abstract class
    virtual void displayDetails() const = 0;
    virtual string getInfo() const = 0;
    virtual string getType() const = 0;
    
    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getContact() const { return contact; }
    
    // Setters
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setContact(string c) { contact = c; }
};

// Derived class: Patient
class Patient : public Person {
private:
    string medicalHistory;
    string currentCondition;
    int assignedDoctorId;

public:
    Patient() : Person(), assignedDoctorId(0) {}
    Patient(string n, int i, int a, string c, string mh, string cc, int docId = 0)
        : Person(n, i, a, c), medicalHistory(mh), currentCondition(cc), assignedDoctorId(docId) {}
    
    void displayDetails() const override {
        cout << "\n========== PATIENT DETAILS ==========\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Medical History: " << medicalHistory << endl;
        cout << "Current Condition: " << currentCondition << endl;
        cout << "Assigned Doctor ID: " << (assignedDoctorId == 0 ? "None" : to_string(assignedDoctorId)) << endl;
        cout << "====================================\n";
    }
    
    string getInfo() const override {
        return "Patient - " + name + " (ID: " + to_string(id) + ")";
    }
    
    string getType() const override {
        return "Patient";
    }
    
    // Getters
    string getMedicalHistory() const { return medicalHistory; }
    string getCurrentCondition() const { return currentCondition; }
    int getAssignedDoctorId() const { return assignedDoctorId; }
    
    // Setters
    void setMedicalHistory(string mh) { medicalHistory = mh; }
    void setCurrentCondition(string cc) { currentCondition = cc; }
    void setAssignedDoctorId(int docId) { assignedDoctorId = docId; }
    
    // File operations
    string toFileString() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," + 
               contact + "," + medicalHistory + "," + currentCondition + "," + 
               to_string(assignedDoctorId);
    }
    
    static Patient fromFileString(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 7) {
            return Patient(tokens[1], stoi(tokens[0]), stoi(tokens[2]), 
                          tokens[3], tokens[4], tokens[5], stoi(tokens[6]));
        }
        return Patient();
    }
};

// Derived class: Doctor
class Doctor : public Person {
private:
    string specialization;
    vector<int> patientIds;
    string schedule;

public:
    Doctor() : Person() {}
    Doctor(string n, int i, int a, string c, string spec, string sched = "9AM-5PM")
        : Person(n, i, a, c), specialization(spec), schedule(sched) {}
    
    void displayDetails() const override {
        cout << "\n========== DOCTOR DETAILS ==========\n";
        cout << "ID: " << id << endl;
        cout << "Name: Dr. " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Schedule: " << schedule << endl;
        cout << "Number of Patients: " << patientIds.size() << endl;
        cout << "====================================\n";
    }
    
    string getInfo() const override {
        return "Dr. " + name + " - " + specialization + " (ID: " + to_string(id) + ")";
    }
    
    string getType() const override {
        return "Doctor";
    }
    
    // Getters
    string getSpecialization() const { return specialization; }
    string getSchedule() const { return schedule; }
    const vector<int>& getPatientIds() const { return patientIds; }
    
    // Setters
    void setSpecialization(string spec) { specialization = spec; }
    void setSchedule(string sched) { schedule = sched; }
    
    void addPatient(int patientId) {
        if (find(patientIds.begin(), patientIds.end(), patientId) == patientIds.end()) {
            patientIds.push_back(patientId);
        }
    }
    
    void removePatient(int patientId) {
        patientIds.erase(remove(patientIds.begin(), patientIds.end(), patientId), patientIds.end());
    }
    
    // File operations
    string toFileString() const {
        string patientsStr;
        for (size_t i = 0; i < patientIds.size(); i++) {
            patientsStr += to_string(patientIds[i]);
            if (i < patientIds.size() - 1) patientsStr += ":";
        }
        return to_string(id) + "," + name + "," + to_string(age) + "," + 
               contact + "," + specialization + "," + schedule + "," + patientsStr;
    }
    
    static Doctor fromFileString(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            Doctor doc(tokens[1], stoi(tokens[0]), stoi(tokens[2]), 
                      tokens[3], tokens[4], tokens[5]);
            
            if (tokens.size() == 7 && !tokens[6].empty()) {
                stringstream pss(tokens[6]);
                string pid;
                while (getline(pss, pid, ':')) {
                    if (!pid.empty()) {
                        doc.addPatient(stoi(pid));
                    }
                }
            }
            return doc;
        }
        return Doctor();
    }
};

// Derived class: Nurse
class Nurse : public Person {
private:
    string department;
    string shift;
    string assignedWard;

public:
    Nurse() : Person() {}
    Nurse(string n, int i, int a, string c, string dept, string sh, string ward)
        : Person(n, i, a, c), department(dept), shift(sh), assignedWard(ward) {}
    
    void displayDetails() const override {
        cout << "\n========== NURSE DETAILS ==========\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Department: " << department << endl;
        cout << "Shift: " << shift << endl;
        cout << "Assigned Ward: " << assignedWard << endl;
        cout << "===================================\n";
    }
    
    string getInfo() const override {
        return "Nurse " + name + " - " + department + " (ID: " + to_string(id) + ")";
    }
    
    string getType() const override {
        return "Nurse";
    }
    
    // Getters
    string getDepartment() const { return department; }
    string getShift() const { return shift; }
    string getAssignedWard() const { return assignedWard; }
    
    // Setters
    void setDepartment(string dept) { department = dept; }
    void setShift(string sh) { shift = sh; }
    void setAssignedWard(string ward) { assignedWard = ward; }
    
    // File operations
    string toFileString() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," + 
               contact + "," + department + "," + shift + "," + assignedWard;
    }
    
    static Nurse fromFileString(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 7) {
            return Nurse(tokens[1], stoi(tokens[0]), stoi(tokens[2]), 
                        tokens[3], tokens[4], tokens[5], tokens[6]);
        }
        return Nurse();
    }
};

// Appointment class
class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string time;
    string status; // Scheduled, Completed, Cancelled

public:
    Appointment() : appointmentId(0), patientId(0), doctorId(0), status("Scheduled") {}
    Appointment(int appId, int pId, int dId, string d, string t, string s = "Scheduled")
        : appointmentId(appId), patientId(pId), doctorId(dId), date(d), time(t), status(s) {}
    
    void displayDetails() const {
        cout << "\n--- Appointment Details ---\n";
        cout << "Appointment ID: " << appointmentId << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Doctor ID: " << doctorId << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Status: " << status << endl;
        cout << "--------------------------\n";
    }
    
    // Getters
    int getAppointmentId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getStatus() const { return status; }
    
    // Setters
    void setStatus(string s) { status = s; }
    void setDate(string d) { date = d; }
    void setTime(string t) { time = t; }
    
    // File operations
    string toFileString() const {
        return to_string(appointmentId) + "," + to_string(patientId) + "," + 
               to_string(doctorId) + "," + date + "," + time + "," + status;
    }
    
    static Appointment fromFileString(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            return Appointment(stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]), 
                             tokens[3], tokens[4], tokens[5]);
        }
        return Appointment();
    }
};

// Hospital Management System class
class HospitalSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Nurse> nurses;
    vector<Appointment> appointments;
    
    int nextPatientId;
    int nextDoctorId;
    int nextNurseId;
    int nextAppointmentId;

public:
    HospitalSystem() : nextPatientId(1), nextDoctorId(1), nextNurseId(1), nextAppointmentId(1) {}
    
    // Patient Management
    void addPatient() {
        string name, contact, medicalHistory, condition;
        int age;
        
        cout << "\n=== Add New Patient ===\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Contact: ";
        cin.ignore();
        getline(cin, contact);
        cout << "Enter Medical History: ";
        getline(cin, medicalHistory);
        cout << "Enter Current Condition: ";
        getline(cin, condition);
        
        Patient p(name, nextPatientId++, age, contact, medicalHistory, condition);
        patients.push_back(p);
        
        cout << "\n✓ Patient added successfully! Patient ID: " << p.getId() << endl;
    }
    
    void viewAllPatients() const {
        if (patients.empty()) {
            cout << "\nNo patients registered.\n";
            return;
        }
        
        cout << "\n=== All Patients ===\n";
        for (const auto& p : patients) {
            cout << p.getInfo() << endl;
        }
    }
    
    void searchPatient() const {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;
        
        for (const auto& p : patients) {
            if (p.getId() == id) {
                p.displayDetails();
                return;
            }
        }
        cout << "\nPatient not found!\n";
    }
    
    // Doctor Management
    void addDoctor() {
        string name, contact, specialization, schedule;
        int age;
        
        cout << "\n=== Add New Doctor ===\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Contact: ";
        cin.ignore();
        getline(cin, contact);
        cout << "Enter Specialization: ";
        getline(cin, specialization);
        cout << "Enter Schedule (e.g., 9AM-5PM): ";
        getline(cin, schedule);
        
        Doctor d(name, nextDoctorId++, age, contact, specialization, schedule);
        doctors.push_back(d);
        
        cout << "\n✓ Doctor added successfully! Doctor ID: " << d.getId() << endl;
    }
    
    void viewAllDoctors() const {
        if (doctors.empty()) {
            cout << "\nNo doctors registered.\n";
            return;
        }
        
        cout << "\n=== All Doctors ===\n";
        for (const auto& d : doctors) {
            cout << d.getInfo() << endl;
        }
    }
    
    void searchDoctor() const {
        int id;
        cout << "\nEnter Doctor ID to search: ";
        cin >> id;
        
        for (const auto& d : doctors) {
            if (d.getId() == id) {
                d.displayDetails();
                return;
            }
        }
        cout << "\nDoctor not found!\n";
    }
    
    // Nurse Management
    void addNurse() {
        string name, contact, department, shift, ward;
        int age;
        
        cout << "\n=== Add New Nurse ===\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Contact: ";
        cin.ignore();
        getline(cin, contact);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter Shift (Morning/Evening/Night): ";
        getline(cin, shift);
        cout << "Enter Assigned Ward: ";
        getline(cin, ward);
        
        Nurse n(name, nextNurseId++, age, contact, department, shift, ward);
        nurses.push_back(n);
        
        cout << "\n✓ Nurse added successfully! Nurse ID: " << n.getId() << endl;
    }
    
    void viewAllNurses() const {
        if (nurses.empty()) {
            cout << "\nNo nurses registered.\n";
            return;
        }
        
        cout << "\n=== All Nurses ===\n";
        for (const auto& n : nurses) {
            cout << n.getInfo() << endl;
        }
    }
    
    // Appointment Management
    void bookAppointment() {
        int patientId, doctorId;
        string date, time;
        
        cout << "\n=== Book Appointment ===\n";
        viewAllPatients();
        cout << "Enter Patient ID: ";
        cin >> patientId;
        
        viewAllDoctors();
        cout << "Enter Doctor ID: ";
        cin >> doctorId;
        
        // Verify patient and doctor exist
        bool patientExists = false, doctorExists = false;
        
        for (const auto& p : patients) {
            if (p.getId() == patientId) {
                patientExists = true;
                break;
            }
        }
        
        for (auto& d : doctors) {
            if (d.getId() == doctorId) {
                doctorExists = true;
                d.addPatient(patientId);
                break;
            }
        }
        
        if (!patientExists || !doctorExists) {
            cout << "\nInvalid Patient ID or Doctor ID!\n";
            return;
        }
        
        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;
        cout << "Enter Time (HH:MM): ";
        cin >> time;
        
        Appointment app(nextAppointmentId++, patientId, doctorId, date, time);
        appointments.push_back(app);
        
        // Update patient's assigned doctor
        for (auto& p : patients) {
            if (p.getId() == patientId) {
                p.setAssignedDoctorId(doctorId);
                break;
            }
        }
        
        cout << "\n✓ Appointment booked successfully! Appointment ID: " << app.getAppointmentId() << endl;
    }
    
    void viewAllAppointments() const {
        if (appointments.empty()) {
            cout << "\nNo appointments scheduled.\n";
            return;
        }
        
        cout << "\n=== All Appointments ===\n";
        for (const auto& app : appointments) {
            app.displayDetails();
        }
    }
    
    void cancelAppointment() {
        int appId;
        cout << "\nEnter Appointment ID to cancel: ";
        cin >> appId;
        
        for (auto& app : appointments) {
            if (app.getAppointmentId() == appId) {
                app.setStatus("Cancelled");
                cout << "\n✓ Appointment cancelled successfully!\n";
                return;
            }
        }
        cout << "\nAppointment not found!\n";
    }
    
    // File Handling
    void saveToFiles() {
        // Save patients
        ofstream pFile("patients.txt");
        for (const auto& p : patients) {
            pFile << p.toFileString() << endl;
        }
        pFile.close();
        
        // Save doctors
        ofstream dFile("doctors.txt");
        for (const auto& d : doctors) {
            dFile << d.toFileString() << endl;
        }
        dFile.close();
        
        // Save nurses
        ofstream nFile("nurses.txt");
        for (const auto& n : nurses) {
            nFile << n.toFileString() << endl;
        }
        nFile.close();
        
        // Save appointments
        ofstream aFile("appointments.txt");
        for (const auto& app : appointments) {
            aFile << app.toFileString() << endl;
        }
        aFile.close();
        
        // Save next IDs
        ofstream idFile("nextids.txt");
        idFile << nextPatientId << endl;
        idFile << nextDoctorId << endl;
        idFile << nextNurseId << endl;
        idFile << nextAppointmentId << endl;
        idFile.close();
        
        cout << "\n✓ All data saved successfully!\n";
    }
    
    void loadFromFiles() {
        // Load patients
        ifstream pFile("patients.txt");
        if (pFile.is_open()) {
            string line;
            while (getline(pFile, line)) {
                if (!line.empty()) {
                    patients.push_back(Patient::fromFileString(line));
                }
            }
            pFile.close();
        }
        
        // Load doctors
        ifstream dFile("doctors.txt");
        if (dFile.is_open()) {
            string line;
            while (getline(dFile, line)) {
                if (!line.empty()) {
                    doctors.push_back(Doctor::fromFileString(line));
                }
            }
            dFile.close();
        }
        
        // Load nurses
        ifstream nFile("nurses.txt");
        if (nFile.is_open()) {
            string line;
            while (getline(nFile, line)) {
                if (!line.empty()) {
                    nurses.push_back(Nurse::fromFileString(line));
                }
            }
            nFile.close();
        }
        
        // Load appointments
        ifstream aFile("appointments.txt");
        if (aFile.is_open()) {
            string line;
            while (getline(aFile, line)) {
                if (!line.empty()) {
                    appointments.push_back(Appointment::fromFileString(line));
                }
            }
            aFile.close();
        }
        
        // Load next IDs
        ifstream idFile("nextids.txt");
        if (idFile.is_open()) {
            idFile >> nextPatientId >> nextDoctorId >> nextNurseId >> nextAppointmentId;
            idFile.close();
        }
        
        cout << "\n✓ Data loaded successfully!\n";
    }
};

// Main function with menu
int main() {
    HospitalSystem hospital;
    hospital.loadFromFiles();
    
    int choice;
    
    while (true) {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║   HOSPITAL MANAGEMENT SYSTEM          ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "\n1.  Add Patient\n";
        cout << "2.  View All Patients\n";
        cout << "3.  Search Patient\n";
        cout << "4.  Add Doctor\n";
        cout << "5.  View All Doctors\n";
        cout << "6.  Search Doctor\n";
        cout << "7.  Add Nurse\n";
        cout << "8.  View All Nurses\n";
        cout << "9.  Book Appointment\n";
        cout << "10. View All Appointments\n";
        cout << "11. Cancel Appointment\n";
        cout << "12. Save Data\n";
        cout << "13. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.viewAllPatients();
                break;
            case 3:
                hospital.searchPatient();
                break;
            case 4:
                hospital.addDoctor();
                break;
            case 5:
                hospital.viewAllDoctors();
                break;
            case 6:
                hospital.searchDoctor();
                break;
            case 7:
                hospital.addNurse();
                break;
            case 8:
                hospital.viewAllNurses();
                break;
            case 9:
                hospital.bookAppointment();
                break;
            case 10:
                hospital.viewAllAppointments();
                break;
            case 11:
                hospital.cancelAppointment();
                break;
            case 12:
                hospital.saveToFiles();
                break;
            case 13:
                hospital.saveToFiles();
                cout << "\nThank you for using Hospital Management System!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
