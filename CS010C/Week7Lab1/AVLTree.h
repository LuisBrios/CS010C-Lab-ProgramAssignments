#pragma once
#include "Node.h"

//Class for trees. The tree is initialized by the constructor; this class has access to everything that Node.h has. 
class AVLTree{
    public: 
        AVLTree()
         :root(nullptr)
        {
        }
        ~AVLTree(); 
        void insert(const string& nodeVal);
        int balanceFactor(Node* currNode);
        void printBalanceFactors() const;
    private:
        Node* root;
        void insert(Node* newNode);
        void rebalanceTree(Node* currNode); 
        bool setChild(Node* parentNode, const string& childSide, Node* childNode);
        bool replaceChild(Node* parentNode, Node* currChild, Node* newChild);
        void printBalanceFactors(Node* currNode) const; 
        int updateHeight(const string& nodeVal);
        int updateHeightRec(Node* currNode); 
        void rotateLeft(Node* currNode);
        void rotateRight(Node* currNode);
        void destroyTree (Node* currNode); 
};