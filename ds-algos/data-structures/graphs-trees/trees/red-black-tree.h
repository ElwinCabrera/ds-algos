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

    //Convinience method to check childs color because null is considerd as black
    Color leftChildColor(){ 
        if(!left) return Color::BLACK;
        return left->color;
    }

    Color rightChildColor(){
        if(!right) return Color::BLACK;
        return left->color;
    }
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
        insertFix(newNode);
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

    BinaryNode<Type> *rightRotate(BinaryNode<Type> *node){
        //We have a Left Left case
        //we need to rotate the tree to the right
        BinaryNode<Type> *localRoot = node->left;
        node->left = localRoot->right;

        if(localRoot->right != nullptr) localRoot->right->parent = node;

        localRoot->parent = node->parent;
        
        if(node->parent == nullptr){
            this->root = localRoot;
        } else if(node == node->parent->left){
            //node is left child of parent update parents left child to localRoot
            node->parent->left = localRoot;
        } else {
            //node is right child of parent update parents right child to localRoot
            node->parent->right = localRoot;
        }

        localRoot->right = node;
        node->parent = localRoot;
        return localRoot;


    }

    BinaryNode<Type> *leftRotate(BinaryNode<Type> *node){
        //We have Right Right case
        //we need to rotate the tree to the left
        BinaryNode<Type> *localRoot = node->right;
        node->right = localRoot->left;

        if(localRoot->left != nullptr) localRoot->left->parent = node;

        localRoot->parent = node->parent;
        if(node->parent == nullptr){
            //then node is root
            this->root = localRoot;
        } else if (node == node->parent->left){
            node->parent->left = localRoot;
        } else {
            node->parent->right = localRoot;
        }
        
        localRoot->left = node;
        node->parent = localRoot;
        return localRoot;
    }

    void insertFix(BinaryNode<Type> *node){
        
        
        while ( (node != this->root) && node->parent->color == Color::RED ) { // While its not root and we are violating property 3

            BinaryNode<Type> *grandParent = node->parent->parent;
            BinaryNode<Type> *uncle = nullptr;

            if ( grandParent->left == node->parent ) {
                //our parent is the the left

                /* If nodes's parent is left of grandparent then nodes uncle is on the right side of grandparent*/
                if(grandParent->right) uncle = grandParent->right;
                if (uncle && uncle->color == Color::RED) {
                    //uncle is red do recoloring 
                    /* case 1 - change the colors */
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandParent->color = Color::RED;
                    /* Move node up the tree to next red node*/
                    node = grandParent;
                } else {
                    /* uncle is null or a black do rotations */
                    //Do rotations 
                    if ( node->parent->right == node) {
                        /*  
                            Case 2 - Left Right case
                            Update the node to point to parent
                            Parent is to the left of grandparent and node is to the right of parent so we have a RL case 
                            we need to rotate right and then rotate left to fix this.
                        */
                        node = node->parent;
                        leftRotate(node);
                    }

                    /*  
                        Case 3 - Left Left case
                        parent is to the left of grandparent and node is to the left of parent so we have a LL case 
                        we need to rotate right.
                    */

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;

                    rightRotate(node->parent->parent); 
                    
                }


            } else {
                //our parent is to the right 

                /* If nodes's parent is left of grandparent then nodes uncle is on the right side of grandparent*/
                if(grandParent->left) uncle = grandParent->left;
                if (uncle && uncle->color == Color::RED) {
                    //uncle is red do recoloring 
                    /* case 1 - change the colors */
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandParent->color = Color::RED;
                    /* Move node up the tree to next red node*/
                    node = grandParent;
                } else {
                    /* uncle is null or a black do rotations */
                    //Do rotations 
                    if ( node->parent->left == node) {
                        /*  
                            Case 2 - Right Left case
                            Update the node to point to parent
                            Parent is to the right of grandparent and node is to the left of parent so we have a RL case 
                            we need to rotate right and then rotate left to fix this.
                        */
                        node = node->parent;
                        rightRotate(node);
                    }

                    /*  
                        Case 3 - Right Right case
                        parent is to the right of grandparent and node is to the right of parent so we have a RR case 
                        we need to rotate left.
                    */

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;

                    leftRotate(node->parent->parent); 
                    
                }


                
            }
        }
        /* Color the root black */
        this->root->color = Color::BLACK;
    }

    

    BinaryNode<Type>* insertRecursive(BinaryNode<Type> *node, BinaryNode<Type> *newNode){
        if(root == nullptr) {
            root = newNode;
            root->color = Color::BLACK;
            return root;
        }
        if(node == nullptr) return newNode;
        if(newNode->data >= node->data) node->right = insertRecursive(node->right, newNode); 
        if(newNode->data < node->data) node->left = insertRecursive(node->left, newNode);

        if(node->left) node->left->parent = node;
        if(node->right) node->right->parent = node;
        
        return node;

        
    }


    BinaryNode<Type>* safeDeleteNode(BinaryNode<Type> *trash){
        BinaryNode<Type> *trueTrash = trash;

        if(trash->left != nullptr && trash->right != nullptr) trueTrash = getMinNode(trash->right);
        
        BinaryNode<Type> *replacementNode = nullptr;

        if(trueTrash->left != nullptr)  replacementNode = trueTrash->left;
        else replacementNode = trueTrash->right;

        replacementNode->parent = trueTrash->parent;
        if(trueTrash->parent == nullptr){
            this->root = replacementNode;
        } else { 
            if(trueTrash == trueTrash->parent->left) trueTrash->parent->left = replacementNode;
            else trueTrash->parent->right = replacementNode;
        } 

        if(trueTrash != trash) {
            trash->data = trueTrash->data;
            replacementNode->color = trueTrash->color;
        }

        if(trueTrash->color == Color::BLACK){
            replacementNode->color = Color::DOUBLEBLACK;
            fixDoubleBlack(replacementNode);
        }

        return trueTrash;
    }

    void fixDoubleBlack(BinaryNode<Type> *node){
        
        while(node != this->root && node->color == Color::DOUBLEBLACK){
            BinaryNode<Type> *sibling = nullptr;
            if(node->parent->left == node){
                //our node is on the left side of our parent
                sibling = node->parent->right;
                if(sibling && sibling->color == Color::RED){
                    sibling->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }
                if(sibling && sibling->leftChildColor() == Color::BLACK && sibling->rightChildColor() == Color::BLACK){ 
                    sibling->color = Color::RED;
                    node = node->parent;
                    node->color = Color::DOUBLEBLACK;
                } else {
                    if(sibling && sibling->rightChildColor() == Color::BLACK){
                        if(sibling->left) sibling->left = Color::BLACK;
                        sibling->color = Color::RED;
                        rightRotate(sibling);
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    leftRotate(node->parent);
                    node = this->root;
                    node->color = Color::DOUBLEBLACK;
                }


            } else {
                //our node is on the right side of its parent
            }
        }
        node->color = Color::BlLACK;
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
        
        printInOrderRecursive(node->left);
        std::cout << node->data << " ";
        printInOrderRecursive(node->right);
    }
    
};

#endif //TREES_RED_BLACK_TREE_H