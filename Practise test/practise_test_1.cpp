/*In a railway station, there are multiple customers trying to buy train tickets. However, there are limited ticketing counters or booking agents, so customers need to wait their turn to be served. Construct a queue using an Singly linked list to serve customers. Provide following options
Arrival of customer at ticketing system
Serve customer for ticket booking
Display all waiting customers*/

#include <iostream>
#include <string>

using namespace std;

// Node class representing each customer in the queue
class Node {
public:
    string customerName;
    Node* next;

    Node(string name) {
        customerName = name;
        next = nullptr;
    }
};

// Queue class using a singly linked list to manage the customers
class TicketQueue {
private:
    Node* front;  // Front of the queue
    Node* rear;   // Rear of the queue

public:
    // Constructor to initialize an empty queue
    TicketQueue() {
        front = nullptr;
        rear = nullptr;
    }

    // Function to add a customer to the queue
    void enqueue(string name) {
        Node* newCustomer = new Node(name);
        if (rear == nullptr) { // If the queue is empty
            front = rear = newCustomer;
        } else {
            rear->next = newCustomer;
            rear = newCustomer;
        }
        cout << name << " has arrived at the ticketing system." << endl;
    }

    // Function to serve the customer at the front of the queue
    void serveCustomer() {
        if (front == nullptr) {
            cout << "No customers are waiting." << endl;
            return;
        }

        Node* temp = front;
        cout << "Serving " << front->customerName << " for ticket booking." << endl;
        front = front->next;

        if (front == nullptr) { // If the queue becomes empty after serving
            rear = nullptr;
        }

        delete temp; // Free the memory of the served customer
    }

    // Function to display all waiting customers
    void displayWaitingCustomers() {
        if (front == nullptr) {
            cout << "No customers are waiting." << endl;
            return;
        }

        cout << "Waiting customers: " << endl;
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->customerName << endl;
            temp = temp->next;
        }
    }
};

int main() {
    TicketQueue queue;
    int choice;
    string customerName;
    do {
        cout << "\n1. Arrival of customer at ticketing system" << endl;
        cout << "2. Serve customer for ticket booking" << endl;
        cout << "3. Display all waiting customers" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin >> customerName;
                queue.enqueue(customerName);
                break;
            case 2:
                queue.serveCustomer();
                break;
            case 3:
                queue.displayWaitingCustomers();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
    return 0;
}