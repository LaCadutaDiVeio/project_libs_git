#ifndef PROJECT_LIBS_VOID_VECTOR_H
#define PROJECT_LIBS_VOID_VECTOR_H

#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct void_vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t size_of_type;
} void_vector;

void error_alert_v(char *msg);

void_vector void_vector_create(size_t size, const size_t type_size);
void void_vector_reserve(void_vector *v, size_t new_capacity);
void void_vector_clear(void_vector *v);
void void_vector_shrink_to_fit(void_vector *v);
void void_vector_delete(void_vector *v);
//-----------------
bool void_vector_isEmpty(void_vector v);
bool void_vector_isFull(void_vector v);
//---------------
void void_vector_getValueByPos(void_vector *v, size_t pos, void *destination);
void void_vector_setValue(void_vector *v, size_t pos, void *source);
void void_vector_pushBack(void_vector *v, void *src);
void void_vector_popBack(void_vector *v);


#endif //PROJECT_LIBS_VOID_VECTOR_H
