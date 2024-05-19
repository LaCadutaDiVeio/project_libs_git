#include <stdbool.h>

#include <bitset/bitset.h>
#include <unordered_set/unordered_set.h>
#include <ordered_set/ordered_set.h>
#include <vectors/vector.h>
#include <vectors_void/void_vector.h>
#include <matrix/matrix.h>
#include <string_/string_.h>
#include <files/files.h>
#include <lab_20/lab_20.h>
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

void testMatrix_1() {
    matrix mat = getMemMatrix(3, 3);
    assert(mat.values != NULL && mat.nRows == 3 && mat.nCols == 3);
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


void testMatrix_2() {
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
    m = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 4, 3, 3,
                    2, 5, 1, 8, 2, 7,
                    6, 1, 4, 4, 8, 3
            }, 3, 6
    );
    swapped = createMatrixFromArray(
            (int[]) {
                    5, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4
            }, 3, 6
    );
    sortColsByMinElement(m);
    assert(areTwoMatricesEqual(&m, &swapped));
    //freeMemMatrix(&m);
    //freeMemMatrix(&swapped);
    freeMemMatrices_(2, &m, &swapped);
    //__4__
    m = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    3, 4
            }, 2, 2
    );
    matrix m_mul_m = createMatrixFromArray(
            (int[]) {
                    7, 10,
                    15, 22
            }, 2, 2
    );
    matrix mm = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    2, 1
            }, 2, 2
    );
    matrix square_if_sym = createMatrixFromArray(
            (int[]) {
                    5, 4,
                    4, 5
            }, 2, 2
    );
    getSquareOfMatrixIfSymmetric(&mm);
    assert(areTwoMatricesEqual(&square_if_sym, &mm));
    getSquareOfMatrixIfSymmetric(&m);
    assert(!areTwoMatricesEqual(&m, &m_mul_m));
    m = mulMatrices(m, m);
    assert(areTwoMatricesEqual(&m, &m_mul_m));
    freeMemMatrices_(4, &m, &mm, &m_mul_m, &square_if_sym);
    //__5__
    m = createMatrixFromArray(
            (int[]) {
                    2, 4,
                    2, 3
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2, 2,
                    4, 3
            }, 2, 2
    );
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);

    m = createMatrixFromArray(
            (int[]) {
                    2, 4,
                    1, 5
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2, 4,
                    1, 5
            }, 2, 2
    );
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__6__
    m = createMatrixFromArray(
            (int[]) {
                    3, -5,
                    1, -2
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2, -5,
                    1, -3
            }, 2, 2
    );
    matrix mmm = createMatrixFromArray(
            (int[]) {
                    2, 1,
                    1, -3
            }, 2, 2
    );
    assert(isMutuallyInverseMatrices(m, mm));
    assert(!isMutuallyInverseMatrices(m, mmm));
    freeMemMatrices_(3, &m, &mm, &mmm);
    //__7__
    m = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            }, 3, 4
    );
    assert(20 == findSumOfMaxesOfPseudoDiagonal(m));
    freeMemMatrices_(1, &m);
    //__8__
    m = createMatrixFromArray(
            (int[]) {
                    10, 7, 5, 6,
                    3, 11, 8, 9,
                    4, 1, 12, 2
            }, 3, 4
    );
    mm = createMatrixFromArray(
            (int[]) {
                    6, 8, 9, 2,
                    7, 12, 3, 4,
                    10, 11, 5, 1
            }, 3, 4
    );
    assert(getMinInArea(m) == 5);
    assert(getMinInArea(mm) == 6);
    freeMemMatrices_(2, &m, &mm);
    //__9__
    m = createMatrixFromArray(
            (int[]) {
                    5, 11,
                    2, 12,
                    11, 3,
                    4, 2
            }, 4, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    4, 2,
                    11, 3,
                    5, 11,
                    2, 12
            }, 4, 2
    );
    sortByDistances(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__10__
    m = createMatrixFromArray(
            (int[]) {
                    7, 1,
                    2, 7,
                    5, 4,
                    4, 3,
                    1, 6,
                    8, 0
            }, 6, 2
    );
    assert(countEqClassesByRowsSum(m) == 3);
    freeMemMatrices_(1, &m);
    //__11__
    m = createMatrixFromArray(
            (int[]) {
                    3, 5, 5, 4,
                    2, 3, 6, 7,
                    12, 2, 1, 1
            }, 3, 4
    );
    assert(getNSpecialElement(m) == 2);
    freeMemMatrices_(1, &m);
    //__12__
    m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 1
            }, 3, 3
    );
    mm = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    1, 4, 7,
                    7, 8, 1
            }, 3, 3
    );
    swapPenultimateRow(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__13__
    matrix *ms = createArrayOfMatrixFromArray(
            (int[]) {
                    7, 1,
                    1, 1,
                    1, 6,
                    2, 2,
                    5, 4,
                    2, 3,
                    1, 3,
                    7, 9
            }, 4, 2, 2
    );
    assert(countNonDescendingRowsMatrices(ms, 4) == 2);
    freeMemMatrices(ms, 4);
    //__14__
    ms = createArrayOfMatrixFromArray(
            (int[]) {
                    0, 1,
                    1, 0,
                    0, 0,
                    1, 1,
                    2, 1,
                    1, 1,
                    0, 0,
                    0, 0,
                    4, 7,
                    0, 0,
                    1, 0,
                    0, 0,
                    0, 1,
                    0, 2,
                    0, 3,
            },
            5, 3, 2
    );
    //printMatrixWithMaxZeroRows(ms, 5);
    freeMemMatrices(ms, 5);
    //    __15__
    ms = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 4,
                    5, 7,
                    2, 4,
                    6, 9,
                    5, 5,
                    9, 1,
                    1, 1,
                    1, 1
            },
            4, 2, 2
    );
    //printMatrixWithMinNorm(ms, 4);
    freeMemMatrices(ms, 4);
    //__16__
    m = createMatrixFromArray(
            (int[]) {
                    2, 3, 5, 5, 4,
                    6, 2, 3, 8, 12,
                    12, 12, 2, 1, 2
            }, 3, 5
    );
    assert(getNSpecialElement2(m) == 4);
    //__17__
    m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, 3, 3
    );
    int b[] = {1, 4, 7};
    assert(getVectorIndexWithMaxAngle(m, b) == 0);
    freeMemMatrices_(1, &m);
    //__18__
    m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            }, 3, 3
    );
    assert(getSpecialScalarProduct(m, 3) == 102);
    freeMemMatrices_(1, &m);
}


