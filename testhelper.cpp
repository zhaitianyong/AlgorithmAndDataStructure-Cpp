#include "testhelper.h"

int *generateRandomArray(int n, int l, int h){
    // 设置种子数
    srand((unsigned)time(NULL));
    int * arr = new int[n];
    for(int i=0; i<n; i++){
       arr[i] = rand() % (h-l+1) + l;
    }
    return arr;
}

int* copyArray(int arr[], int n){
    int* res = new int[n];
    copy(arr, arr+n, res);
    return res;
}
