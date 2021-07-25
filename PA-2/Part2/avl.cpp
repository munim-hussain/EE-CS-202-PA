#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include <memory>
#include "avl.hpp"

// Constructor
template <class T, class S>
AVL<T, S>::AVL(bool isAVL)
{
    this->root = NULL;
    this->isAVL = isAVL;
}

// This function inserts a given node in the tree
template <class T, class S>
void AVL<T, S>::insertNode(shared_ptr<node<T, S>> newNode)
{
    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        shared_ptr<node<T, S>> temp = root;

        while (temp != NULL)
        {
            if (temp->key == newNode->key)
            {
                return;
            }
            else if (temp->key > newNode->key && temp->left == NULL)
            {
                temp->left = newNode;
                return;
            }
            else if (temp->key < newNode->key && temp->right == NULL)
            {
                temp->right = newNode;
                return;
            }
            else if (temp->key > newNode->key)
            {
                temp = temp->left;
            }
            else if (temp->key < newNode->key)
            {
                temp = temp->right;
            }
        }
    }
}

// This function searches a node in a tree by its key
template <class T, class S>
shared_ptr<node<T, S>> AVL<T, S>::searchNode(T k)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        shared_ptr<node<T, S>> temp = root;

        while (temp != NULL)
        {
            if (temp->key == k)
            {
                return temp;
            }
            else if (temp->key > k)
            {
                temp = temp->left;
            }
            else if (temp->key < k)
            {
                temp = temp->right;
            }
        }
        return NULL;
    }
}

// This function deletes a given node from the tree
template <class T, class S>
void AVL<T, S>::deleteNode(T k)
{
    // shared_ptr<node<T, S>> temp = searchNode(k);
    // shared_ptr<node<T, S>> temp2 = getP(root, k);

    // if (temp == NULL)
    // {
    //     return;
    // }
    // else
    // {

    //     if (temp->left == NULL && temp->right == NULL)
    //     {
    //         if(temp2->left == temp)
    //         {
    //             temp2->left = NULL;
    //         }
    //         else if (temp2->right == temp)
    //         {
    //             temp->right = NULL;
    //         }
    //         return;
    //     }
    //     else if (temp->left != NULL && temp->right == NULL)
    //     {
    //         if (temp != root)
    //         {
    //             temp2->left = temp->left;
    //             return;
    //         }
    //         else
    //         {
    //             root = temp->left;
    //             return;
    //         }
    //     }
    //     else if (temp->left == NULL && temp->right != NULL)
    //     {
    //         if (temp != root)
    //         {
    //             temp2->right = temp->right;
    //             return;
    //         }
    //         else
    //         {
    //             root = temp->right;
    //             return;
    //         }
    //     }
    //     else if (temp->left != NULL && temp->right != NULL)
    //     {
    //         shared_ptr<node<T, S>> temp3 = getMin(temp);
    //         temp->key = temp3->key;
    //         temp->value = temp3->value;
    //         deleteNode(temp3->key);
    //         return;
    //     }
    // }

    deleteHelper(root,k);
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T, S>> AVL<T, S>::getRoot()
{
    return root;
}

// This function calculates and returns the height of the tree
template <class T, class S>
int AVL<T, S>::height(shared_ptr<node<T, S>> p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int l = height(p->left);
        int r = height(p->right);
        if (l > r)
        {
            return (l + 1);
        }
        else
        {
            return (r + 1);
        }
    }
}

template <class T, class S>
shared_ptr<node<T, S>> AVL<T, S>::getP(shared_ptr<node<T, S>> p, T k)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (p->left == NULL && p->right == NULL)
    {
        return NULL;
    }

    if ((p->left != NULL && p->left->key == k) || (p->right != NULL && p->right->key == k))
    {
        return p;
    }

    if (k < p->key)
    {
        return getP(p->left, k);
    }
    if (k > p->key)
    {
        return getP(p->right, k);
    }
}

template <class T, class S>
shared_ptr<node<T, S>> AVL<T, S>::getMin(shared_ptr<node<T, S>> p)
{
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p;
}

template <class T, class S>
shared_ptr<node<T, S>> AVL<T, S>::deleteHelper(shared_ptr<node<T, S>> p, T k)
{
    if (p == NULL)
    {
        return p;
    }
    else if (p->key > k)
    {
        p->left = deleteHelper(p->left, k);
    }
    else if (p->key < k)
    {
        p->right = deleteHelper(p->right, k);
    }
    else
    {
        shared_ptr<node<T, S>> temp;

        if (p->left == NULL)
        {
            temp = p->right;
            p = NULL;
            return temp;
        }
        else if (p->right == NULL)
        {
            temp = p->left;
            p = NULL;
            return temp;
        }
        else
        {
            temp = getMin(p->right);
            p->key = temp->key;
            p->value = temp->value;
            p->right = deleteHelper(p->right, temp->key);
        }
    }
    return p;
}

#endif