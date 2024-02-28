#include <vectors/vector.h>
#include <stdio.h>
#include <stdlib.h>

void print_mem_error() {
    fprintf(stderr, "%s\n", "failed memory lock");
    exit(1);
}


vector vector_create(size_t size) {
    vector v;
    if (size == 0) {
        v.data = NULL;
    } else {
        v.data = malloc(sizeof(int) * size);
        if (!v.data) {
            print_mem_error();
        }
    }
    v.size = 0;
    v.capacity = size;

    return v;
}

void vector_reserve(vector *v, size_t new_cap) {
    if (new_cap == 0) {
        vector_delete(v);
        /*  принцип DRY
        v->capacity = 0;
        v->size = 0;
        v->data = NULL; */
    } else {
        if (v->size > new_cap) {
            v->size = new_cap;
        }
        v->capacity = new_cap;
        v->data = realloc(v->data, sizeof(int) * v->capacity);
        if (!v->data)
            print_mem_error();
    }
}

void vector_clear(vector *v) {
    v->size = 0;
}

void vector_shrink_to_fit(vector *v) {
    vector_reserve(v, v->size);
}

void vector_delete(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}


