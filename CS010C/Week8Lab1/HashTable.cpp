#include "HashTable.h"
#include "WordEntry.h"

#include <fstream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

//Deallocates the array once the program is finished. 
HashTable::~HashTable(){
	delete[] hashTable; 
}

//Default constructor if necessary. In case a size is not implemented manually. 
HashTable::HashTable(){
	size = 10;
	hashTable = new list<WordEntry>[size];
}

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/

//Allocates an array of size s so that a user may input their desired "WordEntry" objects. 
HashTable::HashTable (int s) {
    size = s;
    hashTable = new list<WordEntry>[size];
}

/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/

//Given the inital value of 7 and the multiplier value of 31, this function serves to (try and) produce a unique integer so that, upon inserting, removing, or searching for
//an object, you can access a specific index in the array, then traverse from there if necessary. 
int HashTable::computeHash(const string &s) const{
    long unsigned stringHash = 7; 
    for (unsigned int i = 0; i < s.size(); ++i){
        stringHash = (stringHash * 31) + s.at(i);
    }  
    return (stringHash % size);
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
//Serves to input a string into a bucket (which depends on the hash computed from the string). If the word exists already, the score is simply added to show how many times
//it appears. If not (and the bucket meant for it is full), the table traverses the array until an empty space is met, then inserts it. 
void HashTable::put(const string &s, int score){
    int hashValue = computeHash(s);
    for(WordEntry& eachWordEntry : hashTable[hashValue]){
        if (eachWordEntry.getWord() == s){
            eachWordEntry.addNewAppearance(score);
            return;
        }
    }
    WordEntry newEntry(s, score);
    hashTable[hashValue].push_back(newEntry); 
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

//Accesses a certain index based on the computed hash (and if necessary, traverses the array to locate the passed in string) and returns the average of the WordEntry. 
//If it does not exist, 2.0 is passed in, as it is the "default average."
double HashTable::getAverage(const string &s) const{
    int hashValue = computeHash(s);
    for (WordEntry& eachWordEntry : hashTable[hashValue]){
        if (eachWordEntry.getWord() == s){
            return eachWordEntry.getAverage(); 
        }
    }
    return 2.0; 
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/

//Checks the bucket printed out by computeHash in the event that the element is at said bucket (thus making the whole search faster and less costly. If the element is not
//at the computedHash index, then the array is traversed to find it) and returns true if the element exists in the array. False if otherwise. 
bool HashTable::contains(const string &s) const{
    int hashValue = computeHash(s); 
    for(WordEntry& eachWordEntry : hashTable[hashValue]){
        if (eachWordEntry.getWord() == s){
            return true;
        }
    }
    return false; 
}

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);

	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}	

	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}