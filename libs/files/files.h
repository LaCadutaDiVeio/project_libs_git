#ifndef FILES_H
#define FILES_H

#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>

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

#endif //FILES_H
