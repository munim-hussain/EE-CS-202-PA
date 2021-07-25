#ifndef __EXP_TREE_CPP
#define __EXP_TREE_CPP

#include "exp_tree.hpp"

// class constructor that calls buildTree()
ExpTree::ExpTree(string postfix_exp, bool optimal)
{
    buildTree(postfix_exp, optimal);
}
// returns the constructed expression tree from the given postfix expression
// when the optimal argument is set, the subtrees not containing any variables are computed and their result is stored in the tree as only one node
void ExpTree::buildTree(string postfix_exp, bool optimal)
{
    stack<shared_ptr<node>> stackTree;
    if (postfix_exp.length() == 0)
    {
        root = NULL;
    }

    else
    {

        for (int i = 0; i < postfix_exp.length(); i++)
        {
            char n = postfix_exp[i];
            if ((n > 47 && n < 58) || (n > 96 && n < 123))
            {
                shared_ptr<node> operandNode = make_shared<node>(n);
                stackTree.push(operandNode);
            }

            else if (n == 43 || n == 45 || n == 42 || n == 47)
            {
                shared_ptr<node> tree1 = stackTree.top();
                stackTree.pop();
                shared_ptr<node> tree2 = stackTree.top();
                stackTree.pop();
                if (optimal == true)
                {
                    int ans = 0;

                    if ((tree1->op > 47 && tree1->op < 58) && (tree2->op > 47 && tree2->op < 58))
                    {
                        if (postfix_exp[i] == '+')
                        {
                            cout << (tree1->op - 48) + 2 << endl;
                            ans = (tree1->op - 48) + (tree2->op - 48);
                        }

                        else if (postfix_exp[i] == '-')
                        {
                            ans = (tree2->op - 48) - (tree1->op - 48);
                        }

                        else if (postfix_exp[i] == '*')
                        {
                            ans = (tree1->op - 48) * (tree2->op - 48);
                        }

                        else if (postfix_exp[i] == '/')
                        {
                            ans = (tree2->op - 48) / (tree1->op - 48);
                        }
                        char charans = ans + 48;
                        shared_ptr<node> ret = make_shared<node>(charans);
                        stackTree.push(ret);
                    }

                    else
                    {
                        shared_ptr<node> finalTree = make_shared<node>(postfix_exp[i]);
                        finalTree->right = tree1;
                        finalTree->left = tree2;
                        stackTree.push(finalTree);
                    }
                }

                else
                {
                    shared_ptr<node> finalTree = make_shared<node>(postfix_exp[i]);
                    finalTree->right = tree1;
                    finalTree->left = tree2;
                    stackTree.push(finalTree);
                }
            }
        }

        root = stackTree.top();
    }
}

// returns the root node of the tree;
shared_ptr<node> ExpTree::getRoot()
{
    return root;
}

// returns the value of the expression given the value of the variables in the vector
double ExpTree::calculate(vector<Variable> variables)
{
    return calculateRecurse(root, variables);
}

// recursive function called by calculate():
double ExpTree::calculateRecurse(shared_ptr<node> currNode, vector<Variable> variables)
{
    if (root == NULL)
    {
        return -99;
    }

    else
    {
        if (currNode == NULL)
        {
            return 0.0;
        }

        else
        {
            if (currNode->left == NULL && currNode->right == NULL)
            {

                if (currNode->op > 96 && currNode->op < 123)
                {

                    return variables[currNode->op - 'a'].value;
                }

                else if (currNode->op > 47 && currNode->op < 58)
                {

                    double dr = 0.0;
                    dr = currNode->op - 48;

                    return dr;
                }
            }

            double left = calculateRecurse(currNode->left, variables);
            double right = calculateRecurse(currNode->right, variables);
            double ans = 0.0;

            if (currNode->op == '+')
            {
                ans = left + right;
                return ans;
            }

            else if (currNode->op == '-')
            {
                ans = left - right;
                return ans;
            }

            else if (currNode->op == '*')
            {
                ans = left * right;
                return ans;
            }

            else if (currNode->op == '/')
            {
                ans = left / right;
                return ans;
            }
        }
    }
}

// returns the infix expression with brackets added
string ExpTree::getInfix()
{
    return getInfixRecurse(root);
}

// recursive function called by getInfix():
string ExpTree::getInfixRecurse(shared_ptr<node> currNode)
{
    return "";
}

#endif