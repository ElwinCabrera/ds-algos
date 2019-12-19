//#include <cmath> // abs
#include "../forward_list.h"

Node<int>* intersection(Node<int> *l1, Node<int> *l2){
    if(!l1 || !l2) return nullptr;
    int l1_len = 0;
    int l2_len = 0; 
    Node<int> *ptr1 = l1;
    Node<int> *ptr2 = l2;

    while(ptr1) { ++l1_len; ptr1 = ptr1->next_node;}
    while(ptr2) { ++l2_len; ptr2 = ptr2->next_node;}
    unsigned diff = std::abs(l1_len - l2_len);
    ptr1 = l1;
    ptr2 = l2;
    if(l1_len > l2_len) while(diff--) ptr1 = ptr1->next_node;
    else if(l2_len > l1_len) while(diff--) ptr2 = ptr2->next_node;

    while(ptr1 && ptr2){
        if(ptr1 == ptr2) return ptr1;
        ptr1 = ptr1->next_node;
        ptr2 = ptr2->next_node;
    }
    return nullptr;
}