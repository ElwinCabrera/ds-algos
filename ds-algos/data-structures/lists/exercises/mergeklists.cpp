#include "../forward_list.h"
#include <vector>
using std::vector;
/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6


*/

Node<int>* merge(Node<int> *head1, Node<int> *head2){
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


Node<int>* mergeKLists(vector<Node<int>*> &lists){
    if(lists.size() == 0 ) return nullptr;
    if(lists.size() == 1 ) return lists.at(0);
    
    unsigned idx = 1;
    while(idx < lists.size()){
        lists.at(0) = merge(lists.at(0), lists.at(idx));
        ++idx;
    }
    return lists.at(0);
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

/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6


*/
int main(int argc, char **argv){
    Node<int> *head1 = new Node<int>(1);
    head1->next_node = new Node<int>(2);
    head1->next_node->next_node = new Node<int>(2);

    Node<int> *head2 = new Node<int>(1);
    head2->next_node = new Node<int>(1);
    head2->next_node->next_node = new Node<int>(2);

    // Node<int> *head3 = new Node<int>(2);
    // head3->next_node = new Node<int>(6);


    std::cout << "[\n\t";
    printList(head1);
    std::cout << "\t";
    printList(head2);
    // std::cout << "\t";
    // printList(head3);
    std::cout << "]\n";

    vector<Node<int>*> lists;
    lists.push_back(head1);
    lists.push_back(head2);
    //lists.push_back(head3);

    Node<int> *result = mergeKLists(lists);
    std::cout << "Result:\n";
    printList(result);

    //To lazy to create a function to clean up all allocated nodes, be careful this program will leak memory
    //leak enough and your computer can crash. 


}