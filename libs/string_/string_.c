
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
    char *endStringBuffer = strcopy(word.begin, word.end,_stringBuffer);

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
    char *endStringBuffer = strcopy(word.begin, word.end,_stringBuffer);

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
    char *endStringBuffer = strcopy(word.begin, word.end,_stringBuffer);

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

int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *c1 = w1.begin;
    char *c2 = w2.begin;
    while (*c1 != '\0' && *c2 != '\0') {
        if (*c1 != *c2)
            return 0;
        c1++;
        c2++;
    }
    return 1;
}

void replaceWords (char *source, char *w1, char *w2) {
    size_t len1 = strlen_(w1);
    WordDescriptor word1 = {w1, w1 + len1};
    size_t len2 = strlen_(w2);
    WordDescriptor word2 = {w2, w2 + len2};

    WordDescriptor word;
    char *read = source;
    char *rec = source;
    char buffer[MAX_STRING_SIZE + 1];
    if (len2 > len1) {
        strcopy(source, source + strlen_(source), buffer);
        read = buffer;
        rec = source;
    }

    while (getWord(read, &word)) {
        WordDescriptor result = word2;
        for (char *c = result.begin; c != result.end; ++c) {
            *rec++ = *c;
        }
        *rec++ = ' ';
        read = word.end;
    }
    *(rec) = '\0';
}





