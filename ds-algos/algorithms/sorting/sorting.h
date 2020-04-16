#ifndef SORTING_H
#define SORTING_H


//Got the code snippet below from https://www.eriksmistad.no/measuring-runtime-in-milliseconds-using-the-c-11-chrono-library/ and modified it to my liking 


#define TIMING
 
#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now(); \
                   auto stop = std::chrono::high_resolution_clock::now();

#define START_TIMER  start = std::chrono::high_resolution_clock::now();

#define STOP_TIMER(name)  stop = std::chrono::high_resolution_clock::now(); \
                        std::cout << "RUNTIME of " << name << ": " << \
                        std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count() << " ns, " <<  \
                        std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms, " << \
                        std::chrono::duration_cast<std::chrono::seconds>(stop-start).count() << " sec " << std::endl;

#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif

//End citation 


#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <unordered_map>
#include "../../data-structures/graphs-trees/trees/max-heap.h"
using std::vector;
using std::cout;
using std::set;
using std::unordered_map;

enum SortingType{
    BASE,
    BASEHALF,
    SELECTIONSORT,
    BUBBLESORT,
    INSERTIONSORT,
    MERGESORT,
    OPTIMIZEDMERGESORT,
    QUICKSORT,
    COUNTINGSORT,
    DUMMYLAST       // used as a dummy does not represent anything
};

template<typename T>
class Sorting {
public:
    Sorting(vector<T> &list, uint sampleSize = 1) {
        srand (time(NULL));
        

        sortMe = list;
        originalOrderArray = list;

        
        

        currentlyRunning = SortingType::DUMMYLAST;
        comparisonCount = 0;
        swapCount = 0;
        memWrites = 0;
        this->sampleSize = sampleSize;

        init();

    }


    Sorting(uint size, uint sampleSize = 1){
        
        srand (time(NULL));
        
        sortMe.reserve(size);
        for(uint i = 0; i < size; ++i){
            sortMe.push_back(i);
        }
        cout << "Expected Order: ";
        printArrayAndStats(false);
        randomizeArrayOrder();

        originalOrderArray = sortMe;

        

        currentlyRunning = SortingType::DUMMYLAST;
        comparisonCount = 0;
        swapCount = 0;
        memWrites = 0;
        this->sampleSize = sampleSize;

        init();
    }
    ~Sorting(){

    }

