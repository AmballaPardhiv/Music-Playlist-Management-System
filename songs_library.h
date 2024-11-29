#ifndef SONGS_LIBRARY_H
#define SONGS_LIBRARY_H
typedef struct Song{
    int id;
    char title[100];
    char artist[100];
    int duration;
    int year;
    struct Song* next;
} Song;
void saveSongsToFile();
void loadSongsFromFile();
void addSongToLibrary();
void sortSongsByTitle();
void sortSongsByArtist();
void sortSongsByOldestToNewest();
void sortSongsByNewestToOldest();
void sortSongsByDuration();
void viewSongs();
void removeSongFromLibrary();
void initializeLibrary();
Song* findSongInLibrary(int songID);

#endif

