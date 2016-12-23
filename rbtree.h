#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED
#include "config.h"
using namespace std;
#define RED 1
#define BLACK 0
class RBTNode{
public:
    int k;
    string val;
    RBTNode *left,*right;
    int count;
    bool color;
    RBTNode(int k,string val,int n,bool color){
        this->k = k, this->val = val;
        this->count = n, this->color = color;
    }
};
class RBTREE{
private:
    RBTNode* root;
public:
    void put(int k,string val);
    RBTNode* put(RBTNode* x,int k,string val);
    string get(int k);
    bool contains(int k);
    int size();
    int size(RBTNode* x);
    int size(int lo,int hi);
    int floor(int k);
    RBTNode* floor(RBTNode* x,int k);
    int rank(int k);
    int rank(int k,RBTNode* x);
    int select(int k);
    RBTNode* select(RBTNode* x,int k);
    int min();
    RBTNode* min(RBTNode* x);
    void deleteMin();
    RBTNode* deleteMin(RBTNode* x);
    void del(int k);
    RBTNode* del(RBTNode* x,int k);
    queue<int>* keys();
    void inorder(RBTNode* x,queue<int>* q);
    bool isRed(RBTNode* x);
    RBTNode* rotateLeft(RBTNode* h);
    RBTNode* rotateRight(RBTNode* h);
    void flipColors(RBTNode* h);
};
#endif // RBTREE_H_INCLUDED
