#include <matrix/matrix.h>

#include <stdio.h>
#include <memory.h>
#include <algorithms/algorithms.h>
#include <stdarg.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

#include <array/array.h>


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            values[i][j] = 0;

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
    long long *values = (long long *) malloc(sizeof(long long) * m->nRows);
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

            if (((i == j) && (sum != 1)) || ((i != j) && (sum != 0)))
                return false;
        }
    }

    return true;
}

//функция раюотает только для квадратных матриц 3x3
//можно немного изменить для любых квадратныых матриц
long long findSumOfMaxesOfPseudoDiagonal_forSquaresONLY(matrix m) {
    int n = 3;
    int max_diagonals[5] = {0};
    long long sum = 0;

    for (size_t i = 0; i < n; i++)
        m.values[i][i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int diag_ind = i - j + (n - 1);
            max_diagonals[diag_ind] = max_(max_diagonals[diag_ind], m.values[i][j]);
        }
    }
    for (int i = 0; i < 2 * n - 1; i++) {
        sum += max_diagonals[i];
    }

    return sum;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    //исключаем главную диагональ
    for (size_t i = 0; i < m.nRows; i++)
        m.values[i][i] = 0;

    long long sum = 0;
    for (size_t i = 0; i < m.nCols + m.nRows - 1; ++i) {
        int row = max_(0, m.nRows - i - 1);
        int col = max_(0, i - m.nRows + 1);

        int max_value = INT_MIN;
        while (row < m.nRows && col < m.nCols) {
            max_value = max_(max_value, m.values[row][col]);
            row++;
            col++;
        }
        sum += max_value;
    }

    return sum;
}

//короче, я хз, как выбирается область, но буду думать,
//что это область конусом с вершиной в максимальном элементе матрицы
int getMinInArea(matrix m) {
    position max_el = getMaxValuePos(m);
    //printf("%d %d", max_el.rowIndex, max_el.colIndex);
    int min_el = INT_MAX;
    for (int i = 0; i < max_el.rowIndex + 1; i++) {
        //printf(" a ");
        for (int j = 0; j < max_el.colIndex + 1; j++) {
            if (abs(max_el.colIndex - j) <= abs(max_el.rowIndex - i)) {
                min_el = min_(min_el, m.values[i][j]);
            }
            /*
             * эта проверка основана на визуальном представлении
             * модуля линейной функции
             */
        }
    }

    return min_el;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float *values_by_criteria = malloc(sizeof(int) * m.nRows);
    for (size_t i = 0; i < m.nRows; i++)
        values_by_criteria[i] = criteria(m.values[i], m.nCols);

    //insertionSort
    for (int i = 1; i < m.nRows; i++) {
        float k = values_by_criteria[i];
        int j = i; //column
        while ((k < values_by_criteria[j - 1]) && j > 0) {
            values_by_criteria[j] = values_by_criteria[j - 1];
            swapRows(m, j, j - 1);
            j--;
        }
        values_by_criteria[j] = k;
    }
}

void sortByDistances(matrix *mat) {
    insertionSortRowsMatrixByRowCriteriaF(*mat, getDistance);
}

int countEqClassesByRowsSum(matrix m) {
    long long *sums = (long long *) malloc(sizeof(long long) * m.nRows);
    for (size_t i = 0; i < m.nRows; ++i) {
        long long sum = 0;
        for (size_t j = 0; j < m.nCols; ++j)
            sum += m.values[i][j];

        sums[i] = sum;
    }
    qsort(sums, m.nRows, sizeof(long long), cmp_long_long);

    return countNUnique(sums, m.nRows);
}

int getNSpecialElement(matrix m) {
    int res = 0;

    for (size_t i = 0; i < m.nCols; i++) {
        int sum = 0;
        for (size_t j = 0; j < m.nRows; j++) {
            sum += m.values[j][i];
        }
        for (size_t j = 0; j < m.nRows; j++) {
            if (m.values[j][i] > (sum - m.values[j][i]))
                res++;
        }
    }


    return res;
}

//в getLeftMin(matrix m) нет смысла, так как есть getMinValuePos
void swapPenultimateRow(matrix *m) {
    position pos = getMinValuePos(*m);

    const int temp = m->values[m->nRows - 2][0];
    for (size_t i = 0; i < m->nCols; i++)
        m->values[m->nRows - 2][i] = m->values[i][pos.colIndex];

    m->values[m->nRows - 2][m->nRows - 2] = temp;
}

int isNonDescendingSorted(int *array, int size) {
    for (size_t i = 1; i < size; i++) {
        if (array[i] < array[i - 1])
            return 0;
    }

    return 1;
}

