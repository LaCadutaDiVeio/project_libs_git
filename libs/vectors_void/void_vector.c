#include <vectors_void/void_vector.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

void error_alert(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void_vector v_vector_create(size_t capacity, size_t type_size) {
    void_vector v;
    if (capacity == 0)
        v.data = NULL;
    else {
        v.data = malloc(type_size * capacity);
        if (!v.data)
            error_alert("memory failed");
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
            error_alert("failed memory lock");
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




