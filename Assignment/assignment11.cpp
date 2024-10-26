#include <iostream>
#include <string>

using namespace std;

// EmployeeNode class to represent each entry in the hash table
class EmployeeNode {
public:
    int id;                 // Employee ID
    string name;            // Employee Name
    EmployeeNode* next;     // Pointer to the next node in case of collision

    // Constructor
    EmployeeNode(int empId, string empName) : id(empId), name(empName), next(nullptr) {}
};

// HashTable class to manage the employee entries
class HashTable {
private:
    EmployeeNode** table;   // Array of pointers to EmployeeNode (for linked lists)
    int capacity;

    // Hash function
    int hashFunction(int id) {
        return id % capacity;
    }

public:
    // Constructor
    HashTable(int size) : capacity(size) {
        table = new EmployeeNode*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;  // Initialize all buckets as empty
        }
    }

    // Destructor to free memory
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            EmployeeNode* current = table[i];
            while (current != nullptr) {
                EmployeeNode* temp = current;
                current = current->next;
                delete temp;  // Free each node
            }
        }
        delete[] table; // Free the array of pointers
    }

    // Insert an employee into the hash table
    void insert(int id, string name) {
        int index = hashFunction(id);
        EmployeeNode* newNode = new EmployeeNode(id, name);

        // Insert at the beginning of the linked list for the bucket
        newNode->next = table[index];
        table[index] = newNode;
        cout << "Inserted Employee: " << name << " with ID: " << id << endl;
    }

    // Lookup an employee by ID
    EmployeeNode* lookup(int id) {
        int index = hashFunction(id);
        EmployeeNode* current = table[index];
        while (current != nullptr) {
            if (current->id == id) {
                return current;  // Employee found
            }
            current = current->next;
        }
        return nullptr;  // Employee not found
    }

    // Remove an employee by ID
    bool remove(int id) {
        int index = hashFunction(id);
        EmployeeNode* current = table[index];
        EmployeeNode* prev = nullptr;

        while (current != nullptr) {
            if (current->id == id) {
                if (prev == nullptr) {
                    table[index] = current->next;  // Head node is removed
                } else {
                    prev->next = current->next;    // Bypass the node to be removed
                }
                delete current;  // Free memory
                cout << "Removed Employee with ID: " << id << endl;
                return true;
            }
            prev = current;
            current = current->next;
        }
        cout << "Employee with ID " << id << " not found." << endl;
        return false;
    }

    // Display all employees
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            EmployeeNode* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->id << ", " << current->name << "] ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main() {
    int capacity;
    cout << "Enter the hash table capacity: ";
    cin >> capacity;

    HashTable ht(capacity);  // Create hash table with user-defined capacity

    int choice, id;
    string name;

    do {
        cout << "\nHash Table Menu:\n";
        cout << "1. Insert Employee\n";
        cout << "2. Lookup Employee\n";
        cout << "3. Remove Employee\n";
        cout << "4. Display All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Insert Employee
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter Employee Name: ";
                cin.ignore();  // Clear the input buffer
                getline(cin, name);
                ht.insert(id, name);
                break;

            case 2: // Lookup Employee
                cout << "Enter Employee ID to lookup: ";
                cin >> id;
                EmployeeNode* emp;
                emp = ht.lookup(id);
                if (emp) {
                    cout << "Employee Found - ID: " << emp->id << ", Name: " << emp->name << endl;
                } else {
                    cout << "Employee with ID " << id << " not found." << endl;
                }
                break;

            case 3: // Remove Employee
                cout << "Enter Employee ID to remove: ";
                cin >> id;
                if (!ht.remove(id)) {
                    cout << "Employee with ID " << id << " not found." << endl;
                }
                break;

            case 4: // Display All Employees
                ht.display();
                break;

            case 5: // Exit
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
