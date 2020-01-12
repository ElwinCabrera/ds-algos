#include <vector>
using std::vector;
template<typename Type>
class Node{
public:
    Type data;
    vector<Node> children;    
};

template<typename Type>
class Graph{
    Graph();
    ~Graph();
    

public:
    vector<Node<Type>> nodes;
};