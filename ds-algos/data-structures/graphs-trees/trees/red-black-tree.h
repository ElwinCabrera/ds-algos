#ifndef TREES_RED_BLACK_TREE_H
#define TREES_RED_BLACK_TREE_H

#include <vector>
#include <iostream>
using std::vector;
using std::cout;

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

template<typename Type>
class RedBlackTree{
public:
    RedBlackTree(){
        root = nullptr;
    }

    //copy constructor
    //do a deep copy of the other binary tree
    RedBlackTree(const RedBlackTree &other){
        this->root = deepCopyTree(other.getRoot());
    }

    //move constructor 
    //used when passing the address as argument to function 
    //in that case we dont want a full copy just the address
    RedBlackTree(const RedBlackTree &&other){
        this->root = other->root;
        other->root = nullptr;
    }
    ~RedBlackTree(){
        deleteTree();
    }

    //use copy-swap to get strong exception guarantee
    // to do this we need a fully working copy constructor and our own swap function 
    // 1. make a temp copy of the other object 
    // 2. swap the temporary object with the current object 
    RedBlackTree& operator=(const RedBlackTree &other){
        RedBlackTree tempBtree(other);
        tempBtree.swap(*this);
        return *this;
    }
    
    bool contains(Type value) { 
        return containsRecursive(value, this->root); 
    }
    
    BinaryNode<Type>* find(Type value) { 
        return findRecursive(value, this->root); 
    }

    BinaryNode<Type>* findMinValue() { 
        return getMinNode(this->root); 
    } 
    void insert(Type value) { 
        BinaryNode<Type> *newNode =  new BinaryNode<Type>(value);
        insertRecursive(this->root, newNode); 
        this->root = insertFix(newNode);
    }
    void remove(Type value) { 
        BinaryNode<Type> *trash = findRecursive(value, this->root);
        deleteNode(trash);
    }
    
    void deleteTree() {
        deleteTreeRecursive(this->root);
    }


    void swap(RedBlackTree &other) throw(){
        using std::swap;
        swap(this->root, other.root);
    }

    const BinaryNode<Type>* getRoot() const{
        return this->root;
    }

    vector<vector<Type>> getLevelsAsList() const{
        vector<vector<Type>> result;
        if(this->root == nullptr) return result;
        
        std::vector<BinaryNode<Type>*> lastLevel;
        lastLevel.push_back(this->root); 
        
        while(!lastLevel.empty()){
            vector<BinaryNode<Type>*> newLevel;
            vector<Type> resultElem;
            for(BinaryNode<Type> *bn: lastLevel){
                if(bn){
                    if(bn->left) newLevel.push_back(bn->left);
                    if(bn->right) newLevel.push_back(bn->right);
                    resultElem.push_back(bn->data);
                }
            }

            result.push_back(resultElem);
            lastLevel.clear();   
            for(BinaryNode<Type> *bn: newLevel) lastLevel.push_back(bn);
        }
        return result;
        
    }

    void printInOrder(){
        std::cout << "In order traversal: [";
        printInOrderRecursive(this->root);
        std::cout << "]\n";
    }

    void printLevelOrder(){

        std::cout << "\n";
    }

    friend bool operator==(const RedBlackTree<Type> &bst1, const RedBlackTree<Type> &bst2) { 
       return bst1.getRoot() == bst2.getRoot();
    }
    friend bool operator!=(const RedBlackTree<Type> &bst1, const RedBlackTree<Type> &bst2) {
        return bst1.getRoot() != bst2.getRoot();
    }

    
    friend std::ostream& operator<<(std::ostream &os, const RedBlackTree<Type> &bst) {

        vector<vector<Type>> levels = bst.getLevelsAsList();
        for(vector<Type> level : levels){
            os << '[';
            for(Type data : level){
                os << data << ' ' << ',';
            }
            os << ']' << '\n';
        }
        
        return os ;
    }

    friend std::istream& operator>>(std::istream &is, const RedBlackTree<Type> &bst) {
        return is;
    }

    

private:
    BinaryNode<Type> *root;
    
    bool containsRecursive(Type value, BinaryNode<Type>* node){
        if(!node) return false;
        
        if(value < node->data){
            return containsRecursive(value, node->left);
        } else if(value > node->data){
            return containsRecursive(value, node->right);
        } else {
            return true;
        }
        return false;

    }
    
    BinaryNode<Type>* findRecursive(Type value, BinaryNode<Type>* node){
        if(node == nullptr) return node;
        
        if(value == node->data) return node;
        if(value > node->data) return findRecursive(value, node->right);
        if(value < node->data) return findRecursive(value, node->left);

        return nullptr;
    }

