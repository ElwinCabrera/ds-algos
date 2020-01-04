#include <deque>
#include <vector>
using std::deque;
using std::vector;
using std::min;

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
         if(A.empty()) return -1;
        vector<long> summationVect(A.size()+1, 0);
        
        for(int i = 0; i < A.size(); ++i) summationVect.at(i+1) = summationVect.at(i) + (long) A.at(i);
        
        deque<int> dq;
        int result  = A.size()+1;
        for(int y = 0; y < summationVect.size(); ++y){
            
            while(!dq.empty() && summationVect.at(y) <= summationVect.at(dq.back())) dq.pop_back();
            
            while(!dq.empty() && summationVect.at(y) - summationVect.at(dq.front()) >= K){
                result = min(result, y - dq.front());
                dq.pop_front();
            }
            dq.push_back(y);
        }
        
        return (result == A.size()+1) ? -1:result;
    }
};