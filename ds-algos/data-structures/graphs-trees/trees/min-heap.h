#ifndef TREES_MIN_HEAP_TREE_H
#define TREES_MIN_HEAP_TREE_H

template<typename Type>
class BinaryNode{
public:
    BinaryNode() {}
    BinaryNode(Type t): data(t), left(nullptr), right(nullptr) {}
    Type data;
    BinaryNode *left;
    BinaryNode *right;
};

template<typename Type>
class MinHeap{
public:
    MinHeap();
    ~MinHeap();
    bool find(Type value);
    void insert(Type value);
    void remove(Type value);
private:
    BinaryNode<Type> *root;
};
#endif //TREES_MIN_HEAP_TREE_H