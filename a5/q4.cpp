#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -------------------------------------
// Base Class : Cricketer
// -------------------------------------
class Cricketer {
protected:
    string name, dob;
    int matches;
public:
    Cricketer() {}
    Cricketer(string n, string d, int m) : name(n), dob(d), matches(m) {}

    virtual void input() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Date of Birth (dd-mm-yyyy): ";
        getline(cin, dob);
        cout << "Enter Matches Played: ";
        cin >> matches;
    }

    virtual void showDetails() {
        cout << "\nName: " << name;
        cout << "\nDOB: " << dob;
        cout << "\nMatches: " << matches << endl;
    }

    virtual string getType() { return "Cricketer"; }

    virtual ~Cricketer() {}
};

// -------------------------------------
// Derived Class : Bowler
// -------------------------------------
class Bowler : virtual public Cricketer {
protected:
    int wickets;
    float economy;
public:
    Bowler() {}
    void input() override {
        Cricketer::input();
        cout << "Enter Wickets Taken: ";
        cin >> wickets;
        cout << "Enter Economy Rate: ";
        cin >> economy;
    }
    void showDetails() override {
        cout << "\n--- Bowler Details ---\n";
        Cricketer::showDetails();
        cout << "Wickets Taken: " << wickets;
        cout << "\nEconomy Rate: " << economy << endl;
    }
    string getType() override { return "Bowler"; }

    int getWickets() { return wickets; }
};

// -------------------------------------
// Derived Class : Batsman
// -------------------------------------
class Batsman : virtual public Cricketer {
protected:
    int runs;
    float average;
public:
    Batsman() {}
    void input() override {
        Cricketer::input();
        cout << "Enter Total Runs: ";
        cin >> runs;
        cout << "Enter Batting Average: ";
        cin >> average;
    }
    void showDetails() override {
        cout << "\n--- Batsman Details ---\n";
        Cricketer::showDetails();
        cout << "Total Runs: " << runs;
        cout << "\nBatting Average: " << average << endl;
    }
    string getType() override { return "Batsman"; }

    int getRuns() { return runs; }
};

// -------------------------------------
// Multiple Inheritance : AllRounder
// -------------------------------------
class AllRounder : public Bowler, public Batsman {
public:
    void input() override {
        cout << "\n--- Enter All-Rounder Details ---\n";
        Cricketer::input();
        cout << "Enter Wickets Taken: ";
        cin >> wickets;
        cout << "Enter Economy Rate: ";
        cin >> economy;
        cout << "Enter Total Runs: ";
        cin >> runs;
        cout << "Enter Batting Average: ";
        cin >> average;
    }

    void showDetails() override {
        cout << "\n--- All-Rounder Details ---\n";
        Cricketer::showDetails();
        cout << "Wickets Taken: " << wickets;
        cout << "\nEconomy Rate: " << economy;
        cout << "\nTotal Runs: " << runs;
        cout << "\nBatting Average: " << average << endl;
    }

    string getType() override { return "All-Rounder"; }
};

// -------------------------------------
// Class : Double Wicket Pair
// -------------------------------------
class DoubleWicketPair {
    Bowler* bowler;
    Batsman* batsman;
public:
    DoubleWicketPair(Bowler* b, Batsman* bt) : bowler(b), batsman(bt) {}
    void showPair() {
        cout << "\n### DOUBLE WICKET PAIR ###\n";
        cout << "\nBowler:";
        bowler->showDetails();
        cout << "\nBatsman:";
        batsman->showDetails();
    }
};

// -------------------------------------
// MAIN (Menu-Driven)
// -------------------------------------
int main() {
    vector<Cricketer*> players;
    int choice;

    while (true) {
        cout << "\n\n===== CRICKETER MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Bowler\n";
        cout << "2. Add Batsman\n";
        cout << "3. Add All-Rounder\n";
        cout << "4. Show All Players\n";
        cout << "5. Create Double Wicket Pair\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Cricketer* c = new Bowler();
            c->input();
            players.push_back(c);
            cout << "\nBowler Added Successfully.\n";

        } else if (choice == 2) {
            Cricketer* c = new Batsman();
            c->input();
            players.push_back(c);
            cout << "\nBatsman Added Successfully.\n";

        } else if (choice == 3) {
            Cricketer* c = new AllRounder();
            c->input();
            players.push_back(c);
            cout << "\nAll-Rounder Added Successfully.\n";

        } else if (choice == 4) {
            cout << "\n----- ALL PLAYERS -----\n";
            for (size_t i = 0; i < players.size(); i++) {
                cout << "\nPlayer ID: " << i;
                cout << "\nType: " << players[i]->getType();
                players[i]->showDetails();
                cout << "----------------------\n";
            }

        } else if (choice == 5) {
            int bID, btID;

            cout << "\nEnter Bowler ID: ";
            cin >> bID;
            cout << "Enter Batsman ID: ";
            cin >> btID;

            if (bID >= players.size() || btID >= players.size()) {
                cout << "Invalid IDs!\n";
                continue;
            }

            Bowler* b = dynamic_cast<Bowler*>(players[bID]);
            Batsman* bt = dynamic_cast<Batsman*>(players[btID]);

            if (!b || !bt) {
                cout << "\nInvalid! Must select a bowler and a batsman.\n";
                continue;
            }

            DoubleWicketPair pair(b, bt);
            pair.showPair();

        } else if (choice == 6) {
            cout << "\nExiting...\n";
            break;
        } else {
            cout << "\nInvalid Choice!\n";
        }
    }

    // Free memory
    for (Cricketer* c : players) delete c;

    return 0;
}
