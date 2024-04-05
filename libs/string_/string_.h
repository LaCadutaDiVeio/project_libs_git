#ifndef PROJECT_LIBS_STRING__H
#define PROJECT_LIBS_STRING__H

#include <malloc.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>


#define ASSERT_STRING(expected, got) assertString(expected, got, \
	__FILE__, __FUNCTION__, __LINE__ )

typedef struct WordDescriptor {
    char *m_begin;
    char *m_end;
} WordDescriptor;

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

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line);

#endif //PROJECT_LIBS_STRING__H
