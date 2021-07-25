#ifndef __TRIE_CPP
#define __TRIE_CPP

#include "trie.hpp"

trie::trie()
{
    root = shared_ptr<Node>(new Node);
    root->value = ' ';
}

void trie::insertWord(string word)
{
    int count = word.length();
    shared_ptr<Node> temp = root;
    while (count > 0)
    {
        if (findChar(temp->children, word[word.length() - count]) == -1)
        {
            shared_ptr<Node> temp2 = make_shared<Node>();
            temp2->value = word[word.length() - count];
            temp->children.push_back(temp2);
            temp->children = _helper(temp->children);
        }
        temp = temp->children[findChar(temp->children, word[word.length() - count])];
        count--;
    }
}

bool trie::search(string word)
{
    shared_ptr<Node> temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        int check2 = findChar(temp->children, word[i]);
        if (check2 != -1)
        {
            temp = temp->children[check2];
        }
        else
        {
            return false;
        }
    }

    return true;
}

string trie::longestSubstr(string word)
{
    string subStr = "";
    vector<string> v;
    shared_ptr<Node> temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        int check2 = findChar(temp->children, word[i]);
        if (check2 != -1)
        {
            temp = temp->children[check2];
            string s(1, temp->value);
            v.push_back(s);
        }
        else
        {
            break;
        }
    }
    if (v.size() > 0)
    {
        subStr = v2s(v);
    }
    return subStr;
}

vector<string> trie::getTrie()
{
    string temp = "";
    vector<string> t;
    _helper2(root, t, temp);
    return t;
}

void trie::deleteWord(string word)
{
    shared_ptr<Node> temp = root;
    shared_ptr<Node> temp2;
    int count = word.length();
    while (count > 0)
    {
        char c = word[word.length() - count];
        if (findChar(temp->children, c) != -1)
        {
            int check = findChar(temp->children, c);
            temp2 = temp->children[check];
            if (temp2->children.size() > 0)
            {
                temp = temp2;
            }
            else if (temp2->children.size() == 0)
            {
                temp->children.erase(temp->children.begin() + check);
                string toSend = word.substr(0, word.length() - 1);
                deleteWord(toSend);
            }
        }
        count--;
    }
}

int trie::findChar(vector<shared_ptr<Node>> n, char c)
{
    for (int i = 0; i < n.size(); i++)
    {
        if (c == n[i]->value)
        {
            return i;
        }
    }
    return -1;
}

vector<shared_ptr<Node>> trie::_helper(vector<shared_ptr<Node>> x)
{
    shared_ptr<Node> temp[x.size()];
    for (int i = 0; i < x.size(); i++)
    {
        temp[i] = x[i];
    }
    for (int i = 0; i < x.size(); i++)
    {
        shared_ptr<Node> temp2 = temp[i];
        int j = i - 1;

        while (temp2->value < temp[j]->value && j >= 0)
        {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = temp2;
    }
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = temp[i];
    }
    return x;
}

void trie::_helper2(shared_ptr<Node> r, vector<string> &v, string s)
{
    string temp = s;
    if (r->children.size() == 0)
    {
        v.push_back(temp);
        return;
    }
    else
    {
        int count = r->children.size();
        while (count > 0)
        {
            _helper2(r->children[r->children.size() - count], v, temp + r->children[r->children.size() - count]->value);
            count--;
        }
    }
}

string trie::v2s(vector<string> v)
{
    if (v.size() != 0)
    {
        string s = v[0];
        for (int i = 1; i < v.size(); i++)
        {
            s += v[i];
        }
        return s;
    }
    else
    {
        string s = "";
        return s;
    }
}

#endif