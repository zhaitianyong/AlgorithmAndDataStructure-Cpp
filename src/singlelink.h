#ifndef SINGLELINK_H
#define SINGLELINK_H
#include <cassert>
#include <iostream>
template<typename T>
struct Node{

public:
    Node(T value, Node<T> *next):
    value(value), next(next){}
    Node(T value): value(value){}
    Node(){}

public:
    T value;
    Node<T>* next;
};

// 声明单链表 模板类
template <typename T>
class SingleLink
{
public:
    SingleLink();
    ~SingleLink(){};

    // 表头插入
    void insert_head(T val);

    // 尾部插入
    void insert_end(T val);

    // 在某个位置插入
    void insert(int i, T val);

    // 移除
    void remove(int i);

    // 是否为空
    bool isEmpty() {return count == 0;}

    // 链表长度
    int size() const{return count;}

    //
    T getValue(int i);

    void printLink();

private:
    int count;
    Node<T> *phead; // 头指针

    Node<T>* getNode(int i); // 根据索引获得链表节点

};


// 定义单链表


template <typename T>
SingleLink<T>::SingleLink()
{
    count = 0;
    phead = new Node<T>(0, nullptr);
}

template<typename T>
void SingleLink<T>::insert_head(T val){
   Node<T> *newNode = new Node<T>(val, nullptr);
      newNode->next = phead->next;
      phead->next = newNode;
      count ++;
}

template<typename T>
void SingleLink<T>::insert_end(T val){
    Node<T> *newNode = new Node<T>(val, nullptr);
    Node<T> *node = getNode(count);
    if (node != nullptr){
       newNode->next = node->next;
       node->next = newNode;
       count ++;
    }
}
template<typename T>
void SingleLink<T>::insert(int i, T val){
    Node<T> *newNode = new Node<T>(val, nullptr);
    Node<T> *node = getNode(i);
    if (node != nullptr){
       newNode->next = node->next;
       node->next = newNode;
       count ++;
    }
}

template<typename T>
void SingleLink<T>::remove(int i){
    Node<T> *node = getNode(i);
    if (node != nullptr && node->next!=nullptr){
        node->next = node->next->next;
        count --;
    }
}


// 头指针不算个数，索引都是从0开始，范围上一个节点
template<typename T>
Node<T>* SingleLink<T>::getNode(int i){
    if(i > count){
        return nullptr;
    }
    int index =0;
    Node<T> *node = phead;
    while (index < i) {
        node = node->next;
        index++;
    }
    return node;
}

template<typename T>
T SingleLink<T>::getValue(int i){
    Node<T> *node = getNode(i);
    if (node!=nullptr && node->next!=nullptr){
        return node->next->value;
    }
}

template<typename T>
void SingleLink<T>::printLink(){
    using namespace std;
    Node<T> *node = phead;
    while (node->next!=nullptr) {
        node = node->next;
        T value = node->value;
        cout<< value << " ";
    }
    cout << endl;
}



#endif // SINGLELINK_H
