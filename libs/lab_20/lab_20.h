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
typedef struct tree_node {
    struct tree_node *children[ALPHABET_SIZE];
    int count;
    int is_end_of_word;
} tree_node;

typedef struct Domain {
    char name[MAX_DOMAIN_SIZE];
    int count;
} Domain;

typedef struct tree_arr {
    int value;
    struct tree_arr *left_node;
    struct tree_arr *right_node;
} tree_arr;

tree_node *getNode();
void insertWordInTree (tree_node *root, const char *word);
int isNodeIsWord(tree_node *node);
void freeTree (tree_node *node);
char *findWordInTree(tree_node *root, const char *prefix, int number);

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

tree_arr* constructTreeArr(int *arr, int start, int end);
void freeTreeArr(tree_arr *root);
void printTreeArr(tree_arr *root);
void lab_20_task_07(int *nums, int size, char *result);
int findMaxIndex(int* nums, int start, int end);

void printTreeLevelByLevel(tree_arr * root);
int getDeep(tree_arr *root);
void printByLevel(tree_arr* root, int level);
void printByLevel_FOR_TESTS(tree_arr* root, int level, char *res);
void printTreeLevelByLevel_FOR_TESTS(tree_arr * root, char *res);

void lab_20_task_08(char *s, int *indices, char *res);


#endif //PROJECT_LIBS_LAB_20_H
