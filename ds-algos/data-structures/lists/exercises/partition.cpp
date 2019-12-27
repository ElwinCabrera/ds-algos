#include "../forward_list.h"

Node<int>* partition(Node<int> *head, int x){
    if(head == nullptr) return head;

    Node<int> *lessThanX = nullptr;
    Node<int> *graterOrEqX = nullptr;

    Node<int> *lessThanX_ptr = nullptr;
    Node<int> *graterOrEqX_ptr = nullptr;

    Node<int> *node_ptr = head;
    while(node_ptr){
        Node<int> *hold = node_ptr->next_node;
        if(node_ptr->data < x){
            if(!lessThanX) {
                lessThanX = node_ptr;
                lessThanX_ptr = lessThanX;
            } else {
                lessThanX_ptr->next_node = node_ptr;
                lessThanX_ptr = lessThanX_ptr->next_node;
            }
            
        } else {
            if(!graterOrEqX) {
                graterOrEqX = node_ptr;
                graterOrEqX_ptr = graterOrEqX;
            } else {
                graterOrEqX_ptr->next_node = node_ptr;
                graterOrEqX_ptr = graterOrEqX_ptr->next_node;
            }
            
        }
        node_ptr->next_node = nullptr;
        node_ptr = hold;
    } 

    lessThanX_ptr->next_node = graterOrEqX;
    return lessThanX;
}

/************ TESTS **************/
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
    //Input: 2->1->3->5->6->4->7->NULL
    Node<int> *head = new Node<int>(3);
    head->next_node = new Node<int>(5);
    head->next_node->next_node = new Node<int>(8);
    head->next_node->next_node->next_node = new Node<int>(5);
    head->next_node->next_node->next_node->next_node = new Node<int>(10);
    head->next_node->next_node->next_node->next_node->next_node = new Node<int>(2);
    head->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(1);

    printList(head);
    Node<int> *result = partition(head, 5);
    head = result;
    printList(result);

    delete head->next_node->next_node->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node;
    delete head->next_node->next_node;
    delete head->next_node;
    delete head;
}