//-----------------------------------------


void test_string() {
    test_len();
    test_nonSpace();
    test_space();
    test_compare();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
    test_removeExtraSpaces();
    test_removeAdjacentEqualLetters();
    testWordsWithDigits();
    testDigitsToSpace();
    testEquals();
    testReplaceWordToWord();
    //
    testPalindrome();
    testJoinStrings();
    testReverse();
    testWordsBeforeWordsWithA();
    testLastWordFromFirstInSecond();
    testSameWords();
    testWordsWithSimilarLetters();
    testStringWithoutWordsIdenticToLast();
    testWordPrecedingFirstCommonWord_Status();
    testDeletePalindromes();
    testExpandStr();
    testIsStringHasWordAlp();
}

void test_len() {
    const char *s1 = "Hello, world!";
    const char *s2 = "Hello, world!\t";
    const char *s3 = "";
    assert(strlen_(s1) == 13 && strlen_(s2) == 14 && strlen(s3) == 0);
}

void test_nonSpace() {
    const char *s1 = "asmogus";
    const char *s2 = "\n";
    const char *s3 = "";

    assert(*findNonSpace(s1) == 'a');
    assert(*findNonSpace(s2) == '\0');
    assert(*findNonSpace(s3) == '\0');

    assert(*findNonSpaceReverse(&s1[strlen_(s1) - 1], s1) == 's');
    assert(*findNonSpaceReverse(&s2[strlen_(s2) - 1], s2) == '\0');
    assert(*findNonSpaceReverse(&s3[strlen_(s3) - 1], s3) == '\0');
}

