
#include <string_/string_.h>
#include <stdio.h>


size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end - begin;
}

char *strfind(char *begin, char *end, char ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin))
        begin++;

    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin))
        begin++;

    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs == *rhs && *lhs != '\0' && *rhs != '\0') {
        *lhs++;
        *rhs++;
    }

    return *lhs - *rhs;
}

char *strcopy(const char *beginSource, const char *endSource, char *beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    *(beginDestination + size) = '\0';

    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int ( *f )(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            ++beginDestination;
        }

        ++beginSource;
    }

    *beginDestination = '\0';

    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    char *rbegin_dst = beginDestination;
    while (*rbeginSource >= -1 && *rbeginSource <= 255 && rbeginSource >= rendSource) {
        if (f(*rbeginSource)) {
            *rbegin_dst = *rbeginSource;
            ++rbegin_dst;
        }

        --rbeginSource;
    }

    *rbegin_dst = '\0';
    return rbegin_dst;
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

//------------------------------------

void removeAdjacentEqualLetters(char *s) {
/*    char *write = s;

    while (*s != '\0') {
        printf("%c", *s);
        if (*s != *(s - 1)) {
            *write = *s;
            write++;
        }
        s++;
    }

    *write = '\0';
    printf("%s", s);
}*/
    if (*s != '\0')
        s++;

    char *read = s;
    //printf("%p\n", s);
    while (*read != '\0') {
        //printf("%p %p\n", read, s);
        //printf("%c", *s);
        if (*read != *(--s))
            *(++s) = *read;

        ++s;
        ++read;
    }

    *s = '\0';
    //printf("%s", s);
}

void removeExtraSpaces(char *s) {
    char *read = s;
    while (*read != '\0') {
        if (isspace(*read)) {
            char *write = s;
            if (!isspace(*(write--))) {
                *(++s) = *read;
            }
        } else {
            *(++s) = *read;
        }

        ++read;
    }
    *(++s) = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;

    word->end = findSpace(word->begin);

    return 1;
}

void digitToEnd_(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = strcopy(word.begin, word.end, _stringBuffer);

    char *digitPos = copyIf(_stringBuffer, endStringBuffer, word.begin, isalpha);
    copyIf(_stringBuffer, endStringBuffer, digitPos, isdigit);
}

void digitToEnd(char *s) {
    WordDescriptor word;
    char *read = s;
    while (getWord(read, &word)) {
        digitToEnd_(word);
        read = word.end;
    }
}

void digitToEndReverse_(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = strcopy(word.begin, word.end, _stringBuffer);

    char *digitPos = copyIf(_stringBuffer, endStringBuffer, word.begin, isalpha);
    copyIfReverse(endStringBuffer, _stringBuffer, digitPos, isdigit);
}

void digitToEndReverse(char *s) {
    WordDescriptor word;
    char *read = s;
    while (getWord(read, &word)) {
        digitToEndReverse_(word);
        read = word.end;
    }
}

void digitToStart_(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = strcopy(word.begin, word.end, _stringBuffer);

    char *digitPos = copyIf(_stringBuffer, endStringBuffer, word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, digitPos, isalpha);
}

void digitToStart(char *s) {
    WordDescriptor word;
    char *read = s;
    while (getWord(read, &word)) {
        digitToStart_(word);
        read = word.end;
    }
}

void replaceDigitsWithSpaces(char *s) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *end = s + strlen_(s);
    char *read = _stringBuffer;
    char *endbuf = strcopy(s, end, read);

    while (*read != '\0') {
        if (isalpha(*read))
            *s++ = *read;
        else {
            while (isdigit(*read) && *read != '0') {
                *s++ = ' ';
                (*read)--;
            }
        }
        read++;
    }
    *s = '\0';
}

/*int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *c1 = w1.begin;
    char *c2 = w2.begin;
    while ((*c1 != ' ' || *c2 != ' ') && (*c1 != '\0' && *c2 != '\0')) {
        if ((*c1 != *c2) && (*c1 != '\0' && *c2 != '\0'))
            return 0;
        c1++;
        c2++;
    }
    return c1 == w1.end && c2 == w2.end;
}*/

int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *c1 = w1.begin;
    char *c2 = w2.begin;
    //while (*c1 != '\0' && *c2 != '\0') {
    while ((c1 != w1.end && c2 != w2.end) && (*c1 != ' ' && *c2 != ' ')) {
        if (*c1 != *c2)
            return 0;
        c1++;
        c2++;
    }
    return 1;
}

void replaceWords(char *source, char *w1, char *w2) {
    size_t len1 = strlen_(w1);
    WordDescriptor word1 = {w1, w1 + len1};
    size_t len2 = strlen_(w2);
    WordDescriptor word2 = {w2, w2 + len2};

    WordDescriptor word;
    char buffer[MAX_STRING_SIZE];
    char *read;
    char *rec = source;
    if (len1 >= len2) {
        read = source;
    } else {
        strcopy(source, source + strlen_(source), buffer);
        read = buffer;
    }

    while (getWord(read, &word)) {
        WordDescriptor write = word2;
        //printf("%c %c \n", *word.begin, *(word.end - 1));
        if (!areWordsEqual(word, word1))
            write = word;
        //легче делать перезапись в любом случае:
        for (char *c = write.begin; c != write.end; ++c) {
            *rec++ = *c;
            //printf("%p, %c\n", (rec - 1), *(rec - 1));
        }
        *rec++ = ' ';
        read = word.end;
    }
    *(rec - 1) = '\0';
}

