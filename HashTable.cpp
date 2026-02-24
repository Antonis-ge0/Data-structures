#include "HashTable.h"
#include <cstring>
#include <iostream>

using namespace std;

HashTable::HashTable() //Default constructor that sets the maximum size to 110000
{
    size = 100000000;
    filled = 0;
    table = new char *[size];//Initializing arrays
    for (int i = 0; i < size; i++)
        table[i] = nullptr;
    counter = new int[size];
    for (int i = 0; i < size; i++)
        counter[i] = 0;
}

HashTable::HashTable(int s) //Constructor that sets maximum size to the given number
{
    size = s;
    filled = 0;
    //Initializing arrays
    table = new char *[size];
    for (int i = 0; i < size; i++)
        table[i] = nullptr;
    counter = new int[size];
    for (int i = 0; i < size; i++)
        counter[i] = 0;
}

HashTable::~HashTable() //Destructor
{
    delete[]table;
    delete[]counter;
}

int HashTable::hash(char *w, int i) //Function that returns the position of the word
{
    int c = 31;
    unsigned int h = 0;
    for (int j = 0; w[j] != '\0'; j++)
        h = c * h + w[j];
    return (h + i * i) % size;
}

void HashTable::insert(char *w) { //Function that stores the word in the table

    if (filled == size-300)//resizes the table if it is full
    {
        resize();
    }
    if (filled == size)//resizes the table if it is full
        return ;
    int i = 0, pos;
    pos = hash(w, i);
    while (table[pos] != nullptr)
    {
        if (strcmp(w, table[pos]) == 0) //only increases the counter if w is already added
        {
            counter[pos]++;
            return;
        }
        i++;
        pos = hash(w, i);
    }

    table[pos] = new char[strlen(w) + 1];
    strcpy(table[pos], w);
    counter[pos] = 1;
    filled++;
}

void HashTable::resize() { //Function that doubles the size of the sumOfWords and words arrays
    char **table2 = new char*[size * 2];
    int *counter2 = new int[size * 2];

    for (int i = 0; i < size; i++)
        table2[i] = table[i];

    for (int i = 0; i < size; i++)
        counter2[i] = counter[i];

    delete[] table;
    delete[] counter;

    table = table2;
    counter = counter2;
    //filled = filled2;

    size = size * 2;
}

int HashTable::search(char *w) //Function that returns the number of occurences of the word
{
    int i = 0, pos;
    pos = hash(w, i);
    while (i < size)
    {
        if (table[pos] == nullptr)
            return 0;
        else if (strcmp(table[pos], w) == 0)
            return counter[pos];
        i++;
        pos = hash(w, i);
    }
    return 0;
}
