#include <iostream>
#include <string> 
using namespace std;

class song {
private:
    string title, artist;
    float duration;

public:
    song *next;
    song() {
        next = NULL;
    }

    void read(string name, string artist_name, float time) {
        title = name;
        artist = artist_name;
        duration = time;
    }

    void display() {
        cout << "Song name: " << title << endl;
        cout << "Artist name: " << artist << endl;
        cout << "Duration: " << duration << endl;
    }

    song* getNext() {
        return next;
    }

    void setNext(song* temp) {
        next = temp;
    }

    string getName() {
        return title;
    }
};

class myPlaylist {
public:
    song* head;
    myPlaylist() {
        head = NULL;
    }

    void addsong(string name, string artist_name, float time) {
        song* nn = new song;
        nn->read(name, artist_name, time);
        if (head == NULL) {
            head = nn;
        } else {
            song* cn;
            for (cn = head; cn->next != NULL; cn = cn->next) {
                // Traverse to the end of the list
            }
            cn->next = nn;
        }
    }

    void displayPlaylist() {
        song* cn;
        for (cn = head; cn != NULL; cn = cn->next) {
            cn->display();
            cout << "--------------" << endl;
        }
    }

    void deleteSong(string value) {
        if (head == NULL) {
            cout << "Playlist is empty.\n";
            return;
        }

        song* temp = head;
        song* prev = NULL;
        if (head->getName() == value) {
            head = head->getNext();
            delete temp;
            return;
        }

        while (temp != NULL && temp->getName() != value) {
            prev = temp;
            temp = temp->getNext();
        }

        if (temp == NULL) {
            cout << "Song not found\n";
            return;
        }

        prev->setNext(temp->getNext());
        delete temp;
    }

    void search(string songName) {
        song* temp = head;
        while (temp) {
            if (temp->getName() == songName) {
                temp->display();
                return;
            }
            temp = temp->getNext();
        }
        cout << "\nSong not found.\n";
    }

    void insertAtHead(string name, string artist_name, float time) {
        song* nn = new song;
        nn->read(name, artist_name, time);
        nn->setNext(head);
        head = nn;
    }

    void insertionAtMid(string afterSongName, string name, string artist_name, float time) {
        song* temp = head;
        while (temp != NULL && temp->getName() != afterSongName) {
            temp = temp->getNext();
        }

        if (temp == NULL) {
            cout << "\nSong not found.\n";
            return;
        } else {
            song* nn = new song;
            nn->read(name, artist_name, time);
            nn->setNext(temp->getNext());
            temp->setNext(nn);
        }
    }
};

int main() {
    myPlaylist s;
    int choice;
    string name, artist_name, songName, afterSongName;
    float duration;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Add Song\n";
        cout << "2. Display Playlist\n";
        cout << "3. Delete Song\n";
        cout << "4. Search Song\n";
        cout << "5. Insert at Head\n";
        cout << "6. Insert at Mid\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                cin >> name; // Using >> for single-word input
                cout << "Enter artist name: ";
                cin >> artist_name; // Using >> for single-word input
                cout << "Enter duration: ";
                cin >> duration;
                s.addsong(name, artist_name, duration);
                break;

            case 2:
                s.displayPlaylist();
                break;

            case 3:
                cout << "Enter song title to delete: ";
                cin >> songName; // Using >> for single-word input
                s.deleteSong(songName);
                break;

            case 4:
                cout << "Enter song title to search: ";
                cin >> songName; // Using >> for single-word input
                s.search(songName);
                break;

            case 5:
                cout << "Enter song title: ";
                cin >> name; // Using >> for single-word input
                cout << "Enter artist name: ";
                cin >> artist_name; // Using >> for single-word input
                cout << "Enter duration: ";
                cin >> duration;
                s.insertAtHead(name, artist_name, duration);
                break;

            case 6:
                cout << "Enter song title after which to insert: ";
                cin >> afterSongName; // Using >> for single-word input
                cout << "Enter new song title: ";
                cin >> name; // Using >> for single-word input
                cout << "Enter artist name: ";
                cin >> artist_name; // Using >> for single-word input
                cout << "Enter duration: ";
                cin >> duration;
                s.insertionAtMid(afterSongName, name, artist_name, duration);
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}