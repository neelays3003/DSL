#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node* prev;
    Node* next;

    Node(char c) {
        data = c;
        prev = NULL;
        next = NULL;
    }
};

class TextEditor {
private:
    Node* head;
    Node* tail;
    Node* cursor;

public:
    TextEditor() {
        head = NULL;
        tail = NULL;
        cursor = NULL;
    }

    void insertText(string text) {
        for (char c : text) {
            Node* newNode = new Node(c);
            if (!head) {
                head = tail = cursor = newNode;
            } else {
                if (cursor) {
                    newNode->prev = cursor;
                    newNode->next = cursor->next;
                    if (cursor->next) {
                        cursor->next->prev = newNode;
                    }
                    cursor->next = newNode;
                    cursor = newNode;
                } else {
                    newNode->prev = tail;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }

    void deleteText(int numChars) {
        while (numChars > 0 && cursor) {
            Node* toDelete = cursor;
            if (cursor->prev) {
                cursor->prev->next = cursor->next;
            } else {
                head = cursor->next;
            }
            if (cursor->next) {
                cursor->next->prev = cursor->prev;
            } else {
                tail = cursor->prev;
            }
            cursor = cursor->prev;
            delete toDelete;
            numChars--;
        }
    }

    void displayText() {
        Node* current = head;
        while (current) {
            cout << current->data;
            current = current->next;
        }
        cout << endl;
    }

    void searchText(string substring) {
        Node* current = head;
        int index = 0;
        bool found = false;

        while (current) {
            Node* temp = current;
            int matchIndex = 0;

            while (temp && matchIndex < substring.length() && temp->data == substring[matchIndex]) {
                temp = temp->next;
                matchIndex++;
            }

            if (matchIndex == substring.length()) {
                cout << "Found at index: " << index << endl;
                found = true;
            }

            current = current->next;
            index++;
        }

        if (!found) {
            cout << "Not found" << endl;
        }
    }

    void printReverse() {
        Node* current = tail;
        while (current) {
            cout << current->data;
            current = current->prev;
        }
        cout << endl;
    }

    ~TextEditor() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TextEditor editor;
    int choice;
    string text;
    int numChars;

    do {
        cout << "Text Editor Menu:\n";
        cout << "1. Insert Text\n";
        cout << "2. Delete Text\n";
        cout << "3. Display Text\n";
        cout << "4. Search Text\n";
        cout << "5. Print Reverse Text\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter text to insert: ";
                cin >> text; // Use >> for single word input
                editor.insertText(text);
                break;
            case 2:
                cout << "Enter number of characters to delete: ";
                cin >> numChars;
                editor.deleteText(numChars);
                break;
            case 3:
                cout << "Current text: ";
                editor.displayText();
                break;
            case 4:
                cout << "Enter substring to search: ";
                cin >> text; // Use >> for single word input
                editor.searchText(text);
                break;
            case 5:
                cout << "Reverse text: ";
                editor.printReverse();
                break;
            case 6:
                cout << "Exiting the text editor." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
}