    vector<T> selectionSort(){
        currentlyRunning = SortingType::SELECTIONSORT;
        if(sortingAlgoToNumRuns.find(SortingType::SELECTIONSORT)->second == 0){
            cout << "\n\u001b[34mSelection Sort\u001b[0m\n";
            cout << "Unsorted array: ";
            printArrayAndStats(false);
        }

        startTime = std::chrono::high_resolution_clock::now();
        for(uint i = 0; i < sortMe.size(); ++i ){
            for(uint j = i +1; j < sortMe.size(); ++j){
                if(this->sortMe.at(j) < this->sortMe.at(i)) {
                    swapPos(i, j);
                }
                comparisonCount++;
            }
        }
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::SELECTIONSORT)->second++;
        sortingAlgoToTime.find(SortingType::SELECTIONSORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();


        if(sortingAlgoToNumRuns.find(SortingType::SELECTIONSORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Selection sort done\n";
        }

        return this->sortMe;
    }

    vector<T> bubbleSort(){
        currentlyRunning = SortingType::BUBBLESORT;
        if(sortingAlgoToNumRuns.find(SortingType::BUBBLESORT)->second == 0){
            cout << "\n\u001b[34mBubble Sort\u001b[0m\n";
            cout << "Unsorted array: ";
            printArrayAndStats(false);
        }
        
        
        startTime = std::chrono::high_resolution_clock::now();
        for(uint i = 0; i < sortMe.size(); ++i){
            for(uint j = 1; j < (sortMe.size() - i); ++j){
                if(sortMe.at(j-1) > sortMe.at(j)) {
                    swapPos(j-1, j);
                }
                comparisonCount++;
            }
        }
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::BUBBLESORT)->second++;
        sortingAlgoToTime.find(SortingType::BUBBLESORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        
        if(sortingAlgoToNumRuns.find(SortingType::BUBBLESORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Bubble sort done\n";
        }
        

        return this->sortMe;
    }

    vector<T> insertionSort(){
        currentlyRunning = SortingType::INSERTIONSORT;
        //slightly optimized insertion sort
        // adding the key at the end in its correct position to reduce many writes
        if(sortingAlgoToNumRuns.find(SortingType::INSERTIONSORT)->second == 0){
            cout << "\n\u001b[34mInsertion Sort\u001b[0m\n";
            cout << "Unsorted array: "; 
            printArrayAndStats(false);
        }
        
        
        startTime = std::chrono::high_resolution_clock::now();
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
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::INSERTIONSORT)->second++;
        sortingAlgoToTime.find(SortingType::INSERTIONSORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        
        if(sortingAlgoToNumRuns.find(SortingType::INSERTIONSORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Insertion sort done\n";
        }
        
        return sortMe;
    }


    vector<T> mergeSort(){
        currentlyRunning = SortingType::MERGESORT;
        if(sortingAlgoToNumRuns.find(SortingType::MERGESORT)->second == 0){
            cout << "\n\u001b[34mMerge Sort\u001b[0m\n";
            cout << "Unsorted array: "; 
            printArrayAndStats(false);
        }
        
        startTime = std::chrono::high_resolution_clock::now();
        vector<T> result = mergeSortHelper(sortMe);
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::MERGESORT)->second++;
        sortingAlgoToTime.find(SortingType::MERGESORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        
        sortMe = result;
        if(sortingAlgoToNumRuns.find(SortingType::MERGESORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Merge sort done\n";
        }
        
        return sortMe;
    }

    vector<T> optimizedMergeSort(){
        currentlyRunning = SortingType::OPTIMIZEDMERGESORT;
        if(sortingAlgoToNumRuns.find(SortingType::OPTIMIZEDMERGESORT)->second == 0){
            cout << "\n\u001b[34mOptimized Merge Sort\u001b[0m\n";
            cout << "Unsorted array: "; 
            printArrayAndStats(false);
        }
        
        startTime = std::chrono::high_resolution_clock::now();
        optimizedMergeSortHelper(0, sortMe.size()-1);
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::OPTIMIZEDMERGESORT)->second++;
        sortingAlgoToTime.find(SortingType::OPTIMIZEDMERGESORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();

        if(sortingAlgoToNumRuns.find(SortingType::OPTIMIZEDMERGESORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Optimized merge sort done\n";
        }
        return sortMe;
    }

    vector<T> quickSort(){
        currentlyRunning = SortingType::QUICKSORT;
        if(sortingAlgoToNumRuns.find(SortingType::QUICKSORT)->second == 0){
            cout << "\n\u001b[34mQuick Sort\u001b[0m\n";
            cout << "Unsorted array: " ;
            printArrayAndStats(false);
        }
        
        startTime = std::chrono::high_resolution_clock::now();
        quickSortHelper(0, sortMe.size()-1);
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::QUICKSORT)->second++;
        sortingAlgoToTime.find(SortingType::QUICKSORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();

        if(sortingAlgoToNumRuns.find(SortingType::QUICKSORT)->second >= sampleSize){
            cout << "Sorted array:   ";
            printArrayAndStats(true);
            cout << "Quick sort done\n";
        }
        
        return sortMe;
    }

    vector<T> heapSort(){
        //could use make_heap
        MaxHeap<T> heap(sortMe.size());  // this data structure uses extra memory (usually heapsort wont use any extra memory)
        for(T t: sortMe){
            heap.insert(t);
        }
        for(uint i = sortMe.size()-1; i >=0; --i){
            sortMe.at(i) = heap.extractMax();
        }

    }

    //This will only work with whole numbers
    vector<T> countingSort(){
        currentlyRunning = SortingType::COUNTINGSORT;
        if(sortingAlgoToNumRuns.find(SortingType::COUNTINGSORT)->second == 0){
            cout << "\n\u001b[34mCounting Sort\u001b[0m\n";
            cout << "Unsorted array: "; 
            printArrayAndStats(false);
        }
        
        
        startTime = std::chrono::high_resolution_clock::now();

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
        endTime = std::chrono::high_resolution_clock::now();

        sortingAlgoToNumRuns.find(SortingType::COUNTINGSORT)->second++;
        sortingAlgoToTime.find(SortingType::COUNTINGSORT)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        
        if(sortingAlgoToNumRuns.find(SortingType::COUNTINGSORT)->second >= sampleSize){
            cout << "Sorted array:   ";    
            printArrayAndStats(true);
            cout << "Counting sort done\n";
        }
        
        return sortMe;

    }

    vector<T> radixSort(){

    }

    vector<float> bucketSort(){
        //works only for floating point numbers uniformly distributed (0.0 - 1.0)
        vector<vector<float>> buckets(sortMe.size());
        for(float f: sortMe){
            buckets.at(sortMe.size() * f).push_back(f);
        }
        for(vector<float> v: buckets){
            std::sort(v.begin(), v.end());
            //insertionSort(); // you can also use insertion sort as it might be more effective
        }
        uint idx = 0;
        for(vector<float> v: buckets){
            for(float f : v){
                sortMe.at(idx++) = f;
            }
        }
    }


    void runAllSorting(){
       
        for(uint i = 0; i < sampleSize; ++i){
            selectionSort();
            sortMe = originalOrderArray;
        }
        //randomizeArrayOrder();
        
        for(uint i = 0; i < sampleSize; ++i){
            bubbleSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }

        for(uint i = 0; i < sampleSize; ++i){
            insertionSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }

        for(uint i = 0; i < sampleSize; ++i){
            mergeSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }

        for(uint i = 0; i < sampleSize; ++i){
            optimizedMergeSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }

        for(uint i = 0; i < sampleSize; ++i){
            quickSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }

        for(uint i = 0; i < sampleSize; ++i){
            countingSort();
            //randomizeArrayOrder();
            sortMe = originalOrderArray;
        }
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
            cout << "Comparison count: " << comparisonCount/ sortingAlgoToNumRuns.find(currentlyRunning)->second << "\n";
            cout << "Swap count:       " << swapCount/ sortingAlgoToNumRuns.find(currentlyRunning)->second << "\n";
            cout << "Memory writes:    " << memWrites/ sortingAlgoToNumRuns.find(currentlyRunning)->second << "\n";
            cout << "Number of Runs:   " << sortingAlgoToNumRuns.find(currentlyRunning)->second << "\n";
            if(currentlyRunning != SortingType::DUMMYLAST){
                long avgRuntime = sortingAlgoToTime.find(currentlyRunning)->second / sortingAlgoToNumRuns.find(currentlyRunning)->second;
                cout << "Average run time: " << avgRuntime << " ns\n";
            } 

            comparisonCount = 0;
            swapCount = 0;
            memWrites = 0;
        }

        
    }

    void worstCase(){
        for(uint i = 0; i < sortMe.size(); ++i){
            sortMe.at(i) = (sortMe.size() -1) - i; 
        }
        cout << "Worst case: ";
        printArrayAndStats(false);

    }

    void bestCase(){
        for(uint i = 0; i < sortMe.size(); ++i){
            sortMe.at(i) = i; 
        }
        cout << "Best case: ";
        printArrayAndStats(false);
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
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime; 
    unordered_map<SortingType, long> sortingAlgoToTime; //the type of sorting algorithm to the cumilive time each run in nanoseconds
    unordered_map<SortingType, uint> sortingAlgoToNumRuns;     
    enum SortingType currentlyRunning ;      
    uint sampleSize;   

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

    void init(){
        for(int i = SortingType::BASE; i != SortingType::DUMMYLAST; ++i){
            sortingAlgoToNumRuns.insert({(SortingType)i, 0});
            sortingAlgoToTime.insert({(SortingType)i, 0});
        }

        
        for(uint i = 0; i < sampleSize; ++i){
            startTime = std::chrono::high_resolution_clock::now();
            for(uint i = 0; i < originalOrderArray.size(); ++i) ;
            endTime = std::chrono::high_resolution_clock::now();

            sortingAlgoToNumRuns.find(SortingType::BASE)->second++;
            sortingAlgoToTime.find(SortingType::BASE)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        }


        
        for(uint i = 0; i < sampleSize; ++i){
            startTime = std::chrono::high_resolution_clock::now();
            for(uint i = 0; i < originalOrderArray.size()/2; ++i) ;
            endTime = std::chrono::high_resolution_clock::now();

            sortingAlgoToNumRuns.find(SortingType::BASEHALF)->second++;
            sortingAlgoToTime.find(SortingType::BASEHALF)->second += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
        }

        long avgRuntimeLinear = sortingAlgoToTime.find(SortingType::BASE)->second / sortingAlgoToNumRuns.find(SortingType::BASE)->second;
        long avgRuntimelog = sortingAlgoToTime.find(SortingType::BASEHALF)->second / sortingAlgoToNumRuns.find(SortingType::BASEHALF)->second;
        cout << "Average runtime of a liner run: " << avgRuntimeLinear << " ns\n";
        cout << "Average runtime of a log run: " << avgRuntimelog << " ns\n";


    }
};


#endif //SORTING_H