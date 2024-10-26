//linked list
#include <iostream>
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
        cin >> title;
        cout << "Enter author name: ";
        cin >> author;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << endl;
    }

    // Function to display book details
    void display() {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << endl;
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
        cin >> studentName;
        cout << "Enter PRN: ";
        cin >> studentPRN;
        cout << "Enter library card number: ";
        cin >> libraryCardNo;
        cout << "Enter borrow date (dd-mm-yyyy): ";
        cin >> borrowDate;
        cout << "Return the book after exact 20days.";
        cout << endl;
    }

    // Function to display borrowed book details
    void display() {
        cout << "Borrowed Book: " << bookTitle << " by " << studentName
             << " (PRN: " << studentPRN << ", Library Card: " << libraryCardNo << ")"
             << " (Borrowed on: " << borrowDate << ", Return by: " << returnDate << ")" << endl;
    }
};

// Class representing a stack of books
class BookStack {
private:
    Book* top; // Pointer to the top book in the stack
public:
    // Constructor initializing the stack as empty
    BookStack() { top = NULL; }

    // Function to add a book to the top of the stack
    void push(Book* book) {
        book->next = top; // Link new book to the current top
        top = book;       // Update top to the new book
        cout << "Book added to the library stack.\n\n";
    }

    // Function to remove and return the top book from the stack
    Book* pop() {
        if (top == NULL) {
            cout << "\nNo books to remove from the library stack!\n\n";
            return NULL; // Return NULL if stack is empty
        }
        Book* removedBook = top; // Store the top book
        top = top->next;         // Move top to the next book
        cout << "\nBook removed from the library stack.\n\n";
        return removedBook; // Return the removed book
    }

    // Function to display all books in the stack
    void displayLibraryStack() {
        if (top == NULL) {
            cout << "\nNo books in the library stack!\n\n";
            return; // Return if the stack is empty
        }
        cout << "\nBooks in the Library Stack (Top first):\n";
        Book* current = top; // Start from the top
        while (current != NULL) {
            current->display(); // Display each book
            current = current->next; // Move to the next book
        }
        cout << endl;
    }
};

// Class representing a queue of borrowed books
class BookQueue {
private:
    BorrowedBook* front; // Pointer to the front of the queue
    BorrowedBook* rear;  // Pointer to the rear of the queue
public:
    // Constructor initializing the queue as empty
    BookQueue() { front = NULL; rear = NULL; }

    // Function to add a borrowed book to the end of the queue
    void enqueue(BorrowedBook* book) {
        book->next = NULL; // New book will be the last in the queue
        if (rear == NULL) {
            front = rear = book; // Queue is empty
        } else {
            rear->next = book; // Link the current rear to the new book
            rear = book;       // Update rear to the new book
        }
        cout << "\nBook borrowed and added to the borrowing queue.\n\n";
    }

    // Function to remove and return the front borrowed book from the queue
    BorrowedBook* dequeue() {
        if (front == NULL) {
            cout << "\nNo borrowed books to return!\n\n";
            return NULL; // Return NULL if queue is empty
        }
        BorrowedBook* book = front; // Store the front book
        front = front->next;        // Move front to the next book
        if (front == NULL) {
            rear = NULL; // Queue is now empty
        }
        cout << "\nBook returned.\n\n";
        return book; // Return the dequeued book
    }

    // Function to display all borrowed books in the queue
    void displayBorrowedBooks() {
        if (front == NULL) {
            cout << "\nNo borrowed books!\n\n";
            return; // Return if the queue is empty
        }
        cout << "\nBorrowed Books in Queue:\n";
        BorrowedBook* current = front; // Start from the front
        while (current != NULL) {
            current->display(); // Display each borrowed book
            current = current->next; // Move to the next book
        }
        cout << endl;
    }
};

// Class representing a queue of returned books
class ReturnedBookQueue {
private:
    BorrowedBook* front; // Pointer to the front of the queue
    BorrowedBook* rear;  // Pointer to the rear of the queue
public:
    // Constructor initializing the returned books queue as empty 
    ReturnedBookQueue() { front = NULL; rear = NULL; }

