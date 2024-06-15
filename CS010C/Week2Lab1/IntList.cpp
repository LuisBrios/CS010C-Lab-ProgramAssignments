#include <iostream>
using namespace std;

#include "IntList.h"

//Initializes a list starting off with two dummy nodes, both being linked to the head and tail respectively. 
//They are then linked to each other. 
IntList::IntList(){
    IntNode* DummyHeadNode = new IntNode(-1);
    IntNode* DummyTailNode = new IntNode(-1); 
    dummyhead = DummyHeadNode;
    dummytail = DummyTailNode; 
    dummyhead->next = dummytail; 
    dummytail->prev = dummyhead;
}

//Goes through every node in the intlist, starting from the front, including dummy nodes, and deallocates them until 0 is met.
//(until the pointer reaches after dummytail). 
IntList::~IntList(){
    for (IntNode* currNode = dummyhead; currNode != 0; currNode = currNode->next){
        delete currNode; 
    }
}


//Makes a new object, to which it is pointed to, along with the node in front of the head, making it easier to connect the "prev"
//and the "next" of the currNode, as well as the "next" of the previous node (in this case, the head) as well as the "prev" of the
//node afterwards, ultimately linking all 3 nodes. 
void IntList::push_front(int value){
    IntNode* newNode = new IntNode(value);
    IntNode* succNode = dummyhead->next;

    newNode->next = succNode;
    newNode->prev = dummyhead; 
    dummyhead->next = newNode;
    succNode->prev = newNode; 
}

//Points to the front node (that isn't the dummy) as well as makes another pointer for the node after it, to connect the prev and next
//of the head and node after the node being deleted, to easily link the two, so that there is no harm in deleting the current node. 
void IntList::pop_front(){
    IntNode* currNode = dummyhead->next; 
    IntNode* succNode = currNode->next; 

    dummyhead->next = succNode; 
    succNode->prev = dummyhead; 

    delete currNode; 
}

//Similar to push_front, except it takes the node before the dummy tail, as well as the node two nodes before the dummy tail, to link the
//three together. The next and prev of the newly added node are connected to the tail and prevNode respectively, as well as the prevNode's 
//next and the dummytail's prev being linked to the newest node, causing there to be a connection between the three, making the linked list
//work. 
void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value); 
    IntNode* prevNode = dummytail->prev;

    newNode->prev = prevNode; 
    newNode->next = dummytail; 
    prevNode->next = newNode; 
    dummytail->prev = newNode;
}
HEY
//Points to the node that it wants to delete (the node before the dummytail, specifically) and has the nodes before and after it connect to
//one another by linking through prev and next, ultimately showing no need for the specified current node, thus deleting it. 
void IntList::pop_back(){
    IntNode* currNode = dummytail->prev;
    IntNode* prevNode = currNode->prev;

    dummytail->prev = prevNode; 
    prevNode->next = dummytail; 

    delete currNode; 
}

//Checks if the dummy tails are connected to each other. If so, the linked list is considered empty.
bool IntList::empty() const{
    if (dummyhead->next == dummytail){
        return true;
    }
    else {
        return false; 
    }
}

//Passes through an IntList object and a stream so that each node in the IntList can be easily printed out, by starting at the node
//after the dummy head, and traversing all the way to the node before the dummytail. All of these are printed out so that the user may
//simply type cout << object, as opposed to having to cout each individual element. 
ostream & operator<<(ostream &out, const IntList &rhs){
    for (IntNode* currNode = rhs.dummyhead->next; currNode != rhs.dummytail; currNode = currNode->next){
        out << currNode->data;
        if (currNode != rhs.dummytail->prev){
            out << " ";
        }
    }
    return out;
} 

//Traverses through the linked list (without interacting with the dummy nodes) and prints out their respective data value. Starts with the list
//after head, ends with the list before tail.
void IntList::printReverse() const{
    for (IntNode* currNode = dummytail->prev; currNode != dummyhead; currNode = currNode->prev){
        cout << currNode->data;
        if (currNode != dummyhead->next){
            cout << " ";
        }
    }
}





