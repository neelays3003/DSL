#include <iostream>
using namespace std;

class webpage {
    string site;
public:
    webpage *next;
    webpage() {
        next = NULL;
    }

    void read() {
        cout << "Enter site: ";
        cin >> site;
    }

    void display() {
        cout << site;
    }
};

class BrowserHistory {
    webpage *top;
public:
    BrowserHistory() {
        top = NULL;
    }
    
    void addNewPage() {
        webpage *nn = new webpage();
        nn->read();
        nn->next = top;
        top = nn;
    }
    
    void navigateBack() {
        if (isEmpty()) {
            cout << "No previous site." << endl;
            return;
        }
        webpage *temp = top;
        top = top->next;
        temp->display();
        cout << " has been navigated back." << endl;
        delete temp;
    }

    void showCurrentSite() {
        if (isEmpty()) {
            cout << "No sites to show." << endl;
            return;
        }
        top->display();
        cout << endl;
    }

    bool isEmpty() {
        return top == NULL;
    }
};

int main() {
    BrowserHistory history;
    int choice;
    do {
        cout << "1. Add new page." << endl;
        cout << "2. Navigate to last page." << endl;
        cout << "3. Show current page." << endl;
        cout << "4. Check history is empty or not." << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                history.addNewPage();
                break;
            case 2:
                history.navigateBack();
                break;
            case 3:
                history.showCurrentSite();
                break;
            case 4:
                if (history.isEmpty()) {
                    cout << "History is empty." << endl;
                } else {
                    cout << "History is not empty." << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
    return 0;
}