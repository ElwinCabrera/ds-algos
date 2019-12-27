#include "../forward_list.h"
/*
list1:   0 1 3 5 9
list2:   2 4 6 7 8
merged:  0 1 2 3 4 5 6 7 8 9
*/
Node<int>* merge(Node<int> *head1, Node<int> *head2){
    if(head1 && !head2) return head1;
    if(head2 && !head1) return head2;
    Node<int> *new_head = head1;
    Node<int> *node_ptr1 = new Node<int>(-1000); // dummy node
    Node<int> *node_ptr2 = new Node<int>(-1000); // dummy node
    node_ptr1->next_node = head1;
    node_ptr2->next_node = head2;
    Node<int> *trash1 = node_ptr1;
    Node<int> *trash2 = node_ptr2;

    while(node_ptr1->next_node && node_ptr2->next_node){
        if(node_ptr2->next_node->data <= new_head->data) new_head = node_ptr2->next_node;
        if(node_ptr1->next_node->data >= node_ptr2->next_node->data){
            Node<int> *insert = node_ptr2->next_node;

            node_ptr2->next_node = insert->next_node;
            insert->next_node = node_ptr1->next_node;
            node_ptr1->next_node = insert;   
        }
        node_ptr1 = node_ptr1->next_node;
        
    }
    if(node_ptr2->next_node && !node_ptr1->next_node) node_ptr1->next_node = node_ptr2->next_node;
    
    

    delete trash1;
    delete trash2;
    return new_head;
}



/************* TESTS *****************/

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
    Node<int> *head1 = new Node<int>(0);
    head1->next_node = new Node<int>(1);
    head1->next_node->next_node = new Node<int>(3);
    head1->next_node->next_node->next_node = new Node<int>(5);
    head1->next_node->next_node->next_node->next_node = new Node<int>(9);


    Node<int> *head2 = new Node<int>(2);
    head2->next_node = new Node<int>(4);
    head2->next_node->next_node = new Node<int>(6);
    head2->next_node->next_node->next_node = new Node<int>(7);
    head2->next_node->next_node->next_node->next_node = new Node<int>(8);

    printList(head1);
    printList(head2);

     Node<int> *merged_list = merge(head1, head2);
    //printList(newh);
    std::cout << "Result: \n";
    printList(merged_list);

    
    delete head1->next_node->next_node->next_node->next_node;
    delete head1->next_node->next_node->next_node;
    delete head1->next_node->next_node;
    delete head1->next_node;
    delete head1;

    delete head2->next_node->next_node->next_node->next_node;
    delete head2->next_node->next_node->next_node;
    delete head2->next_node->next_node;
    delete head2->next_node;
    delete head2;
}