#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For table formatting
#include <cstdlib> // For random numbers
#include <ctime>   // For time seeding
#include <sstream> // REQUIRED: Added for the string conversion fix

using namespace std;

// --- Helper for C++98 Compatibility ---
// Since to_string is not available in your compiler, we create it manually
template <typename T>
string to_string(T value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

// --- Class Definition ---
class Student {
private:
    string name;
    string appNumber;
    string mobile;
    int semester;
    double cgpa;
    string email;

public:
    // Constructor
    Student(string n, string app, string mob, int sem, double c, string mail) {
        name = n;
        appNumber = app;
        mobile = mob;
        semester = sem;
        cgpa = c;
        email = mail;
    }

    // Getters
    string getAppNumber() const { return appNumber; }
    string getName() const { return name; }
    
    // Setters for Editing
    void setMobile(string m) { mobile = m; }
    void setSemester(int s) { semester = s; }
    void setCGPA(double c) { cgpa = c; }
    void setEmail(string e) { email = e; }

    // Display Row for Table View
    void printRow() const {
        cout << left << setw(20) << name 
             << setw(15) << appNumber 
             << setw(15) << mobile 
             << setw(10) << semester 
             << setw(8) << fixed << setprecision(2) << cgpa 
             << setw(25) << email << endl;
    }

    // Detailed View for Individual Student
    void printDetails() const {
        cout << "\n--- STUDENT PROFILE ---" << endl;
        cout << "Name:        " << name << endl;
        cout << "App No:      " << appNumber << endl;
        cout << "Mobile:      +91 " << mobile << endl;
        cout << "Semester:    " << semester << endl;
        cout << "CGPA:        " << cgpa << endl;
        cout << "Email:       " << email << endl; 
        cout << "-----------------------" << endl;
    }
};

// --- Global Database ---
vector<Student> students;

// --- Helper Functions ---

// Generate Random Indian Data
void initializeData() {
    string names[] = {"Ram", "Raj", "Krishna", "Tejaswini", "Anjali", "Vikram", "Sneha", "Rahul", "Priya", "Amit"};
    int semOptions[] = {2, 4, 6, 8};
    
    // Seed random number generator
    srand(time(0)); 

    // FIX: Replaced range-based loop with standard loop
    int numNames = sizeof(names) / sizeof(names[0]);
    for (int i = 0; i < numNames; i++) {
        string n = names[i];
        
        // Generate App Number (e.g., AP24110...)
        string app = "AP24" + to_string(1000 + rand() % 9000);
        
        // Generate Mobile (Starts with 9, 8, 7 or 6 for India)
        string mob = to_string(6 + rand() % 4) + to_string(100000000 + rand() % 900000000);
        
        // Generate Semester and CGPA
        int sem = semOptions[rand() % 4];
        double cgpa = 6.0 + (rand() % 40) / 10.0; // Random between 6.0 and 10.0
        
        // Generate Email
        string mail = n + "@srmuniversity.ac.in"; // Generic example domain

        // Add to database
        students.push_back(Student(n, app, mob, sem, cgpa, mail));
    }
}

// Check uniqueness
bool isAppUnique(string app) {
    // FIX: Replaced range-based loop
    for(size_t i = 0; i < students.size(); i++) {
        if(students[i].getAppNumber() == app) return false;
    }
    return true;
}

// --- Admin Functions ---

void viewAllStudents() {
    if (students.empty()) {
        cout << "\n[!] Database is empty." << endl;
        return;
    }
    cout << "\n==========================================================================================" << endl;
    cout << left << setw(20) << "NAME" 
         << setw(15) << "APP NUMBER" 
         << setw(15) << "MOBILE" 
         << setw(10) << "SEM" 
         << setw(8) << "CGPA" 
         << setw(25) << "EMAIL" << endl;
    cout << "==========================================================================================" << endl;
    
    // FIX: Replaced range-based loop
    for (size_t i = 0; i < students.size(); i++) {
        students[i].printRow();
    }
    cout << "==========================================================================================" << endl;
}

void addStudent() {
    string n, app, mob, mail;
    int sem;
    double c;

    cout << "\n--- ADD NEW STUDENT ---" << endl;
    cin.ignore(); 
    
    cout << "Enter App Number: "; getline(cin, app);
    if(!isAppUnique(app)) { cout << "Error: ID already exists!\n"; return; }

    cout << "Enter Name: "; getline(cin, n);
    cout << "Enter Mobile: "; getline(cin, mob);
    cout << "Enter Email: "; getline(cin, mail);
    cout << "Enter Semester: "; cin >> sem;
    cout << "Enter CGPA: "; cin >> c;

    students.push_back(Student(n, app, mob, sem, c, mail));
    cout << ">> Success: Student Added!" << endl;
}

void deleteStudent() {
    string app;
    cout << "\n--- DELETE STUDENT ---" << endl;
    cout << "Enter Application Number to delete: ";
    cin >> app;

    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->getAppNumber() == app) {
            cout << "Deleting record for " << it->getName() << "..." << endl;
            students.erase(it);
            cout << ">> Success: Record Deleted." << endl;
            return;
        }
    }
    cout << ">> Error: Student not found." << endl;
}

