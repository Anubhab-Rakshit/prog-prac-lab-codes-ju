/*
There are number of students. For every student roll (unique), name is to be
stored. For each subject, subject code and name is to be stored. A student can opt
for number of subjects. System should be able to maintain student list, subject list
and will be able to answer: i) which student has selected which subjects and ii)
for a subjects who are the students.
Design the classes and implement. For list consider memory data structure.

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Subject; // forward declaration

// ------------------ Student Class ------------------
class Student {
private:
    int roll;
    string name;
    vector<Subject*> subjects;

public:
    Student(int r, string n) : roll(r), name(n) {}

    int getRoll() const { return roll; }
    string getName() const { return name; }

    void addSubject(Subject* sub) { subjects.push_back(sub); }

    void showSubjects() const;   // Only declaration here
};


// ------------------ Subject Class ------------------
class Subject {
private:
    int code;
    string name;
    vector<Student*> students;

public:
    Subject(int c, string n) : code(c), name(n) {}

    int getCode() const { return code; }
    string getName() const { return name; }

    void addStudent(Student* s) { students.push_back(s); }

    void showStudents() const {
        cout << "\nSubject: " << name << " (" << code << ")\n";
        if (students.empty()) {
            cout << "No students enrolled yet.\n";
            return;
        }
        cout << "Students enrolled:\n";
        for (auto s : students)
            cout << "- " << s->getName() << " (Roll: " << s->getRoll() << ")\n";
    }
};


// ✅ Now the full Student::showSubjects() definition AFTER Subject is fully defined
void Student::showSubjects() const {
    cout << "\nStudent: " << name << " (Roll: " << roll << ")\n";
    if (subjects.empty()) {
        cout << "No subjects opted yet.\n";
        return;
    }
    cout << "Subjects opted:\n";
    for (auto s : subjects)
        cout << "- " << s->getName() << " (" << s->getCode() << ")\n";
}



// ------------------ MENU DRIVEN MAIN ------------------
int main() {
    vector<Student*> students;
    vector<Subject*> subjects;
    int choice;

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Subject\n";
        cout << "3. Enroll Student in Subject\n";
        cout << "4. Show Subjects of a Student\n";
        cout << "5. Show Students of a Subject\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int roll;
            string name;
            cout << "Enter Roll Number: ";
            cin >> roll;
            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);
            students.push_back(new Student(roll, name));
            cout << "✅ Student added.\n";
        }

        else if (choice == 2) {
            int code;
            string name;
            cout << "Enter Subject Code: ";
            cin >> code;
            cout << "Enter Subject Name: ";
            cin >> ws;
            getline(cin, name);
            subjects.push_back(new Subject(code, name));
            cout << "✅ Subject added.\n";
        }

        else if (choice == 3) {
            int roll, code;
            cout << "Enter Student Roll: ";
            cin >> roll;
            cout << "Enter Subject Code: ";
            cin >> code;

            Student *stu = nullptr;
            Subject *sub = nullptr;

            for (auto s : students)
                if (s->getRoll() == roll) stu = s;

            for (auto s : subjects)
                if (s->getCode() == code) sub = s;

            if (stu && sub) {
                stu->addSubject(sub);
                sub->addStudent(stu);
                cout << "✅ Student enrolled in subject.\n";
            } else {
                cout << "❌ Invalid roll number or subject code!\n";
            }
        }

        else if (choice == 4) {
            int roll;
            cout << "Enter Student Roll: ";
            cin >> roll;

            bool found = false;
            for (auto s : students)
                if (s->getRoll() == roll) {
                    s->showSubjects();
                    found = true;
                }

            if (!found) cout << "❌ Student not found.\n";
        }

        else if (choice == 5) {
            int code;
            cout << "Enter Subject Code: ";
            cin >> code;

            bool found = false;
            for (auto s : subjects)
                if (s->getCode() == code) {
                    s->showStudents();
                    found = true;
                }

            if (!found) cout << "❌ Subject not found.\n";
        }

        else if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
