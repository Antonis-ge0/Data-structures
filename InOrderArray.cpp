#include "InOrderArray.h"
#include <iostream>

using namespace std;

InOrderArray::InOrderArray() {  //Empty constructor which sets all members of the InOrderArray class

}

InOrderArray::~InOrderArray() { //Destructor
    delete[] words;
    delete[] sumOfWords;
}

void InOrderArray::insert(string word) { //Inserts the word in the array
    if (counter == size) {
        resize();
    }
    int index = find(word);
    if (index == -1) { //Checks if the word is new or not
        int pos = findPosition(word);
        for (int i = counter; i > pos; i--) {
            words[i] = words[i - 1];
            sumOfWords[i] = sumOfWords[i - 1];
        }
        words[pos] = word;
        sumOfWords[pos] = 1;
        counter++;
    } else {
        sumOfWords[index]++;
    }
}

void InOrderArray::resize() { //Function that doubles the size of the sumOfWords and words arrays
    int *newSumOfWords = new int[size * 2];
    string *newWords = new string[size * 2];

    std::copy(sumOfWords, sumOfWords + std::min(size, size * 2), newSumOfWords);
    std::copy(words, words + std::min(size, size * 2), newWords);

    delete[] words;
    delete[] sumOfWords;

    words = newWords;
    sumOfWords = newSumOfWords;

    size = size * 2;
}

int InOrderArray::findPosition(string word) { //Helper function that returns the position the word should be when inserted in the array
    int i = 0;
    for (i = 0; i < counter; i++) {
        if (word < words[i]) {
            return i;
        }
    }
    return i;
}

int InOrderArray::find(string word) { //Function that returns the position of the word
    int i = 0;
    int flag = counter-1;
    while (i <= flag) {
        int m = i+(flag-i)/2;
        if (word == words[m]) {
            return m;
        }
        if (word < words[m])
            flag = m-1;
        else
            i = m+1;
    }
    return -1;
}


int InOrderArray::search(string word) { //Function that returns the sum of the times the word is seen

    int index = find(word);
    if (index == -1) {
        return -1;
    } else {
        return sumOfWords[index];
    }
}

