#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <cassert>
#include "testhelper.h"
template <class T>
class MaxHeap
{
public:
    MaxHeap(int capacity){
        // 第一个节点空着，不使用 父节点 i  左节点 2*i  右节点 2*i+1
        data = new T[capacity+1];
        count = 0;
        this->capacity= capacity;
    }
    MaxHeap(T arr[], int n){
        data = new T[n+1];
        capacity = n;
        for(int i=0; i<n; i++){
            data[i+1] = arr[i];
        }
        count = n;
        // 创建堆, 从最后一个非叶子结点算起 i = count/2
        for (int i= count/2; i >= 1; i--){
            siftDown(i);
        }
    }

    ~MaxHeap(){delete [] data;}

    bool isEmpty(){ return count==0;}
    int size(){return  count;}
    void insert(T val){
        assert(count < capacity);
        data[count+1] = val;
        count++;
        siftUp(count);
    }

    void siftUp(int k){
        while (k>1 && data[k] > data[k/2]) {
            swap(data[k], data[k/2]);
            k = k/2;
        }
    }
    // 堆的深度
    int getDepth()
    {
        int k= count;
        int depth = 0;
        while (k>0) {
            k = k/2;
            depth ++;
        }
        return depth;
    }



    void printTree()
    {
        printArray(data, count+1);
    }

    T pop()
    {
        assert(count>0);
        T value = data[1];
        if (count == 1){
            count = 0;
        }else{
          swap(data[1], data[count]); // 最后和根节点交换， 第一个节点为空
          count --;
          siftDown(1);
        }
        return value;
    }

    void siftDown(int k)
    {
        // 根据索引，先给左节点索引，如果右节点存在，就与右节点比较大小，
        // 如果大于，则索引增加1，如果当前节点，大于最大的节点，则交换
        T v = data[k];
        while (2*k <= count) {

            int i = 2*k;
            if (i+1< count && data[i] < data[i+1]){
                i++;
            }
            if(v > data[i]){
                break;
            }
            swap(data[k], data[i]); //可以优化为向上赋值
            //data[k] = data[i];
            k = i;
        }
    }
private:
    T *data;
    int count;
    int capacity;
};

/**
 *小顶堆，根节点的值小于子节点的值
 */
template<typename T>
class MinHeap{

private:
    int count;
    T* data;
    int capacity;

public:
    MinHeap(int capacity): capacity(capacity){
        data = new T[capacity+1];
        count = 0;
    }

    ~MinHeap(){
        delete [] data;
    }
    void insert(T val){
        assert(count < capacity);
        data[count+1] = val;
        count ++;
        siftUp(count);
    }

    // 获得第一个元素，也就是最小值
    T pop(){
        assert(count>0);
        T value = data[1];
        if (count == 1){
            count = 0;
        }else{
          swap(data[1], data[count]); // 最后和根节点交换， 第一个节点为空
          count --;
          siftDown(1);
        }
        return value;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count==0;
    }

    void printTree()
    {
        printArray(data, count+1);
    }
private:
    // 向上移动
    void siftUp(int k){
        while (k>1 && data[k] < data[k/2]) {
            swap(data[k], data[k/2]);
            k = k/2;
        }
    }


    // 向下移动
    void siftDown(int k){

        while (2*k <= count) {

            int i = 2*k;
            if(i+1 <= count && data[i] > data[i+1]){
                i = i+1;
            }

            if(data[k] < data[i])
                break;

            swap(data[k], data[i]);

            k = i;
        }

    }

};

#endif // MAXHEAP_H
