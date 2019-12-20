#include "../forward_list.h"
/*
Source: https://leetcode.com/problems/reverse-nodes-in-k-group/

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Note:

    Only constant extra memory is allowed.
    You may not alter the values in the list's nodes, only nodes itself may be changed.


*/

Node<int>* reverseList(Node<int> *begin, int num);

Node<int>* reverseKGroup(Node<int>* head, int k) {
    if(k == 0 || k == 1 || !head) return head;
    
    int group_count = 1;
    Node<int> *ptr = head;
    bool first_group = true;
    Node<int> *prev_sub_list_tail_ptr = nullptr;


    while(ptr && ptr->next_node ){
        if(group_count + 1 == k ){
            Node<int> *hold = ptr->next_node;
            for(unsigned i = group_count; i < k; ++i) hold = hold->next_node;
            Node<int> *sub_list_head ;
            
            if(first_group) {
                sub_list_head = reverseList(head, k);
                head = sub_list_head;
                first_group = false;
            } else sub_list_head = reverseList(prev_sub_list_tail_ptr->next_node, k);

            if(sub_list_head) {
                Node<int> *sub_list_ptr_end = sub_list_head;
                while(sub_list_ptr_end->next_node) sub_list_ptr_end = sub_list_ptr_end->next_node;
                if(prev_sub_list_tail_ptr) prev_sub_list_tail_ptr->next_node = sub_list_head;
                sub_list_ptr_end->next_node = hold;
                prev_sub_list_tail_ptr = sub_list_ptr_end;
                ptr = hold;
            }
            group_count = 1;
        } else {
            ++group_count;
            ptr = ptr->next_node;
        }
        
    }

    return head;
}

Node<int>* reverseList(Node<int> *begin, int num){
    Node<int> *before_start = nullptr;
    Node<int> *after_begin = begin->next_node;

    while(begin && num--){
        begin->next_node = before_start;
        before_start = begin;
        begin = after_begin;
        if(after_begin ) after_begin = after_begin->next_node;
    }
    return before_start;
}







/************** Test **************/
void printList(Node<int> *ptr){
    //Node<int> *ptr = list;
    std::cout <<"List contains: [";
    while(ptr){
        if(ptr->next_node) std::cout << ptr->data << "->";
        else std::cout << ptr->data;
        ptr = ptr->next_node;
    }
    std::cout<<"]\n";
}


int main(int argc, char **argv){
    
    Node<int> *list = new Node<int>(1);
    list->next_node = new Node<int>(2);
    list->next_node->next_node = new Node<int>(3);
    list->next_node->next_node->next_node = new Node<int>(4);
    list->next_node->next_node->next_node->next_node = new Node<int>(5);

    printList(list);
    list = reverseKGroup(list, 2);
    printList(list);

    delete list->next_node->next_node->next_node->next_node;
    delete list->next_node->next_node->next_node;
    delete list->next_node->next_node;
    delete list->next_node;
    delete list;

  
}