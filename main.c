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

    //lab_20_task_11();


    /*trie_node *root = getNode();
    insertWordInTrie(root, "abcd");
    insertWordInTrie(root, "abde");
    printf("%d", root->children[0]->children[1]->children[2]->children[3]->count);*/



    return 0;
}