#pragma once

#include "pch.h"
#include <iostream>
using namespace std;

template <typename T>
class AVLTreeNode {
public:
    T data;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode()
    {
        data = 0;
        height = 0;
        left = right = nullptr;
    }
    AVLTreeNode(T d)
    {
        data = d;
        left = right = nullptr;
        height = 1;
    }
};

template <typename T>
class AVLTree 
{
public:
    AVLTreeNode<T>* root;
    AVLTree()
    {
        root = nullptr;
    }
    AVLTreeNode<T>* getRoot()
    {
        return root;
    }
    void insert(T value)
    {
        root = insertNode(root, value);
    }
    int getHeight(AVLTreeNode<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }
    int BalanceFactor(AVLTreeNode<T>* node)
    {
        if (node == nullptr)
            return 0;
        
        return getHeight(node->left) - getHeight(node->right);
    }
    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, T val)
    {
        if (node == nullptr)
        {
            return new AVLTreeNode<T>(val);
        }
        if (node->data>val)
        {
            node->left = insertNode(node->left, val);
        }
        else if (node->data<val)
        {
            node->right = insertNode(node->right, val);
        }
        else 
            return node;

        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        int balance_factor = BalanceFactor(node);
        //left heavy bhot heavyyy

        if (balance_factor > 1 && val < node->left->data)
        {
            return rotateRight(node);
        }
        else if (balance_factor > 1 && val > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        //balance is in neg
        if (balance_factor < -1 && node->right->data<val)
        {
            return rotateLeft(node);
        }
        else if (balance_factor <-1 && node->right->data>val)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* y)
    {
        AVLTreeNode<T>* x = y->left;
        AVLTreeNode<T>* T = x->right;
        x->right = y;
        y->left = T;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* x)
    {
        AVLTreeNode<T>* y = x->right;
        AVLTreeNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }
    void display()
    {
        cout << "In-order traversal: ";
        inordertranversal(root);
        cout << '\n';
    }
    void inordertranversal(AVLTreeNode<T>* root)
    {
        if (root == nullptr)
            return;
        else if (root != nullptr)
        {
            inordertranversal(root->left);
            cout << root->data << " ";
            inordertranversal(root->right);
        }
    }
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, T key)
    {
       //bst insert
        if (node == nullptr)
        {
            return node;
        }
        if (key > node->data)
        {
            node->right = deleteNode(node->right, key);
        }
        else if (key < node->data)
        {
            node->left = deleteNode(node->left, key);
        }
        else 
        {
            if (node->right == NULL || node->left == NULL)
            {
                AVLTreeNode<T>* n_node = nullptr;
                if (node->right != nullptr)
                {
                    n_node = node->right;
                }
                else if (node->left != nullptr)
                {
                    n_node = node->left;
                }
                if (n_node == nullptr)//no bacha
                {
                    n_node = node;
                    node = nullptr;
                }
                else if(n_node!=nullptr)
                { 
                    node->data = n_node->data;
                    node->left = n_node->left;
                    node->right = n_node->right;
                    node->height = n_node->height;
                }
                delete n_node;
            }
            else
            {
                AVLTreeNode<T>* successor = node->right; //find successor
                while (successor->left != nullptr)
                {
                    successor = successor->left;
                }
                node->data = successor->data;
                node->right = deleteNode(node->right, successor->data);
            }
        }
        if (node == nullptr)
            return node;
        
        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        int balance_factor = BalanceFactor(node);
        //left heavy bhot heavyyy
        if (balance_factor > 1 && key < node->left->data)
        {
            return rotateRight(node);
        }
        else if (balance_factor > 1 && key > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        //balance is in neg
        if (balance_factor < -1 && node->right->data < key)
        {
            return rotateLeft(node);
        }
        else if (balance_factor <-1 && node->right->data>key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    void remove(T val)
    {
        root = deleteNode(root, val);
    }
    AVLTreeNode<T>* findSmallest()
    {
        AVLTreeNode<T>* node=nullptr;
        if (root == nullptr)
            return nullptr;
        else
        {
            node = root;
            while (node->left != nullptr)
            {
                node = node->left;
            }
        }
        return node;
    }
    AVLTreeNode<T>* findLargest()
    {
        AVLTreeNode<T>* node = nullptr;
        if (root == nullptr)
            return nullptr;
        else
        {
            node = root;
            while (node->right != nullptr)
            {
                node = node->right;
            }
        }
        return node;
    }

    //q2
    int getDiameter()
    {
        int diameter = 0;
        if (root->right != nullptr && root->left != nullptr)
        {
            
            diameter = calculateheight(root) + 1;
            return diameter;
        }
        else if (root->left == nullptr && root->right == NULL)
            return 0;
    }
    int calculateheight(AVLTreeNode<T>* r)
    {
        int h = 0;
        if (r == nullptr)
            return 0;
        int right = calculateheight(r->right);
        int left = calculateheight(r->left);
        h = max(left,right) + 1;
        return  h;
    }
    
};