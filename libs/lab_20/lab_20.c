#include <lab_20/lab_20.h>
#include <matrix/matrix.h>

//создание новоой ветки дерева
trie_node *getNode() {
    trie_node *node = (trie_node *) malloc(sizeof(trie_node));
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
void insertWordInTrie(trie_node *root, const char *word) {//a=0 b =1 c =2   abc
    int alp_index;
    trie_node *node = root;
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

int isNodeIsWord(trie_node *node) {
    return node->is_end_of_word;
}

char BAD_RESULT[] = {'-', '1', '\0'};

//найти слово в словаре
char *findWordInTrie(trie_node *root, const char *prefix, int number) {
    //prefix - последовательность по котороу будет поиск
    //number - искомый порядковый номер
    trie_node *node = root;
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

void freeTrie(trie_node *node) {
    if (node == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(node->children[i]);

    free(node);
}

int lab_20_task_11() {
    printf("Введите кол-во слов и кол-во запросов:\n");
    int Q, N;
    scanf("%d %d", &Q, &N);

    trie_node *root = getNode();

    // Чтение слов из словаря
    printf("Вводите слова:\n");
    for (int i = 0; i < Q; i++) {
        char word[1000001];
        scanf("%s", word);
        insertWordInTrie(root, word);
    }
    printf("Введите запросы:\n");

    // Обработка запросов
    for (int i = 0; i < N; i++) {
        int k;
        char prefix[101];
        printf("Запрос %d:", i + 1);
        scanf("%d %s", &k, prefix);
        char *result = findWordInTrie(root, prefix, k);
        printf("  %s\n", result);
        free(result);
    }

    // Освобождение памяти
    freeTrie(root);

    return 0;
}

int lab_20_task_11_FORTESTS(char *words, char *requests, char **testRequests) {
    trie_node *root = getNode();

    char *word = strtok(words, " ");
    while (word != NULL) {
        insertWordInTrie(root, word);
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

        char *result = findWordInTrie(root, prefix, k);
        //printf( "%s", result );
        if (strcmp(result, testRequests[request_index]) != 0) {
            //    free( result );
            freeTrie(root);
            return 0;
        }

        //  free( result );
        request_index++;
    }
    freeTrie(root);

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
    //с учётом угловых ик крайних клеток

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
