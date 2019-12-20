#include "../forward_list.h"

Node<int>* addTwoNumbers(Node<int> *l1, Node<int> *l2){
    Node<int> *result_list = new Node<int>();
    Node<int> *result_list_ptr = result_list;
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
        result_list_ptr->next_node = new_node;

        result_list_ptr = result_list_ptr->next_node;
        ptr1 = ptr1->next_node;
        ptr2 = ptr2->next_node;       
    }

    while(ptr1) {
        result_list_ptr->next_node = new Node<int>(ptr1->data);;
        result_list_ptr = result_list_ptr->next_node;
        ptr1 = ptr1->next_node;
    }

    while(ptr2) {
        result_list_ptr->next_node = new Node<int>(ptr2->data);
        result_list_ptr= result_list_ptr->next_node;
        ptr2 = ptr2->next_node;
    }

    return result_list;

}


/******** TESTS ***************/
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
    list1->next_node->next_node = new Node<int>(6);

    Node<int> *list2 = new Node<int>(5);
    list2->next_node = new Node<int>(9);
    list2->next_node->next_node = new Node<int>(2);

    std::cout << "Printing list1: ";
    printList(list1);
    std::cout << "Printing list2: ";
    printList(list2); 

    Node<int> *sumList = addTwoNumbers(list1, list2);
    std::cout << "Printing sum list: ";
    printList(sumList); 

    delete list1->next_node->next_node;
    delete list1->next_node;
    delete list1;

    delete list2->next_node->next_node;
    delete list2->next_node;
    delete list2;

    delete sumList->next_node->next_node->next_node;
    delete sumList->next_node->next_node;
    delete sumList->next_node;
    delete sumList;

    return 0;
}