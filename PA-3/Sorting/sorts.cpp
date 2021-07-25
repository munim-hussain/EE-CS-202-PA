#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "LinkedList.cpp"

//===========================Helper Function Definition================================

shared_ptr<LinkedList<long>> _helper(shared_ptr<LinkedList<long>> &t);
void _helper2(shared_ptr<LinkedList<long>> &t, shared_ptr<LinkedList<long>> &l, shared_ptr<LinkedList<long>> &r);
shared_ptr<LinkedList<long>> _helper3(shared_ptr<LinkedList<long>> &l, shared_ptr<LinkedList<long>> &r);

//=====================================================================================

vector<long> InsertionSort(vector<long> nums)
{
    long temp[nums.size()];
    for (int i = 0; i < nums.size(); i++)
    {
        temp[i] = nums[i];
    }
    for (int i = 0; i < nums.size(); i++)
    {
        long temp2 = temp[i];
        int j = i - 1;

        while (temp2 < temp[j] && j >= 0)
        {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = temp2;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        nums[i] = temp[i];
    }
    return nums;
}

//=====================================================================================

vector<long> MergeSort(vector<long> nums)
{
    shared_ptr<LinkedList<long>> temp = make_shared<LinkedList<long>>();
    for (int i = 0; i < nums.size(); i++)
    {
        temp->insertAtTail(nums[i]);
    }

    temp = _helper(temp);

    for (int i = 0; i < nums.size(); i++)
    {
        nums[i] = temp->getHead()->value;
        temp->deleteHead();
    }
    return nums;
}

//=====================================================================================

shared_ptr<LinkedList<long>> _helper(shared_ptr<LinkedList<long>> &t) // mergeSort
{
    shared_ptr<LinkedList<long>> l = make_shared<LinkedList<long>>();
    shared_ptr<LinkedList<long>> r = make_shared<LinkedList<long>>();

    if (t->length() <= 1)
    {
        return t;
    }

    _helper2(t, l, r);

    l = _helper(l);
    r = _helper(r);

    return _helper3(l, r);
}

void _helper2(shared_ptr<LinkedList<long>> &t, shared_ptr<LinkedList<long>> &l, shared_ptr<LinkedList<long>> &r) //divide
{
    int count = 0;
    while (t->getHead() != NULL)
    {
        if (count % 2 == 0)
        {
            l->insertAtTail(t->getHead()->value);
        }
        else
        {
            r->insertAtTail(t->getHead()->value);
        }
        t->deleteHead();
        count++;
    }
}

shared_ptr<LinkedList<long>> _helper3(shared_ptr<LinkedList<long>> &l, shared_ptr<LinkedList<long>> &r) // conquer
{
    if (l->getHead() == NULL)
    {
        return r;
    }
    else if (r->getHead() == NULL)
    {
        return l;
    };

    shared_ptr<LinkedList<long>> s = make_shared<LinkedList<long>>();
    long temp;
    if (l->getHead()->value <= r->getHead()->value)
    {
        temp = l->getHead()->value;
        l->deleteHead();
        s = _helper3(l, r);
        s->insertAtHead(temp);
    }
    else
    {
        temp = r->getHead()->value;
        r->deleteHead();
        s = _helper3(l, r);
        s->insertAtHead(temp);
    }
    return s;
}

//==============================Helper Functions=======================================

#endif