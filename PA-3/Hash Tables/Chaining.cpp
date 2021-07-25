#ifndef CHAINING_CPP
#define CHAINING_CPP

#include "Chaining.h"
#include "HashFunction.cpp"

// Constructor
HashC::HashC(int size)
{
    hashTable.reset(new LinkedList<string>[size], default_delete<LinkedList<string>[]>());
    tableSize = size;
}

// Destructor
HashC::~HashC()
{
    // hashTable.reset(new LinkedList<string>[0], default_delete<LinkedList<string>[]>());
    // tableSize = 0;
}

// Given a String, return its hash
unsigned long HashC::hash(string input)
{
    return divCompression(bitHash(input), tableSize);
}

// Takes a hash of 'word' and inserts it into hashTable accordingly
void HashC::insertWord(string word)
{
    hashTable.get()[hash(word)].insertAtTail(word);
}

// Locates 'word' in the hash table and returns a pointer to it
shared_ptr<ListItem<string>> HashC::lookupWord(string word)
{
    for (int i = 0; i < tableSize; i++)
    {
        return hashTable.get()[i].searchFor(word);
    }
    return NULL;
}

// Deletes 'word' from the hash table
void HashC::deleteWord(string word)
{
    if (lookupWord(word) != NULL)
    {
        hashTable.get()[hash(word)].deleteElement(word);
    }
}

#endif