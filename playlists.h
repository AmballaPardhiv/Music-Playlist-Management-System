#ifndef PLAYLISTS_H
#define PLAYLISTS_H

#include "songs_library.h"

typedef struct Playlist{
    char name[100];
    Song* songs;
    struct Playlist* next;
    char userID[40];
}Playlist;

extern Playlist* playlistHead;

void createPlaylist(const char* name);        
void viewPlaylists();
void savePlaylistsToFile();
void loadPlaylistsFromFile();
void addSongToPlaylist(Playlist* playlist);
void removeSongFromPlaylist(Playlist* playlist);
void initialize_P_Library();
void removePlaylist();

#endif
