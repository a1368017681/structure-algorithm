#include "prioprityqueue.h"

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