    // Function to add a returned book to the end of the queue
    void enqueue(BorrowedBook* book) {
        book->next = NULL; // New book will be the last in the queue
        if (rear == NULL) {
            front = rear = book; // Queue is empty
        } else {
            rear->next = book; // Link the current rear to the new book
            rear = book;       // Update rear to the new book
        }
    }

    // Function to display all returned books in the queue
    void displayReturnedBooks() {
        if (front == NULL) {
            cout << "\nNo returned books!\n\n";
            return; // Return if the queue is empty
        }
        cout << "\nReturned Books:\n";
        BorrowedBook* current = front; // Start from the front
        while (current != NULL) {
            current->display(); // Display each returned book
             current = current->next; // Move to the next book
        }
        cout << endl;
    }
};

// Class representing the library management system
class LibraryManagementSystem {
private:
    BookStack libraryStack;          // Stack to manage library books
    BookQueue borrowedBooksQueue;    // Queue to manage borrowed books
    ReturnedBookQueue returnedBooksQueue; // Queue for returned books
public:
    // Function to add a new book to the library
    void addBookToLibrary() {
        Book* newBook = new Book; // Create a new book
        newBook->getdata();       // Get book details from user
        libraryStack.push(newBook); // Add the book to the stack
    }

    // Function to arrange (pop) a book from the stack
    void arrangeBooksInShelf() {
        Book* removedBook = libraryStack.pop(); // Remove the top book
        if (removedBook) {
            cout << "Arranged in Shelf: ";
            removedBook->display(); // Display the arranged book
        }
    }

    // Function to borrow a book
    void borrowBook() {
        BorrowedBook* newBorrow = new BorrowedBook; // Create a new borrowed book
        cout << "\nEnter book title to borrow: ";
        cin >> newBorrow->bookTitle; // Get the title of the book to borrow
        newBorrow->getdata(); // Get other borrowing details from user
        borrowedBooksQueue.enqueue(newBorrow); // Add the borrowed book to the queue
    }

    // Function to return a borrowed book
    void returnBook() {
        BorrowedBook* returnedBook = borrowedBooksQueue.dequeue(); // Remove the front book
        if (returnedBook) {
            returnedBooksQueue.enqueue(returnedBook); // Add it to the returned books queue
        }
    }

    // Function to display all borrowed booksz
    void displayBorrowedBooks() {
        borrowedBooksQueue.displayBorrowedBooks(); // Show all borrowed books
    }

    // Function to display all returned books
    void displayReturnedBooks() {
        returnedBooksQueue.displayReturnedBooks(); // Show all returned books
    }

    // Function to display all books in the library
    void displayBooks() {
        libraryStack.displayLibraryStack(); // Show all books in the library stack
    }

};

// Main function to run the library management system
int main() {
    LibraryManagementSystem library; // Create an instance of the library management system
    int choice; // Variable to store user choice
    do {
        // Display the menu options
        cout << "Library Management System\n";
        cout << "1. Add Book to Library\n";
        cout << "2. Arrange Books in Shelf\n";
        cout << "3. Display Books\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display Borrowed Books\n";
        cout << "7. Display Returned Books\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice; // Get user choice

        // Switch statement to handle different menu options
        switch (choice) {
            case 1:
                library.addBookToLibrary(); // Add book to library
                break;
            case 2:
                library.arrangeBooksInShelf(); // Arrange books on the shelf
                break;
            case 3:
                library.displayBooks(); // Display all books
                break;
            case 4:
                library.borrowBook(); // Borrow a book
                break;
            case 5:
                library.returnBook(); // Return a borrowed book
                break;
            case 6:
                library.displayBorrowedBooks(); // Display borrowed books
                break;
            case 7:
                library.displayReturnedBooks(); // Display returned books
                break;
            case 0:
                cout << "Exiting the Library Management System.\n"; // Exit message
                break;
            default:
                cout << "Invalid choice! Please try again.\n"; // Error message for invalid choice
        }
    } while (choice != 0); // Repeat until user chooses to exit
    return 0; // End of program
}
