#include "../forward_list.h"

Node<int>* loopDetction(Node<int> *head){
    Node<int> *slow = head;
    Node<int> *fast = head;
    bool moveSameSpeed = false;
    bool firstItr = true;
    while(fast && fast->next_node){
        if(fast == slow && !firstItr) {
            if(moveSameSpeed) return slow;
            slow = head;
            moveSameSpeed = true;
        }
        slow = slow->next_node;
        fast = (moveSameSpeed) ? fast->next_node: fast->next_node->next_node;
        firstItr = false;
    }
    return nullptr;
}

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
    Node<int> *head = new Node<int>(8);
    head->next_node = new Node<int>(1);
    head->next_node->next_node = new Node<int>(9);
    head->next_node->next_node->next_node = new Node<int>(4);
    Node<int> *beginingCycle = new Node<int>(2);
    head->next_node->next_node->next_node->next_node = beginingCycle;
    head->next_node->next_node->next_node->next_node->next_node = new Node<int>(3);
    head->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(7);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(100);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node = new Node<int>(101);
    head->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node->next_node = beginingCycle;

    std::cout << "beggining of the list is: "<<beginingCycle->data<< "\n";
    Node<int> *start = loopDetction(head);
    std::cout << "function return beginning of the list is: "<<start->data<< "\n";
    bool same = start == beginingCycle;
    std::cout << "pointing to same node: " << same << "\n";
    

}