    BinaryNode<Type>* findMinValueRecursive(BinaryNode<Type> *node){
        if(node == nullptr) return node;
        return findMinValueRecursive(node->left);
    }

    int getBlackHeightDiff(BinaryNode<Type> *node){
        return 0;
    }

    BinaryNode<Type> *LLCase(BinaryNode<Type> *node){
        //we need to rotate the tree to the right
        BinaryNode<Type> *localRoot = node->left;
        node->left = localRoot->right;
        localRoot->right = node;
        return localRoot;
    }

    BinaryNode<Type> *RRCase(BinaryNode<Type> *node){
        //We need to rotate the tree to the left
        BinaryNode<Type> *localRoot = node->right;
        node->right = localRoot->left;
        localRoot->left = node;
        return localRoot;
    }

    BinaryNode<Type> *LRCase(BinaryNode<Type> *node){
        
        BinaryNode<Type> *localRoot = node->left->right;
        BinaryNode<Type> *localRootLeftSubTree = localRoot->left;
        BinaryNode<Type> *localRootRightSubTree = localRoot->right;
        
        localRoot->left = node->left;
        localRoot->left->right = localRootLeftSubTree;
        localRoot->right = node;
        node->left = localRootRightSubTree;
        return localRoot;
    }

    BinaryNode<Type> *RLCase(BinaryNode<Type> *node){
        BinaryNode<Type> *localRoot = node->right->left;
        BinaryNode<Type> *localRootLeftSubTree = localRoot->left;
        BinaryNode<Type> *localRootRightSubTree = localRoot->right;

        localRoot->right = node->right;
        localRoot->right->left = localRootRightSubTree;
        localRoot->left = node;
        node->right = localRootLeftSubTree;
        return localRoot;
    }

    BinaryNode<Type>* insertFix(BinaryNode<Type> *node){
        
        
        while ( (node != this->root) && node->parent->color == Color::RED ) {

            BinaryNode<Type> *grandParent = node->parent->parent;
            BinaryNode<Type> *uncle = nullptr;

            if ( grandParent->left == node->parent ) {
                /* If nodes's parent is left of grandparent then nodes uncle is on the right side of grandparent*/
                if(grandParent->right) uncle = grandParent->right;
                if (uncle && uncle->color == Color::RED) {
                    /* case 1 - change the colours */
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandParent->color = Color::RED;
                    /* Move node up the tree */
                    node = grandParent;
                } else {
                    /* uncle is a black node */
                    if ( node->parent->right == node) {
                        /* and node is to the right */ 
                        /* case 2 - move node up and rotate */
                        LRcase(grandParent);
                    } else if(node->parent->left == node ){
                        /* case 3 */
                        //llCase - right rotate
                        LLCase(grandParent);
                    }
                    //Swap the colors of nodes parent and grand parent
                    Color parentsColor = node->parent->color;
                    node->parent->color = grandParent->color;
                    grandParent->color = parentsColor; 
                    
                }

            } else {
                /* If nodes's parent is right of grandparent then nodes uncle is on the left side of grandparent*/
                if(grandParent->left) uncle = grandParent->left;

                if (uncle && uncle->color == Color::RED) {
                    /* case 1 - change the colours */
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandParent->color = Color::RED;
                    /* Move node up the tree */
                    node = grandParent;
                } else {
                    /* uncle is a black node */
                    if ( node->parent->left == node) {
                        /* and node is to the right */ 
                        /* case 2 - move node up and rotate */
                        RLCase(grandParent);
                    } else if(node->parent->right == node ){
                        /* case 3 */
                        //rrCase - right rotate
                        RRCase(grandParent);
                    }
                    //Swap the colors of nodes parent and grand parent
                    //Swap the colors of nodes parent and grand parent
                    Color parentsColor = node->parent->color;
                    node->parent->color = grandParent->color;
                    grandParent->color = parentsColor;
                    
                }
            }
        }
        /* Colour the root black */
        this->root->color = Color::BLACK;
    }

    

    BinaryNode<Type>* insertRecursive(BinaryNode<Type> *node, BinaryNode<Type> *newNode){
        if(root == nullptr) {
            root = new BinaryNode<Type>(value);
            root->color = Color::BLACK;
            return root;
        }
        if(node == nullptr) return newNode;
        if(newNode->data >= node->data) node->right = insertRecursive(value, node->right); 
        if(newNode->data < node->data) node->left = insertRecursive(value, node->left);

        if(node->left) node->left->parent = node;
        if(node->right) node->right->parent = node;
        
        return node;

        
    }


