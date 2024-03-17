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

    //matrix m = getMemMatrix(3, 3);
    //inputMatrix(&m);

    //printf("%lld", findSumOfMaxesOfPseudoDiagonal_forSquaresONLY(m));
    //getSquareOfMatrixIfSymmetric(&m);


    //outputMatrix(m);
    //printf("%d %d", getMinValuePos(m).rowIndex, getMinValuePos(m).colIndex);

    //freeMemMatrix(&m);
    return 0;
}