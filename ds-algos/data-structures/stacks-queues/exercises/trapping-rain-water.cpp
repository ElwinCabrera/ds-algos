#include <vector>
#include <stack>
#include "../stack.h"
using std::vector;
using std::stack;
using std::min;
class Solution {
public:
   
    int trap3(vector<int>& height){
        int ans = 0, current = 0;
        Stack<int> st;
        while(current < height.size()){
            while(!st.empty() && height.at(current) > height.at(st.top())){
                int prevTop = st.top();
                st.pop();
                if(st.empty()) break;
                int bounded_width = current - st.top() -1;
                int bounded_height = min(height.at(st.top()), height.at(current)) - height.at(prevTop);
                ans += bounded_width * bounded_height;
            }
            st.push(current++);
        }
        return ans;
        
    }

      /*
    if we are looking at two different bars 
        then the trapped rain water at a specific point depends on the smaller of the two bars
        (we would have to keep track of both max and min seen so far)

    we can try to do this in one iteration by moving the pointer of the smaller bar up one each time
    and checking if the current point is bigger than the maximum seen so far in that direction. if its not bigger then that means that water can be held there, we calculate it by subtraction the maximum seen so far in that direction by the current height of the bar.


    so

    we can use a while loop with two pointers one at begginign and one at end with a counter keeping track the maximum seen so far in either side.

    while(left < right)
        if height[left] < height[right]
            if height[left] > max_left_height
                max_left_height = height[left]
            else
                ans += max_left_height -height[left]

            left++
        else 
            if height[right] > max_right_height
                max_right_height = height[right]
            else
                ans += max_right_height -height[right]

            right--

    */
        
    int trap4(vector<int>& height) {
        
    }
};

int main(int argc, char **argv){

    vector<int> v = {0,1,0,2,1,0,1,3,2,1,2,1};
    Solution s;
    std::cout << "trap2 result :" << s.trap2(v) << "\n";
    return 0;
}