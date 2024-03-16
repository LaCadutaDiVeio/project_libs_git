#include <bitset/bitset.h>
#include <unordered_set/unordered_set.h>
#include <ordered_set/ordered_set.h>
#include <vectors/vector.h>
#include <vectors_void/void_vector.h>
#include <matrix/matrix.h>
#include <test/test_set.h>

bitset bitset1;
bitset bitset2;
bitset bitset3;

void create_bitsets_for_tests() {
    bitset1 = bitset_create(10);
    bitset2 = bitset_create(10);
    bitset3 = bitset_create(10);

    bitset_insert(&bitset1, 1);
    bitset_insert(&bitset1, 2);
    bitset_insert(&bitset1, 3);
    bitset_insert(&bitset1, 4);
    bitset_insert(&bitset1, 5);

    bitset_insert(&bitset2, 1);
    bitset_insert(&bitset2, 2);
    bitset_insert(&bitset2, 3);

    bitset_insert(&bitset3, 1);
    bitset_insert(&bitset3, 5);
    bitset_insert(&bitset3, 6);
}

void test_bitset() {
    create_bitsets_for_tests();
    test_bitset_in();
    test_bitset_isEqual();
    test_bitset_insert();
    test_bitset_delete();
    test_bitset_union();
    test_bitset_intersection();
    test_bitset_difference();
    test_bitset_sym_difference();
    test_bitset_compliment();
}

void test_bitset_in() {
    assert(bitset_in(bitset1, 1));
    assert(bitset_in(bitset2, 3));
    assert(!bitset_in(bitset1, 6));
}

void test_bitset_isEqual() {
    assert(!bitset_isEqual(bitset2, bitset3));
}

void test_bitset_insert() {
    bitset temp = bitset_create(3);
    bitset_insert(&temp, 1);
    bitset_insert(&temp, 5);
    bitset_insert(&temp, 6);
    assert(bitset_isEqual(temp, bitset3));
}

void test_bitset_delete() {
    bitset temp = bitset1;
    bitset_deleteElement(&temp, 5);
    bitset_deleteElement(&temp, 4);
    assert(bitset_isEqual(temp, bitset2));
}

void test_bitset_union() {
    bitset temp;
    bitset_insert(&temp, 4);
    bitset_insert(&temp, 5);
    bitset set_union = bitset_union(bitset2, temp);
    assert(bitset_isEqual(set_union, bitset1));
}

void test_bitset_intersection() {
    bitset intersection = bitset_intersection(bitset1, bitset2);
    assert(bitset_isEqual(intersection, bitset2));
}

void test_bitset_difference() {
    bitset temp = bitset_create(3);
    bitset_insert(&temp, 4);
    bitset_insert(&temp, 5);
    bitset_insert(&temp, 6);

    bitset set_dif = bitset_difference(bitset1, temp);
    assert(bitset_isEqual(set_dif, bitset2));
}

void test_bitset_sym_difference() {
    bitset temp_1 = bitset_create(3);
    bitset_insert(&temp_1, 4);
    bitset_insert(&temp_1, 5);
    bitset_insert(&temp_1, 6);

    bitset result = bitset2;
    bitset_insert(&result, 6);

    bitset set_sym_dif = bitset_symmetricDifference(bitset1, temp_1);

    assert(bitset_isEqual(set_sym_dif, result));
}

void test_bitset_compliment() {
    bitset result = bitset_create(10);
    bitset_insert(&result, 0);
    bitset_insert(&result, 6);
    bitset_insert(&result, 7);
    bitset_insert(&result, 8);
    bitset_insert(&result, 9);
    bitset_insert(&result, 10);

    bitset set_comp = bitset_complement(bitset1);

    assert(bitset_isEqual(result, set_comp));
}

//---------------------------------------------------------

unordered_array_set un_set1;
unordered_array_set un_set2;

void create_unordered_sets_for_tests() {
    un_set1 = unordered_array_set_create_from_array((int[]) {1, 3, 2, 4}, 4);
    un_set2 = unordered_array_set_create_from_array((int[]) {3, 4, 5}, 3);
}

void test_unordered_array_set() {
    create_unordered_sets_for_tests();
    test_unordered_array_set_create_from_array();
    test_unordered_array_set_in();
    test_unordered_array_set_isSubset();
    test_unordered_array_set_isEqual();
    test_unordered_array_set_insert();
    test_unordered_array_set_deleteElement();
    test_unordered_array_set_union();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_sym_difference();
    test_unordered_array_set_complement();

    unordered_array_set_delete(un_set1);
    unordered_array_set_delete(un_set2);
}

