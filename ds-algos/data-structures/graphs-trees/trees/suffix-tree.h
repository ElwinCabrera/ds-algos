#ifndef TREES_SUFFIX_TREE_H
#define TREES_SUFFIX_TREE_H

#include "nodes.h"   //TrieNode definition
//#include <string>
using std::string;


class SuffixTree{  //A.K.A Trie
public:
    SuffixTree(){
        root = new TrieNode();
    }

    ~SuffixTree(){

    }

    void insert(const string &word){
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


    bool search(const string &word){
        TrieNode *tNode = root;
        for(char c: word){
            if(tNode->children.find(c) == tNode->children.end()){
                return false;
            }
            tNode = tNode->children.find(c)->second;
        }
        return tNode->isWord;
    }

    

    bool startsWith(const string &prefix){
        TrieNode *tNode = root;
        for(char c: prefix){
            auto it = tNode->children.find(c);
            if(it == tNode->children.end()){
                return false;
            }
            tNode = it->second;
        }
        return true;
    }

    void insertRecursive(const string &word){
        insertRecursiveHelper(this->root, word, 0);
    }

    bool searchRecursive(const string &word){
        return searchRecursiveHelper(this->root, word, 0);
    }

    bool startsWithRecursive(const string &prefix){
        return startsWithRecursiveHelper(this->root, prefix, 0);
    }

    void remove(const string word){
        removeRecursive(this->root, word, 0);
    }

private:
    TrieNode *root;

    void insertRecursiveHelper(TrieNode *node, const string &word, int wordIdx){
        if(wordIdx >= word.size()) {
            node->isWord = true;
            return;
        }
        TrieNode *tn = nullptr;
        auto it = node->children.find(word.at(wordIdx));

        
        
        if(it == node->children.end()){
            TrieNode *n = new TrieNode();
            node->children.insert({word.at(wordIdx), n});
            tn = n;
        } else tn = it->second; 
         insertRecursiveHelper(tn, word, wordIdx+1);
    }

    bool searchRecursiveHelper(TrieNode *node, const string &word, int wordIdx){
        if(wordIdx >= word.size()) {
            return node->isWord;
        }
        auto it = node->children.find(word.at(wordIdx));

        if(it == node->children.end()){
            return false;
        }  
        return searchRecursiveHelper(it->second, word, wordIdx+1);
    }

    bool startsWithRecursiveHelper(TrieNode *node, const string &prefix, int prefixIdx){
        if(prefixIdx >= prefix.size()) {
            return true;
        }
        auto it = node->children.find(prefix.at(prefixIdx));

        if(it == node->children.end()){
            return false;
        }  
        return startsWithRecursiveHelper(it->second, prefix, prefixIdx+1);
    }

    bool removeRecursive(TrieNode *node, const string &word, int wordIdx){
        if(wordIdx >= word.size()){
            if(!node->isWord){
                return false;
            } 
            node->isWord = false;
            return node->children.empty();

        }

        TrieNode *n = nullptr;
        auto it = node->children.find(word.at(wordIdx));

        if(it != node->children.end()) n = it->second;
        else return false;

        bool canDelete = removeRecursive(n, word, wordIdx+1);

        if(canDelete){
            delete n;
            n = nullptr;
            node->children.erase(it);
        }

        return node->children.empty();
    }

};

#endif // TREES_SUFFIX_TREE_H