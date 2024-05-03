#include <stdio.h>
#include <files/files.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>
#include <malloc.h>
#include <string_/string_.h>


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
        case '+':
            *res = a + b;
            break;
        case '-':
            *res = a - b;
            break;
        case '*':
            *res = a * b;
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

int isValidOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void writeStrInFile(const char *file_name, const char *str) {
    FILE *write = fopen(file_name, "w");
    if (write == NULL)
        perror("cant access file");

    fprintf(write, str);

    fclose(write);
}

int doExpressionWith1or2ops(int a, int b, int c, char op1, char op2) {
    int result;
    if (!isValidOperator(op2)) {
        //сначала вариант для одного оператора
        operation(a, b, op1, &result);
    } else {
        if (op1 != '*' || op2 != '/') {
            if (op2 == '*' || op2 == '/') {
                operation(b, c, op2, &result);
                operation(a, result, op1, &result);
            } else {
                operation(a, b, op1, &result);
                operation(result, c, op2, &result);
            }
        } else {
            operation(a, b, op1, &result);
            operation(result, c, op2, &result);
        }
    }

    return result;
}

void writeExpressionWith1or2opsInFile(int a, int b, int c, char op1, char op2, int result) {
    FILE *write = fopen("data_for_tasks/exercise03.txt", "w");
    if (write == NULL)
        perror("cant acces file");
    fprintf(write, "%d %c %d", a, op1, b);
    if (isValidOperator(op2))
        fprintf(write, " %c %d", op2, c);
    fprintf(write, " = %d", result);

    fclose(write);
}

void lab_19_exercise3(int *res) {
    FILE *file = fopen("data_for_tasks/exercise03.txt", "r");
    if (file == NULL)
        perror("cant acces file");

    int a, b, c;
    char op1, op2;
    fscanf(file, "%d %c %d %c %d", &a, &op1, &b, &op2, &c);
    int result = doExpressionWith1or2ops(a, b, c, op1, op2);
    fclose(file);
    writeExpressionWith1or2opsInFile(a, b, c, op1, op2, result);

    *res = result;
}

int isStrContainCharSequence(char *str, char *sequence) {
    int len_sequence = strlen_(sequence);
    int i_sequence = 0;

    while (*str != '\0') {
        if (*str == sequence[i_sequence]) {
            i_sequence++;
        } else {
            i_sequence = 0;
        }

        if (i_sequence == len_sequence)
            return 1;

        str++;
    }

    return 0;
}

void lab_19_exercise4(char *sequence) {
    FILE *file = fopen("data_for_tasks/exercise04.txt", "r");
    if (file == NULL)
        perror("cant acces file");

    void_vector words = void_vector_create(0, sizeof(char*));
    char read[MAX_STRING_SIZE];
    while (fscanf(file, "%s", &read) == 1) {
        if (isStrContainCharSequence(read, sequence))
            void_vector_pushBack(&words, read);
    }
    fclose(file);

    FILE *write = fopen("data_for_tasks/exercise04.txt", "w");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < words.size; i++) {
        void_vector_getValueByPos(&words, i, read);
        fprintf(write, "%s ", read);
    }

    fclose(write);
}



