#ifndef TREES_BINARY_SEARCH_TREE_H
#define TREES_BINARY_SEARCH_TREE_H

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
class BinarySearchTree{
public:
    BinarySearchTree(){
        root = nullptr;
    }

    BinarySearchTree(BinarySearchTree &other){
    
    }
    BinarySearchTree(BinarySearchTree &&other){

    }
    ~BinarySearchTree(){
        deleteTree();
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
        insertRecursive(value, this->root); 
    }
    void remove(Type value) { 
        removeRecursive(value, this->root); 
    }

    void removeBiggerThan(int val){

    }
    
    void removeSmallerThan(int val){

    }
    
    void deleteTree() {
        deleteTreeRecursive(this->root);
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
    BinaryNode<Type>* insertRecursive(Type value, BinaryNode<Type> *node){
        if(root == nullptr) {
            root = new BinaryNode<Type>(value);
            return root;
        }
        if(node == nullptr) return new BinaryNode<Type>(value);
        if(value >= node->data) node->right = insertRecursive(value, node->right); 
        if(value < node->data) node->left = insertRecursive(value, node->left);
        return node;
        
    }

    BinaryNode<Type> *insertIteratively(Type value){
        
        BinaryNode<Type> *newNode = new BinaryNode<Type>(value);
        
        if(!this->root) {
            this->root = newNode;
            return this->root;
        }

        BinaryNode<Type> *rootPtr = this->root;
        BinaryNode<Type> *parent = nullptr;
        while (rootPtr->left && rootPtr->right){
            parent = rootPtr;
            if(value < rootPtr->data ) rootPtr = rootPtr->left;
            if(value >= rootPtr->data) rootPtr = rootPtr->right;
        }
        while(rootPtr->left){
            parent = rootPtr;
            if(value < rootPtr->data) rootPtr = rootPtr->left;
            if(value >= rootPtr->data) rootPtr = rootPtr->right;
        }
        while (rootPtr->right){
            parent = rootPtr;
            if(value < rootPtr->data) rootPtr = rootPtr->left;
            if(value >= rootPtr->data) rootPtr = rootPtr->right;
        }

        if(parent->right == nullptr) parent->right = newNode;
        else if(parent->left == nullptr) parent->left = newNode;

        return newNode; 

    }
    void removeRecursive(Type value, BinaryNode<Type> *node){
        /*First we need to find the actual node that we want to delete 
        after we find the node we then consider the following three cases.

        Case 1: leaf Node
            -Then just delete that node

        Case 2: node with a left subtree or right subtree
            -Then just point the current node (delete node)
            to whatever subtree that the current node 
            has 

        Case 3: node with both a left and right subtree
            -Then find the minimum node in right 
            subtree or the maximum in the left 
            subtree and set that to the current node 
            that we are trying to delete then just 
            delete the minimum value that we found 
            in one of those trees. */

        if(node->data > value){
            removeRecursive(value, node->right);
        } else if(node->data < value){
            removeRecursive(value, node->left);
        } else {
            BinaryNode<Type> *trash = nullptr;

            if(node->left == nullptr && node->right == nullptr) trash = node;
            if(node->left != nullptr && node->right == nullptr) {
                trash = node;
                node = node->left;
            }
            if(node->left == nullptr && node->right != nullptr){
                trash = node;
                node = node->right;
            }
            if(node->left != nullptr && node->right != nullptr){
                BinaryNode<Type> *minNodeToRight = getMinNode(node->right);
                node->data = minNodeToRight->data;
                removeRecursive(minNodeToRight->data, minNodeToRight);
            }
            if(trash) {
                delete trash;
                trash = NULL;
            }
        }
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
};

#endif //TREES_BINARY_SEARCH_TREE_H