//
// Created by Ilya on 18.02.2024.
//

#ifndef PROJECT_LIBS_ORDERED_SET_H
#define PROJECT_LIBS_ORDERED_SET_H

# include <stdint.h>
# include <assert.h>
# include <memory.h>
# include <stdio.h>
# include <stdbool.h >
# include <array/array.h>
# include <malloc.h>
# include <algorithms/algorithms.h>

typedef struct ordered_array_set {
    int *data;
    size_t size;
    size_t capacity;
} ordered_array_set;

void ordered_set_isAbleToAppend(ordered_array_set *set);

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity);

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size);

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set set, int value);


// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value);

void ordered_array_set_deleteElement(ordered_array_set *set, int value);

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2);

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2);

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2);

ordered_array_set ordered_array_set_sym_difference(ordered_array_set set1, ordered_array_set set2);


bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set);

bool ordered_array_set_isEqual(ordered_array_set subset, ordered_array_set set);

ordered_array_set ordered_set_complement(const ordered_array_set set, const ordered_array_set universe);


//изменение размера
void ordered_array_set_shrink_to_fit(ordered_array_set *set);

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set *set);

void ordered_array_set_print(const ordered_array_set set);


#endif //PROJECT_LIBS_ORDERED_SET_H
