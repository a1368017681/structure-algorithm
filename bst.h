#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "config.h"

class Node{
public:
    int k;
    string val;
    Node *left,*right;
    int count;
    Node(int k,string val){
        this->k = k, this->val = val;
    }
};
class BST{
private:
    Node* root;
public:
    void put(int k,string val);
    Node* put(Node* x,int k,string val);
    string get(int k);
    bool contains(int k);
    int size();
    int size(Node* x);
    int size(int lo,int hi);
    int floor(int k);
    Node* floor(Node* x,int k);
    int rank(int k);
    int rank(int k,Node* x);
    int select(int k);
    Node* select(Node* x,int k);
    int min();
    Node* min(Node* x);
    void deleteMin();
    Node* deleteMin(Node* x);
    void del(int k);
    Node* del(Node* x,int k);
    queue<int>* keys();
    void inorder(Node* x,queue<int>* q);
};


#endif // BST_H_INCLUDED
