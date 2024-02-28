
#ifndef PROJECT_LIBS_VECTOR_H
#define PROJECT_LIBS_VECTOR_H

#include <malloc.h>
#include <assert.h>


typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

void print_mem_error();
vector vector_create(size_t size);
void vector_reserve(vector *v, size_t new_cap);
void vector_clear(vector *v);
void vector_shrink_to_fit(vector *v);
void vector_delete(vector *v);


#endif //PROJECT_LIBS_VECTOR_H
