#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "\nStudent added successfully!\n";
}

void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "\nNo records found!\n";
        return;
    }

    cout << "\n===== Student Records =====\n";

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "--------------------------\n";
    }

    file.close();
}

void searchStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}

void updateStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {

            cout << "\nEnter New Details:\n";
            s.input();

            file.seekp(-(long)sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "\nRecord Updated Successfully!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}

void deleteStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayAll();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
