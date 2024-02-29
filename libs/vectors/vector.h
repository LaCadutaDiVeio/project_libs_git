
#ifndef PROJECT_LIBS_VECTOR_H
#define PROJECT_LIBS_VECTOR_H

#include <malloc.h>
#include <assert.h>
#include <stdbool.h>


typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

//void print_mem_error();
//void print_mem_index_out();
void error_alert(char *msg);
//-------------
vector vector_create(size_t size);
void vector_reserve(vector *v, size_t new_cap);
void vector_clear(vector *v);
void vector_shrink_to_fit(vector *v);
void vector_delete(vector *v);
//------------
bool isEmpty(vector v);
bool isFull(vector v);
//------------
int vector_get_value_by_pos (vector v, size_t pos);
void vector_pushBack(vector *v, int x);
void vector_popBack(vector *v);
int *vector_at(vector *v, size_t index);
int *vector_back(vector *v);
int *vector_front(vector *v);
void test_vector_data_funcs();
void vector_print(vector v);



#endif //PROJECT_LIBS_VECTOR_H
