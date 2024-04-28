#include <stdio.h>
#include <files/files.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>



//функции для записи специфичных типов:
void writeMatrixInFile (const char *f_name, void_vector m) {
    FILE *write = fopen(f_name, "w");
    if (write == NULL)
        perror("open file error");

    for (int i = 0; i < m.size; i++) {
        matrix mat;
        void_vector_getValueByPos(&m, i, &mat);
        fprintf(write, "%d\n", mat.nCols);
    }
}