    void deleteNode(BinaryNode<Type> *trash){
        BinaryNode<Type> *replacement = findReplacementNodeFor(trash);

        bool isDoubleBlack =  ((replacement == nullptr || replacement->color == Color::BLACK) && (trash->color == Color::BLACK));

        // replacement is nullptr therefore trash is leaf 
        if(replacement == nullptr) {
            if(trash != this->root) {
                
                if(isDoubleBlack){
                    fixDoubleBlack(trash);
                } else{
                    // replacement or trash is red 
                    if(trash->parent->left == trash) {
                        // sibling is not null, make it red" 
                        if(trash->parent->right) trash->parent->right->color = Color::RED;
                    } else {
                        // sibling is not null, make it red" 
                        if(trash->left->right) trash->parent->left->color = Color::RED;
                    }
                }

                if(trash->parent->left == trash) trash->parent->left = nullptr;
                else trash->parent->right = nullptr;
            }
            delete trash 
        }

        // trash has 1 child
        if(trash->left == nullptr || trash->right == nullptr){
            if(trash == this->root){
                trash->data = replacement->data;
                trash->left = trash->right = nullptr;
                trash = replacement;
            } else {
                replacement->parent = trash->parent;
                
                if(trash->parent->left == trash) trash->parent->left = replacement;
                else trash->parent->right = replacement;
                
                if(isDoubleBlack) fixDoubleBlack(replacement);
                else replacement->color = Color::RED; // replacement or trash red, color replacement black 
            }
            delete trash;
        } 

        if(trash->left != nullptr || trash->right != nullptr){
            Type tmp = replacement->data;
            replacement->data = trash->data;
            trash->data = tmp;
            deleteNode(replacement);
        } 
    
    }

    void fixDoubleBlack(BinaryNode<Type> *node){
        if(node == this->root) return;

        BinaryNode<Type> *sibling = nullptr;

        if(node->parent->left == node) sibling = node->parent->left;
        else sibling = node->parent->right;

        if(sibling == nullptr){
            fixDoubleBlack(node->parent)
        } else {
            if(sibling->color == Color::RED){
                node->parent->color = Color::RED;
                sibling->color = Color::BLACK;

                if(sibling->parent->left == sibling) LLCase(node->parent);
                else RRCase(node->parent);

                fixDoubleBlack(node);
            } else {
                //sibling is black 

                //if sibling has at least 1 red child 
                if(sibling->left != nullptr && sibling->left->color == Color::RED){
                    if(sibling->parent->left == sibling) {
                        sibling->left->color = sibling->color;
                        sibling->color = sibling->parent->color;
                        LLCase(sibling->parent);
                    } else {
                        sibling->left->color = sibling->parent->color;
                        RLCase(sibling->parent);
                    }
                } else if(sibling->right != nullptr && sibling->right->color == Color::RED){
                    if(sibling->parent->left == sibling) {
                        sibling->left->color = sibling->color;
                        sibling->color = sibling->parent->color;
                        LRCase(sibling->parent);
                    } else {
                        sibling->left->color = sibling->parent->color;
                        RRCase(sibling->parent);
                    }
                }

                if(sibling->left && sibling->right && sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK){
                    sibling->color = Color::RED;
                    if(sibling->parent->color == Color::BLACK) fixDoubleBlack(sibling->parent);
                     
                }
                sibling->parent->color = Color::BLACK;

                
            }
        }
    }

    BinaryNode<Type>* findReplacementNodeFor(BinaryNode<Type> *target){
        if(target->left != nullptr && target->right != nullptr) return getMinNode(target->right);

        if(target->left == nullptr && target->right == nullptr) return nullptr;

        if(target->left != nullptr) return target->left;
        else return target->right;
    }

    void deleteTreeRecursive(BinaryNode<Type> *node){
        if(node == nullptr) return;
        
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        node = NULL;
    }
    BinaryNode<Type> *getMinNode(BinaryNode<Type> *node){
        if(node == nullptr || node->left == nullptr) return node;
        return getMinNode(node->left);
    }


    BinaryNode<Type>* deepCopyTree(const BinaryNode<Type> *node){
        if(node == nullptr) return nullptr;
        BinaryNode<Type> *newNode = new BinaryNode<Type>(node->data);
        newNode->left = deepCopyTree(node->left);
        newNode->right = deepCopyTree(node->right);
        return newNode;
    }

    void printInOrderRecursive(BinaryNode<Type> *node){
        if(node == nullptr) return;
        
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }
    
};

#endif //TREES_RED_BLACK_TREE_H