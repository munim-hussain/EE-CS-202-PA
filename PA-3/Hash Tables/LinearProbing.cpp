#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "LinearProbing.h"
#include "HashFunction.cpp"
#include <memory>

// Constructor
HashL::HashL(int size)
{
    for (int i = 0; i < size; i++)
    {
        hashTable.push_back(NULL);
    }
    tableSize = size;
    count = 0;
}

// Destructor
HashL::~HashL()
{
    // hashTable.clear();
    // tableSize = 0;
    // count = 0;
}

// Computes the key corresponding to the value.
unsigned long HashL::hash(string value)
{
    return divCompression(bitHash(value), tableSize);
}

// Function to resize the hash table
void HashL::resizeTable()
{
    vector<string> temp;
    for (int i = 0; i < tableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            temp.push_back(hashTable[i]->value);
        }
    }

    hashTable.clear();
    tableSize *= 2;
    for (int i = 0; i < tableSize; i++)
    {
        hashTable.push_back(NULL);
    }

    for (int i = 0; i < temp.size(); i++)
    {
        _helper(temp[i]);
    }
}

// Takes the hash of 'value' and insert it into the hash table
void HashL::insertWord(string value)
{
    if (count > ((tableSize * 7) / 10))
    {
        resizeTable();
    }

    unsigned long index = hash(value);
    shared_ptr<tableItem> temp(new tableItem(index, value));
    while (hashTable[index] != NULL)
    {
        index++;
        if (index == tableSize)
        {
            index -= tableSize;
        }
    }
    hashTable[index] = temp;
    count++;
}

// Deletes 'value' from the hash table.
void HashL::deleteWord(string value)
{
    unsigned long index = hash(value);

    if (hashTable[index] == NULL)
    {
        return;
    }

    while (hashTable[index] != NULL)
    {
        if (hashTable[index]->value == value)
        {
            hashTable[index]->value = "i am gay";
            count--;
            return;
        }
        index++;
        if (index == tableSize)
        {
            index -= tableSize;
        }
    }

    return;
}

// Locates value in the hash table and returns a pointer to it
shared_ptr<tableItem> HashL::lookupWord(string value)
{
    unsigned long index = hash(value);
    if (hashTable[index] == NULL)
    {
        return NULL;
    }

    while (hashTable[index] != NULL)
    {
        if (hashTable[index]->value == value)
        {
            return hashTable[index];
        }
        index++;
        if (index == tableSize)
        {
            index -= tableSize;
        }
    }
    
    return NULL;
}

void HashL::_helper(string x)
{
    unsigned long index = hash(x);
    shared_ptr<tableItem> temp(new tableItem(index, x));
    while (hashTable[index] != NULL)
    {
        index++;
        if (index == tableSize)
        {
            index -= tableSize;
        }
    }
    hashTable[index] = temp;
}

#endif
