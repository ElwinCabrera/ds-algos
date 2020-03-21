#ifndef TREES_RED_BLACK_TREE_H
#define TREES_RED_BLACK_TREE_H

#include <vector>
using std::vector;

template<typename Type>
class BinaryNode{
public:
    BinaryNode(): left(nullptr), right(nullptr), parent(nullptr), red(true) {}
    BinaryNode(Type t): data(t), left(nullptr), right(nullptr), parent(nullptr), red(true) {}
    Type data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;
    bool red;
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
        this->root = restoreTree(newNode);
    }
    void remove(Type value) { 
        removeRecursive(value, this->root); 
        this->root = restoreTree(this->root);
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

    BinaryNode<Type>* restoreTree(BinaryNode<Type> *node){
        
        
        while ( (node != this->root) && node->parent->red ) {

            BinaryNode<Type> *grandParent = node->parent->parent;
            BinaryNode<Type> *uncle = nullptr;

            if ( grandParent->left == node->parent ) {
                /* If nodes's parent is left of grandparent then nodes uncle is on the right side of grandparent*/
                if(grandParent->right) uncle = grandParent->right;
                if (uncle && uncle->red) {
                    /* case 1 - change the colours */
                    node->parent->red = false;
                    uncle->red = false;
                    grandParent->red = true;
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
                        x->parent->colour = black;
                        x->parent->parent->colour = red;
                        LLCase(grandParent);
                    }
                    //Swap the colors of nodes parent and grand parent
                    bool parentsColor = node->parent->red;
                    node->parent->red = grandParent->red;
                    grandParent->red = parentsColor; 
                    
                }

            } else {
                /* If nodes's parent is right of grandparent then nodes uncle is on the left side of grandparent*/
                if(grandParent->left) uncle = grandParent->left;

                if (uncle && uncle->red) {
                    /* case 1 - change the colours */
                    node->parent->red = false;
                    uncle->red = false;
                    grandParent->red = true;
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
                    bool parentsColor = node->parent->red;
                    node->parent->red = grandParent->red;
                    grandParent->red = parentsColor; 
                    
                }
            }
        }
        /* Colour the root black */
        this->root->red = false;
    }

    

    BinaryNode<Type>* insertRecursive(BinaryNode<Type> *node, BinaryNode<Type> *newNode){
        if(root == nullptr) {
            root = new BinaryNode<Type>(value);
            root->red = false;
            return root;
        }
        if(node == nullptr) return newNode;
        if(newNode->data >= node->data) node->right = insertRecursive(value, node->right); 
        if(newNode->data < node->data) node->left = insertRecursive(value, node->left);

        if(node->left) node->left->parent = node;
        if(node->right) node->right->parent = node;
        
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

       

        return restoreTree(node);
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

#endif //TREES_RED_BLACK_TREE_H