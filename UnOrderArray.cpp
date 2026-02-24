#include "UnOrderArray.h"

using namespace std;


UnOrderArray::UnOrderArray() {  //Empty constructor which sets all members of the UnOrderArray class

}

UnOrderArray::~UnOrderArray() { //Destructor
    delete[] words;
    delete[] sumOfWords;
}

void UnOrderArray::insert(string word) { //Function that adds the word to the array
    if (counter == size) {
        resize();
    }

    int index = find(word);
    if (index == -1) {
        words[counter] = word;
        sumOfWords[counter] = 1;
        counter++;
    } else {
        sumOfWords[index]++;
    }
}

void UnOrderArray::resize() { //Function that doubles the size of the SumOfWords and Words arrays
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


int UnOrderArray::find(string word) { //Function that returns the position of the word
    for (int i = 0; i < counter; i++) {
        if (word == words[i]) {
            return i;
        }
    }
    return -1;
}


int UnOrderArray::search(string word) { //Function that returns the number of times the word is in the array

    int index = find(word);
    if (index == -1) {
        return -1;
    } else {
        return sumOfWords[index];
    }
}
