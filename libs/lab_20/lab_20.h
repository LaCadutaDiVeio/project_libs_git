#ifndef PROJECT_LIBS_LAB_20_H
#define PROJECT_LIBS_LAB_20_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_/string_.h>

#define ALPHABET_SIZE 26

//Для задания 11
typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];
    int count;
    int is_end_of_word;
} trie_node;

trie_node *getNode();
void insertWordInTrie (trie_node *root, const char *word);
int isNodeIsWord(trie_node *node);
void freeTrie (trie_node *node);
char *findWordInTrie(trie_node *root, const char *prefix, int number);

int lab_20_task_11();
int lab_20_task_11_FORTESTS(char *words, char *requests, char **testRequests);


#endif //PROJECT_LIBS_LAB_20_H
