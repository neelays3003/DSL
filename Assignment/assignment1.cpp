#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    int rollNo;
    string name;
    float sgpa;

    // Constructor to initialize a student object
    Student(int rollNo = 0, string name = "", float sgpa = 0.0)
    {
        this->rollNo = rollNo;
        this->name = name;
        this->sgpa = sgpa;
    }

    void display()
    {
        cout << "Roll No: " << rollNo << ", Name: " << name << ", SGPA: " << sgpa << endl;
    }
};

class StudentDatabase
{
private:
    Student students[100];
    int size;

public:
    void inputStudents()
    {
        cout << "Enter the number of students: ";
        cin >> size;

        for (int i = 0; i < size; i++)
        {
            int rollNo;
            string name;
            float sgpa;

            cout << "Enter Roll No: ";
            cin >> rollNo;
            cout << "Enter Name: ";
            cin.ignore(); // to ignore the newline character from previous input
            getline(cin, name);
            cout << "Enter SGPA: ";
            cin >> sgpa;

            students[i] = Student(rollNo, name, sgpa);
        }
    }

    void insertionSortByRollNo()
    {
        for (int i = 1; i < size; i++)
        {
            Student key = students[i];
            int j = i - 1;

            while (j >= 0 && students[j].rollNo > key.rollNo)
            {
                students[j + 1] = students[j];
                j--;
            }

            students[j + 1] = key;
        }
    }

    void shellSortByName()
    {
        int gap = size / 2;

        while (gap > 0)
        {
            for (int i = gap; i < size; i++)
            {
                Student temp = students[i];
                int j = i;

                while (j >= gap && students[j - gap].name > temp.name)
                {
                    students[j] = students[j - gap];
                    j -= gap;
                }

                students[j] = temp;
            }

            gap /= 2;
        }
    }

    void radixSortBySGPA()
    {
        // Use counting sort for floating point SGPA by treating SGPA as an integer
        // For example, we can multiply SGPA by 100 to convert it into an integer
        for (int exp = 1; exp <= 100; exp *= 10)
        {
            countingSortBySGPA(exp);
        }
    }

    void countingSortBySGPA(int exp)
    {
        Student output[100];
        int count[10] = {0};

        // Treat SGPA as an integer by multiplying it by 100 (2 decimal precision)
        for (int i = 0; i < size; i++)
        {
            int index = static_cast<int>(students[i].sgpa * 100) / exp % 10;
            count[index]++;
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--)
        {
            int index = static_cast<int>(students[i].sgpa * 100) / exp % 10;
            output[count[index] - 1] = students[i];
            count[index]--;
        }

        for (int i = 0; i < size; i++)
        {
            students[i] = output[i];
        }
    }

    void displayStudents()
    {
        for (int i = 0; i < size; i++)
        {
            students[i].display();
        }
    }

    void displayTopTenToppers()
    {
        // Sort students by SGPA descending (assuming radix sort gives ascending order)
        for (int i = size - 1; i >= size - 10 && i >= 0; i--)
        {
            students[i].display();
        }
    }
};

void mainMenu()
{
    cout << "\nStudent Database Management System" << endl;
    cout << "---------------------------------" << endl;
    cout << "1. Input Student Data" << endl;
    cout << "2. Display Roll Call List (Sorted by Roll No)" << endl;
    cout << "3. Display Alphabetical List (Sorted by Name)" << endl;
    cout << "4. Display Top Ten Toppers (Sorted by SGPA)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    StudentDatabase database;
    int choice;

    while (true)
    {
        mainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            database.inputStudents();
            break;

        case 2:
            database.insertionSortByRollNo();
            cout << "Roll Call List (Sorted by Roll No):" << endl;
            database.displayStudents();
            break;

        case 3:
            database.shellSortByName();
            cout << "Alphabetical List (Sorted by Name):" << endl;
            database.displayStudents();
            break;

        case 4:
            database.radixSortBySGPA();
            cout << "Top Ten Toppers (Sorted by SGPA):" << endl;
            database.displayTopTenToppers();
            break;

        case 5:
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}