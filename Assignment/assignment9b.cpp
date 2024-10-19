#include <iostream>
#include <string>
using namespace std;

// Node class representing each customer in the queue
class Node {
public:
    string customerName;
    Node* next;

    Node(string name) : customerName(name), next(NULL) {}
};

// Circular Queue class using a circular linked list
class CircularQueue {
private:
    Node* front;
    Node* rear;
    bool isClosed; // Flag to check if the checkout counter is closed

public:
    CircularQueue() {
        front = rear = NULL;
        isClosed = false;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == NULL;
    }

    // Add a customer to the circular queue
    void customerArrival(string name) {
        if (isClosed) {
            cout << "\033[37m" << "Checkout counter is closed. No more customers can be added.\n" << "\033[0m";
            return;
        }

        Node* newNode = new Node(name);

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
            rear->next = front; // Circular link
        } else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front; // Maintain circular link
        }

        cout << "\033[37m" << "Customer " << name << " added to the queue.\n" << "\033[0m";
    }

    // Remove a customer from the front of the queue
    void customerCheckout() {
        if (isEmpty()) {
            cout << "\033[37m" << "No customers are in the queue.\n" << "\033[0m";
            return;
        }

        // If there is only one customer in the queue
        if (front == rear) {
            cout << "\033[37m" << "Customer " << front->customerName << " has checked out.\n" << "\033[0m";
            delete front;
            front = rear = NULL; // Queue is now empty
        } else {
            Node* temp = front;
            cout << "\033[37m" << "Customer " << temp->customerName << " has checked out.\n" << "\033[0m";
            front = front->next;
            rear->next = front; // Maintain circular link
            delete temp;
        }
    }

    // Close the checkout counter (no more customers can be added)
    void closeCheckoutCounter() {
        isClosed = true;
        cout << "\033[37m" << "The checkout counter is now closed. No more customers can arrive.\n" << "\033[0m";
    }

    // Display all customers currently in the queue
    void viewCustomers() {
        if (isEmpty()) {
            cout << "\033[37m" << "No customers are in the queue.\n" << "\033[0m";
            return;
        }

        Node* temp = front;
        cout << "\033[37m" << "Customers in the queue:\n";
        do {
            cout << temp->customerName << "\n";
            temp = temp->next;
        } while (temp != front); // Stop when we complete the circle
        cout << "\033[0m"; // Reset color
    }
};

// Main function to provide a menu-driven interface for the supermarket checkout system
int main() {
    CircularQueue checkoutQueue;
    int choice;
    do {
        cout << "\033[37m" << "\nMenu\n";
        cout << "1. Customer Arrival\n";
        cout << "2. Customer Checkout\n";
        cout << "3. Close Checkout Counter\n";
        cout << "4. View Customers\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                cout << "Enter customer name: ";
                cin >> name;
                checkoutQueue.customerArrival(name);
                break;
            }
            case 2:
                checkoutQueue.customerCheckout();
                break;
            case 3:
                checkoutQueue.closeCheckoutCounter();
                break;
            case 4:
                checkoutQueue.viewCustomers();
                break;
            case 5:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
