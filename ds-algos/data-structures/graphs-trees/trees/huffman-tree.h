#ifndef TREES_HUFFMAN_TREE_H
#define TREES_HUFFMAN_TREE_H

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
class HuffmanTree{
public:
    HuffmanTree();
    ~HuffmanTree();
    bool find(Type value);
    void insert(Type value);
    void remove(Type value);
private:
    BinaryNode<Type> *root;
};
#endif //TREES_HUFFMAN_TREE_H