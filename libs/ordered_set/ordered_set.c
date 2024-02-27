#include "ordered_set.h"

//создание мн.
ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}

//создание мн. из массива
ordered_array_set ordered_array_set_create_from_array(const int *arr, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&set, arr[i]);
    }
    ordered_array_set_shrink_to_fit(&set);

    return set;
}

void ordered_set_isAbleToAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(*set, value) == set->size) {
        ordered_set_isAbleToAppend(set);


        size_t pos = binarySearchNear(set->data, set->size, value);
        for (size_t i = set->size; i > pos; i--) {
            set->data[i] = set->data[i - 1];
        }
        set->data[pos] = value;
        (set->size)++;

    }
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    if (ordered_array_set_in(*set, value) == set->size)
        return;
    size_t read = 0;
    while (read < set->size && set->data[read] != value)
        read++;
    size_t write = read;
    while (read < set->size) {
        if (set->data[read] != value) {
            set->data[write] = set->data[read];
            write++;
        }
        read++;
    }
    set->size = write;
}


ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; i++) {
        ordered_array_set_insert(&set, set1.data[i]);
    }
    for (size_t i = 0; i < set2.size; i++) {
        ordered_array_set_insert(&set, set2.data[i]);
    }
    ordered_array_set_shrink_to_fit(&set);
    return set;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; i++) {
        size_t pos = binarySearch(set2.data, set2.size, set1.data[i]);
        if (pos != set2.size)
            ordered_array_set_insert(&set, set1.data[i]);
    }
    ordered_array_set_shrink_to_fit(&set);

    return set;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    size_t max_cap = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(max_cap);
    for (size_t i = 0; i < set1.size; i++) {
        size_t pos = binarySearch(set2.data, set2.size, set1.data[i]);
        if (pos == set2.size)
            ordered_array_set_insert(&set, set1.data[i]);
    }
    ordered_array_set_shrink_to_fit(&set);

    return set;
}

ordered_array_set ordered_array_set_sym_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set first = ordered_array_set_difference(set1, set2);
    ordered_array_set second = ordered_array_set_difference(set2, set1);

    ordered_array_set set = ordered_array_set_union(first, second);

    return set;
}

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set set, int value) {
    for (size_t i = 0; i < set.size; i++) {
        if (set.data[i] == value)
            return i;
        else if (set.data[i] > value)
            return set.size;
    }
    return set.size;
}


bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    int intersections = 0;
    for (size_t i = 0; i < set.size; i++) {
        for (size_t j = 0; j < subset.size; j++) {
            if (subset.data[j] == set.data[i])
                intersections++;
        }
    }
    return intersections == subset.size;
}


bool ordered_array_set_isEqual(ordered_array_set subset, ordered_array_set set) {
    int intersections = 0;
    for (size_t i = 0; i < set.size; i++) {
        for (size_t j = 0; j < subset.size; j++) {
            if (subset.data[j] == set.data[i])
                intersections++;
        }
    }
    return intersections == subset.size && set.size == subset.size;
}


void ordered_array_set_shrink_to_fit(ordered_array_set *set) {
    if (set->capacity != set->size) {
        set->data = realloc(set->data, sizeof(int) * set->size);
        set->capacity = set->size;
    }
}


ordered_array_set ordered_set_complement(const ordered_array_set set, const ordered_array_set universe) {
    ordered_array_set comp = ordered_array_set_difference(universe, set);

    return comp;
}

void ordered_array_set_print(const ordered_array_set set) {
    for (size_t i = 0; i < set.size; ++i)
        printf("%d ", set.data[i]);
    printf("\n");
}

void ordered_array_set_delete(ordered_array_set *set) {
    set->size = 0;
    set->capacity = 0;
    free(set->data);
}





