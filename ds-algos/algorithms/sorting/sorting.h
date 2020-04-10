#ifndef SORTING_H
#define SORTING_H


//Got the code snippet below from https://www.eriksmistad.no/measuring-runtime-in-milliseconds-using-the-c-11-chrono-library/ 
#define TIMING
 
#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::nanoseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ns " << std::endl; 
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif

//End citation 



#include <vector>
#include <set>
#include <iostream>
#include <chrono>
using std::vector;
using std::cout;
using std::set;

template<typename T>
class Sorting {
public:
    Sorting(vector<T> &list) {
        srand (time(NULL));
        
        sortMe = list;
        originalOrderArray = list;

        comparisonCount = 0;
        swapCount = 0;
        memWrites = 0;

    }
    Sorting(uint size){
        srand (time(NULL));
        
        sortMe.reserve(size);
        for(uint i = 0; i < size; ++i){
            sortMe.push_back(i);
        }
        cout << "Expected Order: ";
        printArrayAndStats(false);
        randomizeArrayOrder();

        originalOrderArray = sortMe;

        INIT_TIMER
        START_TIMER
        for(uint i = 0; i < originalOrderArray.size(); ++i) ;
        STOP_TIMER("Linear Run")

        comparisonCount = 0;
        swapCount = 0;
        memWrites = 0;
    }
    ~Sorting(){

    }

    vector<T> selectionSort(){
        cout << "\n\u001b[34mSelection Sort\u001b[0m\n";
        cout << "Unsorted array: ";
        printArrayAndStats(false);

        INIT_TIMER
        START_TIMER
        for(uint i = 0; i < sortMe.size(); ++i ){
            for(uint j = i +1; j < sortMe.size(); ++j){
                if(this->sortMe.at(j) < this->sortMe.at(i)) {
                    swapPos(i, j);
                }
                comparisonCount++;
            }
        }
        STOP_TIMER("Selection Sort")


        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Selection sort done\n";

        return this->sortMe;
    }

    vector<T> bubbleSort(){
        cout << "\n\u001b[34mBubble Sort\u001b[0m\n";
        cout << "Unsorted array: ";
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER   
        for(uint i = 0; i < sortMe.size(); ++i){
            for(uint j = 1; j < (sortMe.size() - i); ++j){
                if(sortMe.at(j-1) > sortMe.at(j)) {
                    swapPos(j-1, j);
                }
                comparisonCount++;
            }
        }
        STOP_TIMER("Bubble Sort")

        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Bubble sort done\n";

        return this->sortMe;
    }

    vector<T> insertionSort(){
        //slightly optimized insertion sort
        // adding the key at the end in its correct position to reduce many writes
        cout << "\n\u001b[34mInsertion Sort\u001b[0m\n";
        cout << "Unsorted array: "; 
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER
        for(uint i = 1; i < sortMe.size(); ++i){
            T key = sortMe.at(i);
            int j = i -1;
            
            while(j >= 0 && sortMe.at(j) > key){
                swapPos(j, j+1);
                j -= 1;
            }
            comparisonCount++;
            sortMe.at(j+1) = key; 
        }
        STOP_TIMER("Insertion Sort")
        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Insertion sort done\n";
        
        return sortMe;
    }


    vector<T> mergeSort(){
        cout << "\n\u001b[34mMerge Sort\u001b[0m\n";
        cout << "Unsorted array: "; 
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER
        vector<T> result = mergeSortHelper(sortMe);
        STOP_TIMER("Merge Sort")
    
        sortMe = result;

        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Merge sort done\n";
        
        return sortMe;
    }

    vector<T> optimizedMergeSort(){
        cout << "\n\u001b[34mOptimized Merge Sort\u001b[0m\n";
        cout << "Unsorted array: "; 
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER
        optimizedMergeSortHelper(0, sortMe.size()-1);
        STOP_TIMER("Optimized Merge Sort")

        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Optimized merge sort done\n";
        
        return sortMe;
    }

    vector<T> quickSort(){
        cout << "\n\u001b[34mQuick Sort\u001b[0m\n";
        cout << "Unsorted array: " ;
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER
        quickSortHelper(0, sortMe.size()-1);
        STOP_TIMER("Quick Sort")
        
        
        cout << "Sorted array:   ";
        printArrayAndStats(true);
        cout << "Quick sort done\n";
        
        return sortMe;
    }

    vector<T> heapSort(){

    }

    //This will only work with numbers
    vector<T> countingSort(){
        cout << "\n\u001b[34mCounting Sort\u001b[0m\n";
        cout << "Unsorted array: "; 
        printArrayAndStats(false);
        
        INIT_TIMER
        START_TIMER

        T maxVal = sortMe.at(0);
        for(T val: sortMe){
            maxVal = std::max(maxVal, val);
        }
        vector<int> v(maxVal+1,0);
        for(T val: sortMe){
            v.at(val)++;
        }
        uint sortMeIdx = 0;
        for(uint i = 0; i < v.size(); ++i){
            while(v.at(i)-- > 0){
                sortMe.at(sortMeIdx++) = (T) i;
            }
        }
        STOP_TIMER("Counting Sort")
        
        cout << "Sorted array:   ";    
        printArrayAndStats(true);
        cout << "Counting sort done\n";

        return sortMe;

    }

    vector<T> radixSort(){

    }

    vector<T> bucketSort(){

    }


    void runAllSorting(){
        selectionSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        bubbleSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        insertionSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        mergeSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        optimizedMergeSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        quickSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;

        countingSort();
        //randomizeArrayOrder();
        sortMe = originalOrderArray;
    }

   



