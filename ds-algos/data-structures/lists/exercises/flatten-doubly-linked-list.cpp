#include <iostream>
template <class Type> 
class Node {
public:
    Node(): data(0), next_node(0), prev_node(0) {}
    Node(const Type &value, Node<Type> *ptr= nullptr): data(value), next_node(0) {}
    
    Type  data;
    Node<Type> *next_node;
    Node<Type> *prev_node;
    Node<Type> *child_node;

};


Node<int> *recurse(Node<int> *head){
    if(!head) return head;
    Node<int> *node_ptr = head;
    while(node_ptr ){
        Node<int> *hold_next = nullptr;
        if(node_ptr->child_node){
            hold_next = node_ptr->next_node;
            Node<int> *child_tail = recurse(node_ptr->child_node);
            node_ptr->next_node = node_ptr->child_node;
            node_ptr->child_node->prev_node = node_ptr;
            child_tail->next_node = hold_next;
            if(hold_next) hold_next->prev_node = child_tail;
            node_ptr->child_node = nullptr;   
        }
        if(!node_ptr->next_node) break;
        node_ptr = node_ptr->next_node; 
    }

    return node_ptr;
}

Node<int> *flatten(Node<int> *head){
    if(!head) return head;
    recurse(head);
    return head;
}



/************ TESTS **************/
void printList(Node<int> *ptr, bool childNode){
    //Node<int> *ptr = list;
    if(!childNode) std::cout <<"List contains: [";
    else std::cout << "[";
    while(ptr){
        if(ptr->next_node) std::cout << ptr->data << "->";
        else std::cout << ptr->data;
        if(ptr->child_node) printList(ptr->child_node, true);
        ptr = ptr->next_node;
    }
    if(!childNode) std::cout<<"]\n";
    else std::cout<<"]->";
    
}


int main(int argc, char **argv){
    //Input: 2->1->3->5->6->4->7->NULL
    Node<int> *head = new Node<int>(1);
    
    head->next_node = new Node<int>(2);
    head->next_node->prev_node = head;
    
    head->next_node->next_node = new Node<int>(3);
    head->next_node->next_node->prev_node = head->next_node;

    head->next_node->next_node->next_node = new Node<int>(4);
    head->next_node->next_node->next_node->prev_node = head->next_node->next_node;
    
    head->next_node->next_node->next_node->next_node = new Node<int>(5);
    head->next_node->next_node->next_node->next_node->prev_node = head->next_node->next_node->next_node;

    head->next_node->next_node->next_node->next_node->next_node = new Node<int>(6);
    head->next_node->next_node->next_node->next_node->next_node->prev_node = head->next_node->next_node->next_node->next_node;

    head->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(7);
    head->next_node->next_node->next_node->next_node->next_node->next_node->prev_node = head->next_node->next_node->next_node->next_node->next_node;

    /*Child nodes*/
    head->next_node->next_node->child_node = new Node<int>(7);
    
    head->next_node->next_node->child_node->next_node = new Node<int>(8);
    head->next_node->next_node->child_node->next_node->prev_node = head->next_node->next_node->child_node;
    
    head->next_node->next_node->child_node->next_node->next_node = new Node<int>(9);
    head->next_node->next_node->child_node->next_node->next_node->prev_node = head->next_node->next_node->child_node->next_node;
    
    head->next_node->next_node->child_node->next_node->next_node->next_node = new Node<int>(10);
    head->next_node->next_node->child_node->next_node->next_node->next_node->prev_node = head->next_node->next_node->child_node->next_node->next_node;

    /*Child nodes*/
    // head->next_node->next_node->child_node->next_node->child_node = new Node<int>(11);
    
    // head->next_node->next_node->child_node->next_node->child_node->next_node = new Node<int>(12);
    // head->next_node->next_node->child_node->next_node->child_node->next_node->prev_node = head->next_node->next_node->child_node->next_node->child_node;

    // Node<int> *head = new Node<int>(1);
    // head->child_node = new Node<int>(2);
    // head->child_node->child_node = new Node<int>(3);
    // head->child_node->child_node->child_node = new Node<int>(4);
    // head->child_node->child_node->child_node->child_node = new Node<int>(5);
    // head->child_node->child_node->child_node->child_node->child_node = new Node<int>(6);
    // head->child_node->child_node->child_node->child_node->child_node->child_node = new Node<int>(7);

    printList(head, false);
    Node<int> *result = flatten(head);
    printList(head, false);

    //To lazy to create a function to clean up all allocated nodes, be careful this program will leak memory
    //leak enough and your computer can crash. 

}
