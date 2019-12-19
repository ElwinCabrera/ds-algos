#include "../forward_list.h"

Node<int>* addTwoNumbers(Node<int> *l1, Node<int> *l2){
    Node<int> *result_list = new Node<int>();
    Node<int> *ptr1 = l1;
    Node<int> *ptr2 = l2;
    
    int carry = 0;
    while(ptr1 && ptr2){
        Node<int> *new_node = new Node<int>();
        int sum_node_data = ptr1->data + ptr2->data + carry;
        if(sum_node_data > 9){
            carry = sum_node_data /10;
            sum_node_data = sum_node_data %10;
        } 
        new_node->data = sum_node_data;
        result_list->next_node = new_node;

        result_list = result_list->next_node;
        ptr1 = ptr1->next_node;
        ptr2 = ptr2->next_node;       
    }

    while(ptr1) {
        result_list->next_node = new Node<int>(ptr1->data);;
        result_list = result_list->next_node;
        ptr1 = ptr1->next_node;
    }

    while(ptr2) {
        result_list->next_node = new Node<int>(ptr2->data);
        result_list = result_list->next_node;
        ptr2 = ptr2->next_node;
    }

    return result_list;

}