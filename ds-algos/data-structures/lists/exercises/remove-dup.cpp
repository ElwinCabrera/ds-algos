#include "../forward_list.h"
#include <unordered_set>
void removeDups1(Node<int> *head){
    Node<int> *node_ptr = head;
    std::unordered_set<int> set;
    set.insert(node_ptr->data);
    while(node_ptr->next_node){
        if(set.find(node_ptr->next_node->data) != set.end()){
            Node<int> *trash = node_ptr->next_node;
            node_ptr->next_node = trash->next_node;
            delete trash;
            trash = nullptr; 
        } else {
            set.insert(node_ptr->next_node->data);
            node_ptr = node_ptr->next_node;
        }
    }
}


void removeDups2(Node<int> *head){
    Node<int> *node_ptr = head;
    while(node_ptr){
        Node<int> *ptr2 = node_ptr;
        while(ptr2->next_node){
            if(ptr2->next_node->data == node_ptr->data){
                Node<int> *trash = ptr2->next_node;
                ptr2->next_node = trash->next_node;
                delete trash;
                trash = nullptr;
            } else ptr2 = ptr2->next_node;
        }
        node_ptr = node_ptr->next_node;
    }
}


/***************** TESTING *************************/

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

    Node<int> *head = new Node<int>(1);
    head->next_node = new Node<int>(2);
    head->next_node->next_node = new Node<int>(3);
    head->next_node->next_node->next_node = new Node<int>(1);
    head->next_node->next_node->next_node->next_node = new Node<int>(1);
    head->next_node->next_node->next_node->next_node->next_node = new Node<int>(3);
    head->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(4);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(2);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(2);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(5);
    
    printList(head);
    std::cout << "After the removal of duplicates\n";
    removeDups2(head);
    printList(head);

    // The new list should be different so not deleting here thus memory leak (lazy to make a function to do it, got lots to do); 

    return 0;
}