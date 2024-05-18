#include <lab_20/lab_20.h>
#include <matrix/matrix.h>
#include <array/array.h>
#include <algorithms/algorithms.h>

//создание новоой ветки дерева
tree_node *getNode() {
    tree_node *node = (tree_node *) malloc(sizeof(tree_node));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
            node->is_end_of_word = 0;
        }
    }

    return node;
}

//добавление слова в словарь
void insertWordInTree(tree_node *root, const char *word) {//a=0 b =1 c =2   abc
    int alp_index;
    tree_node *node = root;
    /*проходим по всем буквам слова и создаём (или расширяем)
    ветку соответствующей буквы*/
    for (int i = 0; word[i]; i++) {
        alp_index = word[i] - 'a';
        if (!node->children[alp_index]) {
            node->children[alp_index] = getNode();
        }
        node = node->children[alp_index];//углубляемся в дерево
        //printf("%c", )
        node->count++;
    }
    node->is_end_of_word = 1;
}

int isNodeIsWord(tree_node *node) {
    return node->is_end_of_word;
}

char BAD_RESULT[] = {'-', '1', '\0'};

//найти слово в словаре
char *findWordInTree(tree_node *root, const char *prefix, int number) {
    //prefix - последовательность по котороу будет поиск
    //number - искомый порядковый номер
    tree_node *node = root;
    int alp_index;
    for (int i = 0; prefix[i]; i++) {
        //если нужной ветки не окажется - -1
        alp_index = prefix[i] - 'a';
        if (!node->children[alp_index]) {
            return BAD_RESULT;
        }
        node = node->children[alp_index];
    }

    //если ветка слишком мала - -1
    int count = node->count;
    if (number > count)
        return BAD_RESULT;

    //выведем слово:
    char *word = (char *) malloc(sizeof(char) * (strlen(prefix) + 10000000));
    strcpy(word, prefix);
    int len = strlen(prefix);

    if (isNodeIsWord(node)) {
        if (number == 1) {
            word[len] = '\0';
            return word;
        } else {
            number--;
        }
    }

    while (number > 0) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                count = node->children[i]->count;
                //шагая в ветку смотрим: если мы можем выбрать number слов в этой ветке -
                //выбираем, если нет, ищем невыбранное кол-во от number в следующей ветке.
                if (number <= count) {
                    word[len++] = 'a' + i;
                    node = node->children[i];//aaaa  1 a
                    if (isNodeIsWord(node)) {
                        if (number == 1) {
                            word[len] = '\0';
                            return word;
                        } else {
                            number--;
                        }
                    }
                    break;
                }
                number -= count;
            }
        }
    }
    word[len] = '\0';
    return word;
}

void freeTree(tree_node *node) {
    if (node == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTree(node->children[i]);

    free(node);
}

int lab_20_task_11() {
    printf("Введите кол-во слов и кол-во запросов:\n");
    int Q, N;
    scanf("%d %d", &Q, &N);

    tree_node *root = getNode();

    // Чтение слов из словаря
    printf("Вводите слова:\n");
    for (int i = 0; i < Q; i++) {
        char word[1000001];
        scanf("%s", word);
        insertWordInTree(root, word);
    }
    printf("Введите запросы:\n");

    // Обработка запросов
    for (int i = 0; i < N; i++) {
        int k;
        char prefix[101];
        printf("Запрос %d:", i + 1);
        scanf("%d %s", &k, prefix);
        char *result = findWordInTree(root, prefix, k);
        printf("  %s\n", result);
        free(result);
    }

    // Освобождение памяти
    freeTree(root);

    return 0;
}

int lab_20_task_11_FORTESTS(char *words, char *requests, char **testRequests) {
    tree_node *root = getNode();

    char *word = strtok(words, " ");
    while (word != NULL) {
        insertWordInTree(root, word);
        //printf( "%s ", word );
        word = strtok(NULL, " ");//классная штука, не знал о такой
    }

    char *request = strtok(requests, " ");
    int request_index = 0;
    while (request != NULL) {
        int k = atoi(request);
        request = strtok(NULL, " ");
        if (request == NULL)
            break;
        char *prefix = request;
        //printf( "%d %s ", k, prefix );
        request = strtok(NULL, " ");

        char *result = findWordInTree(root, prefix, k);
        //printf( "%s", result );
        if (strcmp(result, testRequests[request_index]) != 0) {
            //    free( result );
            freeTree(root);
            return 0;
        }

        //  free( result );
        request_index++;
    }
    freeTree(root);

    return 1;
}

void lab_20_task_01(matrix *m, int queries[][4], int size_q) {
    for (int i = 0; i < size_q; i++) {
        int *q = queries[i];
        for (int row = q[0]; row <= q[2]; row++) {
            for (int col = q[1]; col <= q[3]; col++) {
                m->values[row][col] += 1;
            }
        }
    }
}

//по сути задача сводится просто к подсчёты очков соседей:
int countPointsFromNeighbours(matrix *m,/*передача клетки:*/ int row, int col) {
    int top = max_(0, row - 1);
    int bot = min_(m->nRows - 1, row + 1);
    int left = max_(0, col - 1);
    int right = min_(m->nCols - 1, col + 1);
    //с учётом угловых и крайних клеток

    int count_p_neighbours = 0;
    for (int i = top; i <= bot; i++) {
        for (int j = left; j <= right; j++) {
            if (!(col == j && row == i) && m->values[i][j])
                count_p_neighbours++;
        }
    }
    return count_p_neighbours;
}

void lab_20_task_02(matrix *m, matrix *m_res) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            int points = countPointsFromNeighbours(m, i, j);

            m_res->values[i][j] = 1;
            if (m->values[i][j] == 1) {
                if (points < 2 || points > 3)
                    m_res->values[i][j] = 0;
            } else {
                if (points != 3)
                    m_res->values[i][j] = 0;
            }
        }
    }
}

