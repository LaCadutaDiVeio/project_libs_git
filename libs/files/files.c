#include <stdio.h>
#include <files/files.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>
#include <malloc.h>


/*За отличную идею с вводом и выводом через пустые вектора спасибо
моему прекрасному, умному и доброму коллеге SS_ryzen*/

//функции для записи специфичных типов:
void writeMatrixInFile (const char *f_name, void_vector m) {
    FILE *write = fopen(f_name, "w");
    if (write == NULL)
        perror("open file error");

    for (int i = 0; i < m.size; i++) {
        matrix mat;
        void_vector_getValueByPos(&m, i, &mat);
        fprintf(write, "%d\n", mat.nCols);
        for (int row = 0; row < mat.nRows; row++) {
            for (int col = 0; col < mat.nCols; col++) {
                fprintf(write, "%d", mat.values[row][col]);
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
        int *values = (int*)malloc(sizeof(int) * n * n);
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
