#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Forward declaration of LibraryManagementSystem class
class LibraryManagementSystem;

// Class representing a book in the library
class Book {
private:
    string title;  // Title of the book
    string author; // Author of the book
    string ISBN;   // ISBN of the book
public:
    Book* next;    // Pointer to the next book in the stack

    // Function to get book details from user input
    void getdata() {
        cout << "\nEnter book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, ISBN);
        cout << endl;
    }

    // Function to display book details
    void display() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << endl;
    }

    // Function to save book details to file
    void saveToFile(ofstream& outFile) const {
        outFile << title << '\n' << author << '\n' << ISBN << '\n';
    }

    // Function to load book details from file
    void loadFromFile(ifstream& inFile) {
        getline(inFile, title);
        getline(inFile, author);
        getline(inFile, ISBN);
    }

    // Granting friendship to LibraryManagementSystem class to access private members
    friend class LibraryManagementSystem;
};

// Class representing a borrowed book
class BorrowedBook {
public:
    string studentName;  // Name of the student borrowing the book
    string bookTitle;    // Title of the borrowed book
    string borrowDate;   // Date the book was borrowed
    string returnDate;   // Due date for returning the book
    string studentPRN;   // Student PRN (Permanent Registration Number)
    string libraryCardNo; // Library card number
    BorrowedBook* next;  // Pointer to the next borrowed book

    // Function to get borrowed book details from user input
    void getdata() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter PRN: ";
        getline(cin, studentPRN);
        cout << "Enter library card number: ";
        getline(cin, libraryCardNo);
        cout << "Enter borrow date (dd-mm-yyyy): ";
        getline(cin, borrowDate);
        cout << "Return the book after exact 20 days.\n";
    }

    // Function to display borrowed book details
    void display() const {
        cout << "Borrowed Book: " << bookTitle << " by " << studentName
             << " (PRN: " << studentPRN << ", Library Card: " << libraryCardNo << ")"
             << " (Borrowed on: " << borrowDate << ", Return by: " << returnDate << ")" << endl;
    }

    // Function to save borrowed book details to file
    void saveToFile(ofstream& outFile) const {
        outFile << studentName << '\n' << bookTitle << '\n' << borrowDate << '\n'
                << returnDate << '\n' << studentPRN << '\n' << libraryCardNo << '\n';
    }

    // Function to load borrowed book details from file
    void loadFromFile(ifstream& inFile) {
        getline(inFile, studentName);
        getline(inFile, bookTitle);
        getline(inFile, borrowDate);
        getline(inFile, returnDate);
        getline(inFile, studentPRN);
        getline(inFile, libraryCardNo);
    }
};

// Class representing a stack of books
class BookStack {
private:
    Book* top; // Pointer to the top book in the stack
public:
    BookStack() { top = nullptr; }

    void push(Book* book) {
        book->next = top;
        top = book;
    }

    Book* pop() {
        if (top == nullptr) {
            cout << "\nNo books to remove from the library stack!\n\n";
            return nullptr;
        }
        Book* removedBook = top;
        top = top->next;
        return removedBook;
    }

    void displayLibraryStack() const {
        if (top == nullptr) {
            cout << "\nNo books in the library stack!\n\n";
            return;
        }
        cout << "\nBooks in the Library Stack (Top first):\n";
        Book* current = top;
        while (current != nullptr) {
            current->display();
            current = current->next;
        }
        cout << endl;
    }

    // Function to save books to a file
    void saveToFile() const {
        ofstream outFile("library_books.txt");
        Book* current = top;
        while (current != nullptr) {
            current->saveToFile(outFile);
            current = current->next;
        }
        outFile.close();
    }

