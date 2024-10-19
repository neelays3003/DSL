#include <iostream>
using namespace std;

void printarray(int EMP_ID[], int n){
    for(int i = 0 ; i < n ; i++){
        cout << EMP_ID[i] << " ";
    }
}

int partition(int EMP_ID[], int s, int e){
    int pivot = EMP_ID[s];
    int low = s, high = e;
   
    while(low<high){
        while(EMP_ID[low] <= pivot)
             low++;
        while(EMP_ID[high] > pivot)
             high--;
        if(low < high){
            int temp = EMP_ID[low];
            EMP_ID[low] = EMP_ID[high];
            EMP_ID[high] = temp;
        }    
    }      

    int temp = EMP_ID[high];
    EMP_ID[high] = EMP_ID[s];
    EMP_ID[s] = temp;
    return high;
}

void quicksort(int EMP_ID[], int s, int e){
    if(s < e){
        int pp = partition(EMP_ID, s, e);
        quicksort(EMP_ID, s, pp - 1);
        quicksort(EMP_ID, pp + 1, e);
    }
}

int main() {
   
    int EMP_ID[] = {2,4,1,9,7,8,10,5,6,3};
    int n = sizeof(EMP_ID)/sizeof(int);
   
    cout << "EMP_ID OF THE EMPLOYEES : ";
    for(int i = 0 ;i < n ; i++){
        cout << EMP_ID[i] << " ";
    }
   
    quicksort(EMP_ID, 0, n - 1);
    cout << "\nSORTED EMP_ID OF THE EMPLOYEES : ";

    printarray(EMP_ID , n);
   
    return 0;
}