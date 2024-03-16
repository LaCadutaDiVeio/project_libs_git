//
// Created by Ilya on 18.02.2024.
//

#ifndef PROJECT_LIBS_ALGPRITHMS_H
#define PROJECT_LIBS_ALGPRITHMS_H
#include <stdio.h>
#include <assert.h>

void error_alert(char *msg);

size_t binarySearch( const int *array, const size_t size, const int x );

size_t binarySearchNear( const int *array, const size_t size, const int x );

void swap( void *a, void *b );

void ascan( int *array, const size_t size );

void aprint( const int *array, const size_t size );

void swapByMem( void *a, void *b, const size_t type_size );

void swapInt( int *a, int *b );

int getElementIndexInArrayIf_(int *const array, const size_t size, int( *comp )(int, int));

int compareMax(int a, int req);

int getMaxElementIndexInArray(int *const array, const size_t size);

int compareMin(int a, int req);

int getMinElementIndexInArray(int *const array, const size_t size);

#endif //PROJECT_LIBS_ALGPRITHMS_H
