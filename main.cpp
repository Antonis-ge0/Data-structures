//
// Created by Antonis Georgosopoulos on 6/2022.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include "BST.h"
#include "HashTable.h"
#include "AVL.h"
#include "UnOrderArray.h"
#include "InOrderArray.h"

#define random_size 1500

using namespace std;

bool removeChars(char *str) //Bool type so that when the resulting string is empty it will not be inserted into the structures
{
    char temp;
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if(ispunct(str[i]))
        {

            str[i]='\0';
            for(int j=i; str[j+1] != '\0'; j++)
                {
                    temp=str[j];
                    str[j]=str[j+1];
                    str[j+1]=temp;
                }
            i--;
        }
        else
        {
            if(isalpha(str[i]))
                str[i]=tolower(str[i]);
            count++;
        }
    }
    str[count] = '\0';
    if (count > 0) //The necessary check so that the empty string is not inserted in the structures
        return true;
    else
        return false;
}

int main() {
    //Declaration of the file based on the content of which the structures will be created
    ifstream f;
    f.open("small-file.txt");
    if (f.is_open()) {
        //Declaration of objects for each structure
        BST *bst = new BST;
        AVL *avl = new AVL;
        HashTable *htable = new HashTable;
        UnOrderArray *unorderarray = new UnOrderArray;
        InOrderArray *inorderarray = new InOrderArray;

        ofstream of;
        of.open("output.txt");
        if(of.is_open())
        {
            of << "Reading words from text file and inserting them to the data structures..." << endl;
            of.close();
        }
        else
            cout << "File could not be opened!" << endl;

        char **Q; //Creating a random set Q based on which the structures will be searched
        Q = new char *[random_size];  //Can store up to random_size words. Random_size is defined at the beginning
        char str[100],tempstr[100]; //Characters are stored until the space is read (words no longer than 100 characters)
        int count = 0; //Counter for the number of words in the set Q
        srand(time(0));//Use the srand to create the random set Q
        long long int bst_construction_time=0, avl_construction_time=0, htable_construction_time=0, inorderedArray_construction_time=0, unorderedArray_construction_time=0;
        chrono::time_point<chrono::steady_clock> start, end;
        while (!f.eof()) //All the words in the file are read and inserted into the structures
        {
            //Reads the first word if its the first loop
            if(count==0)
                f >> str;
            //Reads a second word and concatenates it with the previous word
            f >> tempstr;

            strcat(str," ");
            strcat(str,tempstr);

            if (removeChars(str)) //Function that removes non-Latin characters from the word.
            {
                char *pch;
                pch = strtok(str, "\0");

                while (pch != NULL) {
                    //Enters the word in BST and updates construction time
                    start = chrono::steady_clock::now();
                    bst->insert(str);
                    end = chrono::steady_clock::now();
                    bst_construction_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                    //Enters the word in AVL and updates construction time
                    start = chrono::steady_clock::now();
                    avl->insert(str);
                    end = chrono::steady_clock::now();
                    avl_construction_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                    //Enters the word in hash table and updates construction time
                    start = chrono::steady_clock::now();
                    htable->insert(str);
                    end = chrono::steady_clock::now();
                    htable_construction_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                    //Enters the word in InOrderArray and updates construction time
                    start = chrono::steady_clock::now();
                    inorderarray->insert(str);
                    end = chrono::steady_clock::now();
                    inorderedArray_construction_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                    //Enters the word in UnOrderArray and updates construction time
                    start = chrono::steady_clock::now();
                    unorderarray->insert(str);
                    end = chrono::steady_clock::now();
                    unorderedArray_construction_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

                    pch = strtok(NULL, ",.-");
                }
                if (count < random_size && rand() % 31 == 0) {
                    Q[count] = new char[strlen(str) + 1]; //Space allocation and storage for the string in table Q
                    strcpy(Q[count], str);
                    count++;
                }
            }
            strcpy(str,tempstr); //Saves the second word for the next loop
        }
        f.close();
        of.open("output.txt",ios::out|ios::app);
        if(of.is_open())
        {
            of << "All words have been added to the data structures." << endl << "Initiating search..." << endl;
            of.close();
        }
        else
            cout << "File could not be opened!" << endl;

        //Declaration of necessary variables for counting time
        long long int bst_total_time = 0, avl_total_time = 0, htable_total_time = 0, inorderedArray_total_time = 0, unorderedArray_total_time = 0;
        int times_found;
        of.open("output.txt",ios::out|ios::app);
        if(of.is_open()){

            for (int i = 0; i < count; i++)
            {
                of << "-----------------------------------------------" << endl;
                //Search the UnorderedArray and update all the time
                start = chrono::steady_clock::now();
                times_found = unorderarray->search(Q[i]);
                end = chrono::steady_clock::now();
                unorderedArray_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                of << "'" << Q[i] << "'"<< " was found " << times_found << " times in UnorderedArray" << endl;

                //Search the InorderedArray and update all the time
                start = chrono::steady_clock::now();
                times_found = inorderarray->search(Q[i]);
                end = chrono::steady_clock::now();
                inorderedArray_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                of << "'" << Q[i] << "'" << " was found " << times_found << " times in InorderedArray" << endl;

                //BST search and total time update
                start = chrono::steady_clock::now();
                times_found = bst->search(Q[i]);
                end = chrono::steady_clock::now();
                bst_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                of << "'" << Q[i] << "'" << " was found " << times_found << " times in BST" << endl;

                //AVL search and total time update
                start = chrono::steady_clock::now();
                times_found = avl->search(Q[i]);
                end = chrono::steady_clock::now();
                avl_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                of << "'" << Q[i] << "'" << " was found " << times_found << " times in AVL tree" << endl;

                //Search the hash table and update total time
                start = chrono::steady_clock::now();
                times_found = htable->search(Q[i]);
                end = chrono::steady_clock::now();
                htable_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                of << "'" << Q[i] << "'" << " was found " << times_found << " times in Hash table" << endl;
            }
        //Display of necessary messages
        of << endl << "Search completed." << endl << "Showing results..." << endl;

        of << "Elapsed time for UnorderedArray construction: " << unorderedArray_construction_time<< "ns" <<endl;
        of << "Elapsed time for UnorderedArray search: " << unorderedArray_total_time << " ns" << endl;

        of << "Elapsed time for InorderedArray construction: " << inorderedArray_construction_time<< "ns" <<endl;
        of << "Elapsed time for InorderedArray search: " << inorderedArray_total_time << " ns" << endl;

        of << "Elapsed time for BST construction: " << bst_construction_time<< "ns" <<endl;
        of << "Elapsed time for BST search: " << bst_total_time << " ns" << endl;

        of << "Elapsed time for AVL construction: " << avl_construction_time<< "ns" <<endl;
        of << "Elapsed time for AVL tree search: " << avl_total_time << " ns" << endl;

        of << "Elapsed time for Hash table construction: " << htable_construction_time<< "ns" <<endl;
        of << "Elapsed time for Hash table search: " << htable_total_time << " ns" << endl;
        of.close();
        }
        else
            cout << "File could not be opened!" << endl;
    } else
        cout << "File could not be opened!" << endl;
    return 0;

}

