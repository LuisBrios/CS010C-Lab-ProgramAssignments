#include <iostream>
using namespace std;

#include "Tree.h"

//Helper function for the destructor.
Tree::~Tree(){
    destroyTree(root);
}

//Deletes each node, starting from left to middle to right once the program ends. 
void Tree::destroyTree(Node* currNode){
    if (currNode){
        destroyTree(currNode->left);
        destroyTree(currNode->middle);
        destroyTree(currNode->right);
        delete currNode; 
    }
}

//Helper function for the insert function. If there is no root, a root is made with the value of the users input. 
void Tree::insert(const string& nodeVal){
    if (root == nullptr){
        root = new Node (nodeVal);
    }
    else{
        insertRecursive(root, nodeVal);
    }
}


//Inserts a node (or adds to a node) based on 2-3 specifications and maintaining 2-3 rules throughout. If nodes are filled, then
//they are split so additional room is made, allowing for manipulation of nodes and their values. Resulting insertions remian
//in alphabetical order as well as in the format of a balanced tree. 
Node* Tree::insertRecursive(Node* currNode, const string& nodeVal){
    if (search(nodeVal) == true){
        return nullptr; 
    }
    if (currNode->left != nullptr || currNode->middle != nullptr || currNode->right != nullptr){
        if (nodeVal < currNode->small){
            return insertRecursive(currNode->left, nodeVal);
        }
        else if (nodeVal < currNode->large || currNode-> large == ""){
            return insertRecursive(currNode->middle, nodeVal);
        }
        else {
            return insertRecursive(currNode->right, nodeVal); 
        }
    }
    else {
        if (currNode->small != "" && currNode->large != ""){
            currNode = splitNode(currNode, currNode->parent, nodeVal); 
        }
        else {
            insertLeafNode(currNode, nodeVal);
            return currNode;
        } 
        return currNode; 
    }
}

//Function that traverses each branch of the tree in attempt to locate the user value. Returns true or false depending on it's absence. 
bool Tree::search(const string& nodeVal) const{
    Node* currNode = root;
    while (currNode != nullptr){
        if (nodeVal == currNode->small || nodeVal == currNode->large){
            return true;
        }
        if (nodeVal < currNode->small){
            currNode = currNode->left; 
        }
        else if (nodeVal < currNode->large || currNode->large == ""){
            currNode = currNode->middle;
        }
        else {
            currNode = currNode->right; 
        }
    }
    return false; 
}

//Function called on by insertRecursive. This function splits a node into three separate nodes, with the middle value being the parent of the
//other two. All nodes have an empty "large" value, allowing space for insertions. 
Node* Tree::splitNode(Node* currNode, Node* parentNode, const string& nodeVal){
    Node* leftNode;
    Node* rightNode;
    string nodeValHolder = nodeVal;

    if (nodeVal < currNode->small){
        nodeValHolder = currNode->large; 
        currNode->large = currNode->small;
        currNode->small = nodeVal; 
    } 
    else if (nodeVal < currNode->large){
        nodeValHolder = currNode->large;
        currNode->large = nodeVal; 
    }
    leftNode = new Node(currNode->small);
    leftNode->left = currNode->left;
    leftNode->middle = currNode->middle;

    rightNode = new Node(nodeValHolder);
    rightNode->left = currNode->left;
    rightNode->middle = currNode->middle; 

    if (parentNode != nullptr){
        insertChildKey(parentNode, currNode->large, leftNode, rightNode);
    }
    else {
        parentNode = new Node(currNode->large);
        parentNode->left = leftNode;
        parentNode->middle = rightNode;
        leftNode->parent = parentNode;
        rightNode->parent = parentNode; 
        root = parentNode; 
    }
    return parentNode; 
}

//Called by the splitNode function. Allows for the insertion of node values into a node based on space and positioning, as well as readjusting
//pointers to continue following 2-3 protocol. 
void Tree::insertChildKey(Node* parentNode, const string& nodeVal, Node* leftChild, Node* rightChild){
    if (parentNode->small != "" && parentNode-> large != ""){
        Node* newNode = new Node(nodeVal);
        newNode->left = leftChild;
        newNode->middle = rightChild;
        leftChild->parent = newNode;
        rightChild->parent = newNode;
        parentNode->left = parentNode->middle;
        parentNode->middle = parentNode-> right;
    }
    else if (nodeVal < parentNode->small){
        parentNode->large = parentNode->small;
        parentNode->small = nodeVal;
        parentNode->right = parentNode->middle; 
        parentNode->middle = rightChild;
        parentNode->left = leftChild;
        rightChild->parent = parentNode;
        leftChild->parent = parentNode; 
    }
    else {
        parentNode->large = nodeVal;
        parentNode->right = rightChild;
        parentNode->middle = leftChild;
        rightChild->parent = parentNode;
        leftChild->parent = parentNode; 
    }
}

