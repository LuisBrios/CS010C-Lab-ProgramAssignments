#include <iostream>
using namespace std;

#include "BSTree.h"

//Given a string by the user, this function allows for insertion of any string into the Binary Search Tree, by alphabetically ordering the
//string with the strings of the already existing nodes. 
void BSTree::insert(const string& nodeVal){ 
    Node* currentNode = root;
    if (root == nullptr){
        root = new Node(nodeVal);
    }
    else {
        while (currentNode != nullptr){
            if (nodeVal < currentNode->GetData()){
                if (currentNode->GetLeft() == nullptr){
                    currentNode->SetLeft(new Node(nodeVal));
                    currentNode = nullptr; 
                }
                else {
                    currentNode = currentNode->GetLeft(); 
                }
            }
            else if (nodeVal > currentNode->GetData()) {
                if (currentNode->GetRight() == nullptr){
                    currentNode->SetRight(new Node(nodeVal));
                    currentNode = nullptr; 
                }
                else {
                    currentNode = currentNode->GetRight(); 
                }
            }
            else {
                if (nodeVal == currentNode->GetData()){
                    currentNode->IncNum(); 
                    currentNode = nullptr; 
                }
            }
        }
    }
}

//Simply returns whether or not a node (prompted by a user's string input) exists by calling a recursive function. 
bool BSTree::search(const string& nodeVal) const{
    Node* currNode = root;
    if (searchRecursive(currNode, nodeVal) == nullptr){
        return false; 
    }
    return true; 
}

//Private Helper Function: Recursively locates a node based on the string the user inputs. The BSTree is sorted alphabetically, so it is 
//only necessary to check whether the string is lower or greater than the currently accessed, then proceed from then. 
Node* BSTree::searchRecursive(Node* currNode, const string& nodeVal) const{
    if (currNode != nullptr){
        if (nodeVal == currNode->GetData()){
            return currNode; 
        }
        else if (nodeVal < currNode->GetData()){
            return searchRecursive(currNode->GetLeft(), nodeVal);
        }
        else {
            return searchRecursive(currNode->GetRight(), nodeVal); 
        }
    }
    return nullptr; 
}

//Goes all the way to the right of the BSTree to access the last value (largest) and return the string. 
string BSTree::largest() const{
    Node* currentNode = root;
    if (currentNode == nullptr){
        return ""; 
    }
    else {
        while (currentNode->GetRight() != nullptr){
            currentNode = currentNode->GetRight(); 
        }
        return currentNode->GetData();
    }
}

//Goes all the way to the left of the BSTree to access the first value (smallest) and return the string. 
string BSTree::smallest() const{
    Node* currentNode = root;
    if (currentNode == nullptr){
        return "";
    }
    else {
        while (currentNode->GetLeft() != nullptr){
            currentNode = currentNode->GetLeft();
        }
        return currentNode->GetData(); 
    }
}

//Searches for a node based on the string passed in by the user. Once reached, it calls on a recursive function to get the height of that
//specific subtree. 
int BSTree::height(const string& nodeVal) const{
    Node* currNode = root;
    if (search(nodeVal) == false){
        return -1; 
    }
    while (currNode->GetData() != nodeVal){
        if (nodeVal < currNode->GetData()){
            currNode = currNode->GetLeft(); 
        }
        else if (nodeVal > currNode->GetData()){
            currNode = currNode->GetRight(); 
        }
    }
    return heightRecursive(currNode);
}

//Private Helper Function: Traverses each possible branch of a subroot, calculating the size of each and returning the largest one.
int BSTree::heightRecursive(Node* currNode) const{
    if (currNode == nullptr){
        return -1;
    }
    int leftHeight = heightRecursive(currNode->GetLeft());
    int rightHeight = heightRecursive(currNode->GetRight());
    return 1 + max(leftHeight, rightHeight);
}

//Calls for a recursive function to find the parent of a given node. 
Node* BSTree::getParent(Node* currNode) const{
    Node* rootNode = root; 
    return getParentRecursive(rootNode, currNode); 
}

