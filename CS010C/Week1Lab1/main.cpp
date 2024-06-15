#include <iostream>
#include <string> 
using namespace std; 

#include "Playlist.h"

/*Print Menu function that keeps displaying after a user has chosen an action to perform on their playlist.*/

void PrintMenu(const string& userPlaylist); 

int main(){
    Playlist newPlaylist; 
    string userPlaylist;
    char userSelect;
    string userUniqueID;
    string userSongName;
    string userArtistName;
    int userSongLength; 
    int currSongPosition;
    int newSongPosition;

/* The user is prompted to enter the name of the playlist, which will be saved so that the Nodes can be put into it. */

    cout << "Enter playlist's title:" << endl;
    cout << endl; 
    getline(cin, userPlaylist); 
    PrintMenu(userPlaylist);
    cin >> userSelect; 


/*Depending on the user's choice, a variety of options are able to be made.*/

    while(userSelect != 'q'){
        if (userSelect == 'o'){
            cout << userPlaylist << " - OUTPUT FULL PLAYLIST" << endl; 
            if (newPlaylist.empty()){
                cout << "Playlist is empty" << endl; 
                cout << endl; 
            }
            else {
                (newPlaylist.output_list());
            }
        }
        else if (userSelect == 'a'){
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> userUniqueID;
            cin.ignore(); 
            cout << "Enter song's name:" << endl;
            getline(cin, userSongName);
            cout << "Enter artist's name:" << endl;
            getline(cin, userArtistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> userSongLength; 
            PlaylistNode newPlaylistNode(userUniqueID, userSongName, userArtistName, userSongLength);
            newPlaylist.push_back(newPlaylistNode);
            cout << endl; 
        }
        else if (userSelect == 'd'){
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> userUniqueID;
            newPlaylist.remove(userUniqueID);
            cout << endl; 
        }
        else if (userSelect == 'c'){
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> currSongPosition;
            cout << "Enter new position for song:" << endl;
            cin >> newSongPosition; 
            newPlaylist.move_songs(currSongPosition, newSongPosition); 
        }
        else if (userSelect == 's'){
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            cin.ignore(); 
            getline(cin, userArtistName);
            cout << endl; 
            newPlaylist.artist_select(userArtistName);
        }
        else if (userSelect == 't'){
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << newPlaylist.total_time() << " seconds" << endl; 
            cout << endl;
        }
        PrintMenu(userPlaylist); 
        cin >> userSelect; 
    }
    return 0; 
}

void PrintMenu(const string& userPlaylist){
    cout << userPlaylist << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl; 
}