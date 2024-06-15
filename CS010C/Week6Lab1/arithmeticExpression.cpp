#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;

#include "arithmeticExpression.h"

//Initializes the tree by first creating root to be nullptr, as well as taking in a string that will soon be translated into a tree. 
arithmeticExpression::arithmeticExpression(const string& userVal){
    root = nullptr;
    infixExpression = userVal; 
}

//Calls the recursive function responsible for deleting the nodes.
arithmeticExpression::~arithmeticExpression(){
    destroyTree(root);
}

//Deletes each node, starting from left to right. 
void arithmeticExpression::destroyTree(TreeNode* currNode){
    if (currNode){
        destroyTree(currNode->left);
        destroyTree(currNode->right);
        delete currNode; 
    }
}

//With the string already made into postfix format, the code goes through the string and checks for both operators and numbers/letters. 
//If the current char being checked is not an operator, it is put into a stack to be popped out for later (and connected to the tree).
//If not, two nodes are popped out of the stack, to which it is connected with a node meant for the operator. 
void arithmeticExpression::buildTree(){
    TreeNode* newNode;
    TreeNode* poppedNode; 
    TreeNode* currNode = root; 
    stack<TreeNode*> nodeStacks;
    infixExpression = infix_to_postfix();
    for (unsigned int i = 0; i < infixExpression.size(); ++i){
        if (isalnum(infixExpression.at(i))){
            newNode = new TreeNode(infixExpression.at(i), 1);
            nodeStacks.push(newNode);
        } 
        else {
            newNode = new TreeNode(infixExpression.at(i), 1);
            root = newNode;
            currNode = root;
            poppedNode = nodeStacks.top();
            currNode->left = poppedNode;
            nodeStacks.pop(); 
            poppedNode = nodeStacks.top();
            currNode->right = poppedNode;
            nodeStacks.pop();
            nodeStacks.push(currNode); 
        }
    }

}

//Given Function; Optional (Unused)
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

//Given Function; translates the string so operators come last. 
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

//Optional; Unused. 
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

//Calls the recursive function, starting at the root. 
void arithmeticExpression::infix() const{
    infix(root);
}

//Prints out the tree going from right to left (as well as placing parentheses when proper). 
void arithmeticExpression::infix(TreeNode* currNode) const{
    if (currNode->right != nullptr){
        cout << "(";
        infix(currNode->right); 
    }
    cout << currNode->data;
    if (currNode->left != nullptr){
        infix(currNode->left);
        cout << ")";
    } 
}

//Calls the recursive function, starting at the root. 
void arithmeticExpression::prefix() const{
    prefix(root); 
}

//Prints out the tree starting at the top (parent) node, goes to the right child node, then swiftly proceeds to the parent's left child node.
void arithmeticExpression::prefix(TreeNode* currNode) const{
    cout << currNode->data;
    if (currNode->right != nullptr){
        prefix(currNode->right);
    }
    if (currNode->left != nullptr){
        prefix(currNode->left); 
    }
}

//Calls the recursive function, starting at the root. 
void arithmeticExpression::postfix() const{
    postfix(root);
}

//Prints out the tree's bottom nodes, then eventually rising to the top. 
void arithmeticExpression::postfix(TreeNode* currNode) const{
    if (currNode->right != nullptr){
        postfix(currNode->right);
    }
    if (currNode->left != nullptr){
        postfix(currNode->left);
    }
    cout << currNode->data; 
}

//Unused Function; Optional
void arithmeticExpression::visualizeTree(ofstream& o, TreeNode* currNode){
}

