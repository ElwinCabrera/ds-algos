#include "../forward_list.h"

Node<int>* splitHalf(Node<int> *head){
    Node<int> *slow = head;
    Node<int> *fast = head->next_node;
    while(fast && fast->next_node){
        slow = slow->next_node;
        fast = fast->next_node->next_node;
    }
    Node<int> *otherHalf = slow->next_node;
    slow->next_node = nullptr;
    return otherHalf;
}

Node<int>* mergeSortedList(Node<int> *head1, Node<int> *head2){
    if(head1 && !head2) return head1;
    if(head2 && !head1) return head2;
    
    Node<int> *node_ptr1 = new Node<int>(-1000); // dummy node
    Node<int> *node_ptr2 = new Node<int>(-1000); // dummy node
    node_ptr1->next_node = head1;
    node_ptr2->next_node = head2;
    Node<int> *trash1 = node_ptr1;
    Node<int> *trash2 = node_ptr2;

    while(node_ptr1->next_node && node_ptr2->next_node){
        if(node_ptr1->next_node->data >= node_ptr2->next_node->data){
            Node<int> *insert = node_ptr2->next_node;

            node_ptr2->next_node = insert->next_node;
            insert->next_node = node_ptr1->next_node;
            node_ptr1->next_node = insert;   
        }
        node_ptr1 = node_ptr1->next_node;
        
    }
    if(node_ptr2->next_node && !node_ptr1->next_node) node_ptr1->next_node = node_ptr2->next_node;
    
    
    Node<int> *result_head = trash1->next_node;
    delete trash1;
    delete trash2;
    return result_head;
}

Node<int>* mergeSort(Node<int> *head){
    if(!head || !head->next_node) return head;

    Node<int> *a = head;
    Node<int> *b = splitHalf(head);

    Node<int> *sortedA = mergeSort(a);
    Node<int> *sortedB = mergeSort(b);

    head = mergeSortedList(sortedA, sortedB);
    return head;

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
    Node<int> *head1 = new Node<int>(40);
    head1->next_node = new Node<int>(20);
    head1->next_node->next_node = new Node<int>(60);
    head1->next_node->next_node->next_node = new Node<int>(10);
    head1->next_node->next_node->next_node->next_node = new Node<int>(50);
    head1->next_node->next_node->next_node->next_node->next_node = new Node<int>(30);

    printList(head1);

    Node<int> *sorted = mergeSort(head1);
    std::cout<<"Result:\n";
    printList(sorted);

    delete sorted->next_node->next_node->next_node->next_node->next_node;
    delete sorted->next_node->next_node->next_node->next_node;
    delete sorted->next_node->next_node->next_node;
    delete sorted->next_node->next_node;
    delete sorted->next_node;
    delete sorted;
}
