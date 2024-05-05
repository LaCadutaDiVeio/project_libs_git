#ifndef FILES_H
#define FILES_H

#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>

typedef struct polynomial {
    int power;
    int coefficient;
} polynomial;

typedef struct sportsman {
    char *name;
    int result;
} sportsman;

typedef struct product {
    char *name;
    int price;
    int full_price;
    int count;
} product;

typedef struct order {
    char *name;
    int count;
} order;

void writeMatrixInFile (const char *f_name, void_vector m);
void lab_19_exercise1(void_vector *matricies);
void writeFloatInFile(const char *file_name, const char *format, void_vector f);
void lab_19_exercise2(void_vector *f);
void operation (int a, int b, char operator, int *res);
void writeStrInFile(const char *file_name, const char *str);
void writeExpressionWith1or2opsInFile(int a, int b, int c, char op1, char op2, int result);
int isValidOperator(char c);
void lab_19_exercise3(int *res);
int isStrContainCharSequence(char *str, char *sequence);
void lab_19_exercise4(char *str);
void lab_19_exercise5();
void lab_19_exercise6(float x, void_vector *v);
void lab_19_exercise7(void_vector *nums);
void lab_19_exercise8(void_vector *matrices);
void lab_19_exercise9(int n, void_vector *team);
int compareSportsmans(const void *p1, const void *p2);
void lab_19_exercise10(void_vector *v);

#endif //FILES_H
