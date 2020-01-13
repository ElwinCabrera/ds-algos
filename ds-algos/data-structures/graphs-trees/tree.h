#ifndef TREE_HPP
#define TREE_HPP

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
class NarryNode{
public:
    NarryNode() {}
    NarryNode(Type t): data(t)  {}
    Type data;
    vector<NarryNode*> children;
};

namespace trees {


    template<typename Type>
    class Forest{ // or N-ary Tree

    };

    template<typename Type>
    class BinaryTree{
    public:
        BinaryTree();
        ~BinaryTree();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };

    template<typename Type>
    class BinarySearchTree{
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };



    template<typename Type>
    class AVLTree{  //height balanced tree
    public:
        AVLTree();
        ~AVLTree();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };

    template<typename Type>
    class RedBlackTree{
    public:
        RedBlackTree();
        ~RedBlackTree();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };

    template<typename Type>
    class Trie{

    };

    template<typename Type>
    class SuffixTree{

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

    template<typename Type>
    class MinHeap{
    public:
        MinHeap();
        ~MinHeap();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };

    template<typename Type>
    class MaxHeap{
    public:
        MaxHeap();
        ~MaxHeap();
        bool find(Type value);
        void insert(Type value);
        void remove(Type value);
    private:
        BinaryNode<Type> *root;
    };

};


template<typename Type>
class BinaryTree {

private:
    TreeNode *root ;
    TreeNode *rootPtr;

    BinaryNode* buildTreeHelper(vector<int> preorder, vector<int> inorder, int leftBound, int rightBound, int nextRootIdx);
    int findIdx(vector<int> inorder, int num);
public:
    
   
    BinaryTree(vector<int> preorder, vector<int> inorder);

    BinaryNode *buildTree(vector<int> preorder, vector<int> inorder);

    BinaryNode* insert(BinaryNode *tn, int num);

    void remove(BinaryNode *tn, int val);
    void remove(BinaryNode *deleteNode);
    void removeBiggerThan(int val);
    void removeSmallerThan(int val);

    TreeNode* getMin(TreeNode *tn);

};



BinaryTree::BinaryTree(vector<int> preorder, vector<int> inorder){
    root = buildTree(preorder, inorder);
}


/* Building tree from preorder and inorder */
TreeNode* BinaryTree::buildTree(vector<int> preorder, vector<int> inorder){
    if(preorder.empty() || inorder.empty()) return NULL;
    //inorder contains the root in the middle of the children
    //preorder has all the roots in
    return buildTreeHelper(preorder, inorder, 0, inorder.size()-1, 0); 
}

TreeNode* BinaryTree::buildTreeHelper(vector<int> preorder, vector<int> inorder, int leftBound, int rightBound, int nextRootIdx){
    if(leftBound > rightBound || nextRootIdx >= preorder.size()) return NULL;

    int rootVal = preorder.at(nextRootIdx);
    TreeNode *tn = new TreeNode(rootVal);


    int rootIdx = findIdx(inorder, rootVal);
    tn->left = buildTreeHelper(preorder, inorder, leftBound, rootIdx-1, nextRootIdx + 1);
    tn->right = buildTreeHelper(preorder, inorder, rootIdx+1, rightBound, nextRootIdx + 2);

    return tn;
}
int BinaryTree::findIdx(vector<int> inorder, int num){
    if(inorder.empty()) return -1;
    for(int i = 0; i < inorder.size(); ++i) if(inorder.at(i) == num) return i;
    return -1;
}


/* Inserting into tree */
TreeNode* BinaryTree::insert(TreeNode *tn, int val){
    
    //recursive way
    if(!tn) {

        if(!root) {
            root = new TreeNode(val);
            return root;
        }

        return new TreeNode(val);
    }
    if(val > tn->value) tn->right =  insert(tn->right,val);
    if(val < tn->value) tn->left =  insert(tn->left, val);

    
    return tn;


    //Iterative way
    /* TreeNode *rootPtr = root;
    TreeNode *newNode = new TreeNode(val);
    while(rootPtr->left && rootPtr->right){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }
        
    }

    while(rootPtr->right){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }       
    }

    while(rootPtr->left){
        if(val >= rootPtr->value){
            rootPtr = rootPtr->right;
        } else {
            rootPtr = rootPtr->left;
        }       
    }

    if(val >= rootPtr->value) rootPtr->right = newNode;
    else rootPtr->left = newNode;

    return newNode;*/

}


/*removing from list */
void BinaryTree::remove(TreeNode *tn, int val){
    /*
    First we need to find the actual node that we want to delete 
    after we find the node we then condider the following three cases.

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
         in one of those trees. 
    */

   if(!tn) return;
   
   if(val > tn->value){
       remove(tn->right, val);
   } else if(val < tn->value){
       remove(tn->left, val);
   } else {
       TreeNode *trash  = NULL;

       if( tn->left== NULL && tn->right == NULL){
           trash = tn;
       } else if(tn->left == NULL && tn->right != NULL){
           trash = tn;
           tn = tn->right;
       } else if(tn->left != NULL && tn->right == NULL){
           trash = tn;
           tn = tn->left;
       } else {
           TreeNode *min = getMin(tn->right);
           tn->value = min->value;
           remove(min, min->value);
       }
       if(trash) delete trash;
   }
   
}

TreeNode* BinaryTree::getMin(TreeNode *tn){
    if(!tn || !tn->left) return tn;
    return getMin(tn->left);
}
#endif  //BT_HPP