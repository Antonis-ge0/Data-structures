#ifndef DOMES_AVL_H
#define DOMES_AVL_H

class AVL {

public:

    AVL();
    ~AVL();

    void insert(char *);
    int search(char *);
    AVL *deletion(char *);
    AVL *findMinNode();
    void inorder();
    void preorder();
    void postorder();

private:
    char *word; //Word of the node
    AVL *left; //Left child
    AVL *right; //Right child
    int counter; //Counter for the number of occurrences of the word
    int height; //Height of the node
    int newHeight(); //Height of the node after an insert or delete
    int balance; //Node balance
    int newBalance(); //Node balance after an insert or delete
    //Methods for rotating nodes
    void LeftRotation();
    void RightRotation();
};


#endif //DOMES_AVL_H
