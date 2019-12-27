#include "../forward_list.h"
/*
Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL

Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

*/
Node<int>* oddEven(Node<int> *head){
    Node<int> *oddHead = head;
    Node<int> *evenHead = head->next_node;
    Node<int> *oddPtr = oddHead;
    Node<int> *evenPtr = evenHead;

    while(oddPtr && evenPtr){
        if(oddPtr->next_node) oddPtr->next_node = oddPtr->next_node->next_node;
        if(evenPtr->next_node) evenPtr->next_node = evenPtr->next_node->next_node;

        oddPtr = oddPtr->next_node;
        evenPtr = evenPtr->next_node;
    }
    oddPtr = oddHead;
    while(oddPtr->next_node) oddPtr = oddPtr->next_node;
    oddPtr->next_node = evenHead;
    return oddHead;
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
    Node<int> *head = new Node<int>(2);
    head->next_node = new Node<int>(1);
    head->next_node->next_node = new Node<int>(3);
    head->next_node->next_node->next_node = new Node<int>(5);
    head->next_node->next_node->next_node->next_node = new Node<int>(6);
    head->next_node->next_node->next_node->next_node->next_node = new Node<int>(4);
    head->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(7);

    printList(head);
    Node<int> *result = oddEven(head);
    printList(head);

    delete head->next_node->next_node->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node->next_node;
    delete head->next_node->next_node->next_node;
    delete head->next_node->next_node;
    delete head->next_node;
    delete head;
}