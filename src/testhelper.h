#ifndef TESTHELPER_H
#define TESTHELPER_H
#include <iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <string>


using namespace std;

template<typename T>
void printArray(T arr[], int length)
{
    for(int i=0; i<length;i++){
         std::cout << arr[i] << " ";
    }
    std::cout<< std::endl;

}

template <typename T>
bool isSorted(T arr[], int length)
{
    for(int i=0; i<length-1; i++)
    {
        if(arr[i]>arr[i+1])
        {
            return false;
        }
    }
    return true;
}

template<typename T>
void testSort(string name, void (*fn)(T[], int), T arr[], int n)
{
    clock_t start = clock();
    fn(arr, n);
    clock_t end = clock();
    bool ok = isSorted(arr, n);
    if (!ok){
        cout <<name <<  ":exception" << endl;
    }
    cout << name << ":" << double(end - start)/ CLOCKS_PER_SEC << "s" << endl;
}

int *generateRandomArray(int n, int l, int h);

int* copyArray(int arr[], int n);
#endif // TESTHELPER_H
