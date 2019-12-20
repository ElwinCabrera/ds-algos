#include "../list.h"
#include<vector>
using std::vector;

void reverseList1(Node<int> *head){
    vector<int> v;
    Node<int> *head_ptr = head;
    while(head_ptr){
        v.push_back(head_ptr->data);
        head_ptr = head_ptr->next_node;
    }
    head_ptr = head;
    for(unsigned i = v.size()-1; i >= 0; ++i){
        head_ptr->data = v.at(i);
        head_ptr = head_ptr->next_node;
    }
}

void reverseList2(Node<int> *head){
    Node<int> *before_begin = nullptr;
    Node<int> *begin = head;
    Node<int> *after_begin = head->next_node;

    while(begin ){
        begin->next_node = before_begin;
        before_begin = begin;
        begin = after_begin;
        if(after_begin ) after_begin = after_begin->next_node;
    }
}