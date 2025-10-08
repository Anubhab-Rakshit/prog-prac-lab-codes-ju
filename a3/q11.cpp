#include <iostream>


class Node {
public:
    int data;    
    Node* next;


    Node(int val) : data(val), next(nullptr) {}
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
        std::cout << "\nLinkedList destroyed and memory freed." << std::endl;
    }

  
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        std::cout << "Inserted " << val << " at head." << std::endl;
    }

   
    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            std::cout << "Inserted " << val << " at tail (list was empty)." << std::endl;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        std::cout << "Inserted " << val << " at tail." << std::endl;
    }

  
    void printList() const {
        Node* current = head;
        if (current == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        std::cout << "List (int): ";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};


int main() {

    LinkedList my_list;


    my_list.insertAtHead(5);
    my_list.insertAtTail(20);
    my_list.insertAtHead(1);
    my_list.insertAtTail(50);

    my_list.printList();


    return 0;
}
