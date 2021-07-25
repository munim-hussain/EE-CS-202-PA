#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    shared_ptr<ListItem<T>> temp = otherLinkedList.head;
    while(temp!=NULL)
     {
        insertAtTail(temp->value);
        temp = temp->next;
     }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    if(head==NULL)
    {
        head = make_shared<ListItem<T>> (item);
        tail = head;
    }
    else
    {
        shared_ptr<ListItem<T>> temp = head;
        head = make_shared<ListItem<T>> (item);
        temp->prev = head;
        head->prev = NULL;
        head->next = temp;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    if(tail==NULL)
    {
        tail = make_shared<ListItem<T>> (item);
        head = tail;
    }
    else
    {
        shared_ptr<ListItem<T>> temp = tail;
        tail = make_shared<ListItem<T>> (item);
        temp->next = tail;
        tail->prev = temp;
        tail->next = NULL;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    shared_ptr<ListItem<T>> temp = searchFor(afterWhat);
    if(temp==NULL)
    {
        return;
    }
    else if(temp==tail)
    {
        insertAtTail(toInsert);
    }
    else
    {
        shared_ptr<ListItem<T>> temp2 = make_shared<ListItem<T>> (toInsert);
        temp2->prev = temp;
        temp2->next = temp->next;
        temp->next->prev = temp2;
        temp->next = temp2;
    }
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
    return head;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
    shared_ptr<ListItem<T>> temp = head;
    while(temp!=NULL)
    {
        if(temp->value==item)
        {
            break;
        }
        else
        {
        temp = temp->next;
        }
    }
    return temp;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    shared_ptr<ListItem<T>> temp = searchFor(item);
    if(temp==NULL)
    {
        return;
    }
    else if(temp==head)
    {
        deleteHead();
    }
    else if(temp==tail)
    {
        deleteTail();
    }
    else
    {
    shared_ptr<ListItem<T>> temp2 = temp->prev;
    temp2->next = temp->next;
    temp->next->prev = temp2;
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head!=NULL)
    {
        if(head->next==NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }
    }
    else 
    {
        return;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    if(tail!=NULL)
    {
        if(tail->prev == NULL)
        {
            tail = NULL;
            head = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;
        }
    }
    else
    {
        return;
    }
}

template <class T>
int LinkedList<T>::length()
{
    int count = 0;
    shared_ptr<ListItem<T>> temp = head;
     while(temp!=NULL)
     {
        count++;
        temp = temp->next;
     }
     return count;
}

#endif
