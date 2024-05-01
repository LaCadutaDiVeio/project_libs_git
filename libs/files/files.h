#ifndef FILES_H
#define FILES_H

#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>

void writeMatrixInFile (const char *f_name, void_vector m);
void lab_19_exercise1(void_vector *matricies);
void writeFloatInFile(const char *file_name, const char *format, void_vector f);
void lab_19_exercise2(void_vector *f);
void operation (int a, int b, char operator, int *res);
void lab_19_exercise3(int *res);

#endif //FILES_H
