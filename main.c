#include <array/array.h>
#include <bitset/bitset.h>
#include <unordered_set/unordered_set.h>
#include <ordered_set/ordered_set.h>
#include <vectors/vector.h>
#include <vectors_void/void_vector.h>
#include <matrix/matrix.h>
#include <test/test_set.h>


int main() {
    //test_bitset();
    //test_unordered_array_set();
    //test_ordered_array_set();
    //test_vectors();
    //test_void_vector();

    matrix m = getMemMatrix(2, 3);
    inputMatrix(&m);
    transposeMatrix(&m);

    outputMatrix(m);

    freeMemMatrix(&m);
}