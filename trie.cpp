#include "trie.h"

TrieNode* createTrieNode() {
	TrieNode *root = (TrieNode*)malloc(sizeof(TrieNode));
	root->count = 0;
	memset(root->next,0,sizeof(root));
	return root;
}

void trie_insert(Trie root,char* word) {
	TrieNode* node = root;
	char *p = word;
	while(*p) {
		if(NULL == node->next[*p-'a']){
			node->next[*p-'a'] = createTrieNode();
		}
		node = node->next[*p-'a'];
		p++;
	}
	node->count++;
}

bool trie_search(Trie root,char* word) {
	TrieNode* node = root;
	char *p = word;
	while(*p && node!=NULL){
		node = node->next[*p-'a'];
		p++;
	}
	return (node!=NULL && node->count > 0);
}

int trie_word_count(Trie root,char* word) {
	TrieNode* node = root;
	char *p = word;
	while(*p && node != NULL) {
		node = node->next[*p-'a'];
		p++;
	}
	if(node == NULL) return 0;
	else return node->count;
}

int main(){
	return 0;
}