void getPointsFromNeighbours(matrix *m, int row, int col, void_vector *neighbours, int filter) {
    /*int top = max_(0, row - filter/2);
    int bot = min_(m->nRows - filter/2 + 1, row + filter/2);
    int left = max_(0, col - filter/2);
    int right = min_(m->nCols - filter/2 + 1, col + filter/2);*/

    int half_filter = filter / 2;
    int top = max_(0, row - half_filter);
    int bot = min_(m->nRows - 1, row + half_filter);
    int left = max_(0, col - half_filter);
    int right = min_(m->nCols - 1, col + half_filter);

    for (int i = top; i <= bot; i++) {
        for (int j = left; j <= right; j++) {
            if (!(col == j && row == i))
                void_vector_pushBack(neighbours, &m->values[i][j]);
        }
    }
}

/*честно, я до сих пор не до конца понимаю, как работает вся эта
ерунда с указателями, пример compare для qsort был в методичке, а
значит мне не стыдно :)*/
int compareNeighbourPoints(const void *pa, const void *pb) {
    int a = *(const int *) pa;
    int b = *(const int *) pb;

    return a - b;
}

void lab_20_task_03(matrix *m, matrix *m_res, int filter) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            //пропуск краевых
            if (i < filter / 2 || i >= m->nRows - filter / 2 || j < filter / 2 || j >= m->nCols - filter / 2) {
                m_res->values[i][j] = m->values[i][j];
            } else {
                void_vector neighbors = void_vector_create(0, sizeof(int));
                getPointsFromNeighbours(m, i, j, &neighbors, filter);
                qsort(neighbors.data, neighbors.size, neighbors.size_of_type, compareNeighbourPoints);

                int middle;
                void_vector_getValueByPos(&neighbors, neighbors.size / 2, &middle);
                m_res->values[i][j] = middle;
            }
        }
    }
}

void lab_20_task_04(char *domains[], int amount, void_vector *sub_domains) {
    for (int i = 0; i < amount; i++) {
        char domain[MAX_DOMAIN_SIZE];
        memset(domain, 0, sizeof(char) * MAX_DOMAIN_SIZE);
        int visits_count = 0;

        sscanf(domains[i], "%d %s", &visits_count, &domain);
        void_vector tokens = void_vector_create(0, sizeof(char *));
        char *token = strtok(domain, ".");
        while (token != NULL) {
            void_vector_pushBack(&tokens, &token);
            token = strtok(NULL, ".");
        }

        for (int j = 0; j < tokens.size; j++) {
            char new_dom[MAX_DOMAIN_SIZE];
            memset(new_dom, 0, sizeof(char) * MAX_DOMAIN_SIZE);
            for (int k = j; k < tokens.size; k++) {
                char *tok;
                void_vector_getValueByPos(&tokens, k, &tok);

                strcat(new_dom, tok);
                if (k != tokens.size - 1) {
                    strcat(new_dom, ".");
                }
            }

            int is_in = 0;
            for (int n = 0; n < sub_domains->size; n++) {
                Domain d;
                void_vector_getValueByPos(sub_domains, n, &d.name);

                if (strcmp(new_dom, d.name) == 0) {
                    is_in = 1;
                    d.count += visits_count;
                    void_vector_setValue(sub_domains, n, &d);
                    break;
                }
            }

            if (!is_in) {
                Domain n_d;
                strcpy(n_d.name, new_dom);
                n_d.count = visits_count;
                void_vector_pushBack(sub_domains, &n_d);
            }
        }
    }
}

//в моей задумке понадобится min для 3 значений
int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;

    return min;
}

/*
Вообще, хотел изначально использовать другой подход:
в доп. матрице в каждой ячейке отмечать, сколько потенциальных
матриц может заканчиваться в ней, однако у меня получилось реализовать
такой подход только для квадратных матриц

как работает алгоритм из методички мне, если честно, не до конца понятно
*/

void lab_20_task_05(matrix *m, int *sub_m) {
    matrix dp = getMemMatrix(m->nRows, m->nCols);
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            //первая клетка
            if (i == 0 && m->values[i][j] == 1) {
                dp.values[i][j] = 1;
            } else if (m->values[i][j] == 1) {
                dp.values[i][j] = dp.values[i - 1][j] + 1;// + 1 т.к. в клетке уже 1
            }
        }
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            for (int k = j + 1; k < m->nCols + 1; k++) {
                int n = dp.values[i][j];
                for (int t = j; t < k; t++) {
                    n = min_(n, dp.values[i][t]);
                }
                (*sub_m) += n;
            }
        }
    }
}

