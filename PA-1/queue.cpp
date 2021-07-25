#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
    //redundant 
}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
    shared_ptr<ListItem<T>> temp = otherQueue.list.getHead();
    while(temp!=NULL)
     {
        list.insertAtTail(temp->value);
        temp = temp->next;
     }
}

template <class T>
Queue<T>::~Queue()
{
    while(!isEmpty())
    {
        list.deleteTail();
    }
}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
    T temp = list.getHead()->value;
    return temp;
}

template <class T>
T Queue<T>::dequeue()
{
    T temp = front();
    list.deleteHead();
    return temp;
}

template <class T>
int Queue<T>::length()
{
    return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
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
