#ifndef SEARCH_H
#define SEARCH_H

/**
  *
  * 查找有关算法
  *
  **/
/**
 * @brief binary_search 二分查找迭代实现
 * @param arr 队列, 是一个有序数组
 * @param n 队列长度
 * @param val 目标值
 * @return
 */
template<typename T>
int binary_search(T arr [], int n, T val){
    int l = 0;
    int r = n -1;
    // [l, r]
    while (l <= r ) {
        int mid = l + (r-l) / 2; // 中间索引
        if (arr[mid] == val)
            return mid;
        else if(val < arr[mid]){// 左半边
            r = mid -1;
        }else{
            // 右半边
            l = mid + 1;
        }

    }
    return  -1; // 没有找到
}

/**
 * @brief binary_search_recurve 二分查找的递归实现
 * @param arr
 * @param n
 * @param val
 * @return
 */
template<typename T>
int binary_search_recurve(T arr [], int n, T val){
    return  __binary_search(arr, 0, n-1, val);
}
template<typename T>
int __binary_search(T arr[], int l, int r, T val){

    if ( l > r){
        return -1; // 遍历越界，没有找到返回-1
    }

    int mid = l + (r-l)/2;
    if (val == arr[mid]){
        return mid;
    }else if(val < arr[mid])
        return __binary_search(arr, l, mid-1, val);
    else
        return __binary_search(arr, mid+1, r, val);

}





#endif // SEARCH_H
