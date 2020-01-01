#include "../stack.h"
#include <vector>
using std::vector;

/*
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,1,2,1,1].

Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,4,6].
*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation*/
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;
 
     // Return the single integer that this NestedInteger holds, if it holds a single integer
     // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;
    
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
 };
 
vector<int> flatten1(vector<NestedInteger> &nestedList){
    vector<int> flattenList;
    Stack<vector<NestedInteger>> st;
    Stack<int> continueIdxs;

    continueIdxs.push(0);
    st.push(nestedList);
    while(!st.empty()){
        vector<NestedInteger> currList = st.top();
        
        int idx = continueIdxs.top();
        continueIdxs.pop();
        if(idx >= currList.size()) {st.pop(); continue;}
        while(idx < currList.size()){
            if(currList.at(idx).isInteger()) flattenList.push_back(currList.at(idx).getInteger());
            else  {
                continueIdxs.push(idx+1);
                st.push(currList.at(idx).getList());
                continueIdxs.push(0);
                break;
            }
            if(idx >= currList.size()-1) st.pop();
            ++idx;
        }
    }

    return flattenList;
}



void flatten2(vector<int> &flattenList,vector<NestedInteger> &nestedList, int currIdx){
    if(currIdx >= nestedList.size()) return;
    if(nestedList.at(currIdx).isInteger()) flattenList.push_back(nestedList.at(currIdx).getInteger());
    else flatten2(flattenList, nestedList.at(currIdx).getList(), 0);
    flatten2(flattenList, nestedList, currIdx+1);
}

 void flatten3(vector<int> &flattenList, vector<NestedInteger> &nestedList) {
    
    for(unsigned i =  0; i < nestedList.size(); ++i) {
        if(nestedList.at(i).isInteger()) flattenList.push_back(nestedList.at(i).getInteger());
        else flatten3(flattenList, nestedList.at(i).getList());
    }
    
}