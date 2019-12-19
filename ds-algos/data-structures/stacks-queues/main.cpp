#include "stack.h"

int main(int argc , char **argv){

    Stack<int> s;
    s.push(11);
    s.push(12);
    s.push(13);
    s.push(14);
    s.push(15);

    std::cout << s<<"\n";
    s.pop();
    std::cout << s<<"\n";
    return 0;
}