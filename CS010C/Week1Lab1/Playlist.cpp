#include <iostream>
using namespace std; 

#include "Playlist.h"

/*Destructor that simply serves to, once the program finishes running, deallocate any leftover memory in the heap
that has not been deleted before. It uses a pointer to go through each node (until nullptr is reached), deleting 
them one by one. */

Playlist::~Playlist(){
    for (PlaylistNode* currNode = head; currNode != nullptr; currNode = currNode -> GetNext()){
        delete currNode; 
    }
}

/*Mainly used as a helper function to determine whether or not it was appropriate to perform a task given if the list was empty or not
(detected by if head was set to any value). */

bool Playlist::empty() const{
    if (head == nullptr){
        return true;
    }
    else {
        return false; 
    }
}

/*As we are not able to use a struct to access the next node of a pointer, we must use a derived class. This means, to access it, a pointer
from the derived class Playlist must be able to access private data members from the base class. To do this, we needed to use a node
from the base class that would grant us the rights to access private data members. */
void PlaylistNode::SetNext(PlaylistNode* nextNode){
    nextNodePtr = nextNode; 
} 

/*Helper function for SetNext, practically. This function was more of a call, while the SetNext function was more of a direct access to the private data member.*/
void PlaylistNode::InsertAfter(PlaylistNode* nextNode){
    SetNext(nextNode); 
}

/*If a song were to be added, push_back would be used to create a new object and store it within the playlist. There were conditions for this when being created, 
as see in the code below. If the list was empty, then the head and tail would be initialized to the newly constructed PlayListNode. If not, then
only the tail would be changed, as we are always going to be adding a new object to the end of the list. */
void Playlist::push_back(const PlaylistNode& songNode){
    PlaylistNode* newSongNode = new PlaylistNode(songNode.GetID(), songNode.GetSongName(), songNode.GetArtistName(), songNode.GetSongLength());
    if (empty() == false){
        tail->SetNext(newSongNode);
        tail = newSongNode; 
    }
    else {
        head = newSongNode;
        tail = newSongNode; 
    }
}

/*This function simply served to display every node within the Playlist. It started at the head, then went all the way to nullptr, displaying
the private data member information from the PlayListNode class. As well, it just counted the amount of nodes displayed to resemble
a proper Playlist. */
void Playlist::output_list() const{
    int numberOfNodes = 1;
    for (PlaylistNode* currNode = head; currNode != nullptr; currNode = currNode->GetNext()){
        cout << numberOfNodes << "." << endl;
        cout << "Unique ID: " << currNode->GetID() << endl;
        cout << "Song Name: " << currNode->GetSongName() << endl;
        cout << "Artist Name: " << currNode->GetArtistName() << endl;
        cout << "Song Length (in seconds): " << currNode->GetSongLength() << endl; 
        cout << endl; 
        numberOfNodes += 1; 
    } 
}

/*This function served to remove any song that the user requested, by giving them the opportunity to pass through an ID to eliminate a song
from the playlist. Once the user entered a unique ID, every node from the playlist is accessed (assuming the playlist is not empty) 
until either the song containing the user passed ID is removed, or every element is accessed but no ID is found. If the song is found, it 
is deleted from the heap to deallocate any excess memory. */

void Playlist::remove(const string& uniqueID){
    if (head != nullptr){
        PlaylistNode* prevNode = head; 
        if (prevNode->GetID() == uniqueID){
            head = prevNode->GetNext(); 
            cout << "\"" << prevNode->GetSongName() << "\" removed." << endl; 
            delete prevNode; 
        }
        else{
            for (PlaylistNode* currNode = head->GetNext(); currNode != nullptr; currNode = currNode->GetNext()){
                if (currNode->GetID() == uniqueID){
                    prevNode->SetNext(currNode->GetNext());
                    cout << "\"" << currNode->GetSongName() << "\" removed." << endl; 
                    delete currNode; 
                }
                prevNode = prevNode->GetNext(); 
            }
        }
    }
} 

/*Outputs songs by a specific artist that the user has chosen. This function serves to display each individual song node, 
but skips any that do not have the artistName data member equivalent to the string passed in. It does so by iterating through
the node until nullptr is reached and, even though some songs can be skipped, keeps the counter going to produce a list format
that does not simply go 1, 2, 3, but stays in format as if there were songs between it. */

void Playlist::artist_select(const string& artistName) const{
    int numberOfNodes = 1;
    for (PlaylistNode* currNode = head; currNode != nullptr; currNode = currNode->GetNext()){
        if (currNode->GetArtistName() == artistName){ 
            cout << numberOfNodes << "." << endl;
            cout << "Unique ID: " << currNode->GetID() << endl;
            cout << "Song Name: " << currNode->GetSongName() << endl;
            cout << "Artist Name: " << currNode->GetArtistName() << endl;
            cout << "Song Length (in seconds): " << currNode->GetSongLength() << endl; 
            cout << endl; 
        }
        numberOfNodes += 1; 
    }    
}


