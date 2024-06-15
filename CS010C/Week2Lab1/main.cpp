#include <iostream>
using namespace std; 

#include "IntList.h" 

//A test of each and every function; not many test cases, as there aren't really edge cases to check thanks to the dummy nodes. 

int main() {
    IntList newlist1; 
    cout << "With no additional operations, list is: " <<  newlist1.empty() << endl;
    newlist1.push_front(5);
    cout << "Current List: " << newlist1 << endl;
    cout << "With an additional operation, the list is: " << newlist1.empty() << endl;
    newlist1.pop_back();
    cout << "Removing the value. The list is now: " << newlist1.empty() << endl; 
    newlist1.push_front(1);
    newlist1.push_back(2);
    newlist1.push_back(3);
    newlist1.push_back(4); 
    newlist1.push_back(5);
    cout << "Expecting Numbers 1-5" << endl;
    cout << "Numbers: " << newlist1 << endl;
    cout << "Numbers in Reverse: ";
    newlist1.printReverse(); 
    cout << endl;
    cout << "Removing Front and Back. New Nums should be 2 - 4. " << endl;
    newlist1.pop_back();
    newlist1.pop_front(); 
    cout << "New Numbers: " << newlist1 << endl; 
    cout << endl; 
    return 0;
}