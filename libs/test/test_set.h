#ifndef PROJECT_LIBS_TEST_SET_H
#define PROJECT_LIBS_TEST_SET_H

void create_bitsets_for_tests();
void test_bitset();
void test_bitset_in();
void test_bitset_isEqual();
void test_bitset_insert();
void test_bitset_delete();
void test_bitset_union();
void test_bitset_intersection();
void test_bitset_difference();
void test_bitset_sym_difference();
void test_bitset_compliment();
//---------------------------------
void create_unordered_sets_for_tests();
void test_unordered_array_set();
void test_unordered_array_set_create_from_array();
void test_unordered_array_set_in();
void test_unordered_array_set_isSubset();
void test_unordered_array_set_isEqual();
void test_unordered_array_set_insert();
void test_unordered_array_set_deleteElement();
void test_unordered_array_set_union();
void test_unordered_array_set_intersection();
void test_unordered_array_set_difference();
void test_unordered_array_set_sym_difference();
void test_unordered_array_set_complement();
//-------------------------------------
void create_ordered_sets_for_tests();
void test_ordered_array_set();
void test_ordered_array_set_create_from_array();
void test_ordered_array_set_in();
void test_ordered_array_set_isSubset();
void test_ordered_array_set_isEqual();
void test_ordered_array_set_insert();
void test_ordered_array_set_deleteElement();
void test_ordered_array_set_union();
void test_ordered_array_set_intersection();
void test_ordered_array_set_difference();
void test_ordered_array_set_sym_difference();
void test_ordered_array_set_complement();
//-----------------------------------
void create_vectors_for_tests();
void test_vectors();
void test_pushBack_emptyVector();
void test_pushBack_fullVector();
void test_popBack_notEmptyVector();
void test_vector_pointers();

void test_void_vector_from_lab_1();
void test_void_vector_from_lab_2();
void test_void_vector();

//-----------------
void testMatrix_1 ();
void testMatrix_2 ();

//-------------------
void test_string();
void test_len ();





#endif //PROJECT_LIBS_TEST_SET_H
