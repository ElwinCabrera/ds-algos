#include "../stack.h"

/*
Implement the following operations of a queue using stacks.

    push(x) -- Push element x to the back of queue.
    pop() -- Removes the element from in front of queue.
    peek() -- Get the front element.
    empty() -- Return whether the queue is empty.

Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);  
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false

Notes:

    You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
    Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
    You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).


*/
class MyQueue {
private:
    Stack<int> st;
    Stack<int> reverseSt;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        
        if(st.empty()) {
            while(!reverseSt.empty()) { st.push(reverseSt.top()); reverseSt.pop(); }
            st.push(x);
            while(!st.empty()) { reverseSt.push(st.top()); st.pop(); }
        } else if (reverseSt.empty()){
            while(!st.empty()) { reverseSt.push(st.top()); st.pop(); }
            reverseSt.push(x);
            while(!reverseSt.empty()) { st.push(reverseSt.top()); reverseSt.pop(); }
        }
        
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int result ;
        if(st.empty()){
            result = reverseSt.top();
            reverseSt.pop();
        } else {
            result = st.top();
            st.pop();
        }
        return result;
    }
    
    /** Get the front element. */
    int peek() {
        return (st.empty()) ? reverseSt.top():st.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return (st.empty()) ? reverseSt.empty():st.empty();
    }
};