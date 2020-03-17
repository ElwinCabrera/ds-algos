#ifndef TREES_BINARY_SEARCH_TREE_H
#define TREES_BINARY_SEARCH_TREE_H

#include <vector>
using std::vector;

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

    //copy constructor
    //do a deep copy of the other binary tree
    BinarySearchTree(const BinarySearchTree &other){
        this->root = deepCopyTree(other.getRoot());
    }

    //move constructor 
    //used when passing the address as argument to function 
    //in that case we dont want a full copy just the address
    BinarySearchTree(const BinarySearchTree &&other){
        this->root = other->root;
        other->root = nullptr;
    }
    ~BinarySearchTree(){
        deleteTree();
    }

    //use copy-swap to get strong exception guarantee
    // to do this we need a fully working copy constructor and our own swap function 
    // 1. make a temp copy of the other object 
    // 2. swap the temporary object with the current object 
    BinarySearchTree& operator=(const BinarySearchTree &other){
        BinarySearchTree tempBtree(other);
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
        insertRecursive(value, this->root); 
    }
    void remove(Type value) { 
        removeRecursive(value, this->root); 
    }

    void removeGTE(Type val){
        removeGTERecursive(val, this->root);
    }
    
    void removeLTE(Type val){
        removeLTERecursive(val, this->root);
    }
    
    void deleteTree() {
        deleteTreeRecursive(this->root);
    }

    // friend void swap(BinarySearchTree &first, BinarySearchTree &second){
    //     using std::swap;
    //     swap(first.root, second.root);
    // }

    void swap(BinarySearchTree &other) throw(){
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

    friend bool operator==(const BinarySearchTree<Type> &bst1, const BinarySearchTree<Type> &bst2) { 
       return bst1.getRoot() == bst2.getRoot();
    }
    friend bool operator!=(const BinarySearchTree<Type> &bst1, const BinarySearchTree<Type> &bst2) {
        return bst1.getRoot() != bst2.getRoot();
    }

    
    friend std::ostream& operator<<(std::ostream &os, const BinarySearchTree<Type> &bst) {

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

    friend std::istream& operator>>(std::istream &is, const BinarySearchTree<Type> &bst) {
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

    //not tested
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
    BinaryNode<Type>* removeRecursive(Type value, BinaryNode<Type> *node){
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
        if(node == nullptr) return node;

        

        if(value < node->data  ){
            node->left = removeRecursive(value, node->left);
        } else if(value > node->data){
            node->right = removeRecursive(value, node->right);
        } else {
            BinaryNode<Type> *trash = nullptr;
            BinaryNode<Type> *result = nullptr;

            if(node->left == nullptr && node->right == nullptr) {  // no children (leaf node)
                trash = node; 
            } else if(node->left != nullptr && node->right == nullptr) {  // only a left child 
                trash = node;
                result = node->left;
            } else if(node->left == nullptr && node->right != nullptr){  // only a right child
                trash = node;
                result = node->right;
            } else if(node->left != nullptr && node->right != nullptr){ // both left and right child 
                BinaryNode<Type> *minNodeToRight = getMinNode(node->right);
                node->data = minNodeToRight->data;
                node->right =  removeRecursive(minNodeToRight->data, node->right);
                //removeRecursive(minNodeToRight->data, minNodeToRight);
            }

            if(trash) {
                trash->left = nullptr;
                trash->right = nullptr;
                delete trash;
                trash = nullptr;
            }
            return result;
        }

        return node;
    }

    BinaryNode<Type>* removeGTERecursive(Type val, BinaryNode<Type> *node){
        if(node == nullptr) return node;
        if(val < node->data) node->left = removeGTERecursive(val, node->left);
        else if(val > node->data) node->right = removeGTERecursive(val, node->right);
        else {
            deleteTreeRecursive(node->right);
            BinaryNode<Type> *trash = node;
            BinaryNode<Type> *result = result = node->left;
            
            if(trash){
                trash->left = nullptr;
                trash->right = nullptr;
                delete trash ;
                trash = nullptr;
            }
            return result;
            
        }
        return node;
    }

    void removeLTERecursive(Type val, BinaryNode<Type> *node){
        if(node == nullptr) return node;
        if(val < node->data) node->left = removeLTERecursive(val, node->left);
        else if(val > node->data) node->right = removeLTERecursive(val, node->right);
        else {
            deleteTreeRecursive(node->right);
            BinaryNode<Type> *trash = node;
            BinaryNode<Type> *result = result = node->left;
            
            if(trash){
                trash->left = nullptr;
                trash->right = nullptr;
                delete trash ;
                trash = nullptr;
            }
            return result;
            
        }
        return node;
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
    
};

#endif //TREES_BINARY_SEARCH_TREE_H