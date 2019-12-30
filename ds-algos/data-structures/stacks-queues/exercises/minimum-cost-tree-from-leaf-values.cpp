#include "../stack.h"
#include "../../../helper.h"
#include <vector>
using std::vector;

int mctFromLeafValues(vector<int>& arr) {
    
    return 0; 
}

int main(int argc, char **argv){
    vector<int> randV = genRandomIntVector(5);
    printVect(randV);
    mctFromLeafValues(randV);
    return 0;
}