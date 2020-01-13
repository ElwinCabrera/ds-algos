#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
using std::vector;
using std::unordered_set;

template<typename Type>
class Node{
public:
    Node() {}
    Node(Type d) : data(d) {}
    Type data;
    vector<Node*> children;    
};

template<typename Type>
class Graph{
public:
    Graph(int vertices) {
        nodes.reserve(vertices);
        for(unsigned i = 0; i < vertices; ++i){
            Node<Type> *dummy = new Node<Type>();
            nodes.push_back(dummy);
        }
    }
    ~Graph(){
        unordered_set<Node<Type>*> visited;
        for(Node<Type> *node: nodes){
            deleteAll(node,visited);
            delete node;
            node = nullptr;
        }
        nodes.clear();
    }

    void deleteAll(Node<Type> *node, unordered_set<Node<Type>*> &visited){
        if(node->children.empty() || visited.find(node) != visited.end() || node == nullptr) return;
        for(Node<Type> *child: node->children){
            visited.insert(child);
            deleteAll(child, visited);
            delete child;
            child = nullptr;
        }
    }
    void addEdge(int nodeIdx, Type t){
        Node<Type> *newNode = new Node<Type>(t);

        this->nodes.at(nodeIdx)->children.push_back(newNode);
    }
    

private:
    vector<Node<Type>*> nodes;
};



#endif // GRAPH_H