#include <iostream>
#include <string>
using namespace std;

// Node class representing each party in the queue
class Node {
public:
    string partyName;
    int partySize;
    Node* next;

    Node(string name, int size) : partyName(name), partySize(size), next(NULL) {}
};

// Queue class implemented using a linked list
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = NULL;
        rear = NULL;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == NULL;
    }

    // Add a party to the waitlist (enqueue operation)
    void addParty(string name, int size) {
        Node* newNode = new Node(name, size);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Party " << name << " of size " << size << " added to the waitlist.\n";
    }

    // Seat the first party from the waitlist (dequeue operation)
    void seatParty() {
        if (isEmpty()) {
            cout << "No parties are waiting to be seated.\n";
        } else {
            Node* temp = front;
            cout << "Seating party " << temp->partyName << " of size " << temp->partySize << ".\n";
            front = front->next;
            if (front == NULL) rear = NULL; // If the queue is empty after seating
            delete temp;
        }
    }

    // Display the waitlist
    void displayWaitlist() {
        if (isEmpty()) {
            cout << "The waitlist is currently empty.\n";
        } else {
            cout << "Current Waitlist:\n";
            Node* temp = front;
            while (temp != NULL) {
                cout << "Party Name: " << temp->partyName << ", Party Size: " << temp->partySize << "\n";
                temp = temp->next;
            }
        }
    }
};

// Main function to provide a menu-driven interface for the restaurant waitlist
int main() {
    Queue waitlist;
    int choice;
    do {
        cout << "\nMenu\n";
        cout << "1. Add Party to Waitlist\n";
        cout << "2. Seat Party\n";
        cout << "3. Display Waitlist\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int size;
                cout << "Enter party name: ";
                cin >> name;
                cout << "Enter party size: ";
                cin >> size;
                waitlist.addParty(name, size);
                break;
            }
            case 2:
                waitlist.seatParty();
                break;
            case 3:
                waitlist.displayWaitlist();
                break;
            case 4:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
