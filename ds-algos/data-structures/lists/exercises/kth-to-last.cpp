#include "../forward_list.h"


Node<int>* kToLast(Node<int> *head, int k){
    
    int count = 0;
    Node<int> *node_ptr = head;
    while (node_ptr){
        ++count;
        node_ptr = node_ptr->next_node;
    }
    if(k > count) return head;
    if(k <= 0) k = 1;
    count = count - k;
    node_ptr = head;
    while (count-- && node_ptr) node_ptr = node_ptr->next_node;
        
    return node_ptr;
}


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


int main(int argc, char** argv){
    
    Node<int> *list1 = new Node<int>(7);
    list1->next_node = new Node<int>(1);
    list1->next_node->next_node =  new Node<int>(4);
    list1->next_node->next_node->next_node =  new Node<int>(3);
    list1->next_node->next_node->next_node->next_node = new Node<int>(6);


    std::cout << "Printing list: ";
    printList(list1);

    Node<int> *k_to_last_node = kToLast(list1, -1);
    std::cout << "K to last node: " << k_to_last_node->data << "\n";


    delete list1->next_node->next_node->next_node->next_node;
    delete list1->next_node->next_node->next_node;
    delete list1->next_node->next_node;
    delete list1->next_node;
    delete list1;


    return 0;
}