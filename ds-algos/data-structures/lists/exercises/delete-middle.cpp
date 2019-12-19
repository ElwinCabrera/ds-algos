#include "../forward_list.h"

void deleteNode(Node<int> *head, Node<int> *deleteMe){
    while (head->next_node != deleteMe) head = head->next_node;
    head->next_node = deleteMe->next_node;
    delete deleteMe;
    deleteMe = nullptr;
}