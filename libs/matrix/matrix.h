
#ifndef PROJECT_LIBS_MATRIX_H
#define PROJECT_LIBS_MATRIX_H

#include <malloc.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);
void freeMemMatrix(matrix *m);
void freeMemMatrices(matrix *m, size_t matrices);
void inputMatrix(matrix *m);
void outputMatrix(matrix m);



#endif //PROJECT_LIBS_MATRIX_H
