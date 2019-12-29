#include "../stack.h"
#include <string>
using std::string;
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


string decodeString(string s){
    
}


int main(int argc, char **argv){
    string s1 = "3[a]2[bc]"; // return "aaabcbc".
    string s2 = "3[a2[c]]"; // return "accaccacc".
    string s3 = "2[abc]3[cd]ef"; // return "abcabccdcdcdef".

    std::cout << "s1: " << s1 <<", Ans: aaabcbc\n";
    std::cout << "s2: " << s2 <<", Ans: aaccaccacc\n";
    std::cout << "s3: " << s3 <<", Ans: abcabccdcdcdef\n";

    string decodedS1 = decodeString(s1);
    std::cout << "decoded s1: " << decodedS1 << "\n";

    string decodedS2 = decodeString(s2);
    std::cout << "decoded s2: " << decodedS2 << "\n";

    string decodedS3 = decodeString(s3);
    std::cout << "decoded s3: " << decodedS3 << "\n";
    return 0;
}
