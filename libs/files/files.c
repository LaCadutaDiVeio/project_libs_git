#include <stdio.h>
#include <files/files.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>
#include <malloc.h>
#include "../test/test_set.h"


/*За отличную идею с вводом и выводом через пустые вектора спасибо
моему прекрасному, умному и доброму коллеге SS_ryzen*/

//функции для записи специфичных типов:
void writeMatrixInFile(const char *f_name, void_vector m) {
    FILE *write = fopen(f_name, "w");
    if (write == NULL)
        perror("open file error");

    for (int i = 0; i < m.size; i++) {
        matrix mat;
        void_vector_getValueByPos(&m, i, &mat);
        fprintf(write, "%d\n", mat.nRows);
        for (int row = 0; row < mat.nRows; row++) {
            for (int col = 0; col < mat.nCols; col++) {
                fprintf(write, "%d ", mat.values[row][col]);
            }
            fprintf(write, "\n");
        }
    }

    fclose(write);
}

void lab_19_exercise1(void_vector *matricies) {
    FILE *file = fopen("data_for_tasks/exercise01.txt", "r");
    if (file == NULL)
        perror("cant acces file");

    int n;
    while (fscanf(file, "%d", &n) == 1) {
        int *values = (int *) malloc(sizeof(int) * n * n);
        for (int i = 0; i < n * n; i++) {
            fscanf(file, "%d", &values[i]);
        }
        matrix mat = createMatrixFromArray(values, n, n);
        transposeMatrix(&mat);
        void_vector_pushBack(matricies, &mat);
    }
    writeMatrixInFile("data_for_tasks/exercise01.txt", *matricies);
    fclose(file);
}

//если честно, до этой лабы даже не знал, что форматную строку можно передать как аргумент
void writeFloatInFile(const char *file_name, const char *format, void_vector f) {
    FILE *write = fopen(file_name, "w");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < f.size; i++) {
        float f_format;
        void_vector_getValueByPos(&f, i, &f_format);
        fprintf(write, format, f_format);
    }

    fclose(write);
}

void lab_19_exercise2(void_vector *f) {
    FILE *file = fopen("data_for_tasks/exercise02.txt", "r");
    if (file == NULL)
        perror("cant acces file");

    float fl;
    while (fscanf(file, "%f", &fl) == 1) {
        void_vector_pushBack(f, &fl);
    }
    writeFloatInFile("data_for_tasks/exercise02.txt", "%f ", *f);

    fclose(file);
}

void operation(int a, int b, char operator, int *res) {
    //о боже, неужели первое практическое применение switch-case!!!
    switch (operator) {
        case '+': *res = a + b;
            break;
        case '-': *res = a - b;
            break;
        case '*': *res = a * b;
            break;
        case '/':
            if (b != 0) {
                *res = a / b;
            } else {
                printf("Error: Division by zero is not allowed.\n");
                return;
            }
            break;
        default:
            printf("Error: Invalid operator.\n");
            return;
    }
}

void lab_19_exercise3(int *res) {
    FILE *file = fopen("data_for_tasks/exercise03.txt", "r");
    if (file == NULL)
        perror("cant acces file");


}
