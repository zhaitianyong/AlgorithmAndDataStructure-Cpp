//
// Created by atway on 2020/6/24.
//
#include "sorts.h"
#include "testhelper.h"
/**
 * @brief main0 测试排序
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    int n = 10000;
    int* arr1 = generateRandomArray(n, 0, 10000);
    int* arr2 = copyArray(arr1, n);
    int* arr3 = copyArray(arr1, n);
    int* arr4 = copyArray(arr1, n);
    //testSort("bubble sort", bubble_sort, arr1, n);
    //print_sort(arr, n);
    //printArray(arr1, n);
    testSort("inser sort2", insert_sort2, arr1, n);
    testSort("inser sort3", insert_sort3, arr2, n);

    //printArray(arr2, n);
    //testSort("shell sort", shell_sort, arr1, n);
    //testSort("quick sort", quick_sort, arr1, n);
    //testSort("heap sort1", heap_sort1, arr2, n);
    //testSort("heap sort2", heap_sort2, arr3, n);
    //testSort("heap sort", heap_sort, arr4, n);
    //printArray(arr1, n);
    //printArray(arr4, n);
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    return 0;
}

