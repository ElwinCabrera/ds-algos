#include <queue>
#include <vector>
#include "../queue.h"
using std::priority_queue;
using std::vector;

int leastInterval(vector<char>& tasks, int n) {
    if(n == 0 || tasks.size() == 1) return tasks.size();
    sort(tasks.begin(), tasks.end());
    priority_queue<int> round;
    vector<int> lastRound;
    int count = 1;
    for(unsigned i = 1; i < tasks.size(); ++i){
        if(tasks.at(i) == tasks.at(i-1)) ++count;
        else {round.push(count);  count = 1;}
    }
    round.push(count);
    
    int overallTime = 0;
        
    while(!round.empty()){
        int coolingTime = 0;
        while(coolingTime <= n){
            if(!round.empty()) {
                if(round.top() - 1 > 0) lastRound.push_back(round.top() -1);
                round.pop();
            }
            ++overallTime;
            ++coolingTime;
            if (round.empty() && lastRound.empty()) break;
            
            
        }
        while(!lastRound.empty()) { round.push(lastRound.back()); lastRound.pop_back(); }
    }
        
    return overallTime; 
}