    void randomizeArrayOrder(){
        cout << "\nShuffling the array\n";
        // do randomizing here
        for(uint i = 0; i < sortMe.size(); ++i){
            uint randomIdx = rand() % sortMe.size();
            while(randomIdx == i) randomIdx = rand() % sortMe.size();
            swapPos(i, randomIdx);
        }

        cout << "Shuffled array: ";
        printArrayAndStats(false);

        memWrites = 0;
        swapCount = 0;
    }

    void printArrayAndStats(bool printStats){
        
        if(isSorted()) cout << "\u001b[32m";
        else cout << "\u001b[31m";

        
        
        cout << "[";
        if(sortMe.size() < 20){
            for(uint i = 0; i < sortMe.size(); ++i){
                cout << sortMe.at(i) << ",";
            }
        } else {
            //print first 10
            for(uint i = 0; i < 10; ++i){
                cout << sortMe.at(i)  << ",";
            }
            cout <<"...,";
            //print last 10
            for(uint i = sortMe.size()-10; i < sortMe.size(); ++i){
                cout << sortMe.at(i)  << ",";
            }
        }
        
        cout << "\b]\n";
        cout << "\u001b[0m";

        if(printStats){
            cout << "Comparison count = " << comparisonCount << "\n";
            cout << "Swap count = " << swapCount << "\n";
            cout << "Memory writes = " << memWrites << "\n";
            //elapsedSeconds = endTime - startTime;
            //cout << "Elapsed time: " << elapsedSeconds.count() << "s\n"; 

            comparisonCount = 0;
            swapCount = 0;
            memWrites = 0;
        }

        
    }

    bool isSorted(){
        for(uint i =0; i < sortMe.size(); ++i){
            if(sortMe.at(i) != i) return false;
        }
        return true;
    }


private:
    vector<T> sortMe;
    vector<T> originalOrderArray;
    uint comparisonCount ;
    uint swapCount;
    uint memWrites;
    //std::chrono::time_point<std::chrono::system_clock> startTime;
    //std::chrono::time_point<std::chrono::system_clock> endTime;
    //std::chrono::duration<double> elapsedSeconds; 
              

    void swapPos(int pos1, int pos2){
        T save = this->sortMe.at(pos1);
        this->sortMe.at(pos1) = this->sortMe.at(pos2);
        this->sortMe.at(pos2) = save;
        swapCount++;
        memWrites += 2;
    }

    vector<T> mergeSortHelper(vector<T> &vect){
        if(vect.size() <= 1 ) return vect;
        
        int mid =  vect.size()/2;


        vector<T> left;
        vector<T> right;
        for(uint i = 0; i < mid; ++i){
            left.push_back(vect.at(i));
        } 
        for(uint i = mid; i < vect.size(); ++i){
            right.push_back(vect.at(i));
        }
        left = mergeSortHelper(left);
        right = mergeSortHelper(right);
        
        return merge(left, right);
    }

    vector<T> merge(vector<T> &v1, vector<T> &v2){
        
        vector<T> result;
        uint idx1 = 0;
        uint idx2 = 0;
        
        while(idx1 < v1.size() && idx2 < v2.size()){
            if(v1.at(idx1) < v2.at(idx2)){
                result.push_back(v1.at(idx1));
                idx1++;
            } else {
                result.push_back(v2.at(idx2));
                idx2++;
            }
            memWrites++;
            comparisonCount++;
        }
        while(idx1 < v1.size()){
            result.push_back(v1.at(idx1));
            memWrites++;
            idx1++;
        }

        while(idx2 < v2.size()){
            result.push_back(v2.at(idx2));
            memWrites++;
            idx2++;
        }

        return result;
    }


    void optimizedMergeSortHelper(int start, int end){
        if(start >= end) return ;
        
        int mid = start + (end- start) /2;


        optimizedMergeSortHelper(start, mid);
        optimizedMergeSortHelper(mid+1, end);
        
        optimizedMerge(start, mid, end);
    }

    void optimizedMerge(uint start, uint mid, uint end){
        
        vector<T> sortedVec;
        uint idx1 = start;
        uint idx2 = mid +1;

        
        
        while(idx1 <=mid && idx2 <= end){
            if(sortMe.at(idx1) < sortMe.at(idx2)){
                sortedVec.push_back(sortMe.at(idx1));
                idx1++;
            } else {
                sortedVec.push_back(sortMe.at(idx2));
                idx2++;
            }

            memWrites++;
            comparisonCount++;

        }
        while(idx1 <= mid){
            sortedVec.push_back(sortMe.at(idx1));
            memWrites++;
            idx1++;
        }

        while(idx2 <= end){
            sortedVec.push_back(sortMe.at(idx2));
            memWrites++;
            idx2++;
        }

        idx1 = 0;
        for(uint i = start; i <= end; ++i){
            sortMe.at(i) = sortedVec.at(idx1++);
            memWrites++;
        }

    }

    void quickSortHelper(int start, int end){
        if(start >= end) return;
        int pivotIdx = partition(start, end);

        quickSortHelper(start, pivotIdx-1);
        quickSortHelper(pivotIdx+1, end);
    }

    int partition(int start, int end){
        T pivotValue = sortMe.at(end);
        int availableSlotIdx = start;

        
        while(start <= end ){
            if(sortMe.at(start) <= pivotValue){
                swapPos(start, availableSlotIdx);
                availableSlotIdx++;
            }
            start++;
            comparisonCount++;
        }

        return availableSlotIdx-1;

    }
};


#endif //SORTING_H