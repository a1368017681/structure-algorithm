#include <cstdio>
#include <cstring>
#include <iostream>
#include <istream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <cmath>
#include <queue>
#include "rbtree.h"
#define N 10000
#define M 60
typedef long long ll;
using namespace std;
const int maxn = 1e5+5;
#define rep(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define mod 9973
class PQ{
private:
    int n;
    int *a;
public:
    PQ(int sz);
    void insert(int key);
    int delMax();
    void swim(int k);
    void sink(int k);
    void output(){
        for(int i = 1; i <= n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
};
class ST{
private:
public:
    ST();
    void put(int k,string v);
    string get(int k);
    void del(int k);
    bool contains(int k);
    int size();
};

PQ::PQ(int sz){
    n = 0;
    a = new int[sz];
}
void PQ::insert(int key){
    a[++n] = key;
    swim(n);
}
int PQ::delMax(){
    int max = a[1];
    swap(a[1],a[n]);
    a[n--] = NULL;
    sink(1);
    return max;
}
void PQ::swim(int k){
    while(k > 1 && a[k>>1] < a[k]){
        swap(a[k>>1],a[k]);
        k >>= 1;
    }
}
void PQ::sink(int k){
    while(k*2 <= n){
        int j = k<<1;
        if(a[j] < a[j+1]) j = j+1;
        swap(a[k],a[j]);
        k = j;
    }
}
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
    else return rank(hi) - rank(low);
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
void solve(){

}

int main() {
    solve();

    return 0;
}

