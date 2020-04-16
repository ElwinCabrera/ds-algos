#ifndef NODES_H
#define NODES_H


#include <unordered_map>
using std::unordered_map;

enum Color {RED, BLACK, DOUBLEBLACK};

template<typename Type>
class BinaryNode{
public:
    BinaryNode(): left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
    BinaryNode(Type t): data(t), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
    Type data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;
    Color color;

};

class TrieNode{
public:
    unordered_map<char, TrieNode*> children;
    bool isWord;

    TrieNode(): isWord(false) {

    }
};

#endif //NODES_H