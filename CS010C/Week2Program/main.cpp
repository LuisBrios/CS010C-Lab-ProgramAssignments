#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//The "template" of a Node which can connect the linked list through linking to the next node, as well as take
//in the name (given by "payload")
struct Node {
    string payload;
    Node* next;
};   



//Allocates a new node and points to it, initializing the "payload" to whatever name it is given, as well
//as initializing the next pointer to null. This will be adjusted in a later function. 
Node* newNode(string payload) {
   Node* newPlayerNode = new Node();
   newPlayerNode->payload = payload; 
   newPlayerNode->next = nullptr; 
   return newPlayerNode;
}

//Creates the new nodes for the amount of people selected to be in the game. It checks if head is null, then
//proceeds to make a head and "prev" pointer for it, to which it is soon linked as more nodes are later
//initialized. Links the last made node to the head in order to complete the circular list. 
Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); // initialize head specially
            prev = head;  
        } else {
            prev->next = newNode(name);
            prev = prev->next;
        }
    }

    if (prev != nullptr) {
        prev -> next = head; // make circular
    }
    return head;
}


//Prints out every node's data from the linked list by iterating through the circular list and stopping when 
//the curr pointer returns to the reference pointer, which is the start of where the list begins to print its
//node data. 
void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

//It runs through the circular linked list created by the loadGame function, moving the curr and prev pointer,
//with the prev pointer always trailing behind the curr pointer when moving onto the next pointer. After the loop
//iterates k amount of times, the curr node is what is selected to be deleted, so the prev pointer latches onto
//the curr pointer's next node to prevent the circular linked list from breaking. 
Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr; 
            curr = curr->next;    
        }

        prev->next = curr->next;  // delete kth node
        delete curr;
        curr = prev->next; 
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
   //Code turd: there was a "max" variable that was unused. 
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs (and puts the list of names into a vector to be extracted later).
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game (through creating the circular linked list and giving each node its respective
    // values. 
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);
    
    //Uses the returned node from runGame function to print out the name of the winner. 
    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }
    
    //Delete lastPerson so that this isn't left in the heap. 
    delete lastPerson; 
    return 0;
}