int hasAllNonDescendingRows(matrix m) {
    for (size_t i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return 0;
    }

    return 1;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int res = 0;
    for (size_t i = 0; i < nMatrix; i++)
        if (hasAllNonDescendingRows(ms[i]))
            res++;

    return res;
}

int countValues(const int *a, int n, int value) {
    int res = 0;
    for (size_t i = 0; i < n; ++i)
        if (a[i] == value)
            ++res;

    return res;
}

int countZeroRows(matrix m) {
    int res = 0;
    for (size_t i = 0; i < m.nRows; i++) {
        int zeros = countValues(m.values[i], m.nCols, 0);
        if (zeros == m.nCols)
            res++;
    }

    return res;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int max_rows = INT_MIN;
    for (size_t i = 0; i < nMatrix; i++) {
        int zeros = countZeroRows(ms[i]);

        max_rows = max_(max_rows, zeros);
    }

    for (size_t i = 0; i < nMatrix; i++) {
        int zeros = countZeroRows(ms[i]);
        if (zeros == max_rows)
            outputMatrix(ms[i]);
    }
}

//Я так понял, имеется ввиду максимальный модуль числел
int getMatrixNorm(const matrix m) {
    //т.к. имеем дело с модулем - min значение = 0
    int max_el = 0;
    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++) {
            int norm = abs(m.values[i][j]);
            max_el = max_(max_el, norm);
        }
    }

    return max_el;
}

void printMatrixWithMinNorm(matrix *ms, int nMatrix) {
    int min_norm = INT_MAX;
    int norms_arr[nMatrix];

    for (size_t i = 0; i < nMatrix; i++) {
        norms_arr[i] = getMatrixNorm(ms[i]);
        min_norm = min_(min_norm, norms_arr[i]);
    }

    for (size_t i = 0; i < nMatrix; i++) {
        if (norms_arr[i] == min_norm)
            outputMatrix(ms[i]);
    }
}

int getNSpecialElement2(matrix m) {
    int res = 0;
    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++) {
            bool is_decreasing_left = true;
            bool is_increasing_right = true;

            for (size_t k = 0; k < m.nCols; k++) {
                if (k > j && m.values[i][j] > m.values[i][k])
                    is_increasing_right = false;
                if (k < j && m.values[i][j] < m.values[i][k])
                    is_decreasing_left = false;
            }
            if (is_decreasing_left && is_increasing_right)
                res++;
        }
    }

    return res;
}

double getScalarProduct(int *a, int *b, int n) {
    double res = 0;
    for (int i = 0; i < n; i++) {
        res += (a[i] * b[i]);
    }

    return res;
}

double getCosine(int *a, int *b, int n) {
    double res = getScalarProduct(a, b, n);
    float a_len = getDistance(a, n);
    float b_len = getDistance(b, n);

    if ((a_len * b_len) == 0) {
        error_alert("can`t process division by zero.");
    }

    return res / (a_len * b_len);
}

int getVectorIndexWithMaxAngle(matrix mat, int *b) {
    int res = INT_MIN;
    double max_ang = DBL_MIN;

    for (size_t i = 0; i < mat.nRows; i++) {
        double ang = getCosine(b, mat.values[i], mat.nCols);
        if (ang > max_ang) {
            res = i;
            max_ang = ang;
        }
    }

    return res;
}

long long getScalarProductRowAndCol(matrix mat, int row, int col) {
    long long res = 0;

    for (size_t i = 0; i < mat.nCols; ++i)
        res += (mat.values[row][i] * mat.values[i][col]);

    return res;
}

long long getSpecialScalarProduct(matrix m, int n) {
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);

    /* min.rowIndex -= 1;
     min.colIndex -= 1;
     max.rowIndex -= 1;
     max.colIndex -= 1;*/

    return getScalarProductRowAndCol(m, max.rowIndex, min.colIndex);
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

long long getLongSum(int *a, int n) {
    long long res = 0;
    for (size_t i = 0; i < n; ++i)
        res += a[i];

    return res;
}

int max_(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int min_(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

float getDistance(int *array, int size) {
    float ret = 0;
    for (size_t i = 0; i < size; i++)
        ret += (array[i] * array[i]);

    return sqrtf(ret);
}

//Честно, не могу понять работу qsort со всеми этими их compare
//функция любезно позаимствована у коллеги ^.^
int cmp_long_long(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

int countNUnique(long long *array, const size_t size) {
    int count = 1;

    //раз массив будет отсортирован, моэно позволить себе максимально топорную реализацию
    long long record = array[0];
    for (size_t i = 1; i < size; ++i) {
        if (array[i] != record) {
            ++count;
            record = array[i];
        }
    }

    return count;
}



//------------------------