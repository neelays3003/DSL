#include <iostream>
#include <string>
using namespace std;

class Job {
public:
    int jobID;
    int jobPriority;
    string jobDescription;
    Job* next;
    Job* prev;

    Job(int id, int priority, string desc) {
        jobID = id;
        jobPriority = priority;
        jobDescription = desc;
        next = nullptr;
        prev = nullptr;
    }
};

class JobQueue {
private:
    Job* front;
    Job* rear;

public:
    JobQueue() {
        front = rear = nullptr;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Add job to the front (high-priority job)
    void addJobAtFront(int id, int priority, string desc) {
        Job* newJob = new Job(id, priority, desc);
        if (isEmpty()) {
            front = rear = newJob;
        } else {
            newJob->next = front;
            front->prev = newJob;
            front = newJob;
        }
        cout << "Job added at the front.\n";
    }

    // Add job to the rear (low-priority job)
    void addJobAtRear(int id, int priority, string desc) {
        Job* newJob = new Job(id, priority, desc);
        if (isEmpty()) {
            front = rear = newJob;
        } else {
            rear->next = newJob;
            newJob->prev = rear;
            rear = newJob;
        }
        cout << "Job added at the rear.\n";
    }

    // Remove job from the front
    void removeJobFromFront() {
        if (isEmpty()) {
            cout << "No jobs to remove.\n";
            return;
        }
        Job* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        cout << "Job removed from the front.\n";
    }

    // Remove job from the rear
    void removeJobFromRear() {
        if (isEmpty()) {
            cout << "No jobs to remove.\n";
            return;
        }
        Job* temp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        cout << "Job removed from the rear.\n";
    }

    // Display all jobs in the queue
    void displayJobs() {
        if (isEmpty()) {
            cout << "No jobs to display.\n";
            return;
        }
        Job* temp = front;
        cout << "Jobs in the queue:\n";
        while (temp) {
            cout << "Job ID: " << temp->jobID << ", Priority: " << temp->jobPriority
                 << ", Description: " << temp->jobDescription << endl;
            temp = temp->next;
        }
    }

    // Search for a job by ID
    void searchJob(int id) {
        if (isEmpty()) {
            cout << "No jobs to search.\n";
            return;
        }
        Job* temp = front;
        while (temp) {
            if (temp->jobID == id) {
                cout << "Job found - ID: " << temp->jobID << ", Priority: " << temp->jobPriority
                     << ", Description: " << temp->jobDescription << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Job not found.\n";
    }
};

int main() {
    JobQueue jobQueue;
    int choice, id, priority;
    string desc;
    do {
        cout << "\n1. Add Job at Front\n2. Add Job at Rear\n3. Remove Job from Front\n4. Remove Job from Rear\n5. Display Jobs\n6. Search Job\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Job ID: ";
                cin >> id;
                cout << "Priority: :";
                cin >> priority;
                cout << "Description (single word): ";
                cin >> desc;
                jobQueue.addJobAtFront(id, priority, desc);
                break;
            case 2:
                cout << "Enter Job ID: ";
                cin >> id;
                cout << "Priority: :";
                cin >> priority;
                cout << "Description (single word): ";
                cin >> desc;
                jobQueue.addJobAtRear(id, priority, desc);
                break;
            case 3:
                jobQueue.removeJobFromFront();
                break;
            case 4:
                jobQueue.removeJobFromRear();
                break;
            case 5:
                jobQueue.displayJobs();
                break;
            case 6:
                cout << "Enter Job ID to search: ";
                cin >> id;
                jobQueue.searchJob(id);
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    } while (choice != 0);
    return 0;
}