void test_space() {
    const char *s1 = "asmogus\t";
    const char *s2 = "\t\n";
    const char *s3 = "";
    const char *s4 = "a a";

    assert(*findSpaceReverse(&s1[strlen_(s1) - 1], s1) == '\t');
    assert(*findSpaceReverse(&s2[strlen_(s2) - 1], s2) == '\n');
    assert(*findSpaceReverse(&s3[strlen_(s3) - 1], s3) == '\0');
    assert(*findSpaceReverse(&s4[strlen_(s4) - 1], s4) == ' ');

    assert(*findSpace(s1) == '\t');
    assert(*findSpace(s2) == '\t');
    assert(*findSpace(s3) == '\0');
    assert(*findSpace(s4) == ' ');
}

void test_compare() {
    const char *s1 = "string";
    const char *s2 = "string";
    const char *s3 = "str";
    const char *s4 = " ";

    assert(strcmp(s1, s2) == 0);
    assert(strcmp(s1, s3) > 0);
    assert(strcmp(s1, s4) > 0);
}

void test_copy() {
    char *source = "source text";
    char destination[64];
    char *end = strcopy(source, source + strlen_(source), destination);
    assert(strcmp(source, destination) == 0);
}

void test_copyIf() {
    char *source = "1a2 3 b";
    char destination[3];
    char *end = copyIf(source, source + strlen_(source), destination, isalpha);
    //printf("%s", destination);
    assert(strcmp(destination, "ab") == 0);
}

void test_copyIfReverse() {
    char *source = "1a2 3 b";
    char destination[3];
    char *end = copyIfReverse(source + strlen_(source), source, destination, isalpha);
    //printf("%s", destination);
    assert(strcmp(destination, "ba") == 0);
}

//------------------------

void test_removeExtraSpaces() {
    char s1[] = "  more  spaces  ";
    removeExtraSpaces(s1);
    ASSERT_STRING(" more spaces ", s1);
}


void test_removeAdjacentEqualLetters() {
    char s1[] = "aaaamonnguss";
    removeAdjacentEqualLetters(s1);
    ASSERT_STRING("amongus", s1);

    char s2[] = "hoot tubs";
    removeAdjacentEqualLetters(s2);
    ASSERT_STRING("hot tubs", s2);
}

void testWordsWithDigits() {
    char s[] = "a1b2c3d4";

    digitToEnd(s);
    ASSERT_STRING("abcd1234", s);
    digitToEndReverse(s);
    ASSERT_STRING("abcd4321", s);
    digitToStart(s);
    ASSERT_STRING("4321abcd", s);
}

void testDigitsToSpace() {
    char s1[] = "a1b";
    replaceDigitsWithSpaces(s1);
    ASSERT_STRING("a b", s1);

    char s2[] = "a20b";
    replaceDigitsWithSpaces(s2);
    ASSERT_STRING("a  b", s2);
}

void testEquals() {
    char s1[] = "Aaaugh";
    WordDescriptor w1;
    getWord(s1, &w1);
    char s2[] = "Aaaugh";
    WordDescriptor w2;
    getWord(s2, &w2);
    assert(areWordsEqual(w1, w2));
}

void testReplaceWordToWord() {
    char s1[] = "long string is long";
    replaceWords(s1, "long", "bad");
    //printf("%s", s1);
    ASSERT_STRING("bad string is bad", s1);

    char s2[] = "long string is long";
    //replaceWordsSS_ryzen(s2, "long", "bruv");
    replaceWords(s2, "long", "bruv");
    //printf("%s", s2);
    ASSERT_STRING("bruv string is bruv", s2);

    char s3[] = "long string is long";
    replaceWords(s3, "long", "short");
    //printf("%s", s1);
    ASSERT_STRING("short string is short", s3);
}

void testOrdered() {
}

void testPalindrome() {
    char *s1 = "amoma, sugoma, maam";
    assert(getAmountPalindromes(s1) == 2);

    char *s2 = "";
    assert(getAmountPalindromes(s2) == 0);
}

