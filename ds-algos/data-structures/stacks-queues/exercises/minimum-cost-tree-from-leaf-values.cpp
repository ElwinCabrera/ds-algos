#include "../stack.h"
#include "../../../helper.h"
#include <vector>
using std::vector;
using std::min;

int mctFromLeafValues(vector<int>& arr) {
    int result = 0;
    Stack<int> st;
    
    st.push(INT_MAX);
    for(int n: arr){
        while(n >= st.top()){
            int mid = st.top();
            st.pop();
            result += mid * min(st.top(), n);
        }
        st.push(n);
    }
    while(st.size() > 2){
        int lastElem = st.top();
        st.pop();
        result += lastElem * st.top();
    }
    return result;
}

int main(int argc, char **argv){
    vector<int> randV = genRandomIntVector(5);
    printVect(randV);
    mctFromLeafValues(randV);
    return 0;
}