#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
using std::stack;
/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/

string decodeString(string &s){
    stack<string> st;
    string token = "";
    for(char c : s){
        if(c == '[') {
            st.push(token); 
            st.push("[");
            token = "";
        } else if(c == ']'){
            while (st.top() != "[") {token.insert(0, st.top()); st.pop();}
            st.pop();
            stringstream ss(st.top()); 
            st.pop();
            int count;
            ss >> count;
            string res = "";
            while(count--) res += token;
            st.push(res);
            token = "";

        } else {
            if(!token.empty() && token.at(token.size()-1) >= 'a' && token.at(token.size()-1) <= 'z' && c >= '0' && c <= '9') { 
                st.push(token); 
                token = "";
            }
            token += c;
        }
        
        
    }
    if(!token.empty()) st.push(token);
    string result = "";
    while(!st.empty()){ result.insert(0, st.top()); st.pop();} 
    return result;
}


int main(int argc, char **argv){
    string s1 = "3[a]2[bc]"; // return "aaabcbc".
    string s2 = "3[a2[c]]"; // return "accaccacc".
    string s3 = "2[abc]3[cd]ef"; // return "abcabccdcdcdef".

    std::cout << "s1: " << s1 <<", Ans: aaabcbc\n";
    std::cout << "s2: " << s2 <<", Ans: accaccacc\n";
    std::cout << "s3: " << s3 <<", Ans: abcabccdcdcdef\n";

    string decodedS1 = decodeString(s1);
    std::cout << "decoded s1: " << decodedS1 << "\n";

    string decodedS2 = decodeString(s2);
    std::cout << "decoded s2: " << decodedS2 << "\n";

    string decodedS3 = decodeString(s3);
    std::cout << "decoded s3: " << decodedS3 << "\n";
    return 0;
}
