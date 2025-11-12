#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// =============================================================
// BOOK CLASS
// =============================================================
class Book {
public:
    int bookId, serialNo;
    string title, author, publisher;
    float price;
    bool isIssued;

    Book() {}
    Book(int id, int sn, string t, string a, string p, float pr)
        : bookId(id), serialNo(sn), title(t), author(a),
          publisher(p), price(pr), isIssued(false) {}

    void show() {
        cout << "\nBook ID: " << bookId
             << "\nSerial No: " << serialNo
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nPublisher: " << publisher
             << "\nPrice: " << price
             << "\nStatus: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

// =============================================================
// MEMBER (BASE CLASS)
// =============================================================
class Member {
protected:
    string name, email, address;

public:
    int memberId;
    vector<pair<int,int>> issuedBooks; // (bookId, serialNo)

    Member() {}
    Member(int id, string n, string e, string a)
        : memberId(id), name(n), email(e), address(a) {}

    virtual int maxBooksAllowed() = 0;

    bool canIssue() {
        return issuedBooks.size() < maxBooksAllowed();
    }

    void show() {
        cout << "\nMember ID: " << memberId
             << "\nName: " << name
             << "\nEmail: " << email
             << "\nAddress: " << address
             << "\nBooks issued: " << issuedBooks.size() << endl;
    }

    virtual string type() = 0;

    virtual ~Member() {}
};

// =============================================================
// STUDENT MEMBER
// =============================================================
class Student : public Member {
public:
    Student(int id, string n, string e, string a) : Member(id, n, e, a) {}

    int maxBooksAllowed() override { return 2; }
    string type() override { return "Student"; }
};

// =============================================================
// FACULTY MEMBER
// =============================================================
class Faculty : public Member {
public:
    Faculty(int id, string n, string e, string a) : Member(id, n, e, a) {}

    int maxBooksAllowed() override { return 10; }
    string type() override { return "Faculty"; }
};

// =============================================================
// TRANSACTION CLASS
// =============================================================
class Transaction {
public:
    int memberId, bookId, serialNo;
    string date;
    bool returned;

    Transaction(int mid, int bid, int sn, string d, bool r)
        : memberId(mid), bookId(bid), serialNo(sn), date(d), returned(r) {}

    void saveToFile() {
        ofstream fout("transactions.txt", ios::app);
        fout << date << " "
             << memberId << " "
             << bookId << " "
             << serialNo << " "
             << returned << endl;
        fout.close();
    }
};

// =============================================================
// LIBRARY CLASS
// =============================================================
class Library {
    vector<Book> books;
    vector<Member*> members;

public:
    void addBook() {
        int id, sn;
        string t, a, p;
        float pr;

        cout << "Book ID: "; cin >> id;
        cout << "Serial No (copy no): "; cin >> sn;
        cin.ignore();
        cout << "Title: "; getline(cin, t);
        cout << "Author: "; getline(cin, a);
        cout << "Publisher: "; getline(cin, p);
        cout << "Price: "; cin >> pr;

        books.emplace_back(id, sn, t, a, p, pr);
        cout << "\nBook added.\n";
    }

    void addMember() {
        int type, id;
        string n, e, a;

        cout << "1. Student\n2. Faculty\nEnter member type: ";
        cin >> type;

        cout << "Member ID: "; cin >> id;
        cin.ignore();
        cout << "Name: "; getline(cin, n);
        cout << "Email: "; getline(cin, e);
        cout << "Address: "; getline(cin, a);

        if (type == 1)
            members.push_back(new Student(id, n, e, a));
        else
            members.push_back(new Faculty(id, n, e, a));

        cout << "\nMember added.\n";
    }

    Member* findMember(int id) {
        for (auto* m : members)
            if (m->memberId == id)
                return m;
        return nullptr;
    }

    Book* findBook(int id, int sn) {
        for (auto &b : books)
            if (b.bookId == id && b.serialNo == sn)
                return &b;
        return nullptr;
    }

    void issueBook() {
        int mid, bid;
        cout << "Enter Member ID: "; cin >> mid;
        Member* m = findMember(mid);
        if (!m) {
            cout << "Invalid member!\n";
            return;
        }

        cout << "Enter Book ID: "; cin >> bid;

        // find available copy
        Book* available = nullptr;
        for (auto &b : books) {
            if (b.bookId == bid && !b.isIssued) {
                available = &b;
                break;
            }
        }

        if (!available) {
            cout << "No available copy!\n";
            return;
        }

        if (!m->canIssue()) {
            cout << "Issuing limit exceeded!\n";
            return;
        }

        available->isIssued = true;
        m->issuedBooks.push_back({available->bookId, available->serialNo});

        Transaction t(mid, available->bookId, available->serialNo, "today", false);
        t.saveToFile();

        cout << "\nBook issued successfully.\n";
    }

    void returnBook() {
        int mid, bid, sn;
        cout << "Enter Member ID: "; cin >> mid;
        cout << "Book ID: "; cin >> bid;
        cout << "Serial No: "; cin >> sn;

        Member* m = findMember(mid);
        if (!m) {
            cout << "Invalid member!\n";
            return;
        }

        Book* b = findBook(bid, sn);
        if (!b) {
            cout << "Invalid book copy!\n";
            return;
        }

        // check if issued to this member
        bool found = false;
        for (auto it = m->issuedBooks.begin(); it != m->issuedBooks.end(); ++it) {
            if (it->first == bid && it->second == sn) {
                m->issuedBooks.erase(it);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "This copy was not issued to this member!\n";
            return;
        }

        b->isIssued = false;

        Transaction t(mid, bid, sn, "today", true);
        t.saveToFile();

        cout << "\nBook returned successfully.\n";
    }

    void showBooks() {
        for (auto &b : books)
            b.show();
    }

    void showMembers() {
        for (auto* m : members)
            m->show();
    }
};

// =============================================================
// MAIN MENU
// =============================================================
int main() {
    Library L;
    int ch;

    while (true) {
        cout << "\n===== LIBRARY MENU =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Show Books\n";
        cout << "6. Show Members\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: L.addBook(); break;
            case 2: L.addMember(); break;
            case 3: L.issueBook(); break;
            case 4: L.returnBook(); break;
            case 5: L.showBooks(); break;
            case 6: L.showMembers(); break;
            case 7: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}


