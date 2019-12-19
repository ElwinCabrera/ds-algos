#include<stack>
#include "../forward_list.h"
using std::stack;

bool isPalindrome(Node<int> *head){
    stack<int> st;
    Node<int> *ptr = head;
    while(ptr) {
        st.push(ptr->data);
        ptr = ptr->next_node;
    }
    ptr = head;
    while(!st.empty() && ptr){
        if(st.top() != ptr->data) return false;
        st.pop();
        ptr = ptr->next_node;
    }
    return true;
}