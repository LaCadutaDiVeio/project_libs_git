#include <stdio.h>
#include "unordered_set.h"
#include <malloc.h>
#include <windows.h>
//#include <array/array.h>

// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}

// возвращает множество, состоящее из элементов массива a размера size.
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        set.data[i] = a[i];
    }
    set.size = size;
    return set;
}

//возвращает pos если el есть и size, если нет
size_t unordered_array_set_in(unordered_array_set set, int value) {
    for (size_t i = 0; i < set.size; i++) {
        if (set.data[i] == value)
            return i;
    }
    return set.size;
}


bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    int intersections = 0;
    for (size_t i = 0; i < set.size; i++) {
        for (size_t j = 0; j < subset.size; j++) {
            if (subset.data[j] == set.data[i])
                intersections++;
        }
    }
    return intersections == subset.size;
}

bool unordered_array_set_isEqual(unordered_array_set subset, unordered_array_set set) {
    int intersections = 0;
    for (size_t i = 0; i < set.size; i++) {
        for (size_t j = 0; j < subset.size; j++) {
            if (subset.data[j] == set.data[i])
                intersections++;
        }
    }
    return intersections == set.size;
}

//проверка возможности добавления элемента
void unordered_array_set_isAbleToAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

//Добавление элемента
void unordered_array_set_insert(unordered_array_set *set, const int element) {
    if (unordered_array_set_in(*set, element) == set->size) {
        //такая проверка исключит дубликаты
        unordered_array_set_isAbleToAppend(set);
        set->data[set->size] = element;
        (set->size)++;
    }
}

//удаление элемента
void unordered_array_set_deleteElement(unordered_array_set *set, const int value) {
    if (unordered_array_set_in(*set, value) == set->size)
        return;

    size_t read = 0;
    while (read < set->size) {
        if (set->data[read] == value) {
            set->data[read] = set->data[set->size];
            set->size--;
            break;
        } else
            read++;
    }
}

//объединение
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; ++i) {
        unordered_array_set_insert(&set, set1.data[i]);
    }
    for (size_t i = 0; i < set2.size; ++i) {
        unordered_array_set_insert(&set, set2.data[i]);
    }
    unordered_set_shrink_to_fit(&set);

    return set;
}

//пересечение
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; i++) {
        for (size_t j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j])
                unordered_array_set_insert(&set, set1.data[i]);
        }
    }

    unordered_set_shrink_to_fit(&set);
    return set;
}

//разность
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; i++) {
        bool should_be_added = 1;
        for (size_t j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j])
                should_be_added = 0;
        }
        if (should_be_added)
            unordered_array_set_insert(&set, set1.data[i]);
    }

    unordered_set_shrink_to_fit(&set);
    return set;
}

//разность
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universe) {
    return unordered_array_set_difference(universe, set);
}

//разность
unordered_array_set unordered_array_set_sym_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set first = unordered_array_set_difference(set1, set2);
    unordered_array_set second = unordered_array_set_difference(set2, set1);
    unordered_array_set set = unordered_array_set_union(first, second);

    unordered_set_shrink_to_fit(&set);
    return set;
}


//изменение памяти по необходимости
void unordered_set_shrink_to_fit(unordered_array_set *set) {
    if (set->capacity != set->size) {
        set->data = realloc(set->data, sizeof(int) * set->size);
        set->capacity = set->size;
    }
}




// вывод множества set
void unordered_array_set_print(const unordered_array_set set) {
    for (size_t i = 0; i < set.size; i++)
        printf("%d ", set.data[i]);
    printf("\n");
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
    ZeroMemory(&set.data, sizeof(set.data));
}