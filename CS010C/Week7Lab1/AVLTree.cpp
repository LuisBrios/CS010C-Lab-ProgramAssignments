#include <iostream>
using namespace std;

#include "AVLTree.h"


//Destructor that calls on a recursive function to successfully delete all nodes. 
AVLTree::~AVLTree(){
    destroyTree(root);
}

//Deletes each node, starting from left to right at the end of the program to deallocate excess memory. 
void AVLTree::destroyTree(Node* currNode){
    if (currNode){
        destroyTree(currNode->left);
        destroyTree(currNode->right);
        delete currNode; 
    }
}

//Converts the given string into a newly allocated node to efficiently call and perform the helper function. 
void AVLTree::insert(const string& nodeVal){
    Node* newNode = new Node(nodeVal);
    insert(newNode); 
}

//Following BSTree properties, it finds a spot on the Tree that would allow for it to be considered "in order," as well as connects pointers in order to
//easily perform rotations without loss of a node. 
void AVLTree::insert(Node* newNode){
    Node* currNode;
    if (root == nullptr){
        root = newNode;
        newNode->parent = nullptr;
        return; 
    }
    currNode = root;
    while (currNode != nullptr){
        if (newNode->nodeData < currNode->nodeData){
            if (currNode->left == nullptr){
                currNode->left = newNode;
                newNode->parent = currNode;
                currNode = nullptr; 
            }
            else {
                currNode = currNode->left; 
            }
        }
        else if (newNode->nodeData > currNode->nodeData){ 
            if (currNode->right == nullptr){
                currNode->right = newNode;
                newNode->parent = currNode;
                currNode = nullptr; 
            }
            else {
                currNode = currNode->right; 
            }
        }
        else {
            return;
        }
    }
    newNode = newNode->parent; 
    while (newNode != nullptr){
        rebalanceTree(newNode);
        newNode = newNode->parent; 
    }
}

//Provides a "guideline" of when a Node should rotate, where to rotate, and how many rotations to take (if the node is outside a balance factor of [-1, 1])
void AVLTree::rebalanceTree(Node* currNode){
    if (balanceFactor(currNode) == -2){
        if (balanceFactor(currNode->right) == 1){
            rotateRight(currNode->right);
        }
        rotateLeft(currNode);
    }
    else if (balanceFactor(currNode) == 2){
        if (balanceFactor(currNode->left) == -1){
            rotateLeft(currNode->left); 
        }
        rotateRight(currNode);
    }
}

//Allows for a balance to be calculated for a designated node, which indicates whether or not a rotation is necessary to keep the tree balanced.
int AVLTree::balanceFactor(Node* currNode){
    int balanceFactor = (updateHeightRec(currNode->left) - updateHeightRec(currNode->right)); 
    currNode->balanceFactor = balanceFactor;
    return balanceFactor;
}

//Calculates the height of each node, which allows for a balance factor to be calculated as well (thus assisting in when a tree is considered balanced or not). 
int AVLTree::updateHeightRec(Node* currNode){
    if (currNode == nullptr){
        return -1;
    }
    int leftHeight = updateHeightRec(currNode->left);
    int rightHeight = updateHeightRec(currNode->right);
    return (max(leftHeight, rightHeight) + 1);
}

//After a rotation is performed, this function allows for the reassignment of pointers, to keep the tree in proper format.
bool AVLTree::setChild(Node* parentNode, const string& childSide, Node* childNode){
    if (childSide != "left" && childSide != "right"){
        return false; 
    }
    if (childSide == "left"){
        parentNode->left = childNode; 
    }
    else {
        parentNode->right = childNode; 
    }
    if (childNode != nullptr){
        childNode->parent = parentNode; 
    }
    return true; 
}

//After a rotation is performed, this function allows for the reassignment of pointers, calling on setChild to simply replace any currently existing pointers.
bool AVLTree::replaceChild(Node* parentNode, Node* currChild, Node* newChild){
    if (parentNode->left == currChild){
        return setChild(parentNode, "left", newChild);
    }
    else if (parentNode->right == currChild){
        return setChild(parentNode, "right", newChild);
    }
    return false; 
}

//When a node has a balance factor at -2, this functions allows for the rotation of specific nodes in a tree (to the left), permitting the tree to stay in balance. 
void AVLTree::rotateLeft(Node* currNode){
    Node* rightLeftChild = currNode->right->left;
    if (currNode->parent != nullptr){
        replaceChild(currNode->parent, currNode, currNode->right);
    }
    else {
        root = currNode->right;
        root->parent = nullptr; 
    }
    setChild(currNode->right, "left", currNode);
    setChild(currNode, "right", rightLeftChild); 
    balanceFactor(currNode);  
}

//When a node has a balance factor at 2, this function allows for the rotation of specific noeds in a tree (to the right), permitting the trees to stay in balance. 
void AVLTree::rotateRight(Node* currNode){
    Node* leftRightChild = currNode->left->right;
    if (currNode->parent != nullptr){
        replaceChild(currNode->parent, currNode, currNode->left);
    }
    else {
        root = currNode->left;
        root->parent = nullptr; 
    }
    setChild(currNode->left, "right", currNode);
    setChild(currNode, "left", leftRightChild); 
    balanceFactor(currNode); 
}

//Calls the recursive private helper function, which is necessary to prevent the user from inputting nodes as an argument. 
void AVLTree::printBalanceFactors() const{
    if (root != nullptr){
        printBalanceFactors(root); 
    }
    cout << endl; 
}

//Prints the tree in order, allowing for the user to see how balanced the allocated nodes are.
void AVLTree::printBalanceFactors(Node* currNode) const{
    if (currNode->left != nullptr){
        printBalanceFactors(currNode->left);
    }
    cout << currNode->nodeData << "(" << currNode->balanceFactor << "), ";
    if (currNode->right != nullptr){
        printBalanceFactors(currNode->right);
    }
}