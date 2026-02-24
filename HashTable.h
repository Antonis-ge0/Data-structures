#ifndef HASHTABLE_H
#define HASHTABLE_H


class HashTable {
public:
    HashTable();
    HashTable(int);
    ~HashTable();

    void insert(char *);
    int search(char *);

    void show();

private:
    char **table; //Dynamic two-dimensional array that stores words
    int *counter; //Dynamic one-dimensional array that stores the number of occurrences of each word
    long long int size; //Saves the size of the table
    int filled; //Saves the number of full positions in the table
    int hash(char *, int); //Fragmentation function

    void resize();
};

#endif // HASHTABLE_H
