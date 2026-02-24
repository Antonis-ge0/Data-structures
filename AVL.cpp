#include "AVL.h"
#include <cstring>
#include <iostream>

using namespace std;

AVL::AVL() {  //Empty constructor which sets all members of the AVL class

    word = nullptr;
    left = nullptr;
    right = nullptr;
    counter = 0;
    height = 0;
    balance = 0;
}

AVL::~AVL() { //Destructor

    delete[]word;
    word = nullptr;
}

int AVL::newHeight() { //Recursive function that calculates and returns the height of the node

    int L = -1, R = -1;
    if (left != nullptr)
        L = left->height;
    if (right != nullptr)
        R = right->height;
    if (L > R)
        return L + 1;
    else
        return R + 1;
}

int AVL::newBalance() { //Function that calculates and returns the balance of the node

    int L = 0, R = 0;
    if (left != nullptr)
        L = 1 +
            left->height;
    if (right != nullptr)
        R = 1 +
            right->height;
    return L - R;
}

void AVL::LeftRotation() { //Helper function that accomplishes a left rotation

    AVL *temp = this->right;

    AVL *root_copy = new AVL;
    root_copy->word = new char[strlen(this->word) + 1]; //Copying current node
    strcpy(root_copy->word, this->word);
    root_copy->counter = this->counter;
    root_copy->left = this->left;

    root_copy->right = temp->left; //Rotating the current right's left to the left side



    delete[]word;
    this->word = new char[strlen(temp->word) +1];
    strcpy(this->word, temp->word); //Rotating right to current position
    this->counter = temp->counter;


    this->right = temp->right; //Next right replaces the previous one
    this->left = root_copy; //Copying back the rest of the left side
    delete temp;

    this->left->height = this->left->newHeight(); //Adjusting height
    this->height = newHeight();
}

void AVL::RightRotation() { //Helper function that accomplishes a right rotation


    AVL *temp = this->left;

    AVL *root_copy = new AVL;
    root_copy->word = new char[strlen(this->word) + 1];
    strcpy(root_copy->word, this->word); //Copying current node
    root_copy->counter = this->counter;
    root_copy->right = this->right;
    root_copy->left = temp->right; //Rotating the current left's right to the right side

    delete[]word;
    this->word = new char[strlen(temp->word) +1];
    strcpy(this->word, temp->word); //Rotating to the left position
    this->counter = temp->counter;


    this->left = temp->left; //Next left replaces the previous one
    this->right = root_copy; //Copying back the rest of the right side
    delete temp;


    this->right->height = this->right->newHeight(); //Adjusting height
    this->height = newHeight();
}

void AVL::insert(char *w) { //Recursive function that inserts a word to the tree


    if (word == nullptr) { //Empty node found
        word = new char[strlen(w) + 1];
        strcpy(word, w);
        counter++;
        return;
    }
    int flag = strcmp(w, word);
    if (flag == 0) //Word already added
        counter++;
    else if (flag < 0) { //Inserts the word at the correct side
        if (left == nullptr)
            left = new AVL;
        left->insert(w);
    } else {
        if (right == nullptr)
            right = new AVL;
        right->insert(w);
    }

    height = newHeight(); //Calculates new height
    balance = newBalance(); //Calculates new balance

    //Adjusts the tree with the correct rotations
    if (balance > 1)
    {
        if (strcmp(w, left->word) < 0)
            this->RightRotation();
        else if (strcmp(w, left->word) > 0)
        {
            left->LeftRotation();
            this->RightRotation();
        }
    } else if (balance < -1)
    {
        if (strcmp(w, right->word) > 0)
            this->LeftRotation();
        else if (strcmp(w, right->word) < 0)
        {
            right->RightRotation();
            this->LeftRotation();
        }
    }
}

AVL *AVL::deletion(char *w) { //Recursive function that deletes word w

    if (word == nullptr) //Error
        return nullptr;
    int flag = strcmp(w, word);
    if (flag < 0) {
        if (left != nullptr)
            left = left->deletion(w); //Searches left
    } else if (flag > 0) {
        if (right != nullptr)
            right = right->deletion(w); //Searches right
    } else { //Found the correct node
        if (left == nullptr && right == nullptr) {
            delete this;
            return nullptr;
        } else if (right == nullptr) { //Replaces with left node
            AVL *newChild = left;
            delete this;
            return newChild;
        } else if (left == nullptr) { //Replaces with right node
            AVL *newChild = right;
            delete this;
            return newChild;
        } else { //Searches for the minimum node and deletes it
            AVL *temp = right->findMinNode();
            strcpy(word, temp->word);
            counter = temp->counter;
            right = right->deletion(temp->word);
            return this;
        }
    }


    height = newHeight(); //Calculates new height
    balance = newBalance(); //Calculates new balance
    int b;
    //Adjusting balance with the correct rotations
    if (balance > 1)
    {
        b = (left->balance = left->newBalance());
        if (b >= 0)
            this->RightRotation();
        else
        {
            left->LeftRotation();
            this->RightRotation();
        }
    } else if (balance < -1)
    {
        b = (right->balance = right->newBalance());
        if (b > 0)
        {
            right->RightRotation();
            this->LeftRotation();
        } else
            this->LeftRotation();
    }
    return this;
}

int AVL::search(char *w) { //Recursive function that searches for the word and returns the number of occurrences of it
    if (word == nullptr)
        return 0;
    int flag = strcmp(w, word);
    if (flag == 0)
        return counter;
    else if (flag < 0) {
        if (left != nullptr)
            return left->search(w);
    } else {
        if (right != nullptr)
            return right->search(w);
    }
    return 0;
}

AVL *AVL::findMinNode() { //Function that returns the leftmost node
    AVL *min = this;
    while (min->left != nullptr)
        min = min->left;
    return min;
}

void AVL::inorder() { //Recursive function that traverses the tree in-order and prints it
    if (word == nullptr)
        return;
    if (left != nullptr)
        left->inorder();
    cout << word << " height is " << height << endl;
    if (right != nullptr)
        right->inorder();
}

void AVL::preorder() { //Recursive function that traverses the tree pre-order and prints it
    if (word == nullptr)
        return;
    cout << word << endl;
    if (left != nullptr)
        left->preorder();
    if (right != nullptr)
        right->preorder();
}

void AVL::postorder() { //Recursive function that traverses the tree post order and prints it
    if (word == nullptr)
        return;
    if (left != nullptr)
        left->postorder();
    if (right != nullptr)
        right->postorder();
    cout << word << endl;
}
