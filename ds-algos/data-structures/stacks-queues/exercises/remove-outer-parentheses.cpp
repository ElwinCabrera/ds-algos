#include "../stack.h"
#include <string>
using std::string;
/*
A valid parentheses string is either empty (""), "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.  For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.

A valid parentheses string S is primitive if it is nonempty, and there does not exist a way to split it into S = A+B, with A and B nonempty valid parentheses strings.

Given a valid parentheses string S, consider its primitive decomposition: S = P_1 + P_2 + ... + P_k, where P_i are primitive valid parentheses strings.

Return S after removing the outermost parentheses of every primitive string in the primitive decomposition of S.

 

Example 1:

Input: "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:

Input: "(()())(())(()(()))"
Output: "()()()()(())"
Explanation: 
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:

Input: "()()"
Output: ""
Explanation: 
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

 

Note:

    S.length <= 10000
    S[i] is "(" or ")"
    S is a valid parentheses string

*/
string removeOuterParentheses1(string &s){
    if(s.empty()) return s;
    Stack<char> st;
    string result = "";
    int startIdx = 0;
    for(int i= 0; i < s.size(); ++i){
        if(s.at(i) == '(') st.push(s.at(i));
        if(s.at(i) == ')') st.pop();
        
        if(st.empty()){
            result += s.substr(startIdx+1, i - startIdx-1);
            startIdx = i+1;
        }
    }
        
    return result;
}

string removeOuterParentheses2(string &s){
    if(s.empty()) return s;
    string result = "";
    int opened = 0;
    for(char c: s){
      if(c == '(' && opened++ > 0) result += c;
      if(c == ')' && opened-- > 1) result += c;
    }
        
    return result;
}




int main(int argc, char **argv){
    string s1 = "(()())(())"; // return "()()()".
    string s2 = "(()())(())(()(()))"; // return "()()()()(())".
    string s3 = "()()"; // return "".

    std::cout << "s1: " << s1 <<", Ans: '()()()'\n";
    std::cout << "s2: " << s2 <<", Ans: '()()()()(())'\n";
    std::cout << "s3: " << s3 <<", Ans: ''\n\n";

    string ansS1 = removeOuterParentheses1(s1);
    std::cout << "result s1: " << ansS1 << "\n";

    string ansS2 = removeOuterParentheses1(s2);
    std::cout << "result s2: " << ansS2 << "\n";

    string ansS3 = removeOuterParentheses1(s3);
    std::cout << "result s3: " << ansS3 << "\n";
    return 0;
}