    // Function to load books from a file
    void loadFromFile() {
        ifstream inFile("library_books.txt");
        if (!inFile.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        while (true) {
            Book* newBook = new Book;
            newBook->loadFromFile(inFile);
            if (inFile.eof()) {
                delete newBook; // Avoid memory leak if we reach EOF
                break;
            }
            push(newBook);
        }
        inFile.close();
    }

    ~BookStack() {
        // Free memory for all books in stack
        while (top != nullptr) {
            Book* temp = pop();
            delete temp; // Free the memory of removed book
        }
    }
};

// Class representing a queue of borrowed books
class BookQueue {
private:
    BorrowedBook* front;
    BorrowedBook* rear;
public:
    BookQueue() { front = rear = nullptr; }

    void enqueue(BorrowedBook* book) {
        book->next = nullptr;
        if (rear == nullptr) {
            front = rear = book;
        } else {
            rear->next = book;
            rear = book;
        }
    }

    BorrowedBook* dequeue() {
        if (front == nullptr) {
            cout << "\nNo borrowed books to return!\n\n";
            return nullptr;
        }
        BorrowedBook* book = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        return book;
    }

    void displayBorrowedBooks() const {
        if (front == nullptr) {
            cout << "\nNo borrowed books!\n\n";
            return;
        }
        cout << "\nBorrowed Books in Queue:\n";
        BorrowedBook* current = front;
        while (current != nullptr) {
            current->display();
            current = current->next;
        }
        cout << endl;
    }

    // Function to save borrowed books to a file
    void saveToFile() const {
        ofstream outFile("borrowed_books.txt");
        BorrowedBook* current = front;
        while (current != nullptr) {
            current->saveToFile(outFile);
            current = current->next;
        }
        outFile.close();
    }

    // Function to load borrowed books from a file
    void loadFromFile() {
        ifstream inFile("borrowed_books.txt");
        if (!inFile.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        while (true) {
            BorrowedBook* newBorrowedBook = new BorrowedBook;
            newBorrowedBook->loadFromFile(inFile);
            if (inFile.eof()) {
                delete newBorrowedBook; // Avoid memory leak if we reach EOF
                break;
            }
            enqueue(newBorrowedBook);
        }
        inFile.close();
    }

    ~BookQueue() {
        // Free memory for all borrowed books
        while (front != nullptr) {
            BorrowedBook* temp = dequeue();
            delete temp; // Free the memory of removed borrowed book
        }
    }
};

// Class representing the library management system
class LibraryManagementSystem {
private:
    BookStack libraryStack;
    BookQueue borrowedBooksQueue;

public:
    LibraryManagementSystem() {
        libraryStack.loadFromFile();
        borrowedBooksQueue.loadFromFile();
    }

    ~LibraryManagementSystem() {
        libraryStack.saveToFile();
        borrowedBooksQueue.saveToFile();
    }

    void addBookToLibrary() {
        Book* newBook = new Book;
        newBook->getdata();
        libraryStack.push(newBook);
    }

    void arrangeBooksInShelf() {
        Book* removedBook = libraryStack.pop();
        if (removedBook) {
            cout << "Arranged in Shelf: ";
            removedBook->display();
            delete removedBook; // Free the memory of arranged book
        }
    }

    void borrowBook() {
        BorrowedBook* newBorrow = new BorrowedBook;
        cout << "\nEnter book title to borrow: ";
        cin.ignore();
        getline(cin, newBorrow->bookTitle);
        newBorrow->getdata();
        borrowedBooksQueue.enqueue(newBorrow);
    }

    void displayBorrowedBooks() const {
        borrowedBooksQueue.displayBorrowedBooks();
    }

    void displayBooks() const {
        libraryStack.displayLibraryStack();
    }
};

// Main function to run the library management system
int main() {
    LibraryManagementSystem library;
    int choice;
    do {
        cout << "Library Management System\n";
        cout << "1. Add Book to Library\n";
        cout << "2. Arrange Books in Shelf\n";
        cout << "3. Display Books\n";
        cout << "4. Borrow Book\n";
        cout << "5. Display Borrowed Books\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBookToLibrary();
                break;
            case 2:
                library.arrangeBooksInShelf();
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.borrowBook();
                break;
            case 5:
                library.displayBorrowedBooks();
                break;
            case 0:
                cout << "Exiting the Library Management System.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}
