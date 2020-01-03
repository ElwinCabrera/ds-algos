#include "../stack.h"
#include <vector>
using std::vector;
using std::max;
using std::min;
class Solution{
public:
    int maximalRectangle1(vector<vector<char>>& matrix) {
        int rectLimitStartX = 0;
        int rectLimitEndX = 0;
        int maxAreaSoFar = 0;
        int localMaxArea = 0;
        for(unsigned r = 0; r < matrix.size(); ++r){
            for(unsigned c = 0; c < matrix.at(r).size(); ++c){
                if(matrix.at(r).at(c) == '1'){
                    rectLimitStartX = c;
                    rectLimitEndX = c;
                    localMaxArea = 0;
                    int row = r;
                    int col = c;
                    while(col < matrix.at(r).size() && matrix.at(row).at(col++) == '1') ++rectLimitEndX;
                    
                    
                    while(row < matrix.size()){
                        col = c;
                        while(col < matrix.at(r).size() && matrix.at(row).at(col) == '1' && col < rectLimitEndX) ++col;
                        if(col == rectLimitEndX){
                            localMaxArea += rectLimitEndX - rectLimitStartX;
                        } else break;
                        row++;
                    }
                    maxAreaSoFar = max(localMaxArea, maxAreaSoFar);
                    
                }
            }
        }
        return maxAreaSoFar;
    }

    int maximalRectangle2(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int maxArea =0 ;
        vector<vector<int>> dp(matrix.size());


        for(int r = 0; r < matrix.size(); ++r){
            for(int c = 0; c < matrix.at(r).size(); ++c){
                if(matrix.at(r).at(c) == '1'){
                    int widthSoFar = (c==0) ? 1:dp.at(r).at(c-1) +1;
                    dp.at(r).push_back(widthSoFar);
                    
                    for(int row = r; row >=0; --row){
                        widthSoFar = min(widthSoFar, dp.at(row).at(c));
                        maxArea = max(maxArea, widthSoFar * (r - row +1));
                    }
                } else dp.at(r).push_back(0);
            }
        }
        return maxArea;

        
    }

    int maximalRectangle3(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int maxArea =0 ;
        vector<int> dp(matrix.at(0).size(),0);


        for(int r = 0; r < matrix.size(); ++r){
            for(int c = 0; c < matrix.at(r).size(); ++c){
                dp.at(c) = (matrix.at(r).at(c) == '1') ? dp.at(c) +1:0;
            }
            maxArea = max(maxArea, largestRectangleArea(dp));
        }
        return maxArea;

    }
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        if(heights.size() ==1 ) return heights.at(0);
        
        Stack<int> st;
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
    Solution s;
    vector<vector<char>> matrix = {
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    };
    std::cout << "Maximal Rectangle: " << s.maximalRectangle3(matrix) << "\n";
    return 0;
}