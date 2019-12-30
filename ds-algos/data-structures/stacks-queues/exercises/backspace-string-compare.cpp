#include "../stack.h"
#include <string>
using std::string;

/*
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".

Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".

Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".

Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".

Note:

    1 <= S.length <= 200
    1 <= T.length <= 200
    S and T only contain lowercase letters and '#' characters.

Follow up:

    Can you solve it in O(N) time and O(1) space?
*/
 bool backspaceCompare(string S, string T) {
    Stack<char> stack;
    for(char c: S){
        if(c == '#' && !stack.empty()) stack.pop();
        else if(c != '#') stack.push(c);
    }
    
    
    string compareStr = "";
    while(!stack.empty()) { compareStr += stack.top(); stack.pop(); }
    //at this point the string 'compareStr' will be backwords
    
    for(char c: T){
        if(c == '#' && !stack.empty()) stack.pop();
        else if(c != '#') stack.push(c);
    }
    
    if(compareStr.size() != stack.size()) return false;
    for(char c: compareStr){
        if(stack.top() != c) return false;
        stack.pop();
    }
    return true;
}