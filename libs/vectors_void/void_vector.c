#include <vectors_void/void_vector.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void error_alert_v(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void_vector void_vector_create(size_t capacity, size_t type_size) {
    void_vector v;
    if (capacity == 0)
        v.data = NULL;
    else {
        v.data = malloc(type_size * capacity);
        if (!v.data)
            error_alert_v("memory failed");
    }
    v.size = 0;
    v.capacity = capacity;
    v.size_of_type = type_size;

    return v;
}

void void_vector_reserve(void_vector *v, size_t new_cap) {
    if (new_cap == 0) {
        void_vector_delete(v);
    } else {
        if (v->size > new_cap) {
            v->size = new_cap;
        }
        v->capacity = new_cap;
        v->data = realloc(v->data, v->size_of_type * v->capacity);
        if (!v->data)
            error_alert_v("failed memory lock");
    }
}

void void_vector_clear(void_vector *v) {
    v->size = 0;
}

void void_vector_shrink_to_fit(void_vector *v) {
    void_vector_reserve(v, v->size);
}

void void_vector_delete(void_vector *v) {
    free(v->data);
    v->data = NULL;
    v->size_of_type = 0;
    v->size = 0;
    v->capacity = 0;
}

bool void_vector_isEmpty(void_vector v) {
    return v.size == 0;
}

bool void_vector_isFull(void_vector v) {
    return v.size = v.capacity;
}

void void_vector_getValueByPos(void_vector *v, size_t pos, void *destination) {
    if (!v->data)
        error_alert_v("something wrong with vector's data");
    if (pos >= v->size)
        error_alert_v("index out of vector's data range");

    char *source = (char*)v->data + pos * v->size_of_type;
    memcpy(destination, source, v->size_of_type);
}

void void_vector_setValue(void_vector *v, size_t pos, void *source) {
    if (!v->data)
        error_alert_v("something wrong with vector's data");
    if (pos >= v->size)
        error_alert_v("index out of vector's data range");
    char *dist = (char*)v->data + pos * v->size_of_type;
    memcpy(dist, source, v->size_of_type);
}

void void_vector_popBack(void_vector *v) {
    if (!v->data)
        error_alert_v("something wrong with vector's data");
    if (!v->size)
        error_alert_v("vector is empty");
    //v->data[v->size--] = 0;
    v->size--;
}

void void_vector_pushBack(void_vector *v, void *source) {
    if (!v->data)
        void_vector_reserve(v, 1);
    if (v->size >= v->capacity)
        void_vector_reserve(v, v->capacity * 2);
    void_vector_setValue(v, v->size++, source);
}



