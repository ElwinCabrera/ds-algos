#ifndef TREES_SUFFIX_TREE_H
#define TREES_SUFFIX_TREE_H

#include "nodes.h"
//#include <string>
using std::string;


class SuffixTree{  //A.K.A Trie
public:
    SuffixTree(){
        root = new TrieNode();
    }
    ~SuffixTree(){

    }
    void insert(string word){
        TrieNode *tNode = root;
        for(char c: word){
            if(tNode->children.find(c) == tNode->children.end()){
                TrieNode *newNode = new TrieNode();
                tNode->children.insert({c, newNode});
            }
            tNode = tNode->children.find(c)->second;
        }
        tNode->isWord = true;
    }

    bool search(string word){
        TrieNode *tNode = root;
        for(char c: word){
            if(tNode->children.find(c) == tNode->children.end()){
                return false;
            }
            tNode = tNode->children.find(c)->second;
        }
        return tNode->isWord;
    }

    void remove(string word){

    }

private:
    TrieNode *root;

};

#endif // TREES_SUFFIX_TREE_H