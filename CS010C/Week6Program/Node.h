#pragma once
#include <string>
using namespace std;

//Class for Nodes that contain the constructors and the private data members. 
//Allows for the tree class to access its data members. 
class Node{
    friend class Tree;
    public:
        Node()
         :small(""),
          large(""),
          left(nullptr),
          middle(nullptr),
          right(nullptr),
          parent(nullptr)
        {
        }
        Node(const string& nodeVal)
         :small(nodeVal),
          large(""),
          left(nullptr),
          middle(nullptr),
          right(nullptr),
          parent(nullptr)
        {
        }

    private:
        string small;
        string large;
        Node* left;
        Node* middle;
        Node* right; 
        Node* parent;     
};