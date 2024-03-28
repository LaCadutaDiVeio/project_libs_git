#ifndef PROJECT_LIBS_STRING__H
#define PROJECT_LIBS_STRING__H

#include <malloc.h>
#include <memory.h>
#include <ctype.h>

typedef struct WordDescriptor {
    char *m_begin;
    char *m_end;
} WordDescriptor;

size_t strlen_ (const char *begin);
char *strfind (char *begin, char *end, char ch);
char *findNonSpace(char *begin);
char *findSpace(char *begin);
char *findNonSpaceReverse(char *rbegin, const char *rend);
char *findSpaceReverse(char *rbegin, const char *rend);



#endif //PROJECT_LIBS_STRING__H