void replaceWordsSS_ryzen(char *source, char *w1, char *w2) {
    char buf[MAX_STRING_SIZE];
    memset(buf, 0, sizeof(char) * MAX_STRING_SIZE);

    size_t len1 = strlen_(w1);
    WordDescriptor wo1 = {w1, w1 + len1};
    size_t len2 = strlen_(w2);
    WordDescriptor wo2 = {w2, w2 + len2};

    char *read = source;

    int size = 0;
    WordDescriptor word;
    while (getWord(read, &word)) {
        if (areWordsEqual(word, wo1)) {
            for (char *b = wo2.begin; b != wo2.end; ++b) {
                buf[size++] = *b;
            }
            buf[size++] = ' ';
        } else {
            for (char *b = word.begin; b != word.end; ++b) {
                buf[size++] = *b;
            }
            buf[size++] = ' ';
        }
        read = word.end;
    }

    buf[--size] = '\0';
    strcopy(buf, buf + size, source);
}

int areWordsOrdered(char *s) {
    WordDescriptor w1, w2;
    if (getWord(s, &w1)) {
        w2 = w1;
        s = w1.end;
        while (getWord(s, &w1)) {
            if (!areWordsEqual(w1, w2))
                return 0;
            w2 = w1;
            s = w1.end;
        }
        return 1;
    } else
        return 1;
}

void getBagOfWords(char *s, BagOfWords *bag) {
    WordDescriptor word;
    bag->size = 0;
    while (getWord(s, &word)) {
        bag->words[(bag->size)++] = word;
        s = word.end;
    }
}

int isWordPalindrome(char *begin, char *end) {
    end--;//исключает ноль-символ или запятую
    while (end > begin) {
        if (*begin != *end)
            return 0;

        begin++;
        end--;
    }

    return 1;
}

size_t getAmountPalindromes(char *s) {
    char *begin = findNonSpace(s);
    char *end = s + strlen_(s);
    char *l = strfind(begin, end, ',');
    int is_final = *l == '\0' && end > begin;

    size_t count = 0;
    while (*l != '\0' || is_final) {
        count += isWordPalindrome(begin, l);

        if (is_final)
            break;
        if (end <= begin)
            break;

        begin = findNonSpace(l + 1);
        l = strfind(begin, end, ',');
        is_final = *l == '\0' && end > begin;
    }

    return count;
}

void join2StrInStr(char *result, char *s1, char *s2) {
    WordDescriptor w1, w2;
    int isW1Found, isW2Found;
    //int iter = 1;
    while (isW1Found = getWord(s1, &w1), isW2Found = getWord(s2, &w2), isW1Found || isW2Found) {
        //printf("%d", iter++);
        if (isW1Found) {
            //printf("w1");
            for (char *c = w1.begin; c != w1.end; c++) {
                //printf(".");
                *result++ = *c;
                //result++;
            }
            s1 = w1.end;
            isW1Found = getWord(s1, &w1);

            if (isW1Found || isW2Found)
                *result++ = ' ';
        }
        if (isW2Found) {
            //printf("w2");
            for (char *c = w2.begin; c != w2.end; c++) {
                *result++ = *c;
            }
            s2 = w2.end;
            isW2Found = getWord(s2, &w2);

            if (isW1Found || isW2Found)
                *result++ = ' ';
        }
    }
    *result = '\0';
}

void reverseStrOrder(char *s) {
    char destination[MAX_STRING_SIZE];

    BagOfWords bag;
    getBagOfWords(s, &bag);

    size_t write = 0;
    for (int i = bag.size - 1; i != -1; i--) {
        for (char *c = bag.words[i].begin; c != bag.words[i].end; c++) {
            destination[write] = *c;
            write++;
        }
        if (i != 0) {
            destination[write] = ' ';
            write++;
        }
    }
    destination[write++] = '\0';
    strcopy(destination, destination + write, s);
}

int isWordContainChar(WordDescriptor w, char ch) {
    for (char *c = w.begin; c != w.end; c++) {
        if (*c == ch)
            return 1;
    }
    return 0;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA_Status(char *s) {
    if (*s == '\0')
        return EMPTY_STRING;

    WordDescriptor word, track = {NULL};
    while (getWord(s, &word)) {
        if (isWordContainChar(word, 'a') || isWordContainChar(word, 'a')) {
            if (track.begin == NULL)
                return FIRST_WORD_WITH_A;
            else
                return WORD_FOUND;
        }
        track = word;
        s = word.end;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}

void printWordBeforeFirstWithA(char *s) {
    if (*s == '\0')
        return;

    WordDescriptor word, track = {NULL};
    while (getWord(s, &word)) {
        if (isWordContainChar(word, 'a') || isWordContainChar(word, 'A')) {
            if (track.begin == NULL)
                for (char *c = word.begin; c != word.end; c++)
                    printf("%c", *c);
            else
                for (char *c = track.begin; c != track.end; c++)
                    printf("%c", *c);
            printf("\n");
        }
        track = word;
        s = word.end;
    }
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    for (char *c = word.begin; c != word.end; c++)
        *destination++ = *c;

    *destination = '\0';
}

int isWordInBag(WordDescriptor word, BagOfWords bag) {
    char data[MAX_STRING_SIZE];
    char data_[MAX_STRING_SIZE];
    wordDescriptorToString(word, data);
    for (size_t i = 0; i < bag.size; i++) {
        wordDescriptorToString(bag.words[i], data_)
    }
}

