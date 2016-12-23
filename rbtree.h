#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED
#include <cstring>
#include <iostream>
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
string RBTREE::get(int k){
    RBTNode *x = root;
    while(x != NULL){
        if(k < x->k){
            x = x->left;
        }else if(k > x->k){
            x = x->right;
        }else return x->val;
    }
    return "";
}
bool RBTREE::contains(int k){
    string x = get(k);
    if(x != "") return true;
    else return false;
}
RBTNode* RBTREE::put(RBTNode* x,int k,string val){
    if(x == NULL) return new RBTNode(k,val,1,RED);
    int cmp = k - x->k;
    if(cmp < 0)
        x->left = put(x->left,k,val);
    else if(cmp > 0)
        x->right = put(x->right,k,val);
    else
        x->val = val;
    if(isRed(x->right) && !isRed(x->left)) x = rotateLeft(x);
    if(isRed(x->left) && isRed(x->left->left)) x = rotateRight(x);
    if(isRed(x->left) && isRed(x->right)) flipColors(x);
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}
void RBTREE::put(int k,string val){
    root = put(root,k,val);
    root->color = BLACK;
}
int RBTREE::floor(int k){
    RBTNode* x = floor(root,k);
    if(x == NULL) return NULL;
    return x->k;
}
RBTNode* RBTREE::floor(RBTNode* x,int k){
    if(x == NULL) return NULL;
    int cmp = k - x->k;
    if(cmp == 0) return x;
    if(cmp < 0) return floor(x->left,k);
    RBTNode* t = floor(x->right,k);
    if(t != NULL) return t;
    else return x;
}
int RBTREE::size(){
    return size(root);
}
int RBTREE::size(RBTNode* x){
    if(x == NULL) return 0;
    return x->count;
}
int RBTREE::size(int lo,int hi){
    if(contains((hi))) return rank(hi) - rank(lo) + 1;
    else return rank(hi) - rank(lo);
}
int RBTREE::rank(int k){
    return rank(k,root);
}
int RBTREE::rank(int k,RBTNode* x){
    if(x == NULL) return 0;
    int cmp = k - x->k;
    if(k < 0) return rank(k,x->left);
    else if(cmp > 0) return 1+size(x->left)+rank(k,x->right);
    else return size(x->left);
}
int RBTREE::select(int k){
    return select(root,k)->k;
}
RBTNode* RBTREE::select(RBTNode* x,int k){
    if(x == NULL) return NULL;
    int t = size(x->left);
    if(t > k) return select(x->left,k);
    else if(t < k) return select(x->right,k-t-1);
    else return x;
}
queue<int>* RBTREE::keys(){
    queue<int> *q = new queue<int>();
    inorder(root,q);
    return q;
}
void RBTREE::inorder(RBTNode* x,queue<int>* q){
    if(x == NULL) return ;
    inorder(x->left,q);
    q->push(x->k);
    inorder(x->right,q);
}
int RBTREE::min(){
    return min(root)->k;
}
RBTNode* RBTREE::min(RBTNode* x){
    if(x->left == NULL) return x;
    return min(x->left);
}
void RBTREE::deleteMin(){
    root = deleteMin(root);
}
RBTNode* RBTREE::deleteMin(RBTNode* x){
    if(x->left == NULL) return x->right;
    x->left = deleteMin(x->left);
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}
void RBTREE::del(int k){
    root = del(root,k);
}
RBTNode* RBTREE::del(RBTNode* x,int k){
    if(x == NULL) return NULL;
    int cmp = k - x->k;
    if(cmp < 0) x->left = del(x->left,k);
    else if(cmp > 0) x->right = del(x->right,k);
    else{
        if(x->right == NULL) return x->left;
        if(x->left == NULL) return x->right;
        RBTNode* t = x;
        x = min(x->right);
        x->right = deleteMin(t->right);
        x->left = t->left;
    }
    x->count = size(x->left) + size(x->right) + 1;
    return x;
}
bool RBTREE::isRed(RBTNode* x){
    if(x == NULL) return false;
    else return (x->color == RED);
}
RBTNode* RBTREE::rotateLeft(RBTNode* h){
    RBTNode* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->count = h->count;
    h->count = 1 + size(h->left) + size(h->right);
    return x;
}
RBTNode* RBTREE::rotateRight(RBTNode* h){
    RBTNode* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->count = h->count;
    h->count = 1 + size(h->left) + size(h->right);
    return x;
}

void RBTREE::flipColors(RBTNode* h){
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}
#endif // RBTREE_H_INCLUDED
