#include <iostream>
#include <vector> 
#include <string> 
#include <stdexcept> 
using namespace std; 

//Typename + Function Declarations. Implementations are below main. 
template<typename T>
unsigned min_index(const vector<T> &vals, const unsigned index);

template<typename T>
void selection_sort(vector<T> &vals);

template<typename T>
T getElement(const vector<T> vals, const int index); 

vector<char> createVector(); 

int main (){
    //Selection sort test. For this, a list of random double numbers are inputed into the vector solely to see if everything will be ordered
    //properly. Once it works for this, it should work well for both string and integer, as it applies the same logic (in a template).
    cout << "Starting Selection Sort Test." << endl; 
    vector<char> newVect; 
    newVect.push_back('q');
    newVect.push_back('h');
    newVect.push_back('a');
    newVect.push_back('t');
    newVect.push_back('u');
    newVect.push_back('e');
    newVect.push_back('o');
    newVect.push_back('!');

    //Comparison of the vector before and after being sorted. 
    for (unsigned int i = 0; i < newVect.size(); ++i){
        cout << newVect.at(i) << " ";
    } 
    selection_sort(newVect);
    cout << endl; 
    for (unsigned int i = 0; i < newVect.size(); ++i){
        cout << newVect.at(i) << " ";
    }
    cout << endl;
    cout << "Testing complete." << endl;
    
    //For Part B: A vector is created that randomly selects a certain amount of letters (in alphabetical order) to be pushed into the vector.
    //Uses try, throw, and catch to detect if the user attempts to put an index that does not exist in the vector. If the user does, then an
    //exception is thrown. 
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index; 
    int upperindx; 
    int numOfRuns = 10;
    upperindx = vals.size();
    cout << upperindx; 
    while(--numOfRuns >= 0){
        try { 
            cout << "Enter a number: " << endl;
            cin >> index;
            if (index < 0) {
                throw out_of_range("out of range exception occured.");
            }
            if (index >= upperindx){
                throw out_of_range("out of range exception occured.");
            }
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch (out_of_range& excpt){
            cout << excpt.what() << endl; 
        }
    }

    return 0; 
}

//Given any vector of any type, this function simply goes through each index (starting with the index provided by the user and ending at the end)
//of the vector, comparing it with the index with the smallest value (starting with the value of the first index). If a value is smaller than
//the current minimum, then the newest value becomes the newest minimum. 
template<typename T>
unsigned min_index(const vector<T> &vals, const unsigned index){
    unsigned int min_index;
    min_index = index;   
    for (unsigned int i = index; i < vals.size(); ++i){
        if (vals.at(i) < vals.at(min_index)){
            min_index = i; 
        }
    }
    return min_index; 
}

//The function goes through a vector and uses the selection sort method to swap every value into ascending order. It starts off with index 0,
//checking for the minimum value, swapping, then increasing the index (so that the smallest value is not swapped anymore, and a new smallest
//index can be located) until the index is the same size as the vector. 
template<typename T>
void selection_sort(vector<T> &vals){
    unsigned int smallest_indx; 
    T var_swapper; 
    for (unsigned int i = 0; i < vals.size(); ++i){
        smallest_indx = min_index(vals, i);

        var_swapper = vals.at(i); 
        vals.at(i) = vals.at(smallest_indx);
        vals.at(smallest_indx) = var_swapper; 
    }
}

//Given an index by the user, this function simply returns the value of any desired index. This function has a template so that any type of
//vector can be used to output a variable (of the same type). 
template<typename T>
T getElement(const vector<T> vals, const int index){
    T accessed_element;
    for (unsigned int i = 0; i < vals.size(); ++i){
        accessed_element = vals.at(index); 
    }
    return accessed_element; 
}

//Creates a vector that simply has the alphabet pushed into it (but at a random size. Not all 26 letters may appear; it is random). 
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++){
        vals.push_back(c);
        c++;
    }
return vals;
}