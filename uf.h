#ifndef UF_H_INCLUDED
#define UF_H_INCLUDED

#include "config.h"

class UF{ //union-find
private:
    int *id;
    int num; //number of components
    int len; //length of array
public:
    UF(int n);
    void _union();
    int find(int p);
    bool connected(int p,int q);
    int count();
};

class QuickUF: public UF{
private:
public:
    QuickUF(int n):UF(n){}
};

class WeightedQuickUF: public UF{
private:
    int *sz;
public:
    WeightedQuickUF(int n);
};

#endif // UF_H_INCLUDED
