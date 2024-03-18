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
    testMatrix_1();
    testMatrix_2();

    /*matrix m = createMatrixFromArray(
            ( int[ ] ) {
                    3,5,5,4,
                    2,3,6,7,
                    12,2,1,1
            }, 3, 4
    );
    printf("%d", getNSpecialElement(m));*/

    //freeMemMatrix(&m);
    return 0;
}