#ifndef TREES_NARY_TREE_H
#define TREES_NARY_TREE_H

#include <vector>
#include<iostream>
#include <iomanip> 
using std::vector;

template<typename Type>
class NarryNode{
public:
    NarryNode() {}
    NarryNode(Type t): data(t)  {}
    Type data;
    vector<NarryNode*> children;
};


template<typename Type>
class NaryTree{ // or Forest tree

};
#endif //TREES_NARY_TREE_H