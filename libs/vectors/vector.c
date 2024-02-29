#include <vectors/vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <array/array.h>

/*
void print_mem_error() {
    fprintf(stderr, "%s\n", "failed memory lock");
    exit(1);
}
void print_mem_index_out() {
    fprintf(stderr, "%s\n", "index out of data range");
    exit(1);
}
Сначала думал делать по отдельности, но понял, что лучше сделать универсальную
*/
void error_alert(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


vector vector_create(size_t size) {
    vector v;
    if (size == 0) {
        v.data = NULL;
    } else {
        v.data = malloc(sizeof(int) * size);
        if (!v.data) {
            error_alert("failed memory lock");
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
            error_alert("failed memory lock");
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

//не бум-бум, зачем в методичке передают адреса...
bool isEmpty(vector v) {
    return v.size == 0;
}

bool isFull(vector v) {
    return v.size = v.capacity;
}
//--------------

int vector_get_value_by_pos(vector v, size_t pos) {
    //Методичка хочет 1 строчку, а преподаватель хочет проверку неадекватности юзера :/
    if (!v.data)
        error_alert("something wrong with vector's data");
    if (pos >= v.size)
        error_alert("index out of vector's data range");

    return v.data[pos];
}

void vector_pushBack(vector *v, int value) {
    if (!v->capacity)
        vector_reserve(v, 1);
    if (v->size >= v->capacity)
        vector_reserve(v, v->capacity * 2);

    v->data[v->size++] = value;
}

void vector_popBack(vector *v) {
    if (!v->data)
        error_alert("something wrong with vector's data");
    if (!v->size)
        error_alert("vector is empty");
    v->data[v->size--] = 0;
}

int *vector_at(vector *v, size_t index) {
    if (!v->data)
        error_alert("something wrong with vector's data");
    if (index >= v->size)
        error_alert("index out of vector's data range");
    //формулировка из методички мне не нравится, она не отражает смысл ошибки

    return v->data + index;
}

int *vector_back(vector *v) {
    if (!v->data)
        error_alert("something wrong with vector's data");
    return v->data + (v->size - 1);
}

int *vector_front(vector *v) {
    if (!v->data)
        error_alert("something wrong with vector's data");
    return v->data;
}

//хз, чё в методичке не предложили сделать print, ну да ладно
void vector_print(vector v) {
    if (!v.data)
        error_alert("something wrong with vector's data");
    outputArray_(v.data, v.size);
}