void testJoinStrings() {
    char s1[MAX_STRING_SIZE];
    join2StrInStr(s1, "Not single was", "a f*ck given");
    ASSERT_STRING("Not a single f*ck was given", s1);

    char s2[MAX_STRING_SIZE];
    join2StrInStr(s2, "Never give you up", "gonna");
    ASSERT_STRING("Never gonna give you up", s2);

    char s3[MAX_STRING_SIZE];
    join2StrInStr(s3, "Cake", "is a lie");
    ASSERT_STRING("Cake is a lie", s3);
}

void testReverse() {
    char s1[] = "reversed is string";
    reverseStrOrder(s1);
    ASSERT_STRING("string is reversed", s1);

    char s2[] = "word";
    reverseStrOrder(s2);
    ASSERT_STRING("word", s2);

    //несовсем уверен, что это ожидаемое поведение, но оно логичное
    char s3[] = " ";
    reverseStrOrder(s3);
    ASSERT_STRING("", s3);

    char s4[] = "";
    reverseStrOrder(s4);
    ASSERT_STRING("", s4);
}

void testWordsBeforeWordsWithA() {
    char *s1 = "";
    assert(getWordBeforeFirstWordWithA_Status(s1) == EMPTY_STRING);
    char *s2 = "a student";
    assert(getWordBeforeFirstWordWithA_Status(s2) == FIRST_WORD_WITH_A);
    char *s3 = "some ward";
    assert(getWordBeforeFirstWordWithA_Status(s3) == WORD_FOUND);
    char *s4 = "non letters";
    assert(getWordBeforeFirstWordWithA_Status(s4) == NOT_FOUND_A_WORD_WITH_A);
}

void testLastWordFromFirstInSecond() {
    ASSERT_STRING("second", lastWordFromFirstInSecond("first second word", "first third second"));
    ASSERT_STRING("word", lastWordFromFirstInSecond("first second word", "first third word"));
    ASSERT_STRING("", lastWordFromFirstInSecond("one two three", "four five six"));
}

void testSameWords() {
    assert(areSameWordInStr("word1 word1 word3"));
    assert(!areSameWordInStr("word1 word2 word3"));
    assert(!areSameWordInStr(""));
    assert(!areSameWordInStr("word1"));
}

void testWordsWithSimilarLetters() {
    assert(hasWordWithSimilarAlp("Abba abab adn sdfghjk"));
    assert(!hasWordWithSimilarAlp("abc bcd cde def"));
    assert(!hasWordWithSimilarAlp(""));
}

void testStringWithoutWordsIdenticToLast() {
    char s1[] = "a b c d a a";
    getStringWithoutWordsIdenticToLast(s1);
    ASSERT_STRING("b c d", s1);

    char s2[] = "";
    getStringWithoutWordsIdenticToLast(s2);
    ASSERT_STRING("", s2);
}

void testWordPrecedingFirstCommonWord_Status() {
    char s1[] = "a b c d";
    char s2[] = "b c d";
    char s3[] = "a b c d";
    char s4[] = "";
    char s5[] = "e f g";
    char c[MAX_STRING_SIZE];
    WordDescriptor w;
    int stat = WordPrecedingFirstCommonWord_Status(s1, s2, &w);

    wordDescriptorToString(w, c);
    ASSERT_STRING("a", c);
    assert(stat == WORD_FOUND_preceding);
    assert(WordPrecedingFirstCommonWord_Status(s1, s3, NULL) == FIRST_WORD_IS_COMMON_preceding);
    assert(WordPrecedingFirstCommonWord_Status(s1, s4, NULL) == EMPTY_STRING_preceding);
    assert(WordPrecedingFirstCommonWord_Status(s1, s5, NULL) == NOT_FOUND_COMMON_WORD_preceding);
}

void testDeletePalindromes() {
    char s1[] = "word aboba is palindrome";
    deletePalindromesFromStr(s1);
    ASSERT_STRING("word is palindrome", s1);

    char s2[] = "no palindromes here";
    deletePalindromesFromStr(s2);
    ASSERT_STRING("no palindromes here", s2);
}

void testExpandStr() {
    char s1[] = "a b c";
    char s2[] = "d e f g a";

    expandSmallStrWithBigStr(s1, s2);
    ASSERT_STRING("a b c g a", s1);
}

