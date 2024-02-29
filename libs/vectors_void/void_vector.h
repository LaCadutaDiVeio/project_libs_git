#ifndef PROJECT_LIBS_VOID_VECTOR_H
#define PROJECT_LIBS_VOID_VECTOR_H

#include <assert.h>
#include <malloc.h>

typedef struct void_vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t size_of_type;
} void_vector;

void_vector vdvector_create(size_t size, const size_t type_size);

void void_vector_reserve(void_vector *v, size_t new_capacity);

void void_vector_clear(void_vector *v);

void void_vector_shrinkToFit(void_vector *v);

void void_vector_free(void_vector *v);

int void_vector_isEmpty(void_vector v);

int void_vector_isFull(void_vector v);

void void_vector_get(void_vector *v, size_t slot, void *dst);

void void_vector_set(void_vector *v, size_t slot, void *src);

void void_vector_pushBack(void_vector *v, void *src);

void void_vector_popBack(void_vector *v);


#endif //PROJECT_LIBS_VOID_VECTOR_H
