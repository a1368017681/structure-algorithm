#ifndef PRIOPRITYQUEUE_H_INCLUDED
#define PRIOPRITYQUEUE_H_INCLUDED

#include "config.h"

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


#endif // PRIOPRITYQUEUE_H_INCLUDED