void modifyStudent() {
    string app;
    cout << "\n--- MODIFY STUDENT DETAILS ---" << endl;
    cout << "Enter Application Number to edit: ";
    cin >> app;

    // FIX: Replaced range-based loop and 'auto'
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getAppNumber() == app) {
            cout << "\nCurrent Details for " << students[i].getName() << ":" << endl;
            students[i].printDetails();
            
            cout << "\nWhat do you want to change?" << endl;
            cout << "1. Mobile Number\n2. CGPA\n3. Semester\n4. Email\n5. Cancel" << endl;
            int choice;
            cout << "Enter choice: "; cin >> choice;

            if(choice == 5) return;

            if(choice == 1) {
                string m; cout << "New Mobile: "; cin >> m; students[i].setMobile(m);
            } else if(choice == 2) {
                double c; cout << "New CGPA: "; cin >> c; students[i].setCGPA(c);
            } else if(choice == 3) {
                int sm; cout << "New Semester: "; cin >> sm; students[i].setSemester(sm);
            } else if(choice == 4) {
                string e; cout << "New Email: "; cin >> e; students[i].setEmail(e);
            }
            cout << ">> Success: Details Updated." << endl;
            return;
        }
    }
    cout << ">> Error: Student not found." << endl;
}

// --- Menu Logic ---

void adminPanel() {
    string u, p;
    cout << "\n[ADMIN LOGIN REQUIRED]" << endl;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    if (u == "admin" && p == "admin123") {
        cout << "\n>> LOGIN SUCCESSFUL. Loading Database..." << endl;
        
        viewAllStudents(); 

        int choice;
        do {
            cout << "\n--- ADMIN CONTROL PANEL ---" << endl;
            cout << "1. Add New Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Modify Student Details" << endl;
            cout << "4. View All Records (Refresh)" << endl;
            cout << "5. Logout" << endl;
            cout << "Selection: ";
            cin >> choice;

            switch(choice) {
                case 1: addStudent(); break;
                case 2: deleteStudent(); break;
                case 3: modifyStudent(); break;
                case 4: viewAllStudents(); break;
                case 5: cout << "Logging out..." << endl; break;
                default: cout << "Invalid." << endl;
            }
        } while (choice != 5);

    } else {
        cout << ">> Access Denied: Wrong ID or Password." << endl;
    }
}

void studentPanel() {
    string app;
    cout << "\n[STUDENT PORTAL]" << endl;
    cout << "Enter your Application Number: ";
    cin >> app;

    bool found = false;
    // FIX: Replaced range-based loop
    for(size_t i = 0; i < students.size(); i++) {
        if(students[i].getAppNumber() == app) {
            students[i].printDetails();
            found = true;
            break;
        }
    }
    if(!found) cout << ">> No record found with that Application Number." << endl;
}

int main() {
    // Generate the dummy Indian data at start of program
    initializeData();

    int option;
    do {
        cout << "   STUDENT RECORD SYSTEM (SRM AP)  \n\n" << endl;
        cout << "1. Admin Login (Edit/View All)" << endl;
        cout << "2. Student Check (View Self)" << endl;
        cout << "3. Exit" << endl;
        cout << "Selection: ";
        cin >> option;

        switch(option) {
            case 1: adminPanel(); break;
            case 2: studentPanel(); break;
            case 3: cout << "Exiting..." << endl; break;
            default: cout << "Invalid input." << endl;
        }

    } while(option != 3);

    return 0;
}
