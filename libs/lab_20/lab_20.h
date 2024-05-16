#ifndef PROJECT_LIBS_LAB_20_H
#define PROJECT_LIBS_LAB_20_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_/string_.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>

#define ALPHABET_SIZE 26
#define MAX_DOMAIN_SIZE 100

//Для задания 11
typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];
    int count;
    int is_end_of_word;
} trie_node;

typedef struct Domain {
    char name[MAX_DOMAIN_SIZE];
    int count;
} Domain;

trie_node *getNode();
void insertWordInTrie (trie_node *root, const char *word);
int isNodeIsWord(trie_node *node);
void freeTrie (trie_node *node);
char *findWordInTrie(trie_node *root, const char *prefix, int number);

int lab_20_task_11();
int lab_20_task_11_FORTESTS(char *words, char *requests, char **testRequests);

void lab_20_task_01(matrix *m, int queries[][4], int size_q);
int countPointsFromNeighbours(matrix *m,/*передача клетки:*/ int row, int col);
void lab_20_task_02(matrix *m, matrix *m_res);
void getPointsFromNeighbours(matrix *m, int row, int col, void_vector *neighbours, int filter);
int compareNeighbourPoints(const void *pa, const void *pb);
void lab_20_task_03 (matrix *m, matrix *m_res, int filter);
void lab_20_task_04 (char *domains[], int amount, void_vector *sub_domains);

int min3(int a, int b, int c);
void lab_20_task_05(matrix *m, int *sub_m);

void lab_20_task_06(char *pattern, char *result);


#endif //PROJECT_LIBS_LAB_20_H
