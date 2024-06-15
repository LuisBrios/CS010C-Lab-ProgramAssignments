#pragma once
#include <string>
using namespace std; 


/*These member functions and constructors are made in-line, as they are relatively small and need not be placed in a cpp file when it can 
be easily created here. */

class PlaylistNode{
    public:
        PlaylistNode()
            :uniqueID("none"),
             songName("none"),
             artistName("none"),
             songLength(0),
             nextNodePtr(nullptr)
            {
            }

        PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength)
            :uniqueID (uniqueID),
             songName (songName),
             artistName (artistName),
             songLength (songLength),
             nextNodePtr(nullptr)
            {
            }

        void InsertAfter(PlaylistNode* nextNode);
        void SetNext(PlaylistNode* nextNode); 

        const string& GetID() const {
            return uniqueID;
        }
        const string& GetSongName() const {
            return songName; 
        }
        const string& GetArtistName() const {
            return artistName;
        }
        int GetSongLength() const {
            return songLength; 
        }
        const PlaylistNode* GetNext() const {
            return nextNodePtr;
        }
        PlaylistNode* GetNext(){
            return nextNodePtr;
        }
    private:
        string uniqueID;
        string songName;
        string artistName; 
        int songLength;
        PlaylistNode* nextNodePtr;
};

class Playlist : public PlaylistNode{
    public:
        Playlist()
            :head(nullptr),
             tail(nullptr)
            {
            }

        ~Playlist(); 
        bool empty() const;
        void push_back(const PlaylistNode& songNode);
        void remove(const string& uniqueID); 
        void output_list() const; 
        void artist_select(const string& artistName) const; 
        void move_songs(int currPos, int newPos); 
        int total_time() const; 
    private:
        PlaylistNode* head;
        PlaylistNode* tail;   
};