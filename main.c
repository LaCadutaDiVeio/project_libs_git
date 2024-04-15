#include <array/array.h>
#include <bitset/bitset.h>
#include <unordered_set/unordered_set.h>
#include <ordered_set/ordered_set.h>
#include <vectors/vector.h>
#include <vectors_void/void_vector.h>
#include <matrix/matrix.h>
#include <string_/string_.h>
#include <test/test_set.h>


int main() {
    //test_bitset();
    //test_unordered_array_set();
    //test_ordered_array_set();
    //test_vectors();
    //test_void_vector();
    //testMatrix_1();
    //testMatrix_2();
    test_string();

    char s1[] = "string";
    WordDescriptor w1;
    getWord(s1, &w1);
    char s2[] = "string";
    WordDescriptor w2;
    getWord(s2, &w2);
    //printf("%d", areWordsEqual(w1, w2));

    return 0;
}