//Function called by insertRecursive. Simply adds a node in the "large" data member or in the "small" data member depending on the comparison
//between the two. 
void Tree::insertLeafNode(Node* currNode, const string& nodeVal){
    if (nodeVal < currNode->small){
        swap(currNode->small, currNode->large);
        currNode->small = nodeVal;
    }
    else {
        currNode->large = nodeVal;
    }
}

//Helper function for removeRecursive. Simply calls the recursive function if there is a root. 
void Tree::remove(const string& nodeVal){
    if (root == nullptr){
        return; 
    }
    else {
        removeRecursive(root, nodeVal); 
    }
}

//Function that simply removes any node prompted by the user, fixing pointers and deleting unwanted nodes while maintaining 2-3 properties. 
void Tree::removeRecursive(Node* currNode, const string& nodeVal){
    Node* parentNode = currNode->parent;
    if (search(nodeVal) == false){
        return;
    }
    if (nodeVal == currNode->small || nodeVal == currNode->large){
        if (currNode->small != "" && currNode->large == ""){
            if (currNode->left != nullptr && currNode->middle != nullptr){
                currNode->small = currNode->left->small;
                currNode->large = currNode->middle->small;
                delete currNode->left;
                delete currNode->middle;
                currNode->left = nullptr;
                currNode->middle = nullptr;
            }
            else{
                if (parentNode == nullptr){
                    root = nullptr; 
                }
                else {
                    if (parentNode->middle->small == nodeVal){
                        parentNode->middle = nullptr;
                        parentNode->large = parentNode->small;
                        parentNode->small = parentNode->left->small;
                        delete parentNode->left;
                        parentNode->left = nullptr;
                    }
                    else {
                        parentNode->left = nullptr; 
                        parentNode->large = parentNode->middle->small;
                        delete parentNode->middle;
                        parentNode->middle = nullptr; 
                    }
                }
            }
        }
        else {
            currNode->large = "";
        }
    }
    else if (nodeVal < currNode->small){
        removeRecursive(currNode->left, nodeVal);
    }
    else if (nodeVal < currNode->large || currNode->large == ""){
        removeRecursive(currNode->middle, nodeVal);
    }
    else {
        removeRecursive(currNode->right, nodeVal); 
    } 
}

//Helper function that calls the preOrder print function if there is a root. 
void Tree::preOrder() const{
    if (root != nullptr){
        preOrder(root); 
    }
}

//Prints the node from the middle, to the left, then to the right. 
void Tree::preOrder(Node* currNode) const{
    cout << currNode->small << ", ";
    if (currNode->left != nullptr){
        preOrder(currNode->left);
    }
    if (currNode->large != ""){
        cout << currNode->large << ", ";
    }
    if (currNode->middle != nullptr){
        preOrder(currNode->middle); 
    }
    if (currNode->right != nullptr){
        preOrder(currNode->right); 
    }     
}

//Helper function that calls the inOrder print function if there is a root. 
void Tree::inOrder() const{
    if (root != nullptr){
        inOrder(root);
    }
}

//Simply prints the tree starting from left, to middle, to right in alphabtical order.
void Tree::inOrder(Node* currNode) const{
    if (currNode->left != nullptr){
        inOrder(currNode->left); 
    }
    cout << currNode->small << ", ";
    if (currNode->middle != nullptr){
        inOrder(currNode->middle);
    }
    if (currNode->large != ""){
        cout << currNode->large << ", ";
    }
    if (currNode->right != nullptr){
        inOrder(currNode->right); 
    }
}

//Helper function that calls the postOrder print function if there is a root. 
void Tree::postOrder() const{
    if (root != nullptr){
        postOrder(root); 
    }
}

//Prints the function starting from the bottom left up, bottom middle up, bottom right up, then finally at the middle top.  
void Tree::postOrder(Node* currNode) const{
    if(currNode->left != nullptr){
        postOrder(currNode->left);
    }
    if (currNode->middle != nullptr){
        postOrder(currNode->middle);
    }
    cout << currNode->small << ", "; 
    if (currNode->right != nullptr){
        postOrder(currNode->right);
    }
    if (currNode->large != ""){
        cout << currNode->large << ", ";
    }
}