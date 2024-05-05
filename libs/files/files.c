#include <stdio.h>
#include <files/files.h>
#include <matrix/matrix.h>
#include <vectors_void/void_vector.h>
#include <malloc.h>
#include <string_/string_.h>
#include <math.h>
#include <algorithms/algorithms.h>


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
    writeFloatInFile("data_for_tasks/exercise02.txt", "%E ", *f);

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

    void_vector words = void_vector_create(0, sizeof(char *));
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

void lab_19_exercise5() {
    FILE *file = fopen("data_for_tasks/exercise05.txt", "r");
    if (file == NULL)
        perror("cant acces file");

    void_vector words = void_vector_create(0, sizeof(char *));
    char longest_word[MAX_STRING_SIZE];
    char buffer[MAX_STRING_SIZE];

    int max_len = 0;
    while (fgets(buffer, 100u, file) != NULL) {
        int len = 0;
        char word[MAX_STRING_SIZE];

        for (int i = 0; buffer[i] != '\0' && i < strlen_(buffer); i++) {
            if (isspace(buffer[i])) {
                if (len > max_len) {
                    max_len = len;
                    word[len] = '\0';
                    memcpy(&longest_word, &word, sizeof(char) * (len + 1));
                }
                len = 0;
                continue;
            }
            word[len] = buffer[i];
            len++;
        }

        if (max_len == 0) {
            memcpy(&longest_word, &buffer, sizeof(char) * MAX_STRING_SIZE);
        }

        //перед новой строкой обнуляем max;
        max_len = 0;

        void_vector_pushBack(&words, &longest_word);
    }

    FILE *write = fopen("data_for_tasks/exercise05.txt", "w");
    if (write == NULL)
        perror("cant acces file");
    char write_buf[MAX_STRING_SIZE];
    for (int i = 0; i < words.size; i++) {
        void_vector_getValueByPos(&words, i, &write_buf);
        fprintf(write, "%s\n", write_buf);
    }

    fclose(write);
}

void lab_19_exercise6(float x, void_vector *v) {
    FILE *file = fopen("data_for_tasks/exercise06.bin", "rb");
    if (file == NULL)
        perror("cant acces file");

    polynomial poly;
    while (fread(&poly, sizeof(polynomial), 1, file) == 1) {
        int res = poly.coefficient; //коэф. при x^0
        for (int i = 1; i <= poly.power; i++)
            res += poly.coefficient * pow(x, i);
        if (res != 0)
            void_vector_pushBack(v, &poly);
    }
    fclose(file);

    FILE *write = fopen("data_for_tasks/exercise06.bin", "wb");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < v->size; i++) {
        polynomial p;
        void_vector_getValueByPos(v, i, &p);
        fwrite(&p, sizeof(polynomial), 1, write);
    }
    fclose(write);
}

void lab_19_exercise7(void_vector *nums) {
    FILE *file = fopen("data_for_tasks/exercise07.bin", "rb");
    if (file == NULL)
        perror("cant acces file");

    void_vector positive = void_vector_create(0, sizeof(int));
    void_vector negative = void_vector_create(0, sizeof(int));
    int num;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        if (num >= 0)
            void_vector_pushBack(&positive, &num);
        else
            void_vector_pushBack(&negative, &num);
    }

    fclose(file);

    FILE *write = fopen("data_for_tasks/exercise07.bin", "wb");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < positive.size; i++) {
        void_vector_getValueByPos(&positive, i, &num);
        fwrite(&num, sizeof(int), 1, write);
        void_vector_pushBack(nums, &num);
    }
    for (int i = 0; i < negative.size; i++) {
        void_vector_getValueByPos(&negative, i, &num);
        fwrite(&num, sizeof(int), 1, write);
        void_vector_pushBack(nums, &num);
    }

    fclose(write);
}

void lab_19_exercise8(void_vector *matrices) {
    FILE *file = fopen("data_for_tasks/exercise08.bin", "rb");
    if (file == NULL)
        perror("cant acces file");

    matrix m;
    while (fread(&m, sizeof(matrix), 1, file) == 1) {
        if (!isSymmetricMatrix(&m))
            transposeMatrix(&m);
        void_vector_pushBack(matrices, &m);
    }
    fclose(file);

    FILE *write = fopen("data_for_tasks/exercise07.bin", "wb");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < matrices->size; i++) {
        void_vector_getValueByPos(matrices, i, &m);
        fwrite(&m, sizeof(matrix), 1, write);
    }
    fclose(write);
}

int compareSportsmans(const void *p1, const void *p2) {
    sportsman a = *(sportsman *) p1;
    sportsman b = *(sportsman *) p2;

    return b.result - a.result;
}

void lab_19_exercise9(int n, void_vector *team) {
    FILE *file = fopen("data_for_tasks/exercise09.bin", "rb");
    if (file == NULL)
        perror("cant acces file");

    void_vector sportsmans = void_vector_create(0, sizeof(sportsman));
    sportsman sp;
    while (fread(&sp, sizeof(sportsman), 1, file) == 1) {
        void_vector_pushBack(&sportsmans, &sp);
    }

    fclose(file);

    qsort(sportsmans.data, sportsmans.size, sizeof(sportsman), compareSportsmans);

    FILE *write = fopen("data_for_tasks/exercise09.bin", "wb");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < n; i++) {
        void_vector_getValueByPos(&sportsmans, i, &sp);
        void_vector_pushBack(team, &sp);
        fwrite(&sp, sizeof(sportsman), 1, write);
    }

    fclose(write);
}

void lab_19_exercise10(void_vector *v) {

    FILE *f = fopen("data_for_tasks/exercise10f.bin", "rb");
    if (f == NULL)
        perror("cant acces file");
    FILE *g = fopen("data_for_tasks/exercise10g.bin", "rb");
    if (g == NULL)
        perror("cant acces file");

    void_vector orders = void_vector_create(0, sizeof(order));
    order ord;
    while (fread(&ord, sizeof(order), 1, g) == 1) {
        void_vector_pushBack(&orders, &ord);
    }
    fclose(g);

    product pr;
    while (fread(&pr, sizeof(product), 1, f) == 1) {
       for (int i = 0; i < orders.size; i++) {
           void_vector_getValueByPos(&orders, i, &ord);
           if (strcmp(pr.name, ord.name) == 0) {
               pr.count -= ord.count;
               pr.full_price -= pr.price * ord.count;
           }
       }
       if (pr.count > 0)
           void_vector_pushBack(v, &pr);
    }

    fclose(f);

    FILE *write = fopen("data_for_tasks/exercise10f.bin", "wb");
    if (write == NULL)
        perror("cant acces file");

    for (int i = 0; i < v->size; i++) {
        void_vector_getValueByPos(v, i, &pr);
        fwrite(&pr, sizeof(product), 1, write);
    }
    fclose(write);
}