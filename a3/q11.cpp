#include <iostream>

/*
Create a class for linked list. Consider a seperate class NODE for basic node activities 
and use it in class for linked list

Name:- Anubhab Rakshit
Class:- BCSE-II A1
Roll No:- 002410501029
*/
#include<iostream>
#include<string>

using namespace std;

class Node {
public:
    int data;    
    Node* next;
    Node(int val) : 
    data(val), next(nullptr) {}
};


class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        Node* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next; 
            delete current;        
            current = nextNode;      
        }
        head = nullptr;
        cout << "\nLinkedList destroyed and memory freed." << endl;
    }

  
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        cout << "Inserted " << val << " at head." << endl;
    }

   
    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            cout << "Inserted " << val << " at tail (list was empty)." << endl;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        cout << "Inserted " << val << " at tail." << endl;
    }

  
    void printList() const {
        Node* current = head;
        if (current == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        cout << "List (int): ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }
};


int main() {

    LinkedList my_list;
    while(1){
        cout<<"\n MENU:- \n 1. Insert At Head \n 2. Insert at Tail \n 3. Display \n 4.Exit"<<endl;
        cout<<"Enter your choice :- ";
        int ch;
        cin>>ch;
        int data;
        switch(ch){
            case 1:
            cout<<"Enter your value :- ";
            cin>>data;
            my_list.insertAtHead(data);
            break;

            case 2:
            cout<<"Enter your value :- ";
            cin>>data;
            my_list.insertAtTail(data);

            case 3:
            my_list.printList();
            break;

            case 4:
            exit(0);
        }
    }
    return 0;
}