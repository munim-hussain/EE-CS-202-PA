#ifndef __TREE_CPP
#define __TREE_CPP

#include "tree.hpp"

// Constructor
template <class T, class S>
Tree<T, S>::Tree(shared_ptr<node<T, S>> root)
{
    this->root = root;
}

// This function finds a key in the tree and returns the respective node
template <class T, class S>
shared_ptr<node<T, S>> Tree<T, S>::findKey(T key)
{
    return findKeyHelper(root, key);
}

// Helper function to find a key in the tree
template <class T, class S>
shared_ptr<node<T, S>> Tree<T, S>::findKeyHelper(shared_ptr<node<T, S>> currNode, T key)
{
    if (currNode == NULL)
    {
        return currNode;
    }

    if (currNode->key == key)
    {
        return currNode;
    }

    shared_ptr<node<T, S>> temp = findKeyHelper(currNode->child, key);
    if (temp != NULL)
    {
        return temp;
    }

    shared_ptr<node<T, S>> temp2 = findKeyHelper(currNode->sibling, key);
    if (temp2 != NULL)
    {
        return temp2;
    }

    return NULL;
}

// This function inserts a the given node as a child of the given key
template <class T, class S>
bool Tree<T, S>::insertChild(shared_ptr<node<T, S>> c, T key)
{
    shared_ptr<node<T, S>> temp = findKey(key);

    if (temp == NULL)
    {
        return false;
    }

    if (findKey(c->key) != NULL)
    {
        return false;
    }

    if (temp->child == NULL)
    {
        temp->child = c;
        return true;
    }
    else
    {
        temp = temp->child;
        while (temp->sibling != NULL)
        {
            temp = temp->sibling;
        }
        temp->sibling = c;
        return true;
    }
}

// This function returns all the children of a node with the given key
template <class T, class S>
vector<shared_ptr<node<T, S>>> Tree<T, S>::getAllChildren(T key)
{
    vector<shared_ptr<node<T, S>>> children;
    shared_ptr<node<T, S>> temp = findKey(key);

    if (temp == NULL)
    {
        return children;
    }

    if (temp->child == NULL)
    {
        return children;
    }
    else
    {
        temp = temp->child;
        children.push_back(temp);
        if (temp->sibling != NULL)
        {
            while (temp->sibling != NULL)
            {
                children.push_back(temp->sibling);
                temp = temp->sibling;
            }
        }
    }

    return children;
}

// This function returns the height of the tree
template <class T, class S>
int Tree<T, S>::findHeight()
{
    return findHeightHelper(root);
}

// Helper function to find height of the tree
template <class T, class S>
int Tree<T, S>::findHeightHelper(shared_ptr<node<T, S>> currNode)
{
    int h = -1;
    while (currNode != NULL)
    {
        h++;
        currNode = currNode->child;
    }
    return h;
}

// This function deletes the node of a given key (iff it is a leaf node)
template <class T, class S>
bool Tree<T, S>::deleteLeaf(T key)
{
    if (deleteLeafHelperHelper(key))
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Helper function to delete lead node
template <class T, class S>
shared_ptr<node<T, S>> Tree<T, S>::deleteLeafHelper(shared_ptr<node<T, S>> currNode, T key)
{
    // if (currNode == NULL)
    // {
    //     return currNode;
    // }

    // vector<shared_ptr<node<T, S>>> helper = getAllChildren(currNode->key);
    // for (int i = 0; i < helper.size(); i++)
    // {
    //     if (key == helper[i]->key)
    //     {
    //         return currNode;
    //     }
    // }

    // if (currNode->key == key)
    // {
    //     return currNode;
    // }

    // shared_ptr<node<T, S>> temp = findKeyHelper(currNode->child, key);
    // if (temp != NULL)
    // {
    //     return temp;
    // }

    // shared_ptr<node<T, S>> temp2 = findKeyHelper(currNode->sibling, key);
    // if (temp2 != NULL)
    // {
    //     return temp2;
    // }

    // if (currNode == NULL)
    // {
    //     return currNode;
    // }

    // shared_ptr<node<T, S>> leaf = findKey(key);

    // if (currNode->child == findKey(key))
    // {
    //     if (leaf->sibling == NULL)
    //     {
    //         currNode->child == NULL;
    //     }
    //     else
    //     {
    //         currNode->child = currNode->child->sibling;
    //     }
    // }

    // if (currNode->sibling == findKey(key))
    // {
    //     currNode->sibling = currNode->sibling->sibling;
    // }

    // shared_ptr<node<T, S>> temp = findKeyHelper(currNode->child, key);
    // if (temp != NULL)
    // {
    //     return temp;
    // }

    // shared_ptr<node<T, S>> temp2 = findKeyHelper(currNode->sibling, key);
    // if (temp2 != NULL)
    // {
    //     return temp2;
    // }

    // return NULL;

    return getP(currNode, key);
}

// This function deletes the tree
template <class T, class S>
void Tree<T, S>::deleteTree(shared_ptr<node<T, S>> currNode)
{
    this->root = NULL;
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T, S>> Tree<T, S>::getRoot()
{
    return root;
}

template <class T, class S>
shared_ptr<node<T, S>> Tree<T, S>::getP(shared_ptr<node<T, S>> currNode, T key)
{
    shared_ptr<node<T, S>> temp = currNode;
    while (temp != NULL)
    {
        if (temp->child->key == key)
        {
            return temp;
        }

        temp = temp->child;
    }

    temp = getP(currNode->sibling, key);
    return temp;
}

template <class T, class S>
bool Tree<T, S>::deleteLeafHelperHelper(T key)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->key == key)
    {
        return false;
    }

    shared_ptr<node<T, S>> temp = findKey(key);

    if (temp->child)
    {
        return false;
    }

    if (temp->sibling == NULL && temp->child == NULL)
    {
        shared_ptr<node<T, S>> temp2 = deleteLeafHelper(root, key);
        temp2->child = NULL;
        return true;
    }

    if (temp->sibling != NULL && temp->child == NULL)
    {
        shared_ptr<node<T, S>> temp2 = deleteLeafHelper(root, key);
        temp2->child = temp->sibling;
        return true;
    }

    return false;
}

#endif