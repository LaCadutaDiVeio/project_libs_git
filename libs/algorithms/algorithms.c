#include <algorithms/algorithms.h>
#include <memory.h>
#include <malloc.h>

void error_alert(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

size_t binarySearch(const int *array, const size_t size, const int x) {
    if (!size)
        return 0u;

    size_t low = 0u;
    size_t high = size - 1u;
    while (low <= high && low <= size && high <= size) {
        size_t middle = low + (high - low) / 2;
        if (array[middle] < x)
            low = middle + 1u;
        else if (array[middle] > x)
            high = middle - 1u;
        else
            return middle;
    }
    return size;
}

size_t binarySearchNear(const int *array, const size_t size, const int x) {
    if (array[0] >= x)
        return 0u;

    size_t low = 0u;
    size_t high = size;
    while (low + 1 < high) {
        size_t middle = low + (high - low) / 2u;
        if (array[middle] < x)
            low = middle;
        else
            high = middle;
    }
    return high;
}

void swap(void *a, void *b) {
    void *tmp = a;
    a = b;
    b = tmp;
}

void swapByMem(void *a, void *b, const size_t type_size) {
    char *src = malloc(type_size);

    memcpy(src, a, type_size);
    memcpy(a, b, type_size);
    memcpy(b, src, type_size);

    free(src);
}

void swapInt(int *a, int *b) {
    swapByMem(a, b, sizeof(int));
}


void ascan(int *array, const size_t size) {
    for (size_t i = 0u; i < size; ++i)
        scanf("%d", &array[i]);
}

void aprint(const int *array, const size_t size) {
    for (size_t i = 0u; i < size; ++i)
        printf("%d ", array[i]);

    printf("%d\n");
}

int getElementIndexInArrayIf_(int *const array, const size_t size, int( *comp )(int, int)) {
    int el = array[0];
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (comp(array[i], el)) {
            el = array[i];
            index = i;
        }
    }
    return index;
}

int compareMax(int a, int req) {
    return a > req;
}

int getMaxElementIndexInArray(int *const array, const size_t size) {
    return getElementIndexInArrayIf_(array, size, compareMax);
}

int compareMin(int a, int req) {
    return a < req;
}

int getMinElementIndexInArray(int *const array, const size_t size) {
    return getElementIndexInArrayIf_(array, size, compareMin);
}
