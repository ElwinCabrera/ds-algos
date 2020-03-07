#ifndef TREES_AVL_TREE_H
#define TREES_AVL_TREE_H

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
class AVLTree{  //height balanced tree
public:
    AVLTree();
    ~AVLTree();
    bool find(Type value);
    void insert(Type value);
    void remove(Type value);
private:
    BinaryNode<Type> *root;
};
#endif //TREES_AVL_TREE_H