
#ifndef PROJECT_LIBS_MATRIX_H
#define PROJECT_LIBS_MATRIX_H

#include <malloc.h>
#include <stdbool.h>

//void error_alert(char *msg);

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
void freeMemMatrices_(size_t num, ...);
void inputMatrix(matrix *m);
void inputMatrices(matrix *m, int matrices);
void outputMatrix(matrix m);
void outputMatrices(const matrix *m, int matrices);
void copyMatrix(const matrix m1, matrix *m2);
void swapRows(matrix m, size_t i, size_t j);
void swapColumns(matrix m, size_t i, size_t j);
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));
void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));
int isSquareMatrix(matrix *m);
int areTwoMatricesEqual(matrix *m1, matrix *m2);
int isEMatrix(matrix *m);
int isSymmetricMatrix(matrix *m);
void transposeSquareMatrix(matrix *m);
void transposeMatrix(matrix *m);
position getMinValuePos(matrix m);
position getMaxValuePos(matrix m);
matrix createMatrixFromArray(const int *a, int nRows, int nCols);
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);
//-------------------------------
void swapColsWithMinMaxElements(matrix *m);
void sortRowsByMinElement(matrix m);
void sortColsByMinElement(matrix m);
matrix mulMatrices(matrix m1, matrix m2);
void getSquareOfMatrixIfSymmetric(matrix *m);
int isUnique(long long *a, int n);
long long getLongSum( int *a, int n );
void transposeIfMatrixHasNotEqualSumOfRows(matrix *m);
bool isMutuallyInverseMatrices(matrix m1, matrix m2);

//----
int getSum(int *a, int n);
int getMax( int *a, int n );
int getMin( int *a, int n );
//----



#endif //PROJECT_LIBS_MATRIX_H
