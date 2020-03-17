#ifndef TREES_MAX_HEAP_TREE_H
#define TREES_MAX_HEAP_TREE_H

#include<vector>
#include <limits.h>
using std::vector;

template<typename Type>
class MaxHeap{
public:
    MaxHeap(size_t capacity){
        if(capacity <= 0) capacity = 1;
        heapElements.resize(capacity);
        this->size = 0;
        this->capacity = capacity;
    }

    MaxHeap(MaxHeap &other){
        this->size = other.size;
        this->capacity = other.capacity;
        for(int i = 0; i < other.size; ++i){
            heapElements.at(i) = other.heapElements.at(i);
        }
    }

    MaxHeap(MaxHeap &&other){
        &this->heapElements = &other.heapElements;
        &this->size = &other.size;
        &this->capacity = &other.capacity;
    }

    ~MaxHeap(){
        heapElements.clear();
        size = 0;
        capacity = 0;
    }

    
    
    bool isEmpty(){
        return size == 0;
    }

    Type peek(){
        return heapElements.at(0);
    }

    void insert(Type value){
        if(size == capacity){
            return;
        }
        ++size;

        int newElemIdx = size-1;
        heapElements.at(newElemIdx) = value;
        
        
        while(newElemIdx != 0 && heapElements.at(getParentIdx(newElemIdx)) < heapElements.at(newElemIdx)){
            swapElems(getParentIdx(newElemIdx), newElemIdx);
            newElemIdx = getParentIdx(newElemIdx);
        } 
    }

    Type extractMax(){
        if(size <= 0) return INT_MAX;
        if(size == 1) {
            --size;
            return heapElements.at(0);
        }

        Type result = heapElements.at(0);
        heapElements.at(0) = heapElements.at(size-1);
        --size;

        heapify(0);
        return result;
    }

    void update(int idx, Type newValue){
        if(idx < size) heapElements.at(idx) = newValue;
    }

    //use copy-swap to get strong exception guarantee
    // to do this we need a fully working copy constructor and our own swap function 
    // 1. make a temp copy of the other object 
    // 2. swap the temporary object with the current object 
    MaxHeap& operator=(const MaxHeap &other){
        MaxHeap temp(other);
        temp.swap(*this);
        return *this;
    }

    friend bool operator==(const MaxHeap<Type> &heap1, const MaxHeap<Type> &heap2) { 
       return false;
    }
    friend bool operator!=(const MaxHeap<Type> &heap1, const MaxHeap<Type> &heap2) {
        return false; 
    }

    
    friend std::ostream& operator<<(std::ostream &os, const MaxHeap<Type> &heap) {

        
        
        return os ;
    }

    friend std::istream& operator>>(std::istream &is, const MaxHeap<Type> &heap) {
        return is;
    }

    // friend void swap(BinarySearchTree &first, BinarySearchTree &second){
    //     using std::swap;
    //     swap(first.root, second.root);
    // }

    void swap(MaxHeap &other) throw(){
        using std::swap;
        swap(&this->heapElements, other.heapElements);
        swap(this->capacity, other.capacity);
        swap(this->size, other.size);
    }


private:
    vector<Type> heapElements;
    size_t capacity;
    size_t size;

    int getParentIdx(int childIdx){
        return (childIdx -1) /2;
    }
    int getLeftChildIdx(int parentIdx){
        return parentIdx *2 +1;
    }
    int getRightChildIdx(int parentIdx){
        return parentIdx *2 +2;
    }

    void heapify(int idx){
        int leftChildIdx = getLeftChildIdx(idx);
        int rightChildIdx = getRightChildIdx(idx);
        int largerIdx = idx;
        
        
        if(leftChildIdx < size && heapElements.at(leftChildIdx) > heapElements.at(idx) ) largerIdx = leftChildIdx;

        if(rightChildIdx < size && heapElements.at(rightChildIdx) > heapElements.at(largerIdx)) largerIdx = rightChildIdx;

        if(largerIdx != idx){
            swapElems(largerIdx, idx);
            heapify(largerIdx);
        }

    }

    void swapElems(int idx1, int idx2){
        Type tmp = heapElements.at(idx1);
        heapElements.at(idx1) = heapElements.at(idx2);
        heapElements.at(idx2) = tmp;
    }

};
#endif //TREES_MAX_HEAP_TREE_H