#include <iostream>
using namespace std;

class DoubleHashingHashTable
{
private:
    int table[7];
    int size;
    int numElements;

public:
    DoubleHashingHashTable() : size(7), numElements(0)
    {
        for (int i = 0; i < size; i++)
        {
            table[i] = -1; // Initialize table with -1 to represent empty slots
        }
    }
    // Hash function 1
    int h1(int key)
    {
        return key % size;
    }
    // Hash function 2
    int h2(int key)
    {
        return 2 + (key % 5);
    }

    // Insert a key using double hashing
    void insert(int key)
    {
        if (numElements == size)
        {
            cout << "Hash Table is full, cannot insert more elements." << endl;
            return;
        }
        int index = h1(key);
        if (table[index] == -1)
        {
            table[index] = key;
            numElements++;
        }
        else
        {
            // Collision resolution with double hashing
            int i = 1;
            int newIndex;
            while (true)
            {
                newIndex = (index + i * h2(key)) % size;
                if (table[newIndex] == -1)
                { // Found an empty slot
                    table[newIndex] = key;
                    numElements++;
                    break;
                }
                i++; // Increment i for next probing step
            }
        }
    }

    // Display the hash table
    void display()
    {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < size; i++)
        {
            if (table[i] != -1)
                cout << "Index " << i << ": " << table[i] << endl;
            else
                cout << "Index " << i << ": " << "Empty" << endl;
        }
    }
};

int main()
{
    DoubleHashingHashTable hashTable;
    // Insert keys
    int keys[] = {10, 22, 31, 4, 15, 28, 17}; // Sample keys
    for (int key : keys)
    {
        hashTable.insert(key);
    }
    // Display hash table
    hashTable.display();
    return 0;
}
