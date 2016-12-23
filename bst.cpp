#include "bst.h"
string BST::get(int k){
    Node *x = root;
    while(x != NULL){
        if(k < x->k){
            x = x->left;
        }else if(k > x->k){
            x = x->right;
        }else return x->val;
    }
    return "";
}
bool BST::contains(int k){
    return (get(k) != "");
}
Node* BST::put(Node* x,int k,string val){
    if(x == NULL) return new Node(k,val);
    int cmp = k - x->k;
    if(cmp < 0)
        x->left = put(x->left,k,val);
    else if(cmp > 0)
        x->right = put(x->right,k,val);
    else
        x->val = val;
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}
void BST::put(int k,string val){
    root = put(root,k,val);
}
int BST::floor(int k){
    Node* x = floor(root,k);
    if(x == NULL) return NULL;
    return x->k;
}
Node* BST::floor(Node* x,int k){
    if(x == NULL) return NULL;
    int cmp = k - x->k;
    if(cmp == 0) return x;
    if(cmp < 0) return floor(x->left,k);
    Node* t = floor(x->right,k);
    if(t != NULL) return t;
    else return x;
}
int BST::size(){
    return size(root);
}
int BST::size(Node* x){
    if(x == NULL) return 0;
    return x->count;
}
int BST::size(int lo,int hi){
    if(contains(hi)) return rank(hi) - rank(lo) + 1;
    else return rank(hi) - rank(lo);
}
int BST::rank(int k){
    return rank(k,root);
}
int BST::rank(int k,Node* x){
    if(x == NULL) return 0;
    int cmp = k - x->k;
    if(k < 0) return rank(k,x->left);
    else if(cmp > 0) return 1+size(x->left)+rank(k,x->right);
    else return size(x->left);
}
int BST::select(int k){
    return select(root,k)->k;
}
Node* BST::select(Node* x,int k){
    if(x == NULL) return NULL;
    int t = size(x->left);
    if(t > k) return select(x->left,k);
    else if(t < k) return select(x->right,k-t-1);
    else return x;
}
queue<int>* BST::keys(){
    queue<int> *q = new queue<int>();
    inorder(root,q);
    return q;
}
void BST::inorder(Node* x,queue<int>* q){
    if(x == NULL) return ;
    inorder(x->left,q);
    q->push(x->k);
    inorder(x->right,q);
}
int BST::min(){
    return min(root)->k;
}
Node* BST::min(Node* x){
    if(x->left == NULL) return x;
    return min(x->left);
}
void BST::deleteMin(){
    root = deleteMin(root);
}
Node* BST::deleteMin(Node* x){
    if(x->left == NULL) return x->right;
    x->left = deleteMin(x->left);
    x->count = 1 + size(x->left) + size(x->right);
    return x;
}
void BST::del(int k){
    root = del(root,k);
}
Node* BST::del(Node* x,int k){
    if(x == NULL) return NULL;
    int cmp = k - x->k;
    if(cmp < 0) x->left = del(x->left,k);
    else if(cmp > 0) x->right = del(x->right,k);
    else{
        if(x->right == NULL) return x->left;
        if(x->left == NULL) return x->right;
        Node* t = x;
        x = min(x->right);
        x->right = deleteMin(t->right);
        x->left = t->left;
    }
    x->count = size(x->left) + size(x->right) + 1;
    return x;
}