//Private Helper Function: Recursively checks cases to determine which node the currentNode is the child of, given a root and the desired
//node you'd like a parent for. 
Node* BSTree::getParentRecursive(Node* subRoot, Node* currNode) const{
    if (subRoot == nullptr){
        return nullptr; 
    }
    if (subRoot->GetLeft() == currNode || subRoot->GetRight() == currNode){
        return subRoot; 
    }
    if (currNode->GetData() < subRoot->GetData()){
        return getParentRecursive(subRoot->GetLeft(), currNode);
    }
    return getParentRecursive(subRoot->GetRight(), currNode); 
}

//Initializes a node and its parent to pass into the recursive remove function.
void BSTree::remove(const string& nodeVal) {
    Node* currNode = root;
    Node* node = searchRecursive(currNode, nodeVal);
    Node* parent = getParentRecursive(currNode, node);
    removeNode(parent, node);
}

//Checks cases in order to determine when a node should be removed, as well as how to fix the previously used pointers to prevent any
//dangling pointers/improperly linked pointers. 
bool BSTree::removeNode(Node* parentNode, Node* currNode) {
    Node* succNode;
    Node* succParent; 
    if (currNode == nullptr){
        return false; 
    }
    if (currNode->GetNum() > 1){
        currNode->DecNum(); 
        return false; 
    }
    else if (currNode->GetLeft() != nullptr){
        succNode = currNode->GetLeft();
        succParent = currNode;
        while (succNode->GetRight() != nullptr){
            succParent = succNode;
            succNode = succNode->GetRight(); 
        }
        currNode->SetData(succNode->GetData());
        currNode->SetNum(succNode->GetNum());
        succNode->SetNum(1); 
        removeNode(succParent, succNode);
    }
    else if (currNode->GetRight() != nullptr){
        succNode = currNode->GetRight();
        succParent = currNode;
        while(succNode->GetLeft() != nullptr){
            succParent = succNode;
            succNode = succNode->GetLeft();
        } 
        currNode->SetData(succNode->GetData());
        currNode->SetNum(succNode->GetNum());
        succNode->SetNum(1); 
        removeNode(succParent, succNode); 
    }
    else if (currNode->GetLeft() == nullptr && currNode->GetRight() == nullptr){
        delete currNode; 
        if (parentNode != nullptr){
            if (parentNode->GetRight() == currNode){
                parentNode->SetRight(nullptr);
            }
            else if (parentNode->GetLeft() == currNode) {
                parentNode->SetLeft(nullptr); 
            }
        }
        else {
            root = nullptr; 
        }  
    }
    return true;
}

//If there is a root, these three different function calls use their respective recursive functions to print the BSTree out in three
//different ways.
//Prints in the following ways:
//PreOrder: Middle, Left, Right
//InOrder: Left, Middle, Right
//PostOrder: Right, Left, Middle

void BSTree::preOrder() const{
    if (smallest() != ""){
        preOrder(root); 
    }
    cout << endl; 
}

void BSTree::preOrder(Node* currNode) const{
    cout << currNode->GetData() << "(" << currNode->GetNum() << "), ";
    if (currNode->GetLeft() != nullptr) {
        preOrder(currNode->GetLeft()); 
    }
    if (currNode->GetRight() != nullptr){
       preOrder(currNode->GetRight()); 
    }
}

void BSTree::inOrder() const{
    if (smallest() != ""){
        inOrder(root); 
    }
    cout << endl;
}

void BSTree::inOrder(Node* currNode) const{
    if (currNode->GetLeft() != nullptr){
        inOrder(currNode->GetLeft());
    }
    cout << currNode->GetData() << "(" << currNode->GetNum() << "), ";
    if (currNode->GetRight() != nullptr){
        inOrder(currNode->GetRight());
    }
}

void BSTree::postOrder() const{
    if (smallest() != ""){
        postOrder(root); 
    }
    cout << endl;
}

void BSTree::postOrder(Node* currNode) const{
    if (currNode->GetLeft() != nullptr){
        postOrder(currNode->GetLeft());
    }
    if (currNode->GetRight() != nullptr){
        postOrder(currNode->GetRight());
    }
    cout << currNode->GetData() << "(" << currNode->GetNum() << "), "; 
}