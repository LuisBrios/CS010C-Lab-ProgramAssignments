#include <iostream>
using namespace std;

#include "Heap.h"

//Initializes the heap array so that it may start with 0 elements.
Heap::Heap(){
    numItems = 0;  
}

//Once the code finishes running, it goes through each index, deletes the object, and moves onto the next. 
Heap::~Heap(){
    for (unsigned int i = 0; i < numItems; ++i){
        delete arr[i]; 
    }
}

//It initializes the new object at the bottom of the heap, and it percolates up if the priority level is higher than the parentNode, swapping
//places. 
void Heap::enqueue(PrintJob* newObj){
    int nodeIndex = numItems;
    int parentIndex; 
    if (numItems < MAX_HEAP_SIZE){
        if(nodeIndex == 0){
            arr[nodeIndex] = newObj;
        }
        else{
            while (nodeIndex > 0){
                arr[nodeIndex] = newObj; 
                parentIndex = ((nodeIndex - 1)/2);
                if (arr[nodeIndex]->getPriority() <= arr[parentIndex]->getPriority()){
                    return;
                }
                else {
                    swap(arr[nodeIndex], arr[parentIndex]);
                    nodeIndex = parentIndex; 
                }
            }
        }
        ++numItems;
    }
}

//Calls on the private helper function; makes sure that the array does have at least one object before commencing. 
void Heap::dequeue(){
    if (numItems == 0){
        return; 
    }
    else {
        arr[0] = arr[numItems-1];
        --numItems;
        trickleDown(0);
    }
}

//Returns the node with the highest priority (always the root). 
PrintJob* Heap::highest(){
    if (numItems != 0){
        return arr[0]; 
    }
    return 0;
}

//Prints out the node with the highest priority (the root). 
void Heap::print(){
    cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl; 
}

//Compares the node to it's child node. If it has a smaller priority than the child, the node percolates down, swapping with the child. =
void Heap::trickleDown(int nodeIndex){
    int childIndex = (2*nodeIndex+1);
    int maxIndx = nodeIndex;
    
    if ((childIndex < numItems) && (arr[childIndex]->getPriority() > arr[maxIndx]->getPriority())){
        maxIndx = childIndex;
    }
    if ((childIndex+1 < numItems) && (arr[childIndex+1]->getPriority() > arr[maxIndx]->getPriority())){
        maxIndx = childIndex+1;
    } 
    if (nodeIndex != maxIndx){
        swap(arr[nodeIndex], arr[maxIndx]);
        trickleDown(maxIndx); 
    }
}