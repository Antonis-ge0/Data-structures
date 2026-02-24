#include "BST.h"
#include <cstring>
#include <iostream>

using namespace std;

BST::BST() //Empty constructor which sets all members of the BST class
{
    word = nullptr;
    left = nullptr;
    right = nullptr;
    counter = 0;
}

BST::~BST() //Destructor
{
    delete[]word;
    word = nullptr;
}

void BST::insert(char *w) //Recursive function that stores the word
{
    if (word == nullptr) //Stores the word if there are no subtrees
    {
        word = new char[strlen(w) + 1];
        strcpy(word, w);
        counter++;
        return;
    }
    int flag = strcmp(w, word);
    if (flag == 0) //Increases the counter if the word is already stored
        counter++;
    else if (flag < 0) //Creates a subtree if empty or else recurs insert
    {
        if (left == nullptr)
            left = new BST;
        left->insert(w);
    } else
    {
        if (right == nullptr)
            right = new BST;
        right->insert(w);
    }
}

int BST::search( //Recursive function that returns the number of times the word is stored
        char *w)
{
    if (word == nullptr)
        return 0;
    int flag = strcmp(w, word);
    if (flag == 0)
        return counter;
    else if (flag < 0) //Searches the subtrees
    {
        if (left != nullptr)
            return left->search(w);
    } else
    {
        if (right != nullptr)
            return right->search(w);
    }
    return 0;
}

BST *BST::deletion(char *w) //Recursive function that deletes the word
{
    if (word == nullptr)
        return nullptr;
    //Searches for the word
    int flag = strcmp(w, word);
    if (flag < 0)
    {
        if (left != nullptr)
            left = left->deletion(w);
    } else if (flag > 0)
    {
        if (right != nullptr)
            right = right->deletion(w);
    } else
    {
        //Deletes the word, and is replaced by the child if there is one
        if (left == nullptr && right == nullptr)
        {
            delete this;
            return nullptr;
        } else if (right == nullptr)
        {
            BST *newChild = left;
            delete this;
            return newChild;
        } else if (left == nullptr)
        {
            BST *newChild = right;
            delete this;
            return newChild;
        } else
        {
            BST *temp = right->findMinNode();
            strcpy(word,
                   temp->word);
            counter = temp->counter;
            right = right->deletion(temp->word);
            return this;
        }
    }
    return this;
}

BST *BST::findMinNode() //Function that returns the tree's minimum node
{

    BST *min = this;
    while (min->left != nullptr)
        min = min->left;
    return min;
}

void BST::inorder() //Recursive function that traverses the tree in-order and prints it
{    if (word == nullptr)
        return;
    if (left != nullptr)
        left->inorder();
    cout << word << endl;
    if (right != nullptr)
        right->inorder();
}

void BST::preorder() //Recursive function that traverses the tree pre-order and prints it
{
    if (word == nullptr)
        return;
    cout << word << endl;
    if (left != nullptr)
        left->preorder();
    if (right != nullptr)
        right->preorder();
}

void BST::postorder(){ //Recursive function that traverses the tree post order and prints it
    if (word == nullptr)
        return;
    if (left != nullptr)
        left->postorder();
    if (right != nullptr)
        right->postorder();
    cout << word << endl;
}
