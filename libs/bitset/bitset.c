#include "bitset.h"
#include <stdio.h>

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create(unsigned max_value) {
    bitset set;
    set.maxValue = max_value;
    set.values = 0;
    return set;
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset set, unsigned int value) {
    return ((set.values >> value) & 1);
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual(bitset set1, bitset set2) {
    return (set1.values == set2.values);
}

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset subset, bitset set) {
    return ((subset.values | set.values) == set.values);
}

// добавляет элемент value в множество set
void bitset_insert(bitset *set, unsigned int value) {
    (*set).values |= (1 << value);
}

// удаляет элемент value из множества set
void bitset_deleteElement(bitset *set, unsigned int value) {
    (*set).values &= ~(1 << value);
}

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2) {
    bitset union_bitset;
    union_bitset.maxValue = set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue;
    union_bitset.values = set1.values | set2.values;
    return union_bitset;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2) {
    bitset intersections_bitset;
    intersections_bitset.maxValue = set1.maxValue < set2.maxValue ? set1.maxValue : set2.maxValue;
    intersections_bitset.values = set1.values & set2.values;
    return intersections_bitset;
}

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2) {
    bitset difference_bitset;
    difference_bitset.maxValue = set1.maxValue;
    difference_bitset.values = set1.values & (~set2.values);
    return difference_bitset;
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset sym_difference_bitset;
    sym_difference_bitset.maxValue = set1.maxValue;
    sym_difference_bitset.values = set1.values ^ set2.values;
    return sym_difference_bitset;
}

// возвращает дополнение до универсума множества set
/*bitset bitset_complement ( bitset set ) {
    bitset complement = bitset_create(set.maxValue);
    complement.values = ~set.values;
    return complement;
    //оставил чисто как напоминание о собственной глупости
}*/
/*bitset bitset_complement(bitset set) {
    bitset res = bitset_create(set.maxValue);
    for (size_t i = 0; i <= res.maxValue; ++i) {
        if (!bitset_in(set, i))
            bitset_insert(&res, i);
    }

    return res;
}*/
bitset bitset_complement ( bitset set ) {
    bitset complement = bitset_create(set.maxValue);
    complement.values = ~set.values;
    complement.values <<= (31 - complement.maxValue);
    complement.values >>= (31 - complement.maxValue);
    return complement;
    //оставил чисто как напоминание о собственной глупости
}


// вывод множества set
void bitset_print(bitset set) {
    for (int i = set.maxValue; i >= 0; i--) {
        printf("%d", (set.values >> i) & 1);
    }
}