void lab_20_task_06(char *pattern, char *result) {
    int n = strlen(pattern);
    if (pattern[n - 1] == 'D')
        pattern[n] = 'D';
    else
        pattern[n] = 'I';
    n++;

    char* num = (char*)malloc(sizeof(char) * (n + 2));
    strcopy(pattern, pattern + n, num);
    char values[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int ind = 0;
    for (int i = 0; i <= n; i++) {
        if (num[i] == 'I') {
            num[i] = values[ind++];
        }
    }

    int is_D = 0;
    int count_D = 0;

    for (int i = 0; i <= n; i++) {
        if (num[i] == 'D') {
            is_D = 1;
            count_D++;
        }

        if (is_D && (num[i] != 'D')) {
            is_D = 0;
            int k =  i - 1;
            while (count_D > 0) {
                num[k--] = values[ind++];
                count_D--;
            }
        }
    }

    num[n + 1] = '\0';
    strcpy(result, num);
}

int findMaxIndex(int* nums, int start, int end) {
    int maxIndex = start;
    for (int i = start; i <= end; i++) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}


tree_arr* constructTreeArr(int *arr, int start, int end) {
    if (start > end)
        return NULL;

    //int ind_max = findMaxIndex(arr, start, end);
    int ind_max = getMaxElementIndexInArray(arr + start, end - start + 1);
    //outputArray_(arr + start, end - start + 1);
    ind_max += start;// индекс в исходном массиве

    tree_arr *node = (tree_arr*)malloc(sizeof(tree_arr));
    node->value = arr[ind_max];
    node->left_node = node->right_node = NULL;
    //printf(" %d ", node->value);

    node->left_node = constructTreeArr(arr, start, ind_max - 1);
    node->right_node = constructTreeArr(arr, ind_max + 1, end);

    return node;
}

void freeTreeArr(tree_arr *root) {
    if (root == NULL)
        return;

    freeTreeArr(root->left_node);
    freeTreeArr(root->right_node);
    free(root);
}

/*void printTreeArr(tree_arr *root) {
    if (root == NULL) {
        printf("null ");
        return;
    }
    printf("%d ", root->value);
    printTreeArr(root->left_node);
    printTreeArr(root->right_node);
}*/
int getDeep(tree_arr *root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = getDeep(root->left_node);
        int rightHeight = getDeep(root->right_node);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}

void printByLevel(tree_arr* root, int level) {
    if (root == NULL) {
        printf("ошибка ветви! ");
        return;
    }
    if (level == 1) {
        printf("%d ", root->value);
    } else if (level > 1) {
        if (root->left_node != NULL && root->right_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            printByLevel(root->left_node, level - 1);
            printByLevel(root->right_node, level - 1);
        } else if (root->left_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            printByLevel(root->left_node, level - 1);
            if (level - 1 == 1)
                printf("null ");
        } else if (root->right_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            if (level - 1 == 1)
                printf("null ");
            printByLevel(root->right_node, level - 1);
        } else {
            //ветка для отладки
        }
    }
}

void printTreeLevelByLevel(tree_arr * root) {
    int height = getDeep(root);
    for (int i = 1; i <= height; i++) {
        printByLevel(root, i);
        //printf("\n");
    }
}

void printByLevel_FOR_TESTS(tree_arr* root, int level, char *res) {
    if (root == NULL) {
        printf("ошибка ветви! ");
        return;
    }
    if (level == 1) {
        char num_str[10];
        sprintf(num_str, " %d", root->value);
        strcat(res, num_str);
    } else if (level > 1) {
        if (root->left_node != NULL && root->right_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            printByLevel_FOR_TESTS(root->left_node, level - 1, res);
            printByLevel_FOR_TESTS(root->right_node, level - 1, res);
        } else if (root->left_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            printByLevel_FOR_TESTS(root->left_node, level - 1, res);
            if (level - 1 == 1)
                strcat(res, " null");
        } else if (root->right_node != NULL) {
            //printf("ветвь от: %d - ", root->value);
            if (level - 1 == 1)
                strcat(res, " null");
            printByLevel_FOR_TESTS(root->right_node, level - 1, res);
        } else {
            //ветка для отладки
        }
    }
}

void printTreeLevelByLevel_FOR_TESTS(tree_arr * root, char *res) {
    int height = getDeep(root);
    for (int i = 1; i <= height; i++) {
        printByLevel_FOR_TESTS(root, i, res);
        //printf("\n");
    }
}

void lab_20_task_07(int *nums, int size, char *result) {
    tree_arr *root = constructTreeArr(nums, 0, size - 1);
    char *res = (char*)malloc(sizeof(char) * (size * 20 + 1));
    res[0] = '\0';

    printTreeLevelByLevel_FOR_TESTS(root, res);
    res++;//удалить первый пробел
    strcpy(result, res);
    //printf("%s\n", res);

    freeTreeArr(root);
}
