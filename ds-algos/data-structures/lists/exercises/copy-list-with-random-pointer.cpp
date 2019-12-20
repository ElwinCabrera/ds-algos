#include "../list.h"

Node<int>* copyRandomList(Node<int>* head) {
    if(!head) return head;
    Node<int> *given_list_ptr = head;

    while (given_list_ptr){
        Node<int> *insert_node = new Node<int>(given_list_ptr->data);
        Node<int> *insert_next = given_list_ptr->next_node;
        given_list_ptr->next_node = insert_node;
        insert_node->next_node = insert_next;
        given_list_ptr = insert_next; 
    }
    given_list_ptr = head;
    while(given_list_ptr){
        if(given_list_ptr->prev_node) given_list_ptr->next_node->prev_node = given_list_ptr->prev_node->next_node;
        given_list_ptr = given_list_ptr->next_node->next_node;
    }
    given_list_ptr = head;
    Node<int> *result_head = given_list_ptr->next_node;
    Node<int> *result_list_ptr = result_head;
    while (given_list_ptr){
        Node<int> *given_list_next = nullptr;
        if(given_list_ptr->next_node)given_list_next =  given_list_ptr->next_node->next_node;
        Node<int> *result_list_next = nullptr;
        if(result_list_ptr->next_node) result_list_next = result_list_ptr->next_node->next_node;
        
        given_list_ptr->next_node = given_list_next;
        result_list_ptr->next_node = result_list_next;

        given_list_ptr = given_list_ptr->next_node;
        result_list_ptr = result_list_ptr->next_node;
    }

    return result_head;
    
}



/*********** TESTS ***********/
void printList(Node<int> *ptr){
    Node<int> *p = ptr;
    std::cout <<"List contains: [";
    while(p){
        if(p->next_node) std::cout << p->data << "->";
        else std::cout << p->data;
        p = p->next_node;
    }
    std::cout<<"]\n";

    std::cout <<"                ";
    p = ptr;
    while(p){

        if(p->next_node) std::cout << "|" << "  ";
        else std::cout << "|";
        p = p->next_node;
    }
    std::cout<<"\n";

    std::cout <<"Random:        [";
    p = ptr;
    while(p){
        if(p->next_node){
            if(p->prev_node) std::cout << p->prev_node->data << "  ";
            else std::cout << "n  ";
        } else {
            if(p->prev_node) std::cout << p->prev_node->data;
            else std::cout << "null";
        }
        p = p->next_node;
    }
    std::cout<<"]\n";
}

bool areListSame(Node<int> *l1, Node<int> *l2){
    while(l1 && l2){
        if(l1->next_node == l2->next_node || l1->prev_node == l2->prev_node) return true;
        l1 = l1->next_node;
        l2 = l2->next_node;
    }

    return false;
}


int main(int argc, char** argv){
    
    Node<int> *list1 = new Node<int>(7);
    list1->next_node = new Node<int>(13);
    list1->next_node->next_node =  new Node<int>(11);
    list1->next_node->next_node->next_node =  new Node<int>(10);
    list1->next_node->next_node->next_node->next_node = new Node<int>(1);

    list1->prev_node = nullptr;
    list1->next_node->prev_node = list1;
    list1->next_node->next_node->prev_node = list1->next_node->next_node->next_node->next_node;
    list1->next_node->next_node->next_node->prev_node  = list1->next_node->next_node;
    list1->next_node->next_node->next_node->next_node->prev_node = list1;

    Node<int> *cpy_list = copyRandomList(list1);

    std::cout << "Printing list1: \n";
    printList(list1);

    
    std::cout << "Printing from copied list: \n";
    printList(cpy_list);

    std::cout << "Are the same: " << areListSame(list1, cpy_list) << "\n";

    list1->next_node->data = 111;

    std::cout << "Original list1: \n";
    printList(list1);

    
    std::cout << "copied list: \n";
    printList(cpy_list);


    delete list1->next_node->next_node->next_node->next_node;
    delete list1->next_node->next_node->next_node;
    delete list1->next_node->next_node;
    delete list1->next_node;
    delete list1;

    delete cpy_list->next_node->next_node->next_node->next_node;
    delete cpy_list->next_node->next_node->next_node;
    delete cpy_list->next_node->next_node;
    delete cpy_list->next_node;
    delete cpy_list;

    return 0;
}