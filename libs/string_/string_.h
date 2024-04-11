#ifndef PROJECT_LIBS_STRING__H
#define PROJECT_LIBS_STRING__H

#include <malloc.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>


#define ASSERT_STRING(expected, got) assertString(expected, got, \
	__FILE__, __FUNCTION__, __LINE__ )

#define MAX_STRING_SIZE 100u
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

typedef struct WordDescriptor {
    char *begin;
    char *end;
} WordDescriptor;

extern char _stringBuffer[MAX_STRING_SIZE + 1];


size_t strlen_(const char *begin);

char *strfind(char *begin, char *end, char ch);

char *findNonSpace(char *begin);

char *findSpace(char *begin);

char *findNonSpaceReverse(char *rbegin, const char *rend);

char *findSpaceReverse(char *rbegin, const char *rend);

int strcmp(const char *lhs, const char *rhs);

char *strcopy(const char *beginSource, const char *endSource, char *beginDestination);

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int ( *f )(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

//------------------------------------

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line);

void removeAdjacentEqualLetters(char *s);

void removeExtraSpaces(char *s);

int getWord(char *beginSearch, WordDescriptor *word);

void digitToEnd_(WordDescriptor word);

void digitToEnd(char *s);

void digitToEndReverse_(WordDescriptor word);

void digitToEndReverse(char *s);

void digitToStart_(WordDescriptor word);

void digitToStart(char *s);

void replaceDigitsWithSpaces(char *s);

void replaceWords (char *source, char *w1, char *w2);

int areWordsEqual(WordDescriptor w1, WordDescriptor w2);

#endif //PROJECT_LIBS_STRING__H
