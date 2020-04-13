#ifndef TREES_BINARY_TREE_H
#define TREES_BINARY_TREE_H

#include "nodes.h"
#include <vector>
#include<iostream>
#include <iomanip> 
using std::vector;



template<typename Type>
class BinaryTree {

public:
    
    BinaryTree(vector<int> preorder, vector<int> inorder){
        this->root = buildTree(preorder, inorder, 0, inorder.size()-1, 0);
    }

    BinaryTree(const BinaryTree &other){

    }
    BinaryTree(const BinaryTree &&other){

    }

    ~BinaryTree(){
        deleteTree();
    }

    BinaryTree& operator=(const BinaryTree &other){
        BinaryTree<Type> tmp(other);
        tmp.swap(*this);
        return *this;
    }

    BinaryTree& operator=(const BinaryTree &&other) {}

    void swap(BinaryTree &other) noexcept{
        using std::swap;
        swap(this->root, other.root);
    }
    
    BinaryNode<Type> *buildTree(vector<int> &preorder, vector<int> &inorder, int leftBound , int rightBound, int nextRootIdx){
        if(preorder.empty() || inorder.empty()) return nullptr;
        if(leftBound > rightBound || leftBound < 0 || rightBound > inorder.size()) return nullptr;

        Type val = preorder.at(nextRootIdx);
        BinaryNode<Type> *node = new BinaryNode<Type>(val);

        int rootIdxInInorderList = -1;
        for(int i = 0; i < inorder.size(); ++i) if(inorder.at(i) == val) {rootIdxInInorderList = i; break; }

        node->left = buildTree(preorder, inorder, leftBound, rootIdxInInorderList-1, nextRootIdx+1);
        node->right = buildTree(preorder, inorder, rootIdxInInorderList +1, rightBound, nextRootIdx +2);
        return node;
    }

    bool contains(Type data) { 
        return containsRecursive(data, this->root);
    }
    
    BinaryNode<Type>* find(Type data) { 
        return findRecursive(data, this->root);
    } 
    
    void remove(Type data) { 
        removeRecursive(data, this->root);
    }

    void deleteTree() { 
       deleteTreeRecursive(this->root);
    }

    void prettyPrintTree(){
        prettyPrintTreeRecursive(this->root);
    }

    /*friend std::ostream& operator<<(std::ostream &os, const BinaryTree<Type> *node = root, int indent = 0) {
    
        os.put('[');
        char arrow[3] = {'\0', ' ','\0'};
        for (auto it = l.begin(); it != l.end(); ++it) {
            os << arrow << it->data;
            arrow[0] = '<';
            arrow[1] = '-';
            arrow[2] = '>';
        }
        return os << ']';
    }
    friend std::istream& operator>>(std::istream &is, const List<Type> &l) {}*/

private:
    BinaryNode<Type> *root;

    bool containsRecursive(Type data, BinaryNode<Type>* node) { 
        if(!node) return false;
        if(node->data == data) return true;
        return containsRecursive(data, node->left) || containsRecursive(data, node->right);
    }

    BinaryNode<Type>* findRecursive(Type data, BinaryNode<Type>* node) { 
        if(!node) return nullptr;
        findRecursive(data, node->left);
        if(node->data == data) return node;
        findRecursive(data, node->right); 
    }

    void removeRecursive(Type data, BinaryNode<Type>* node) { 
        if(!node) return;

        removeRecursive(data, node->left);
        removeRecursive(data, node->right);
        if(node->data == data) {
            BinaryNode<Type> *trash = nullptr;
            if(node->left == nullptr && node->right == nullptr) trash = node;
            if(node->left != nullptr && node->right == nullptr){
                trash = node;
                node = trash->left;
            } else if(node->left == nullptr && node->right != nullptr){
                trash = node;
                node = trash->right;
            } else if(node->left != nullptr && node->right != nullptr){
                BinaryNode<Type> *n = getLeftMostLeafNode(node);
                node->data =  n->data;
                removeRecursive(n->data, n);
            }
            if(trash) delete trash;
        }
        

    }

    void deleteTreeRecursive(BinaryNode<Type>* node) { 
        if(!node) return;
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        node = nullptr; 
    }

    void prettyPrintTreeRecursive(BinaryNode<Type> *node, int indent = 0){
        if(node == nullptr) return;
        
        if(node->left) prettyPrintTreeRecursive(node->left, indent+4);
        if(node->right) prettyPrintTreeRecursive(node->right, indent+4);
        if(indent) std::cout << std::setw(indent) << ' ';
        
        std::cout<< node->data << "\n ";
    } 
    
    BinaryNode<Type> *getLeftMostLeafNode(BinaryNode<Type> *node){
        if(node == nullptr || node->left == nullptr) return node;
        return getLeftMostLeafNode(node->left);
    }
};

#endif // TREES_BINARY_TREE_H