void testIsStringHasWordAlp() {
    assert(isStringHasAlphabetOfWord("abcde", "abc"));
    assert(isStringHasAlphabetOfWord("ab cde", "abc"));
    assert(!isStringHasAlphabetOfWord("abcde", ""));
    assert(!isStringHasAlphabetOfWord("abcde", "fg"));
    assert(!isStringHasAlphabetOfWord("ab c de", "fg"));
}


//тесты для 19 лаб.
void test_files() {
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
}

void test_01() {
    void_vector tests = void_vector_create(2, sizeof(matrix));
    matrix m1 = createMatrixFromArray((int[])
                                              {
                                                      1, 2,
                                                      3, 4
                                              }, 2, 2
    );
    matrix m2 = createMatrixFromArray((int[])
                                              {
                                                      1, 2, 3,
                                                      4, 5, 6,
                                                      7, 8, 9
                                              }, 3, 3
    );
    void_vector_pushBack(&tests, &m1);
    void_vector_pushBack(&tests, &m2);
    writeMatrixInFile("data_for_tasks/exercise01.txt", tests);

    void_vector mats = void_vector_create(2, sizeof(matrix));
    matrix m01 = createMatrixFromArray((int[])
                                               {
                                                       1, 3,
                                                       2, 4
                                               }, 2, 2
    );
    matrix m02 = createMatrixFromArray((int[])
                                               {
                                                       1, 4, 7,
                                                       2, 5, 8,
                                                       3, 6, 9
                                               }, 3, 3
    );
    void_vector_pushBack(&mats, &m01);
    void_vector_pushBack(&mats, &m02);
    void_vector res = void_vector_create(0, sizeof(matrix));
    lab_19_exercise1(&res);

    for (int i = 0; i < mats.size; i++) {
        matrix a, b;
        void_vector_getValueByPos(&mats, i, &a);
        void_vector_getValueByPos(&res, i, &b);
        assert(areTwoMatricesEqual(&a, &b));
    }
}

void test_02() {
    void_vector tests = void_vector_create(4, sizeof(int));
    float f_arr[4] = {0.0f, 1.0f, 1.1113f, -3.1322f};
    for (int i = 0; i < 4; i++) {
        void_vector_pushBack(&tests, &f_arr[i]);
    }
    writeFloatInFile("data_for_tasks/exercise02.txt", "%f ", tests);
}

void test_03() {
    int result;

    writeStrInFile("data_for_tasks/exercise03.txt", "1 + 10");
    lab_19_exercise3(&result);
    assert(result == 11);
    writeStrInFile("data_for_tasks/exercise03.txt", "1 - 10");
    lab_19_exercise3(&result);
    assert(result == -9);
    writeStrInFile("data_for_tasks/exercise03.txt", "2 * 5");
    lab_19_exercise3(&result);
    assert(result == 10);
    writeStrInFile("data_for_tasks/exercise03.txt", "15 / 3");
    lab_19_exercise3(&result);
    assert(result == 5);
}

void test_04() {
    writeStrInFile("data_for_tasks/exercise04.txt", "word school sort nuts");
    lab_19_exercise4("or");

    char *test[] = {"word", "sort"};
    char buffer[100u];
    void_vector result = void_vector_create(0, sizeof(char *));
    FILE *file1 = fopen("data_for_tasks/exercise04.txt", "r");
    while (fscanf(file1, "%s", &buffer) == 1)
        void_vector_pushBack(&result, buffer);

    for (int i = 0; i < result.size; i++) {
        void_vector_getValueByPos(&result, i, &buffer);
        assert(strcmp(test[i], buffer) == 0);
    }

    fclose(file1);
}

void test_05() {
    FILE *file = fopen("data_for_tasks/exercise05.txt", "w");
    fprintf(file, "a bbbbb aa\nc\naaa bbb ccc\n\0\n");
    fclose(file);
    lab_19_exercise5();

    FILE *read = fopen("data_for_tasks/exercise05.txt", "r");
    char buffer[100u];
    char *answer[] = {"bbbbb", "c", "aaa", "\0"};
    int i = 0;
    while (fgets(buffer, 100u, read) != NULL) {
        assert(strcmp(buffer, answer[i]));
        i++;
    }
}

