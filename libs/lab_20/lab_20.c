#include <lab_20/lab_20.h>

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

char BAD_RESULT[] = {'-','1','\0'};
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

int lab_20_task_11_FORTESTS( char *words, char *requests, char **testRequests ) {
    trie_node *root = getNode( );

    char *word = strtok( words, " " );
    while ( word != NULL ) {
        insertWordInTrie( root, word );
        //printf( "%s ", word );
        word = strtok( NULL, " " );//классная штука, не знал о такой
    }

    char *request = strtok( requests, " " );
    int request_index = 0;
    while ( request != NULL ) {
        int k = atoi( request );
        request = strtok( NULL, " " );
        if ( request == NULL )
            break;
        char *prefix = request;
        //printf( "%d %s ", k, prefix );
        request = strtok( NULL, " " );

        char *result = findWordInTrie( root, prefix, k );
        //printf( "%s", result );
        if ( strcmp( result, testRequests[ request_index ] ) != 0 ) {
            //    free( result );
            freeTrie( root );
            return 0;
        }

        //  free( result );
        request_index++;
    }
    freeTrie( root );

    return 1;
}