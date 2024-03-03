#include <matrix/matrix.h>

#include <stdio.h>
#include <memory.h>
#include <algorithms/algorithms.h>
#include <float.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};

}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (size_t i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);
    m->values = NULL;
}

void freeMemMatrices(matrix *m, size_t matrices) {
    for (size_t i = 0; i < matrices; i++) {
        freeMemMatrix(&m[i]);
    }
}

void inputMatrix(matrix *m) {
    for (size_t i = 0; i < m->nRows; i++)
        for (size_t j = 0; j < m->nCols; j++)
            scanf("%d", &m->values[i][j]);
}

void outputMatrix(const matrix m) {
    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);

        printf("\n");
    }
}

void inputMatrices(matrix *m, int matrices) {
    for (size_t i = 0; i < matrices; i++)
        inputMatrix(&m[i]);
}

void outputMatrices(const matrix *m, int matrices) {
    for (size_t i = 0; i < matrices; i++)
        outputMatrix(m[i]);
}

void swapRows(matrix m, size_t i, size_t j) {
    int *temp = m.values[i]; //т.к. values - это по сути строки
    memcpy(&m.values[i], &m.values[j], sizeof(int*));
    memcpy(&m.values[j], &temp, sizeof(int*));
}

void swapColumns(matrix m, size_t i, size_t j) {
    for (size_t k = 0; k <  m.nRows; k++) {
        int temp = m.values[k][i];

        memcpy(&m.values[k][i], &m.values[k][j], sizeof(int));
        memcpy(&m.values[k][j], &temp, sizeof(int));
    }
}