void test_06() {
    polynomial poly[3] = {
            {2, 1},
            {1, 1},
            {0, 1},
    };

    FILE *write = fopen("data_for_tasks/exercise06.bin", "wb");
    fwrite(poly, sizeof(polynomial), 3, write);
    fclose(write);

    void_vector result = void_vector_create(0, sizeof(polynomial));
    lab_19_exercise6(-1.f, &result);

    polynomial answer[2] = {
            {2, 1},
            {0, 1},
    };

    for (int i = 0; i < 2; i++) {
        polynomial p;
        void_vector_getValueByPos(&result, i, &p);
        assert(p.coefficient == answer[i].coefficient && p.power == answer[i].power);
    }
}

void test_07() {
    FILE *file = fopen("data_for_tasks/exercise07.bin", "wb");
    int nums[] = {1, 2, -4, 3, -5, 6};
    fwrite(&nums, sizeof(int), 6, file);
    fclose(file);
    void_vector numbers = void_vector_create(6, sizeof(int));
    lab_19_exercise7(&numbers);

    int test[] = {1, 2, 3, 6, -4, -5};
    for (int i = 0; i < 6; i++) {
        int n;
        void_vector_getValueByPos(&numbers, i, &n);
        assert(n == test[i]);
    }
}

void test_08() {
    int n = 3;
    int arr[] = {
            1, 2, 3,
            2, 1, 2,
            3, 2, 1,
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
    };

    //знаете, а ведь я хотел скипнуть это функцию...
    matrix *matrices = createArrayOfMatrixFromArray(arr, 2, n, n);

    FILE *file = fopen("data_for_tasks/exercise08.bin", "wb");
    fwrite(matrices, sizeof(matrix) * 2, 1, file);
    fclose(file);

    void_vector result = void_vector_create(0, sizeof(matrix));
    lab_19_exercise8(&result);

    matrix answer1 = createMatrixFromArray((int[]) {1, 2, 3, 2, 1, 2, 3, 2, 1}, 3, 3);
    matrix answer2 = createMatrixFromArray((int[]) {1, 4, 7, 2, 5, 8, 3, 6, 9}, 3, 3);
    matrix answer[2] = {answer1, answer2};
    for (int i = 0; i < 2; i++) {
        matrix m;
        void_vector_getValueByPos(&result, i, &m);
        assert(areTwoMatricesEqual(&m, &answer[i]));
    }
}

void test_09() {
    sportsman sportsmans[] = {
            {"Zmishenko I. I.",  50},
            {"GITler A. A.",     25},
            {"Sawwin B. B.",     100},
            {"Pochitailo V. V.", 100},
    };
    FILE *file = fopen("data_for_tasks/exercise09.bin", "wb");
    fwrite(sportsmans, sizeof(sportsman), 4, file);
    fclose(file);

    void_vector result = void_vector_create(2, sizeof(sportsman));
    lab_19_exercise9(2, &result);

    sportsman ans1 = {"Sawwin B. B.", 100};
    sportsman ans2 = {"Pochitailo V. V.", 100};
    sportsman answer[2] = {ans1, ans2};

    for (int i = 0; i < 2; i++) {
        sportsman sp;
        void_vector_getValueByPos(&result, i, &sp);
        assert(sp.result == answer[i].result);
    }
}

void test_10() {
    product products[] = {
            {"missile", 1000, 10000, 10},
            {"soap",    5,    25,    5},
            {"meat",    50,   500,   10},
    };
    order orders[] = {
            {"meat",    5},
            {"missile", 5},
            {"meat",    5},
            {"soap",    1},
            {"soap",    2},
    };

    FILE *f = fopen("data_for_tasks/exercise10f.bin", "wb");
    fwrite(products, sizeof(product), 3, f);
    fclose(f);

    FILE *g = fopen("data_for_tasks/exercise10g.bin", "wb");
    fwrite(orders, sizeof(order), 5, g);
    fclose(g);

    void_vector result = void_vector_create(0, sizeof(product));
    lab_19_exercise10(&result);

    product ans1 = {"missile", 1000, 5000, 5};
    product ans2 = {"soap", 5, 10, 2};
    product answer[] = {ans1, ans2};

    for (int i = 0; i < 2; i++) {
        product pr;
        void_vector_getValueByPos(&result, i, &pr);

        assert(strcmp(pr.name, answer[i].name) == 0 && pr.price == answer[i].price
               && pr.full_price == answer[i].full_price && pr.count == answer[i].count);
    }

}


