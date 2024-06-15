#pragma once

//Struct that allows for easy implementation of a node object.

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

//Class that permits the user to use a few functions to create their own list. 

class IntList {
    private:
        IntNode* dummyhead;
        IntNode* dummytail; 
    public:
        IntList(); 
        ~IntList(); 
        void push_front(int value); 
        void pop_front();
        void push_back(int value);
        void pop_back();
        bool empty() const; 
        friend ostream & operator<<(ostream &out, const IntList &rhs); 
        void printReverse() const; 
};