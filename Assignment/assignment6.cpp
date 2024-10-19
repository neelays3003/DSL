#include <iostream>
using namespace std;

class Node {
public:
    int coefficient;
    int exponent;
    Node* next;

    Node(int coeff, int exp) {
        coefficient = coeff;
        exponent = exp;
        next = nullptr;
    }
};

class Polynomial {
private:
    Node* head;

public:
    Polynomial() {
        head = NULL;
    }

    void insertTerm(int coefficient, int exponent) {
        Node* newNode = new Node(coefficient, exponent);
        if (!head || head->exponent < exponent) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            Node* previous = nullptr;

            while (current && current->exponent >= exponent) {
                if (current->exponent == exponent) {
                    current->coefficient += coefficient;
                    delete newNode; 
                    return;
                }
                previous = current;
                current = current->next;
            }

            previous->next = newNode;
            newNode->next = current;
        }
    }

    Polynomial add(Polynomial other) {
        Polynomial result;
        Node* p1 = head;
        Node* p2 = other.head;

        while (p1 || p2) {
            if (p1 && (!p2 || p1->exponent > p2->exponent)) {
                result.insertTerm(p1->coefficient, p1->exponent);
                p1 = p1->next;
            } else if (p2 && (!p1 || p2->exponent > p1->exponent)) {
                result.insertTerm(p2->coefficient, p2->exponent);
                p2 = p2->next;
            } else {
                result.insertTerm(p1->coefficient + p2->coefficient, p1->exponent);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        return result;
    }

    void display() {
        Node* current = head;
        while (current) {
            if (current->coefficient > 0 && current != head) {
                cout << "+";
            }
            cout << current->coefficient << "x^" << current->exponent;
            current = current->next;
        }
        cout << endl;
    }

    ~Polynomial() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    Polynomial p1, p2;
    int choice, coeff, exp;

    do {
        cout << "Menu:\n";
        cout << "1. Insert Term into Polynomial 1\n";
        cout << "2. Insert Term into Polynomial 2\n";
        cout << "3. Display Polynomial 1\n";
        cout << "4. Display Polynomial 2\n";
        cout << "5. Add Polynomials\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter coefficient: ";
                cin >> coeff;
                cout << "Enter exponent: ";
                cin >> exp;
                p1.insertTerm(coeff, exp);
                break;
            case 2:
                cout << "Enter coefficient: ";
                cin >> coeff;
                cout << "Enter exponent: ";
                cin >> exp;
                p2.insertTerm(coeff, exp);
                break;
            case 3:
                cout << "Polynomial 1: ";
                p1.display();
                break;
            case 4:
                cout << "Polynomial 2: ";
                p2.display();
                break;
            case 5: {
                Polynomial sum = p1.add(p2);
                cout << "Sum: ";
                sum.display();
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}