//Для лабораторной 20

void test_lab20() {
    test_lab20_11();
    test_lab20_01();
    test_lab20_02();
    test_lab_20_03();
    test_lab_20_04();
    test_lab_20_05();
    test_lab_20_06();
    test_lab_20_07();
    test_lab_20_08();
    test_lab_20_09();
}

void test_lab20_11() {
    char words[] = "aa aaa aab ab abc ac ba daa dab dadba";
    char requests[] = "4 a 2 da 4 da";
    char *test_requests[] = {"ab", "dab", "-1"};

    int res = lab_20_task_11_FORTESTS(words, requests, test_requests);
    if (res) {
        //printf( "\nassertion passed" );
    } else {
        printf("\nassertion failed");
    }

    char words1[] = "aa aaaa";
    char requests1[] = "1 a 2 a 1 aa 2 aa";
    char *test_requests1[] = {"aa", "aaaa", "aa", "aaaa"};

    int res1 = lab_20_task_11_FORTESTS(words1, requests1, test_requests1);
    if (res1) {
        //printf( "\nassertion passed" );
    } else {
        printf("\nassertion failed");
    }
}

void test_lab20_01() {
    int n1 = 3;
    matrix m1 = getMemMatrix(n1, n1);
    int queries1[][4] = {
            {1, 1, 2, 2},
            {0, 0, 1, 1},
    };
    lab_20_task_01(&m1, queries1, 2);

    matrix test1 = createMatrixFromArray((int[]) {
                                                 1, 1, 0,
                                                 1, 2, 1,
                                                 0, 1, 1
                                         }, 3, 3
    );
    assert(areTwoMatricesEqual(&m1, &test1));

    int n2 = 5;
    matrix m2 = getMemMatrix(n2, n2);
    int queries2[][4] = {
            {0, 0, 4, 4},
            {2, 2, 2, 2},
    };
    lab_20_task_01(&m2, queries2, 2);
    matrix test2 = createMatrixFromArray((int[]) {
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 2, 1, 1,
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1,
                                         }, 5, 5
    );
    assert(areTwoMatricesEqual(&m2, &test2));
}

void test_lab20_02() {
    matrix m1 = createMatrixFromArray((int[]) {
                                              0, 1, 0,
                                              0, 0, 1,
                                              1, 1, 1,
                                              0, 0, 0
                                      }, 4, 3
    );
    matrix mm1 = getMemMatrix(4, 3);
    lab_20_task_02(&m1, &mm1);
    matrix test1 = createMatrixFromArray((int[]) {
                                                 0, 0, 0,
                                                 1, 0, 1,
                                                 0, 1, 1,
                                                 0, 1, 0
                                         }, 4, 3
    );
    assert(areTwoMatricesEqual(&mm1, &test1));
}

