/*

2. In a library, for each book book-id, serial number (denotes copy number of a
book), title, author, publisher and price are stored. Book-id and serial number
together will be unique identifier for a book. Members are either student or
faculty. Each member has unique member-id. Name, e-mail, address are also to
be stored. For any transaction (book issue or return), members are supposed to
place transactions slip. User will submit member-id, book-id, and serial number
(only for book return). While processing a transaction, check the validity of the
member. While issuing, availability of a copy of the book is to be checked. While
returning a book, it is to be checked whether this copy was issued to the member
or not. A student member can have 2 books issued at a point of time. For faculty
members it is 10. Transaction information is to be stored like date of transaction,
member-id, book-id, serial number, returned or not. An entry is made when
book is issued and updated when the book is returned.
Design the classes and implement. For list consider memory data structure.



Name :- Anubhab Rakshit
Class :- BCSE-II A1
Roll Number:- 002410501029
*/


#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Book class (details)
class Book {
public:
    string bookId;
    int serialNo;
    string title;
    string author;
    string publisher;
    double price;
    bool isIssued;

    Book(string b, int s, string t, string a, string p, double pr)
        : bookId(b), serialNo(s), title(t), author(a), publisher(p), price(pr), isIssued(false) {}
};

//Member Class (contains member details)
class Member {
public:
    string memberId;
    string name;
    string email;
    string address;
    string type; // student or faculty
    int issuedCount;

    Member(string id, string n, string e, string a, string t)
        : memberId(id), name(n), email(e), address(a), type(t), issuedCount(0) {}
};

// Transaction class
class Transaction {
public:
    string date;
    string memberId;
    string bookId;
    int serialNo;
    bool returned;

    Transaction(string d, string m, string b, int s)
        : date(d), memberId(m), bookId(b), serialNo(s), returned(false) {}
};

vector<Book> books; //list of books
vector<Member> members; //list of members
vector<Transaction> transactions; //list of transactions

Member* findMember(string id) {
    for (auto &m : members)
        if (m.memberId == id) return &m;
    return nullptr;
}

Book* findBook(string id, int s) {
    for (auto &b : books)
        if (b.bookId == id && b.serialNo == s) return &b;
    return nullptr;
}

Transaction* findTransaction(string m, string b, int s) { 
    for (auto &t : transactions)
        if (t.memberId == m && t.bookId == b && t.serialNo == s && !t.returned)
            return &t;
    return nullptr;
}

void issueBook() {
    string memberId, bookId, date;
    int serialNo;
    cout << "Enter Member ID: "; cin >> memberId;
    Member* mem = findMember(memberId);
    if (!mem) { cout << "Invalid Member ID!\n"; return; }

    int limit = (mem->type == "student") ? 2 : 10;
    if (mem->issuedCount >= limit) {
        cout << "Issue limit reached!\n";
        return;
    }

    cout << "Enter Book ID: "; cin >> bookId;
    cout << "Enter Serial No: "; cin >> serialNo;
    Book* bk = findBook(bookId, serialNo);
    if (!bk) { cout << "Book not found!\n"; return; }
    if (bk->isIssued) { cout << "Book already issued!\n"; return; }

    cout << "Enter Date: "; cin >> date;
    bk->isIssued = true;
    mem->issuedCount++;
    transactions.push_back(Transaction(date, memberId, bookId, serialNo));
    cout << "Book Issued Successfully!\n";
}

void returnBook() {
    string memberId, bookId, date;
    int serialNo;

    cout << "Enter Member ID: "; cin >> memberId;
    cout << "Enter Book ID: "; cin >> bookId;
    cout << "Enter Serial No: "; cin >> serialNo;

    Member* mem = findMember(memberId);
    if (!mem) { cout << "Invalid Member ID!\n"; return; }

    Book* bk = findBook(bookId, serialNo);
    if (!bk || !bk->isIssued) { cout << "Book not issued!\n"; return; }

    Transaction* tr = findTransaction(memberId, bookId, serialNo);
    if (!tr) { cout << "This book is not issued to this member!\n"; return; }

    cout << "Enter Date: "; cin >> date;
    tr->returned = true;
    bk->isIssued = false;
    mem->issuedCount--;

    cout << "Book Returned Successfully!\n";
}

void addBook() {  //add book function
    string id, title, author, publisher;
    int serialNo;
    double price;

    cout << "Enter Book ID: "; cin >> id;
    cout << "Enter Serial No: "; cin >> serialNo;
    cout << "Enter Title: "; cin >> title;
    cout << "Enter Author: "; cin >> author;
    cout << "Enter Publisher: "; cin >> publisher;
    cout << "Enter Price: "; cin >> price;

    books.push_back(Book(id, serialNo, title, author, publisher, price));
    cout << "Book Added Successfully!\n";
}

void addMember() { //add member function
    string id, name, email, address, type;
    cout << "Enter Member ID: "; cin >> id;
    cout << "Enter Name: "; cin >> name;
    cout << "Enter Email: "; cin >> email;
    cout << "Enter Address: "; cin >> address;
    cout << "Enter Type (student/faculty): "; cin >> type;

    members.push_back(Member(id, name, email, address, type));
    cout << "Member Added Successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\nLIBRARY MENU :-\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 5);

    return 0;
}