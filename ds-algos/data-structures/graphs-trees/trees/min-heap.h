#ifndef TREES_MIN_HEAP_TREE_H
#define TREES_MIN_HEAP_TREE_H

#include<vector>
#include <limits.h>
using std::vector;

template<typename Type>
class MinHeap{
public:
    MinHeap(size_t capacity){
        if(capacity <= 0) capacity = 1;
        heapElements.resize(capacity);
        this->size = 0;
        this->capacity = capacity;
    }

    MinHeap(MinHeap &other){

    }

    MinHeap(MinHeap &&other){

    }

    ~MinHeap(){
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
        
        
        while(newElemIdx != 0 && heapElements.at(getParentIdx(newElemIdx)) > heapElements.at(newElemIdx)){
            swapElems(getParentIdx(newElemIdx), newElemIdx);
            newElemIdx = getParentIdx(newElemIdx);
        } 
    }

    Type extractMin(){
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
        int smallestIdx = idx;
        
        
        if(leftChildIdx < size && heapElements.at(leftChildIdx) < heapElements.at(idx) ) smallestIdx = leftChildIdx;

        if(rightChildIdx < size && heapElements.at(rightChildIdx) < heapElements.at(smallestIdx)) smallestIdx = rightChildIdx;

        if(smallestIdx != idx){
            swapElems(smallestIdx, idx);
            heapify(smallestIdx);
        }

    }

    void swapElems(int idx1, int idx2){
        Type tmp = heapElements.at(idx1);
        heapElements.at(idx1) = heapElements.at(idx2);
        heapElements.at(idx2) = tmp;
    }

};
#endif //TREES_MIN_HEAP_TREE_H