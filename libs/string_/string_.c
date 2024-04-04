
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
    while (rbegin >= rend && isspace(*rbegin))
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
    //*(beginDestination + size) = '\0';

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

    //*beginDestination = '\0';

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    char *rbegin_dst = beginDestination;
    while ( *rbeginSource >= -1 && *rbeginSource <= 255 && rbeginSource >= rendSource ) {
        if ( f( *rbeginSource ) ) {
            *rbegin_dst = *rbeginSource;
            ++rbegin_dst;
        }

        --rbeginSource;
    }

    //*rbegin_dst = '\0';

    return rbegin_dst;
}


