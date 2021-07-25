#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
    //redundant 
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
    shared_ptr<ListItem<T>> temp = otherStack.list.getHead();
    while(temp!=NULL)
     {
        list.insertAtTail(temp->value);
        temp = temp->next;
     }
}

template <class T>
Stack<T>::~Stack()
{
    while(!isEmpty())
    {
        list.deleteTail();
    }
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Stack<T>::top()
{
    T temp = list.getTail()->value;
    return temp;
}

template <class T>
T Stack<T>::pop()
{
    T temp = top();
    list.deleteTail();
    return temp;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if(length()==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif
