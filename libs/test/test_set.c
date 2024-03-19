#include <stdbool.h>

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
    m = createMatrixFromArray(
            (int[]) {
                3,5,2,4,3,3,
                2,5,1,8,2,7,
                6,1,4,4,8,3
            }, 3, 6
    );
    swapped = createMatrixFromArray(
            (int[]) {
                    5,2,3,3,3,4,
                    5,1,2,2,7,8,
                    1,4,6,8,3,4
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
                1,2,
                3,4
            }, 2, 2
    );
    matrix m_mul_m = createMatrixFromArray(
            (int[]) {
                    7,10,
                    15,22
            }, 2, 2
    );
    matrix mm = createMatrixFromArray(
            (int[]) {
                    1,2,
                    2,1
            }, 2, 2
    );
    matrix square_if_sym = createMatrixFromArray(
            (int[]) {
                    5,4,
                    4,5
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
                    2,4,
                    2,3
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2,2,
                    4,3
            }, 2, 2
    );
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);

    m = createMatrixFromArray(
            (int[]) {
                    2,4,
                    1,5
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2,4,
                    1,5
            }, 2, 2
    );
    transposeIfMatrixHasNotEqualSumOfRows(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__6__
    m = createMatrixFromArray(
            (int[]) {
                    3,-5,
                    1,-2
            }, 2, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    2,-5,
                    1,-3
            }, 2, 2
    );
    matrix mmm = createMatrixFromArray(
            (int[]) {
                    2,1,
                    1,-3
            }, 2, 2
    );
    assert(isMutuallyInverseMatrices(m, mm));
    assert(!isMutuallyInverseMatrices(m, mmm));
    freeMemMatrices_(3, &m, &mm, &mmm);
    //__7__
    m = createMatrixFromArray(
            (int[]) {
                    3,2,5,4,
                    1,3,6,3,
                    3,2,1,2
            }, 3, 4
    );
    assert(20 == findSumOfMaxesOfPseudoDiagonal(m));
    freeMemMatrices_(1, &m);
    //__8__
    m = createMatrixFromArray(
            (int[]) {
                10,7,5,6,
                3,11,8,9,
                4,1,12,2
            }, 3, 4
    );
    mm = createMatrixFromArray(
            (int[]) {
                6,8,9,2,
                7,12,3,4,
                10,11,5,1
            }, 3, 4
    );
    assert(getMinInArea(m) == 5);
    assert(getMinInArea(mm) == 6);
    freeMemMatrices_(2, &m, &mm);
    //__9__
    m = createMatrixFromArray(
            (int[]) {
                    5,11,
                    2,12,
                    11,3,
                    4,2
            }, 4, 2
    );
    mm = createMatrixFromArray(
            (int[]) {
                    4,2,
                    11,3,
                    5,11,
                    2,12
            }, 4, 2
    );
    sortByDistances(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__10__
    m = createMatrixFromArray(
            ( int[ ] ) {
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
            ( int[ ] ) {
                    3,5,5,4,
                    2,3,6,7,
                    12,2,1,1
            }, 3, 4
    );
    assert(getNSpecialElement(m) == 2);
    freeMemMatrices_(1, &m);
    //__12__
    m = createMatrixFromArray(
            ( int[ ] ) {
                    1,2,3,
                    4,5,6,
                    7,8,1
            }, 3, 3
    );
    mm = createMatrixFromArray(
            ( int[ ] ) {
                    1,2,3,
                    1,4,7,
                    7,8,1
            }, 3, 3
    );
    swapPenultimateRow(&m);
    assert(areTwoMatricesEqual(&m, &mm));
    freeMemMatrices_(2, &m, &mm);
    //__13__
    matrix *ms = createArrayOfMatrixFromArray(
            ( int[ ] ) {
                    7, 1,
                    1, 1,
                    1, 6,
                    2, 2,
                    5, 4,
                    2, 3,
                    1, 3,
                    7, 9
            },4,2, 2
    );
    assert(countNonDescendingRowsMatrices(ms, 4) == 2);
    freeMemMatrices(ms, 4);
    //__14__
    ms = createArrayOfMatrixFromArray(
            ( int[ ] ) {
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
            5,3, 2
    );
    //printMatrixWithMaxZeroRows(ms, 5);
    freeMemMatrices(ms, 5);
//    __15__
    ms = createArrayOfMatrixFromArray(
            ( int[ ] ) {
                    1, 4,
                    5, 7,
                    2, 4,
                    6, 9,
                    5, 5,
                    9, 1,
                    1, 1,
                    1, 1
            },
            4,2, 2
    );
    //printMatrixWithMinNorm(ms, 4);
    freeMemMatrices(ms, 4);
    //__16__
    m = createMatrixFromArray(
            ( int[ ] ) {
                    2,3,5,5,4,
                    6,2,3,8,12,
                    12,12,2,1,2
            }, 3, 5
    );
    assert(getNSpecialElement2(m) == 4);
    //__17__


}