void test_unordered_array_set_create_from_array() {
    create_unordered_sets_for_tests();

    unordered_array_set set1 = unordered_array_set_create(4);
    unordered_array_set_insert(&set1, 1);
    unordered_array_set_insert(&set1, 2);
    unordered_array_set_insert(&set1, 3);
    unordered_array_set_insert(&set1, 4);

    assert(unordered_array_set_isEqual(un_set1, set1));
}

void test_unordered_array_set_in() {
    assert(unordered_array_set_in(un_set1, 1) == 0);
    assert(unordered_array_set_in(un_set1, 10) == un_set1.size);
}

void test_unordered_array_set_isSubset() {
    unordered_array_set subset = unordered_array_set_create_from_array((int[]) {1, 2}, 2);
    assert(unordered_array_set_isSubset(subset, un_set1));
    assert(!unordered_array_set_isSubset(subset, un_set2));
}

void test_unordered_array_set_isEqual() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {5, 3, 4}, 3);
    assert(unordered_array_set_isEqual(un_set2, set));
    assert(!unordered_array_set_isEqual(un_set1, set));
}

void test_unordered_array_set_insert() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {5, 3}, 2);
    set.capacity++;
    unordered_array_set_insert(&set, 4);
    assert(unordered_array_set_isEqual(set, un_set2));
}

void test_unordered_array_set_deleteElement() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {5, 3, 4, 10}, 4);
    unordered_array_set_deleteElement(&set, 10);
    assert(unordered_array_set_isEqual(set, un_set2));
}

void test_unordered_array_set_union() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 3}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {2, 4}, 2);

    unordered_array_set union_set = unordered_array_set_union(set1, set2);
    assert(unordered_array_set_isEqual(un_set1, union_set));
}

void test_unordered_array_set_intersection() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 3, 4, 5}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {3, 4, 5, 7}, 4);

    unordered_array_set inter_set = unordered_array_set_intersection(set1, set2);
    assert(unordered_array_set_isEqual(un_set2, inter_set));
}

void test_unordered_array_set_difference() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 3, 4, 5}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {1, 2}, 2);

    unordered_array_set diff_set = unordered_array_set_difference(set1, set2);
    assert(unordered_array_set_isEqual(un_set2, diff_set));
}

void test_unordered_array_set_sym_difference() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 4, 5}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {3, 2, 5}, 3);

    unordered_array_set sym_diff_set = unordered_array_set_sym_difference(set1, set2);

    assert(unordered_array_set_isEqual(un_set1, sym_diff_set));
}

void test_unordered_array_set_complement() {
    unordered_array_set uni = unordered_array_set_create_from_array((int[]) {1, 3, 5, 4, 2}, 5);
    unordered_array_set comp = unordered_array_set_create_from_array((int[]) {1, 2}, 2);

    unordered_array_set comp_set = unordered_array_set_complement(un_set2, uni);

    assert(unordered_array_set_isEqual(comp, comp_set));
}

//-------------------------------------------------------


ordered_array_set or_set1;
ordered_array_set or_set2;

void create_ordered_sets_for_tests() {
    or_set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4}, 4);
    or_set2 = ordered_array_set_create_from_array((int[]) {3, 4, 5}, 3);
}

void test_ordered_array_set() {
    create_ordered_sets_for_tests();
    test_ordered_array_set_create_from_array();
    test_ordered_array_set_in();
    test_ordered_array_set_isSubset();
    test_ordered_array_set_isEqual();
    test_ordered_array_set_insert();
    test_ordered_array_set_deleteElement();
    test_ordered_array_set_union();
    test_ordered_array_set_intersection();
    test_ordered_array_set_difference();
    test_ordered_array_set_sym_difference();
    test_ordered_array_set_complement();

    ordered_array_set_delete(&or_set1);
    ordered_array_set_delete(&or_set2);
}

void test_ordered_array_set_create_from_array() {
    create_unordered_sets_for_tests();

    ordered_array_set set1 = ordered_array_set_create(4);
    ordered_array_set_insert(&set1, 1);
    ordered_array_set_insert(&set1, 2);
    ordered_array_set_insert(&set1, 3);
    ordered_array_set_insert(&set1, 4);

    assert(ordered_array_set_isEqual(or_set1, set1));
}

void test_ordered_array_set_in() {
    assert(ordered_array_set_in(or_set1, 1) == 0);
    assert(ordered_array_set_in(or_set1, 10) == un_set1.size);
}

void test_ordered_array_set_isSubset() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {1, 2}, 2);
    assert(ordered_array_set_isSubset(subset, or_set1));
    assert(!ordered_array_set_isSubset(subset, or_set2));
}

