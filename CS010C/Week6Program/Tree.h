#pragma once
#include "Node.h"

//Class for the entire tree that contains constructors, helper functions, recursive functions, etc. 
//Has access to the private data members of the node class. 
class Tree{
    public:
        Tree()
         :root(nullptr)
        {
        }
        ~Tree();
        void insert (const string& nodeVal);
        void preOrder() const; 
        void inOrder() const;
        void postOrder() const;
        void remove(const string& nodeVal);
        bool search (const string& nodeVal) const;
    private:
        Node* root; 
        Node* insertRecursive(Node* currNode, const string& nodeVal);
        Node* splitNode(Node* currNode, Node* parentNode, const string& nodeVal);
        void insertChildKey(Node* parentNode, const string& nodeVal, Node* leftChild, Node* rightChild);
        void insertLeafNode(Node* currNode, const string& nodeVal); 
        void removeRecursive(Node* currNode, const string& nodeVal);
        void preOrder(Node* currNode) const;
        void inOrder(Node* currNode) const;
        void postOrder(Node* currNode) const; 
        void destroyTree(Node* currNode);

};