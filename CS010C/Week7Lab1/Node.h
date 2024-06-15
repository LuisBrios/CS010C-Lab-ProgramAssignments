#pragma once
#include <string>
using namespace std;

//Class for nodes; grants permission to the AVLTree class to access the private data members. 
class Node{
    friend class AVLTree; 
    public:
        Node()
          :nodeData(""),
           balanceFactor(0),
           parent(nullptr),
           left(nullptr),
           right(nullptr)
        {
        }

        Node(const string& nodeVal)
          :nodeData(nodeVal),
           balanceFactor(0),
           parent(nullptr),
           left(nullptr),
           right(nullptr)
        {
        }
    private:
        string nodeData;
        int balanceFactor;
        Node* parent;
        Node* left;
        Node* right;

};