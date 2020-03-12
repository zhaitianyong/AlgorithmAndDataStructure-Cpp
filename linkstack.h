#ifndef LINKSTACK_H
#define LINKSTACK_H
#include "singlelink.h"


template <class T>
class LinkStack
{
public:
    LinkStack();
    ~LinkStack(){};

    // 出栈
    void pop();
    // 入栈
    void push(T val);

    bool isEmpaty(){return count == 0;}

    int size() const{return  count;};


    void printLink();

private:
    int count;
    Node<T> *phead;
};


template <typename T>
LinkStack<T>::LinkStack(){
    count = 0;
    phead = new Node<T>();
    phead->next=nullptr;
}

template <typename T>
void LinkStack<T>::push(T val){
    Node<T> *node = new Node<T>(val, nullptr);
    node->next = phead->next;
    phead->next = node;
    count ++;
}

template <typename T>
void  LinkStack<T>::pop()
{
    if (phead->next!=nullptr)
    {
        phead->next = phead->next->next;
        count --;
    }
}


template <typename T>
void LinkStack<T>::printLink(){
    using namespace std;
    Node<T> *node = phead;
    while (node->next!=nullptr) {
        node = node->next;
        T value = node->value;
        cout<< value << " ";
    }
    cout << endl;
}


#endif // LINKSTACK_H
