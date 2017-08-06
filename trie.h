#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALP_NUM 26
typedef struct Trie_node{
    int count;
    struct Trie_node *next[ALP_NUM];
    
}TrieNode,*Trie;


#endif // TRIE_H_INCLUDED
