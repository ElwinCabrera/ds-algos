#include "../stack.h"
#include <unordered_set>
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_set;
using std::unordered_map;


/*
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"

Example 2:

Input: "cbacdcbc"
Output: "acdb"


*/
class Solution {
public:
    string removeDuplicateLetters(string &s) {
        string result = "";
        if(s.empty()) return result;
        Stack<char> st;
        unordered_set<char> seen;
        unordered_map<char, int> charToIdx;
        
        for(unsigned i = 0; i < s.size(); ++i) {
            auto it = charToIdx.find(s.at(i));
            if(it == charToIdx.end()) charToIdx.insert({s.at(i),i});
            else it->second = i;
        }
        
        for(unsigned i = 0; i < s.size(); ++i){
            char c = s.at(i);
            
            if(seen.find(c) == seen.end()){
                while(!st.empty() && c < st.top() && charToIdx.find(st.top())->second > i){
                    
                    seen.erase(st.top());
                    st.pop();
                }
                seen.insert(c);
                st.push(c);
            }
            
        }
        while(!st.empty()) {result.insert(result.begin(), st.top()); st.pop();}
        return result;
    }
};