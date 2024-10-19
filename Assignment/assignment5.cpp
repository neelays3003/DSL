#include <iostream>
using namespace std;

class route {
    string source, dest;
    int distance;
    route *next;

public:
    route() {
        next = NULL;
    }

    void read() {
        cout << "Enter Source: ";
        cin >> source;
        cout << "Enter Destination: ";
        cin >> dest;
        cout << "Enter Distance: ";
        cin >> distance;
    }

    void display() {
        cout << "Source: " << source << "  ";
        cout << "Destination: " << dest << "  ";
        cout << "Distance: " << distance << endl;
    }

    friend class route_nav;
};

class route_nav {
public:
    route *tail;
    route_nav() {
        tail = NULL;
    }

    void addrouteatend() {
        route *ch = new route;
        ch->read();
        if (tail == NULL) {
            tail = ch;
            tail->next = ch;
        } else {
            ch->next = tail->next;
            tail->next = ch;
            tail = ch;
        }
    }

    void addrouteatstart() {
        route *ch = new route;
        ch->read();
        if (tail == NULL) {
            tail = ch;
            tail->next = ch;
        } else {
            ch->next = tail->next;
            tail->next = ch;
        }
    }

    void displaydata() {
        if (!tail) return;
        route *ch;
        for (ch = tail->next; ch != tail; ch = ch->next) {
            ch->display();
        }
        ch->display();
    }

    void deleteroute() {
        route *p = tail;
        route *t = tail->next;
        string src, desti;
        cout << "Enter source: ";
        cin >> src;
        cout << "Enter destination: ";
        cin >> desti;

        do {
            if (t->source == src && t->dest == desti) {
                if (t == tail) {
                    if (tail == tail->next) {
                        delete t;
                        tail = nullptr;
                        return;
                    } else {
                        p->next = t->next;
                        tail = p;
                        delete t;
                        return;
                    }
                } else {
                    p->next = t->next;
                    delete t;
                    return;
                }
            } else {
                p = t;
                t = t->next;
            }
        } while (t != tail->next);
        
        cout << "Route Does Not Exist" << endl;
    }
};

int main() {
    route_nav s1;
    int n = 1;
    while (n != 0) {
        cout << "1. Adding at end" << endl;
        cout << "2. Adding at first" << endl;
        cout << "3. Display data" << endl;
        cout << "4. Delete route" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> n;

        if (n == 1) {
            s1.addrouteatend();
        } else if (n == 2) {
            s1.addrouteatstart();
        } else if (n == 3) {
            s1.displaydata();
        } else if (n == 4) {
            s1.deleteroute();
        } else {
            n = 0;
        }
    }
    return 0;
}