/*This function permitted the user the ability to switch any song's position to their liking. There were many conditions to this function, 
which usually regard to the head and tail nodes. Of course, if a user wanted to switch a head or tail node, the linked list must be restructed, 
which usually called for 2-3 pointers to assist with the process. The restructured linked list would have the list in the user's designated order,
as well as keeping the head and tail updated. If the user were to input a number that does not fit the bounds, it would go to the closest bound
and switch through such. In my code, there are some blank if statements, but that is more of a visual to show that no change is necessary. */

void Playlist::move_songs(int currPos, int newPos){
    int numberOfNodes = 0;
    int currentPosition = 2;
    if (head != nullptr){
        for(PlaylistNode* currNode = head; currNode != nullptr; currNode = currNode->GetNext()){
            ++numberOfNodes;
        }
        PlaylistNode* prevNode = head;  
        PlaylistNode* currNode = head->GetNext();    
        if (newPos <= 1){
            if (currPos <= 1){
            }
            else if (currPos >= numberOfNodes){
                while (currentPosition < numberOfNodes){
                    prevNode = prevNode->GetNext(); 
                    currNode = currNode->GetNext(); 
                    ++currentPosition; 
                }
                currNode->SetNext(head);
                head = currNode;
                prevNode->SetNext(nullptr);
                tail = prevNode; 
            }
            else {
                while (currentPosition < currPos){
                    prevNode = prevNode->GetNext(); 
                    currNode = currNode->GetNext(); 
                    ++currentPosition; 
                }
                prevNode->SetNext(currNode->GetNext());
                currNode->SetNext(head);
                head = currNode;
            }
        }
        else if (newPos >= numberOfNodes){
            if (currPos <= 1){
                head = currNode;
                tail->SetNext(prevNode);
                tail = prevNode; 
                tail->SetNext(nullptr); 
            }
            else if (currPos >= numberOfNodes){
            }
            else {
                while (currentPosition < currPos){
                    prevNode = prevNode->GetNext(); 
                    currNode = currNode->GetNext(); 
                    ++currentPosition; 
                }
                prevNode->SetNext(currNode->GetNext());
                tail->SetNext(currNode); 
                tail = currNode; 
                tail->SetNext(nullptr); 
            }       
        }
        else {
            PlaylistNode* targetNode = head; 
            if (currPos <= 1){
                while (currentPosition < newPos){
                    prevNode = prevNode->GetNext();
                    currNode = currNode->GetNext(); 
                    ++currentPosition; 
                }
                prevNode = prevNode->GetNext();
                currNode = currNode->GetNext(); 

                head = head->GetNext(); 
                prevNode->SetNext(targetNode); 
                targetNode->SetNext(currNode);

                cout << "\"" << targetNode->GetSongName() << "\" moved to position " << newPos << endl << endl; 
            }
            else if (currPos >= numberOfNodes){
                while (currentPosition < newPos){
                    prevNode = prevNode->GetNext();
                    currNode = currNode->GetNext();
                    ++currentPosition;
                }
                currentPosition = 1;
                while (currentPosition < (numberOfNodes - 1)){
                    targetNode = targetNode->GetNext();
                    ++currentPosition; 
                }
                prevNode->SetNext(tail);
                tail->SetNext(currNode);
                tail = targetNode; 
                tail->SetNext(nullptr); 
            }
            else {
                if (currPos > newPos){
                    while (currentPosition < newPos){
                        prevNode = prevNode->GetNext();
                        currNode = currNode->GetNext();
                        ++currentPosition; 
                    }
                    currentPosition = 1;
                    while (currentPosition < currPos){
                        targetNode = targetNode->GetNext();
                        ++currentPosition; 
                    }

                    prevNode->SetNext(targetNode);
                    currNode->SetNext(targetNode->GetNext());
                    targetNode->SetNext(currNode); 
                }
                else {
                    while (currentPosition < newPos){
                        prevNode = prevNode->GetNext();
                        currNode = currNode->GetNext();
                        ++currentPosition; 
                    }
                    currentPosition = 1;
                    while (currentPosition < (currPos-1)){
                        targetNode = targetNode->GetNext();
                        ++currentPosition; 
                    }
                    targetNode->GetNext()->SetNext(currNode->GetNext());
                    currNode->SetNext(targetNode->GetNext());
                    targetNode->SetNext(prevNode); 
                }
            }
        }
    }
}

/*Declares an int variable that will be used as a counter, as it iterates through every node inside
the loop, accessing each SongLength data member, and tallying them up to return the total (so it can
be displayed in main)*/

int Playlist::total_time() const{
    int totalPlaylistSec = 0; 
    for (PlaylistNode* currNode = head; currNode != nullptr; currNode = currNode->GetNext()){
        totalPlaylistSec += (currNode->GetSongLength()); 
    }
    return totalPlaylistSec; 
}