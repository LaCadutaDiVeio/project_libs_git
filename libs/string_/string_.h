#ifndef PROJECT_LIBS_STRING__H
#define PROJECT_LIBS_STRING__H

#include <malloc.h>
#include <memory.h>
#include <ctype.h>

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

#endif //PROJECT_LIBS_STRING__H
