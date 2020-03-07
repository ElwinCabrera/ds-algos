#ifndef TREES_MAX_HEAP_TREE_H
#define TREES_MAX_HEAP_TREE_H

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
class MaxHeap{
public:
    MaxHeap();
    ~MinHeap();
    bool find(Type value);
    void insert(Type value);
    void remove(Type value);
private:
    BinaryNode<Type> *root;
};
#endif //TREES_MAX_HEAP_TREE_H