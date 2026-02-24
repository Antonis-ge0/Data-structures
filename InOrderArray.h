#ifndef DOMES_INORDERARRAY_H
#define DOMES_INORDERARRAY_H
#include <string>

using namespace std;

class InOrderArray {

public:
    InOrderArray();
    ~InOrderArray();

    void insert(string word);
    int search(string word);
    int find(string word);

private:
    int size = 10; //Overall size of the array
    int counter = 0; //Counter of the words added
    int *sumOfWords = new int[10]; //Number of times each word is in the array
    string *words = new string[10]; //The words saved in the array
    int findPosition(string word);

    void resize();
};

#endif //DOMES_INORDERARRAY_H
