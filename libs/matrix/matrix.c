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
    for (size_t i = 0u; i < m.nRows; i++) {
        for (size_t j = 0u; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);

        printf("\n");
    }
}

