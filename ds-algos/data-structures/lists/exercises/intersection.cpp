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
    Node<int> *intersecting_node = list1->next_node->next_node->next_node->next_node;

    Node<int> *list2 = new Node<int>(5);
    list2->next_node = new Node<int>(9);
    list2->next_node->next_node = intersecting_node;
    list2->next_node->next_node->next_node  = new Node<int>(10);
    list2->next_node->next_node->next_node->next_node  = new Node<int>(13);
    list2->next_node->next_node->next_node->next_node->next_node  = new Node<int>(11);

    


    std::cout << "Printing list1: ";
    printList(list1);
    std::cout << "Printing list2: ";
    printList(list2); 

    Node<int> *int_node = intersection(list1, list2);
    bool tst = int_node == intersecting_node;
    std::cout << "found intersectin node = " << tst << "\n";
    std::cout << "Printing from intersectin node: ";
    printList(int_node);


    delete list1->next_node->next_node;
    delete list1->next_node;
    delete list1;

    delete list2->next_node->next_node;
    delete list2->next_node;
    delete list2;

    //Whatever there is definitely memory leaks here

    return 0;
}