void test_lab_20_03() {
    int filter = 3;
    matrix m1 = createMatrixFromArray((int[]) {
                                              10, 20, 30,
                                              25, 35, 45,
                                              15, 25, 35
                                      }, 3, 3
    );
    matrix res1 = getMemMatrix(filter, filter);
    lab_20_task_03(&m1, &res1, filter);
    matrix test1 = createMatrixFromArray((int[]) {
                                                 10, 20, 30,
                                                 25, 25, 45,
                                                 15, 25, 35
                                         }, 3, 3
    );
    assert(areTwoMatricesEqual(&res1, &test1));
    freeMemMatrix(&res1);

    filter = 5;
    matrix m2 = createMatrixFromArray((int[]) {
                                              1, 2, 3, 4, 5,
                                              1, 2, 3, 4, 5,
                                              1, 2, 10, 4, 5,
                                              1, 2, 3, 4, 5,
                                              1, 2, 3, 4, 5
                                      }, 5, 5
    );
    matrix res2 = getMemMatrix(filter, filter);
    lab_20_task_03(&m2, &res2, filter);
    matrix test2 = createMatrixFromArray((int[]) {
                                                 1, 2, 3, 4, 5,
                                                 1, 2, 3, 4, 5,
                                                 1, 2, 3, 4, 5,
                                                 1, 2, 3, 4, 5,
                                                 1, 2, 3, 4, 5
                                         }, 5, 5
    );
    assert(areTwoMatricesEqual(&res2, &test2));
    freeMemMatrix(&res2);

    filter = 3;
    matrix m3 = createMatrixFromArray((int[]) {
                                              1, 1, 1, 1, 1,
                                              1, 10, 1, 1, 1,
                                              1, 1, 1, 1, 1,
                                              1, 1, 1, 10, 1,
                                              1, 1, 1, 1, 1
                                      }, 5, 5
    );
    matrix res3 = getMemMatrix(5, 5);
    lab_20_task_03(&m3, &res3, filter);
    matrix test3 = createMatrixFromArray((int[]) {
                                                1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1,
                                                 1, 1, 1, 1, 1
                                         }, 5, 5
    );
    assert(areTwoMatricesEqual(&res3, &test3));
}

void test_lab_20_04() {
    char *domains[] = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    void_vector v = void_vector_create(0, sizeof(Domain));
    lab_20_task_04(domains, 4, &v);

    Domain tests[] = {
            "mail.com", 901,
            "com", 951,
            "yahoo.com", 50,
            "intel.mail.com", 1,
            "org", 5,
            "wiki.org", 5,
            "google.mail.com", 900
    };
    for (int i = 0; i < v.size; i++) {
        Domain info;
        void_vector_getValueByPos( &v, i, &info );

        int is_in = 0;
        for (int j = 0; j < 7; j++) {
            if (strcmp(info.name, tests[j].name) == 0 && info.count == tests[j].count) {
                is_in = 1;
            }
        }
        if (!is_in) {
            printf("error!!!");
        }
    }
}

void test_lab_20_05() {
    matrix m1 = createMatrixFromArray((int[]) {
        1,0,1,
        1,1,0,
        1,1,0
    }, 3, 3);
    int res;
    lab_20_task_05(&m1, &res);
    assert(res == 13);
}

void test_lab_20_06() {
    char pattern1[] = "IIIDIDDD";
    char res1[100];
    lab_20_task_06(pattern1, res1);
    assert(strcmp(res1, "123549876") == 0);

    char pattern2[] = "DDD";
    char res2[100];
    lab_20_task_06(pattern2, res2);
    assert(strcmp(res2, "4321") == 0);
}

void test_lab_20_07() {
    char *result1 = (char*)malloc(sizeof(char) * (20 + 1));
    lab_20_task_07((int[]){3,2,1,6,0,5}, 6, result1);
    assert(strcmp(result1, "6 3 5 null 2 0 null null 1") == 0);

    char *result2 = (char*)malloc(sizeof(char) * (20 + 1));
    lab_20_task_07((int[]){3,2,1}, 3, result2);
    assert(strcmp(result2, "3 null 2 null 1") == 0);
}

void test_lab_20_08() {
    char *result1 = (char*)malloc(sizeof(char) * (20 + 1));
    lab_20_task_08("abc", (int[]){0,1,2}, result1);
    assert(strcmp(result1, "abc") == 0);

    char *result2 = (char*)malloc(sizeof(char) * (20 + 1));
    lab_20_task_08("abap", (int[]){0,3,2,1}, result2);
    assert(strcmp(result2, "apab") == 0);
}

void test_lab_20_09() {
    int argc = 4;
    char *argv[] = {"back","data_for_tasks/lab_20_task09_input.txt", "data_for_tasks/lab_20_task09_input.txt", "10"};

    void_vector res = void_vector_create(0, sizeof(int));
    lab_20_task_09(argc, argv, &res);
}