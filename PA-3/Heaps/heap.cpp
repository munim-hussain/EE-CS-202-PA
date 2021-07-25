#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <memory>

MinHeap::MinHeap(int cap)
{
	harr.reset(new int[cap], default_delete<int[]>());
	capacity = cap;
	heap_size = 0;
}

int MinHeap::parent(int i)
{
	return ((i - 1) / 2);
}

int MinHeap::left(int i)
{
	return ((2 * i) + 1);
}

int MinHeap::right(int i)
{
	return ((2 * i) + 2);
}

int MinHeap::extractMin()
{
	if (heap_size <= 0)
	{
		return INT_MAX;
	}

	if (heap_size == 1)
	{
		heap_size--;
		return harr.get()[0];
	}

	int r = harr.get()[0];
	harr.get()[0] = harr.get()[heap_size - 1];
	heap_size--;

	_helper(0);

	return r;
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr.get()[i] = new_val;
	_helper2(i);
}

int MinHeap::getMin()
{
	return harr.get()[0];
}

void MinHeap::deleteKey(int i)
{
	//cout << "delete" << endl;
	if (i >= heap_size)
	{
		return;
	}
	decreaseKey(i, INT_MIN);
	extractMin();
}

void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		return;
	}

	heap_size++;
	int i = heap_size - 1;
	harr.get()[i] = k;

	_helper2(i);
}

shared_ptr<int> MinHeap::getHeap()
{
	return harr;
}

void MinHeap::_helper(int i)
{
	int l = left(i);
	int r = right(i);
	int x = i;

	if (l < heap_size && harr.get()[l] < harr.get()[i])
	{
		x = l;
	}
	if (r < heap_size && harr.get()[r] < harr.get()[x])
	{
		x = r;
	}

	if (x != i)
	{
		int temp = harr.get()[i];
		harr.get()[i] = harr.get()[x];
		harr.get()[x] = temp;

		_helper(x);
	}
}

void MinHeap::_helper2(int i)
{
	if (i != 0 && harr.get()[parent(i)] > harr.get()[i])
	{
		int temp = harr.get()[i];
		harr.get()[i] = harr.get()[parent(i)];
		harr.get()[parent(i)] = temp;

		_helper2(parent(i));
	}
}

#endif