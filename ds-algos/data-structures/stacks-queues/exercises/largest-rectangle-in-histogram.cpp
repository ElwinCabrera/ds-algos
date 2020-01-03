#include "../stack.h"
#include <stack>
#include <vector>
using std::vector;
using std::max;
using std::min;
using std::stack;


class Solution {
public:
    int largestRectangleArea1(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size() ==1 ) return heights.at(0);
        
        int maxArea = 0; 
        for(int i = 0; i < heights.size(); ++i){
            int minHeight = INT_MAX;
            for(int j = i; j < heights.size(); ++j){
                minHeight = min(minHeight, heights.at(j));
                maxArea = max(maxArea, minHeight * (j - i +1));
            }
        }
        return maxArea;
    }

    int largestRectangleArea2(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size() ==1 ) return heights.at(0);
    
        return calculateArea(heights, 0, heights.size()-1);
    }

    int calculateArea(vector<int> &heights, int start, int end){
        if(start > end || end < start) return 0;
        int minIdx = start;
        int i = start;
        while(i <= end) {
            if(heights.at(minIdx) >= heights.at(i)) minIdx = i;
            ++i;
        }
        int maxAreaHere  = heights.at(minIdx) * (end-start+1);
        int maxLeftSide = calculateArea(heights, start, minIdx-1);
        int maxRightSide = calculateArea(heights, minIdx+1, end);
        
        return max(maxAreaHere, max(maxLeftSide, maxRightSide));
    }

     int largestRectangleArea3(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size() ==1 ) return heights.at(0);
        
        stack<int> st;
        st.push(-1);
        int maxArea = 0; 
        for(int i = 0; i < heights.size(); ++i){
            
            while(st.top() != -1 && heights.at(i) <= heights.at(st.top())){
                int lastIdx = st.top();
                st.pop();
                int localArea = heights.at(lastIdx) * (i - st.top() -1);
                maxArea = max(localArea, maxArea);
            }
            st.push(i);
            
        }
        while(st.top() != -1){
            int lastIdx = st.top();
            st.pop();
            maxArea = max(maxArea, heights.at(lastIdx) * ((int)heights.size() - st.top() - 1));
        }
        return maxArea;
    }

};




int main(int argc, char **argv){

    vector<int> v = {1,1,1,1,1,1};
    Solution s;
    std::cout<<"Largest Rectangle: " << s.largestRectangleArea3(v) << "\n";
    return 0;
}