#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <random>
#include <time.h>
#include "maxheap.h"
using namespace std;
/**
 * 冒泡排序
 */
template<typename T>
void bubble_sort(T arr[], int length)
{
    for (int i=0; i< length-1; i++){

        for(int j=0; j< length-1-i; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }

    }
}


/**
 *选择排序
 */
template<typename T>
void select_sort(T arr[], int length){
    for (int i=0; i<length-1; i++){
        int minIndex = i;
        for(int j = i+1; j<length; j++){
            if(arr[minIndex] > arr[j]){
                minIndex = j;
            }
        }
        if(minIndex!=i){
            swap(arr[i], arr[minIndex]);
        }
    }
}

/**
 * 插入排序
 */
template <typename T>
void insert_sort(T arr[], int length){
    for(int i=0; i< length -1; i++){
        for (int j = i+1; j>0 && (arr[j-1] > arr[j]); j--){
            //if (arr[j-1] > arr[j]){
                swap(arr[j-1], arr[j]);
           // }
        }
    }
}

template <typename T>
void insert_sort2(T arr[], int length){
    for(int i=1; i< length; i++){
        for(int j=i; j>0 && arr[j] < arr[j-1]; j--){
            swap(arr[j-1], arr[j]);
        }
    }
}
template <typename T>
void insert_sort3(T arr[], int length){
    for(int i=1; i< length; i++){
        T val = arr[i]; // 当前元素的值
        int j;
        for(j=i; j>0 && val < arr[j-1]; j--){
            arr[j] = arr[j-1]; // 向后移动赋值
        }
        if(j!=i){
            arr[j] = val;
        }
    }
}



template <typename T>
void __merge_sort(T arr[], int l, int r){
    if (l >=r){
        return;
    }

    int mid = l + (r-l) /2;  //(r+l)/2;
    __merge_sort(arr, l, mid);
    __merge_sort(arr, mid+1, r);

    // [l, mid] [mid+1, r]
    T * aux = new T[r-l+1];
    for(int i=l; i<=r; i++){
        aux[i-l] = arr[i];
    }

    int i = l, j = mid+1;
    for(int k = l; k <= r; k++){
        if (i > mid){
            arr[k] = aux[j-l]; // 复制剩下的右半边
            j++;
        }else if (j > r){
            arr[k] = aux[i-l]; // 复制剩下的左半边
            i++;
        }else if(aux[i-l] < aux[j-l]){
            arr[k] = aux[i-l]; // 复制左半边
            i++;
        }
        else{
            arr[k] = aux[j-l]; // 复制右半边
            j++;
        }
    }

    delete[] aux;

}

/**
 *归并排序
 *  分为左右，然后排序，然后合并 开辟临时内存空间
 */
template <typename T>
void merge_sort(T arr[], int length){
    __merge_sort(arr, 0, length-1);
}

template <typename T>
int __partition(T arr[], int l, int r){
    // 从两端向内
    int index = rand()%(r-l+1)+l;
    swap(arr[l], arr[index]);
    T v = arr[l];
    int i = l + 1, j = r;

    while( true ){
        // 注意这里的边界, arr[i] < v, 不能是arr[i] <= v
        while( i <= r && arr[i] < v )
            i ++;

        // 注意这里的边界, arr[j] > v, 不能是arr[j] >= v
        while( j >= l+1 && arr[j] > v )
            j --;

        if( i > j )
            break;

        swap( arr[i] , arr[j] );
        // 注意这里的交换完，需要都向前移动一位
        i ++;
        j --;
    }

    swap(arr[l], arr[j]);
    return j;

}

template<typename T>
void __quick_sort(T arr[], int l, int r){
    if(l >= r)
    {
        return;
    }
    int index = __partition(arr, l, r);
    __quick_sort(arr, l, index-1);
    __quick_sort(arr, index+1, r);

}


/**
 *快速排序  需要选择基准的数据，默认第一个，也可以随机选择
 */
template<typename T>
void quick_sort(T arr[], int length){
    __quick_sort(arr, 0, length-1);
}

/**
 *希尔排序
 *
 */
template <typename T>
void shell_sort(T arr[], int length){
    int gap = 1;
    while (gap < length / 3) {
       gap = 3 * gap + 1;
    }
    cout << "gap = " << gap << endl;
    // 间隔Gap 进行插入排序
    while (gap>0) {
        for(int i = 0; i <length; i += gap){
            for(int j= i + gap; j > 0 && (arr[j] < arr[j-gap]); j -= gap){
                 swap(arr[j], arr[j-gap]);
            }
        }
        gap = gap/3;
    }
}

/**
 *堆排序  （掌握什么是堆， 大顶堆， 小顶堆）
 */
template<typename T>
void heap_sort1(T arr[], int length){
    // 构建堆
//    MaxHeap<T> heap(length);
//    for (int i = 0; i < length; i++){
//        heap.insert(arr[i]);
//    }
//    for( int i = length-1; i >= 0; i--){
//        arr[i] =  heap.pop();
//    }
    MinHeap<T> heap(length);
    for (int i=0; i<length; i++){
        heap.insert(arr[i]);
    }
    heap.printTree();
    for(int i=0; i<length; i++){
        arr[i] = heap.pop();
    }
}
template<typename T>
void heap_sort2(T arr[], int length){
    // 构建堆
    MaxHeap<T> heap(arr, length);
//    for( int i = length-1; i >= 0; i--){
//        arr[i] =  heap.pop();
//    }

}



template<typename T>
void __siftDown(T arr[], int length, int k){

    while ( 2*k+1 < length) {

        int i = 2*k + 1;
        if(i+1<length && arr[i] < arr[i+1]){
            i ++;
        }

        if(arr[k] >= arr[i])
            break;

        swap(arr[k], arr[i]);

        k = i;
    }
}

/**
 * 对元素组的堆排序
 */
template<typename T>
void heap_sort(T arr[], int length){
    for(int i = (length-1)/2; i >= 0; i--){
        __siftDown(arr, length, i);
    }

    for(int i = length-1; i >= 0; i--){
        swap(arr[0], arr[i]);
        __siftDown(arr, i, 0);
    }
}



#endif // SORTS_H
