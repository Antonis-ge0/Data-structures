#ifndef BST_H
#define BST_H

class BST {

public:
    BST();
    ~BST();

    void insert(char *);
    int search(char *);
    BST *deletion(char *);
    BST *findMinNode();
    void inorder();
    void preorder();
    void postorder();

private:
    char *word; //Saves the word entered in the node
    int counter; //Counter for the number of occurrences of the word
    BST *left; //Marker in the left subtree
    BST *right; //Marker in the right subtree
};

#endif // BST_H
