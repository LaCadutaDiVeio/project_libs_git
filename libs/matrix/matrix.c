#include <matrix/matrix.h>

#include <stdio.h>
#include <memory.h>
#include <algorithms/algorithms.h>
#include <stdarg.h>
#include <float.h>
#include <stdbool.h>

#include <array/array.h>


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

void freeMemMatrices_(size_t num, ...) {
    va_list valist;
    va_start(valist, num);
    for (size_t i = 0; i < num; i++) {
        matrix *mat = va_arg(valist, matrix*);
        freeMemMatrix(mat);
    }
    va_end(valist);
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

void copyMatrix(const matrix m1, matrix *m2) {
    memcpy(m2, &m1, sizeof(matrix));
}

void swapRows(matrix m, size_t i, size_t j) {
    int *temp = m.values[i]; //т.к. values - это по сути строки
    memcpy(&m.values[i], &m.values[j], sizeof(int *));
    memcpy(&m.values[j], &temp, sizeof(int *));
}

void swapColumns(matrix m, size_t i, size_t j) {
    for (size_t k = 0; k < m.nRows; k++) {
        int temp = m.values[k][i];

        memcpy(&m.values[k][i], &m.values[k][j], sizeof(int));
        memcpy(&m.values[k][j], &temp, sizeof(int));
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *values_by_criteria = malloc(sizeof(int) * m.nRows);
    for (size_t i = 0; i < m.nRows; i++)
        values_by_criteria[i] = criteria(m.values[i], m.nCols);

    //insertionSort
    for (int i = 1; i < m.nRows; i++) {
        int k = values_by_criteria[i];
        int j = i; //column
        while ((k < values_by_criteria[j - 1]) && j > 0) {
            values_by_criteria[j] = values_by_criteria[j - 1];
            swapRows(m, j, j - 1);
            j--;
        }
        values_by_criteria[j] = k;
    }
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *values_by_criteria = malloc(sizeof(int) * m.nCols);
    for (size_t i = 0; i < m.nCols; i++) {
        int *column = malloc(sizeof(int) * m.nRows);
        for (size_t j = 0; j < m.nRows; j++) {
            column[j] = m.values[j][i];
        }
        values_by_criteria[i] = criteria(column, m.nRows);
    }
    for (int i = 1; i < m.nRows; i++) {
        int k = values_by_criteria[i];
        int j = i;
        while ((k < values_by_criteria[j - 1]) && j > 0) {
            values_by_criteria[j] = values_by_criteria[j - 1];
            swapColumns(m, j, j - 1);
            j--;
        }
        values_by_criteria[j] = k;
    }
    /*for ( int i = m.nCols - 1; i > 0; i-- ) {
        int minPos;
        for (int k = 0; k < m.nCols; k++)
        if ( max != i ) {
            swapInt( values_by_criteria + max, values_by_criteria + i );
            for ( size_t j = 0u; j < m.nRows; ++j )
                swapInt( &m.values[ j ][ max ], &m.values[ j ][ i ] );
        }
    }*/

}


int isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

int areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols)
        return 0;
    for (size_t i = 0; i < m1->nRows; i++) {
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols))
            return 0;
    }

    return 1;
}

int isEMatrix(matrix *m) {
    //единичной может быть только квадратная матрица
    if (!isSquareMatrix(m))
        return 0;

    for (size_t i = 0; i < m->nRows; i++) {
        if (m->values[i][i] != 1)
            return 0;
        for (size_t j = 0; j < m->nCols; j++) {
            if (i != j && m->values[i][j] != 0)
                return 0;
        }
    }
    return 1;
}

int isSymmetricMatrix(matrix *m) {
    matrix transpose;
    copyMatrix(*m, &transpose);
    transposeMatrix(&transpose);

    return areTwoMatricesEqual(m, &transpose);
}

void transposeSquareMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return;

    for (size_t i = 0; i < m->nRows - 1; i++) {
        for (size_t j = i + 1; j < m->nRows; j++) {
            swapInt(&m->values[i][j], &m->values[j][i]);
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix transpose = getMemMatrix(m->nCols, m->nRows);
    for (int column = 0; column < m->nCols; column++) {
        for (int i = 0; i < m->nRows; i++) {
            transpose.values[column][i] = m->values[i][column];
        }
    }
    memcpy(m, &transpose, sizeof(matrix));
}

position getMinValuePos(matrix m) {
    position pos;
    int min = INT_MAX;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                pos.rowIndex = i;
                pos.colIndex = j;
                min = m.values[i][j];
            }
        }
    }
    return pos;
}

position getMaxValuePos(matrix m) {
    position pos;
    int max = INT_MIN;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                pos.rowIndex = i;
                pos.colIndex = j;
                max = m.values[i][j];
            }
        }
    }
    return pos;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}


//LAB_16 functions

void swapColsWithMinMaxElements(matrix *m) {
    int min_val = m->values[0][0];
    int max_val = m->values[0][0];
    int min_row = 0;
    int max_row = 0;

    for (int i = 0; i < m->nRows; ++i) {
        for (int j = 0; j < m->nCols; ++j) {
            if (m->values[i][j] > max_val) {
                max_val = m->values[i][j];
                max_row = i;
            } else if (m->values[i][j] < min_val) {
                min_val = m->values[i][j];
                min_row = i;
            }
        }
    }
    swapRows(*m, min_row, max_row);
}

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void sortColsByMinElement(matrix m) {
    int *values = malloc(sizeof(int) * m.nCols);
    for (size_t i = 0; i < m.nCols; i++) {
        int *col = malloc(sizeof(int) * m.nRows);
        for (size_t j = 0; j < m.nRows; j++)
            col[j] = m.values[j][i];

        values[i] = getMin(col, m.nRows);
    }
    for (int i = 0; i < m.nCols - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < m.nCols; j++)
            if (values[j] < values[minPos])
                minPos = j;
        swapInt(&values[i], &values[minPos]);
        swapColumns(m, i, minPos);
    }
}

matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m1.nRows)
        error_alert("can't multiple this matrices");

    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    for (size_t i = 0; i < result.nRows; i++) {
        for (size_t j = 0; j < result.nCols; j++) {
            result.values[i][j] = 0;
            for (size_t k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(m))
        *m = mulMatrices(*m, *m);
    else
        *m = *m;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long *values = (long long *)malloc(sizeof(long long) * m->nRows);
    for (size_t i = 0; i < m->nRows; i++) {
        values[i] = getLongSum(m->values[i], m->nCols);
    }
    if (isUnique(values, m->nRows)) {
        transposeMatrix(m);
    }
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows && m1.nCols != m2.nCols)
        return false;
    for (size_t i = 0; i < m1.nRows; i++) {
        for (size_t j = 0; j < m2.nCols; j++) {
            int sum = 0;
            for (size_t k = 0; k < m1.nCols; k++)
                sum += (m1.values[i][k] * m2.values[k][j]);

            if ((i == j) && (sum != 1))
                return false;
        }
    }

    return true;
}





//------------------------
int getSum(int *a, int n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

int getMax(int *a, int n) {
    int max = a[0];
    for (size_t i = 1u; i < n; ++i)
        if (a[i] > max)
            max = a[i];

    return max;
}

int getMin(int *a, int n) {
    int min = a[0];
    for (size_t i = 1u; i < n; ++i)
        if (min >= a[i])
            min = a[i];

    return min;
}

int isUnique(long long *a, int n) {
    for (size_t i = 0; i < n; ++i)
        for (size_t j = i + 1; j < n; ++j)
            if (a[i] == a[j])
                return 0;

    return 1;
}

long long getLongSum( int *a, int n ) {
    long long res = 0;
    for ( size_t i = 0; i < n; ++i )
        res += a[ i ];

    return res;
}

//------------------------