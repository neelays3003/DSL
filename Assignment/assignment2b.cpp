#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int iEmployeeID;
    string sName;
public:
    Employee() : iEmployeeID(0), sName("  ") {}

    Employee(int id, string name) : iEmployeeID(id), sName(name) {}

    void setEmployeeId(int id) {
        iEmployeeID = id;        
    }

    void setName(string name) {
        sName = name;
    }

    int getEmployeeID() {
        return iEmployeeID;
    }

    string getName() {
        return sName;
    }                  
};

void merge(Employee Arr[], int start, int mid, int end) {
    int len1 = mid - start + 1;
    int len2 = end - mid;

    Employee* leftArr = new Employee[len1];
    Employee* rightArr = new Employee[len2];

    for (int i = 0; i < len1; ++i)
        leftArr[i] = Arr[start + i];
    for (int j = 0; j < len2; ++j)
        rightArr[j] = Arr[mid + 1 + j];

    int i = 0, j = 0, k = start;
    while (i < len1 && j < len2) {
        if (leftArr[i].getEmployeeID() <= rightArr[j].getEmployeeID())
            Arr[k++] = leftArr[i++];
        else
            Arr[k++] = rightArr[j++];
    }
    while (i < len1)
        Arr[k++] = leftArr[i++];
    while (j < len2)
        Arr[k++] = rightArr[j++];
}

void mergeSort(Employee Arr[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(Arr, start, mid);
        mergeSort(Arr, mid + 1, end);
        merge(Arr, start, mid, end);
    }
}

void printArray(Employee Arr[], int len) {
    for (int i = 0; i < len; ++i)
        cout << Arr[i].getEmployeeID() << " and name: " << Arr[i].getName() << "\n";
}

int main() {
    Employee Arr[] = { {4, "Sachet"}, {3, "Sadhyoj"}, {2, "Yash"}, {1, "Saurabh"} };
    int len = sizeof(Arr) / sizeof(Employee);

    cout << "ARRAY ELEMENTS TO BE SORTED ARE : " << endl;
    printArray(Arr, len);
 
    mergeSort(Arr, 0, len - 1);
   
    cout << "SORTED ELEMENTS OF THE ARRAY ARE : " << endl;
    printArray(Arr, len);

    return 0;
}
