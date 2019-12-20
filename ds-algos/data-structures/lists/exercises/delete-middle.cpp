#include "../forward_list.h"

void deleteNode(Node<int> *removeMe){
    removeMe->data = removeMe->next_node->data;
    Node<int> *trash = removeMe->next_node;
    removeMe->next_node = trash->next_node;
    delete trash;
    trash = nullptr;
}