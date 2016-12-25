#include "uf.h"

UF::UF(int n){
    num = n;
    len = n;
    id = new int[n];
    for(int i = 0 ; i < n; i++)
        id[i] = i;
}

int UF::count(){
    return num;
}

bool UF::connected(int p,int q){
    return find(p) == find(q);
}

int UF::find(int p){
    return id[p];
}

void UF::_union(int p,int q){
    int pID = find(p);
    int qID = find(q);
    if(pID == qID) return ;
    for(int i = 0; i < len; i++){
        if(id[i] == pID) id[i] = qID;
    }
    num--;
}

int QuickUF::find(int p){
    while(p != id[p]){
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}

void QuickUF::_union(int p,int q){
    int pID = find(p);
    int qID = find(q);
    if(pID == qID) return ;
    id[pID] = qID;
    num--;
}

WeightedQuickUF::WeightedQuickUF(int n){
    num = n;
    id = new int[n];
    for(int i = 0; i < n; i++) id[i] = i;
    sz = new int[n];
    for(int i = 0; i < n; i++) sz[i] = 1;
}

int WeightedQuickUF::find(int p){
    while(p != id[p]) {
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}

void WeightedQuickUF::_union(int p,int q){
    int i = find(p);
    int j = find(q);
    if(i == j) return ;
    if(sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    }else{
        id[j] = i;
        sz[i] += sz[j];
    }
    num--;
}
