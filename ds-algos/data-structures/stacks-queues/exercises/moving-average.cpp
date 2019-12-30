#include "../queue.h"


/*
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Example:

MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
*/
class MovingAverage {
private:
    int limit;
    Queue<int> window;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        limit =size;
    }
    
    double next(int val) {
        if(window.size() >= limit) window.pop();
        window.push(val);
        int qSize = window.size();
        int sum = 0;
        while(qSize-- && !window.empty()){
            int front = window.front();
            sum += front;
            window.pop();
            window.push(front);
        }
        return (double) sum / window.size();
    }
};
