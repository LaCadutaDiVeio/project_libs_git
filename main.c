#include <array/array.h>
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

#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    //test_bitset();
    //test_unordered_array_set();
    //test_ordered_array_set();
    //test_vectors();
    //test_void_vector();
    //testMatrix_1();
    //testMatrix_2();
    //test_string();
    //test_files();
    test_lab20();

    /*matrix m3 = createMatrixFromArray((int[]) {
                                              1,2,3,1,1,
                                              4,10,5,1,1,
                                              6,7,8,7,6,
                                              1,1,5,10,4,
                                              1,1,1,2,3
                                      }, 5, 5
    );
    void_vector v = void_vector_create(0, sizeof(int));
    getPointsFromNeighbours(&m3, 3, 3, &v, 3);
    printf("%d ", m3.values[3][3]);
    outputArray_(v.data, v.size);*/


    /*trie_node *root = getNode();
    insertWordInTrie(root, "abcd");
    insertWordInTrie(root, "abde");
    printf("%d", root->children[0]->children[1]->children[2]->children[3]->count);*/

    //lab_20_task_07((int[]){3,2,1,6,0,5}, 6);

    return 0;
}