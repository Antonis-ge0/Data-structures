#ifndef DOMES_UNORDERARRAY_H
#define DOMES_UNORDERARRAY_H
#include <string>

using namespace std;

class UnOrderArray {

public:

    UnOrderArray();
    ~UnOrderArray();

    void insert(string word);
    int search(string word);
    int find(string word);

private:
    int size = 10; //Overall size of the array
    int counter = 0; //Counter of the words added
    int *sumOfWords = new int[10]; //Number of occurrences for each word
    string *words = new string[10]; //Array that includes the words

    void resize();
};

#endif //DOMES_UNORDERARRAY_H
