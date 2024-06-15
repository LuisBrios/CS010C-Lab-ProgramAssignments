#pragma once
#include "Node.h"

//Class made to make the necessary functions and data members for the tree as a whole, taking properties from the class node as well.

class BSTree : public Node {
    public:
        BSTree()
            :root(nullptr)
            {
            }
        ~BSTree(){}
        void insert(const string& nodeVal);
        bool search(const string& nodeVal) const;
        string largest() const;
        string smallest() const;
        int height (const string& nodeVal) const; 
        void remove(const string& nodeVal);
        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
    private:
        Node* root; 
        void preOrder(Node* currNode) const;
        void inOrder(Node* currNode) const;
        void postOrder(Node* currNode) const; 
        Node* searchRecursive(Node* currNode, const string& nodeVal) const; 
        int heightRecursive(Node* currNode) const;
        Node* getParent(Node* currNode) const;
        Node* getParentRecursive(Node* subRoot, Node* currNode) const;
        bool removeNode(Node* parentNode, Node* currNode);
};