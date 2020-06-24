#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include "singlelink.h"


template <class T>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue(){}

    // 入队
    void push(T val);

    // 出队
    void pop();

    bool isEmpty(){ return count == 0;}

    int size()const {return count;}

    void printLink();
private:
    int count;
    Node<T> *phead;
    Node<T> *pend;

};

template <typename T>
LinkQueue<T>::LinkQueue(){
    count = 0;
    phead = new Node<T>(0, nullptr);
    pend = phead;
}

template <typename T>
void LinkQueue<T>::push(T val){
    // 在尾部插入
    Node<T> *node = new Node<T>(val, nullptr);
    pend->next = node;
    pend=node; // 尾指针
    count ++;
}

template <typename T>
void LinkQueue<T>::pop(){
    if(phead->next!=nullptr){
        Node<T>* node = phead->next;
        phead->next = phead->next->next;
        count --;
    }
}

template <typename T>
void LinkQueue<T>::printLink(){
    using namespace std;
    Node<T> *node = phead;
    while (node->next!=nullptr) {
        node = node->next;
        T value = node->value;
        cout<< value << " ";
    }
    cout << endl;
}


#endif // LINKQUEUE_H
