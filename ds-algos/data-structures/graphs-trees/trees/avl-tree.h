#ifndef TREES_AVL_TREE_H
#define TREES_AVL_TREE_H


#include <vector>
using std::vector;

template<typename Type>
class BinaryNode{
public:
    BinaryNode(): left(nullptr), right(nullptr) {}
    BinaryNode(Type t): data(t), left(nullptr), right(nullptr) {}
    Type data;
    BinaryNode *left;
    BinaryNode *right;
};

template<typename Type>
class AVLTree{
public:
    AVLTree(){
        root = nullptr;
    }

    //copy constructor
    //do a deep copy of the other binary tree
    AVLTree(const AVLTree &other){
        this->root = deepCopyTree(other.getRoot());
    }

    //move constructor 
    //used when passing the address as argument to function 
    //in that case we dont want a full copy just the address
    AVLTree(const AVLTree &&other){
        this->root = other->root;
        other->root = nullptr;
    }
    ~AVLTree(){
        deleteTree();
    }

    //use copy-swap to get strong exception guarantee
    // to do this we need a fully working copy constructor and our own swap function 
    // 1. make a temp copy of the other object 
    // 2. swap the temporary object with the current object 
    AVLTree& operator=(const AVLTree &other){
        AVLTree tempBtree(other);
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
        this->root = insertRecursive(value, this->root); 
    }
    void remove(Type value) { 
        removeRecursive(value, this->root); 
    }

    void deleteTree() {
        deleteTreeRecursive(this->root);
    }

    void swap(AVLTree &other) throw(){
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

    friend bool operator==(const AVLTree<Type> &bst1, const AVLTree<Type> &bst2) { 
       return bst1.getRoot() == bst2.getRoot();
    }
    friend bool operator!=(const AVLTree<Type> &bst1, const AVLTree<Type> &bst2) {
        return bst1.getRoot() != bst2.getRoot();
    }

    
    friend std::ostream& operator<<(std::ostream &os, const AVLTree<Type> &bst) {

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

    friend std::istream& operator>>(std::istream &is, const AVLTree<Type> &bst) {
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

    int getMaxHeight(BinaryNode<Type> *node){
        if(node == nullptr) return 0;
        int leftHeight = getMaxHeight(node->left) +1;
        int rightHeight = getMaxHeight(node->right) +1;
        return std::max(leftHeight, rightHeight);
    }

    int getBalanceFactor(BinaryNode<Type> *node){
        return getMaxHeight(node->left) - getMaxHeight(node->right);
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

    

    BinaryNode<Type>* insertRecursive(Type value, BinaryNode<Type> *node){
        if(root == nullptr) {
            root = new BinaryNode<Type>(value);
            return root;
        }
        if(node == nullptr) return new BinaryNode<Type>(value);
        if(value >= node->data) node->right = insertRecursive(value, node->right); 
        if(value < node->data) node->left = insertRecursive(value, node->left);

        int balanceFactor = getBalanceFactor(node);
        //if a node becomes unbalanced balance after inserting, there are 4 cases

        //Left Left Case (LL) we need to right rotate the tree
        if(balanceFactor > 1 && value < node->left->data) 
            return LLCase(node);

        //Right Right Case (RR) we need to left rotate the tree
        if(balanceFactor < -1 && value > node->right->data) 
            return RRCase(node);

        //Left Right Case (LR)
        if(balanceFactor > 1 && value > node->left->data) {
            return LRCase(node);
            
        }

        //Right Left Case (RL)
        if(balanceFactor < -1 && value < node->right->data ){
            return RLCase(node);
        }

        return node;

        
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

        int balanceFactor = getBalanceFactor(node);

        if(balanceFactor > 1 && getBalanceFactor(node->left) >= 0) return LLCase(node);

        if(balanceFactor > 1 && getBalanceFactor(node->left) < 0) return LRCase(node);

        if(balanceFactor < -1 && getBalanceFactor(node->right) <= 0) return RRCase(node);

        if(balanceFactor < -1 && getBalanceFactor(node->right) > 0) return RLCase(node);
        

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

#endif //TREES_AVL_TREE_H