void test_ordered_array_set_isEqual() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {3, 4, 5}, 3);
    assert(ordered_array_set_isEqual(or_set2, set));
    assert(!ordered_array_set_isEqual(or_set1, set));
}

void test_ordered_array_set_insert() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {3, 5}, 2);
    set.capacity++;
    ordered_array_set_insert(&set, 4);
    assert(ordered_array_set_isEqual(set, or_set2));
}

void test_ordered_array_set_deleteElement() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {3, 4, 5, 10}, 4);
    ordered_array_set_deleteElement(&set, 10);
    assert(ordered_array_set_isEqual(set, or_set2));
}

void test_ordered_array_set_union() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 3}, 2);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 4}, 2);

    ordered_array_set union_set = ordered_array_set_union(set1, set2);
    assert(ordered_array_set_isEqual(or_set1, union_set));
}

void test_ordered_array_set_intersection() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 3, 4, 5}, 4);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {3, 4, 5, 7}, 4);

    ordered_array_set inter_set = ordered_array_set_intersection(set1, set2);
    assert(ordered_array_set_isEqual(or_set2, inter_set));
}

void test_ordered_array_set_difference() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 3, 4, 5}, 4);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {1, 2}, 2);

    ordered_array_set diff_set = ordered_array_set_difference(set1, set2);
    assert(ordered_array_set_isEqual(or_set2, diff_set));
}

void test_ordered_array_set_sym_difference() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 4, 5}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 3, 5}, 3);

    ordered_array_set sym_diff_set = ordered_array_set_sym_difference(set1, set2);

    assert(ordered_array_set_isEqual(or_set1, sym_diff_set));
}

void test_ordered_array_set_complement() {
    ordered_array_set uni = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5}, 5);
    ordered_array_set comp = ordered_array_set_create_from_array((int[]) {1, 2}, 2);

    ordered_array_set comp_set = ordered_set_complement(or_set2, uni);

    assert(ordered_array_set_isEqual(comp, comp_set));
}


//--------------------------------------------

void test_vectors() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_vector_pointers();
    test_vector_data_funcs();
}

void test_pushBack_emptyVector() {
    vector a = vector_create(0);
    assert(a.capacity == 0);
    vector_pushBack(&a, 10);
    assert(a.capacity == 1);
    assert(vector_get_value_by_pos(a, 0) == 10);
}

void test_pushBack_fullVector() {
    vector a = vector_create(2);
    vector_pushBack(&a, 1);
    vector_pushBack(&a, 2);
    vector_pushBack(&a, 3);
    assert(a.capacity == 4);
    assert(vector_get_value_by_pos(a, 2) == 3);
}

void test_popBack_notEmptyVector() {
    vector a = vector_create(0);
    vector_pushBack(&a, 10);
    assert(a.size == 1);
    vector_popBack(&a);
    assert(a.size == 0);
    assert(a.capacity == 1);
}

void test_vector_pointers() {
    vector v = vector_create(2);
    vector_pushBack(&v, 1);
    assert(*vector_front(&v) == 1);
    assert(*vector_back(&v) == 1);
    assert(*vector_at(&v, 0) == 1);

    vector_pushBack(&v, 2);
    assert(vector_get_value_by_pos(v, 1) == 2);
}

void test_vector_data_funcs() {
    vector v = vector_create(0);
    assert(v.data == NULL);

    v = vector_create(1);
    assert(v.capacity == 1);

    vector_reserve(&v, 3);
    assert(v.capacity == 3);

    v.size = 1;
    vector_clear(&v);
    assert(v.size == 0);
    assert(v.data != NULL); //так как по условию в мет. clear не трогает содержимое!


    v.size = 2;
    vector_shrink_to_fit(&v);
    assert(v.capacity == 2);

    vector_delete(&v);
    assert(v.data == NULL);
}


//---------------------------------

void test_void_vector_from_lab_1() {
    int n;
    scanf("%d", &n);

    void_vector v = void_vector_create(0, sizeof(int));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        void_vector_pushBack(&v, &x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        void_vector_getValueByPos(&v, i, &x);
        printf("%d ", x);
    }
}

void test_void_vector_from_lab_2() {
    size_t n;
    scanf("%zd", &n);

    void_vector v = void_vector_create(0, sizeof(float));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        void_vector_pushBack(&v, &x);
    }
    for (int i = 0; i < n; i++) {
        float x;
        void_vector_getValueByPos(&v, i, &x);
        printf("%f ", x);
    }
}

