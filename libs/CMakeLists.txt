include_directories(${CMAKE_CURRENT_LIST_DIR})

file (GLOB_RECURSE src_files_array ${CMAKE_CURRENT_LIST_DIR}/array/*.[ch])
file (GLOB_RECURSE src_files_bitset ${CMAKE_CURRENT_LIST_DIR}/bitset/*.[ch])
file (GLOB_RECURSE src_files_unordered_set ${CMAKE_CURRENT_LIST_DIR}/unordered_set/*.[ch])
file (GLOB_RECURSE src_files_ordered_set ${CMAKE_CURRENT_LIST_DIR}/ordered_set/*.[ch])
file (GLOB_RECURSE src_files_algorithms ${CMAKE_CURRENT_LIST_DIR}/algorithms/*.[ch])
file (GLOB_RECURSE src_files_test_set ${CMAKE_CURRENT_LIST_DIR}/test/*.[ch])
file (GLOB_RECURSE src_files_vectors ${CMAKE_CURRENT_LIST_DIR}/vectors/*.[ch])
file (GLOB_RECURSE src_files_vectors_void ${CMAKE_CURRENT_LIST_DIR}/vectors_void/*.[ch])
file (GLOB_RECURSE src_files_matrix ${CMAKE_CURRENT_LIST_DIR}/matrix/*.[ch])
file (GLOB_RECURSE src_files_string ${CMAKE_CURRENT_LIST_DIR}/string_/*.[ch])
file (GLOB_RECURSE src_files_files ${CMAKE_CURRENT_LIST_DIR}/files/*.[ch])
file (GLOB_RECURSE src_files_lab_20 ${CMAKE_CURRENT_LIST_DIR}/lab_20/*.[ch])




#message(STATUS "$src_files_unordered_set")

set (src_libs
        ${src_files_array}
        ${src_files_bitset}
        ${src_files_unordered_set}
        ${src_files_ordered_set}
        ${src_files_algorithms}
        ${src_files_vectors}
        ${src_files_vectors_void}
        ${src_files_matrix}
        ${src_files_string}
        ${src_files_test_set}
        ${src_files_files}
        ${src_files_lab_20}
)