void test_void_vector() {
    void_vector v = void_vector_create(0, sizeof(int));
    assert(v.data == NULL);
    assert(v.size_of_type == sizeof(int));

    v = void_vector_create(1, sizeof(char));
    assert(v.capacity == 1);
    assert(v.size_of_type == sizeof(char));

    void_vector_reserve(&v, 2);
    assert(v.capacity == 2);

    v.size = 1;
    void_vector_clear(&v);
    assert(v.size == 0);
    assert(v.data != NULL);

    void_vector_reserve(&v, 4);
    v.size = 2;
    void_vector_shrink_to_fit(&v);
    assert(v.capacity == 2);

    void_vector_delete(&v);
    assert(v.data == NULL);

    v = void_vector_create(2, sizeof(double));
    char a = 'a';
    char b = 'b';
    void_vector_pushBack(&v, &a);
    void_vector_pushBack(&v, &b);
    assert(void_vector_isFull(v) == 1);
    assert(void_vector_isEmpty(v) == 0);


    char aa;
    char bb;
    void_vector_getValueByPos(&v, 0, &aa);
    void_vector_getValueByPos(&v, 0, &bb);
    assert(aa == a && bb == b);

    void_vector_clear(&v);
    assert(void_vector_isFull(v) == 0);
    assert(void_vector_isEmpty(v) == 1);


    void_vector_pushBack(&v, &a);
    void_vector_pushBack(&v, &b);
    assert(void_vector_isFull(v) == 1);

    void_vector_popBack(&v);
    void_vector_popBack(&v);
    assert(void_vector_isEmpty(v) == 1);

    void_vector_pushBack(&v, &a);
    void_vector_setValue(&v, 0, &b);

    char aaa;
    void_vector_getValueByPos(&v, 0, &aaa);
    assert(aaa == 'a');
}

//-----------------------------

void testMatrix_1 () {
    matrix mat = getMemMatrix(3, 3);
    assert (mat.values != NULL && mat.nRows == 3 && mat.nCols == 3);
    freeMemMatrix(&mat);

    matrix sorted = createMatrixFromArray(
            (int[]) {
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            }, 3, 3
            );

    matrix uns1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    7, 8, 9,
                    4, 5, 6
            }, 3, 3
    );
    matrix uns2 = createMatrixFromArray(
            (int[]) {
                    3, 1, 2,
                    6, 4, 5,
                    9, 7, 8
            }, 3, 3
    );
    insertionSortRowsMatrixByRowCriteria(uns1, getSum);
    insertionSortColsMatrixByColCriteria(uns2, getSum);
    assert(areTwoMatricesEqual(&uns1, &sorted) && areTwoMatricesEqual(&uns2, &sorted));
    freeMemMatrix(&sorted);
    freeMemMatrix(&uns1);
    freeMemMatrix(&uns2);

    mat = createMatrixFromArray(
            (int[]) {
                1, 2,
                2, 1
            }, 2, 2
            );
    assert(isSquareMatrix(&mat));

    matrix E = createMatrixFromArray(
            (int[]) {
                1, 0,
                0, 1
            }, 2, 2
            );
    assert(isEMatrix(&E) && !isEMatrix(&mat));
    assert(isSymmetricMatrix(&mat));
    freeMemMatrix(&E);

    mat = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, 3, 3
    );
    transposeSquareMatrix(&mat);

    matrix transpose = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            }, 3, 3
    );
    assert(areTwoMatricesEqual(&mat, &transpose));

    freeMemMatrix(&mat);
    freeMemMatrix(&transpose);

    mat = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
            }, 2, 3
    );
    transposeMatrix(&mat);

    transpose = createMatrixFromArray(
            (int[]) {
                    1, 4,
                    2, 5,
                    3, 6,
            }, 3, 2
    );
    assert(areTwoMatricesEqual(&mat, &transpose));
    freeMemMatrix(&mat);
    freeMemMatrix(&transpose);
}


void testMatrix_2 () {
    //__1__
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, 3, 3
    );
    matrix swapped = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3
            }, 3, 3
    );
    swapColsWithMinMaxElements(&m);
    assert(areTwoMatricesEqual(&m, &swapped));
    freeMemMatrix(&m);
    freeMemMatrix(&swapped);
    //__2__
    m = createMatrixFromArray(
            (int[]) {
                    7, 1, 2,
                    1, 8, 1,
                    3, 2, 3
            }, 3, 3
    );
    swapped = createMatrixFromArray(
            (int[]) {
                    3, 2, 3,
                    7, 1, 2,
                    1, 8, 1
            }, 3, 3
    );
    sortRowsByMinElement(m);
    assert(areTwoMatricesEqual(&m, &swapped));
    freeMemMatrix(&m);
    freeMemMatrix(&swapped);
    //__3__

}
