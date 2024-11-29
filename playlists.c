#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlists.h"
#include "songs_library.h"
#include "login.h"
#include "utility.h"

Playlist* playlistHead = NULL;

void savePlaylistsToFile(){
    FILE* file = fopen("playlists.txt", "w");
    if (!file) {
        printf(RED"Error opening playlists file for writing.\n"RESET);
        return;
    }

    Playlist* current = playlistHead;
    while (current){
        fprintf(file, "%s|%s\n", current->name, current->userID);
        Song* song = current->songs;
        while (song) {
            fprintf(file, "%d|%s|%s|%d\n", song->id, song->title, song->artist, song->duration);
            song = song->next;
        }
        fprintf(file, "---\n");
        current = current->next;
    }
    fclose(file);
}

void loadPlaylistsFromFile(){
    FILE* file = fopen("playlists.txt", "r");
    if (!file) {
        printf(RED"No playlists file found. Starting with no playlists.\n"RESET);
        return;
    }

    char line[256];
    Playlist* currentPlaylist = NULL;

    while (fgets(line, sizeof(line), file)){
        if (strcmp(line, "---\n") == 0) {
            currentPlaylist = NULL;
        } else if (!currentPlaylist){
            Playlist* newPlaylist = (Playlist*)malloc(sizeof(Playlist));
            if (!newPlaylist){
                printf(RED"Memory allocation failed.\n"RESET);
                fclose(file);
                return;
            }

            sscanf(line, "%[^|]|%s", newPlaylist->name, newPlaylist->userID);
            newPlaylist->songs = NULL;
            newPlaylist->next = playlistHead;
            playlistHead = newPlaylist;
            currentPlaylist = newPlaylist;
        } else {
            Song* newSong = (Song*)malloc(sizeof(Song));
            if (!newSong) {
                printf(RED"Memory allocation failed.\n"RESET);
                fclose(file);
                return;
            }

            sscanf(line, "%d|%[^|]|%[^|]|%d", &newSong->id, newSong->title, newSong->artist, &newSong->duration);
            newSong->next = currentPlaylist->songs;
            currentPlaylist->songs = newSong;
        }
    }

    fclose(file);
}

void createPlaylist(const char* name){
    User* user = getLoggedInUser();
    if (!user){
        printf(RED"You must be logged in to create a playlist.\n"RESET);
        return;
    }

    Playlist* newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    if (!newPlaylist){
        printf(RED"Memory allocation failed.\n"RESET);
        return;
    }

    strcpy(newPlaylist->name, name);
    strcpy(newPlaylist->userID, user->studentID);
    newPlaylist->songs = NULL;
    newPlaylist->next = playlistHead;
    playlistHead = newPlaylist;

    savePlaylistsToFile();
    printDivider();
    printf(GREEN"Playlist '%s' created successfully!\n"RESET, name);
    printDivider();
    printf(YELLOW"Press enter to go back...."RESET);
}

void addSongToPlaylist(Playlist* playlist){
    int songID;
    printDivider();
    printf(YELLOW"Enter the ID of the song you want to add: "RESET);
    scanf("%d", &songID);

    Song* librarySong = findSongInLibrary(songID);
    if (!librarySong){
        printf(GREEN"Song with ID %d not found in the library.\n"RESET, songID);
        return;
    }

    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong){
        printf(RED"Memory allocation failed.\n"RESET);
        return;
    }
    *newSong = *librarySong;
    newSong->next = playlist->songs;
    playlist->songs = newSong;
    savePlaylistsToFile();
    printf(GREEN"Song '%s' by '%s' added to playlist '%s'.\n"RESET, librarySong->title, librarySong->artist, playlist->name);
    printf(YELLOW"Press enter to go back...."RESET);
}

void removeSongFromPlaylist(Playlist* playlist){
    int songID;
    printf(YELLOW"Enter the ID of the song you want to remove: "RESET);
    scanf("%d", &songID);
    Song* current = playlist->songs;
    Song* prev = NULL;
    while (current){
        if (current->id == songID){
            if (prev){
                prev->next = current->next;
            } else{
                playlist->songs = current->next;
            }

            free(current);
            savePlaylistsToFile();
            printf(GREEN"Song with ID %d removed from playlist '%s'.\n"RESET, songID, playlist->name);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf(RED"Song with ID %d not found in playlist '%s'.\n"RESET, songID, playlist->name);
}

void initialize_P_Library(){
    if (!playlistHead){
        loadPlaylistsFromFile();
    }
}

void removePlaylist(const char* name){
    User* user = getLoggedInUser();
    Playlist* current = playlistHead;
    Playlist* prev = NULL;

    while (current){
        if (strcmp(current->name, name) == 0 && strcmp(current->userID, user->studentID) == 0){
            if (prev){
                prev->next = current->next;
            }
            else{
                playlistHead = current->next;
            }
            Song* song = current->songs;
            while (song){
                Song* nextSong = song->next;
                free(song);
                song = nextSong;
            }
            free(current);
            savePlaylistsToFile();
            printf(GREEN"Playlist '%s' removed successfully.\n"RESET, name);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf(RED"Playlist '%s' not found.\n"RESET,name);
}

void viewPlaylists(){
    User* user = getLoggedInUser();
    if (!user){
        printf(RED"You must be logged in to view playlists.\n"RESET);
        pauseScreen(); 
        return;
    }
    while (1){
        clearScreen();
        Playlist* current = playlistHead;
        int playlistCount = 0;
        printf(BLUE"\nYour Playlists:\n"RESET);
        while(current){
            if (strcmp(current->userID, user->studentID) == 0){
                printf(GREEN"[%d] Playlist: %s\n"RESET, ++playlistCount, current->name);
                Song* song = current->songs;
                while (song){
                    printf(YELLOW"  [%d] %s by %s (%d seconds)\n"RESET,
                           song->id, song->title, song->artist, song->duration);
                    song = song->next;}
            }
            current = current->next;
        }
        if (playlistCount == 0){
            printf(RED"You have no playlists.\n"RESET);
        }
        int choice;
        printDivider();
        printCentered(BLUE"\nOptions:\n"RESET);
        printDivider();
        printCentered(YELLOW"1. Add a song to a playlist\n");
        printCentered("2. Remove a song from a playlist\n");
        printCentered("3. Remove a playlist\n");
        printCentered("4. Return to main menu\n"RESET);
        printDivider();
        printf(YELLOW"Enter your choice: "RESET);        
        if (scanf("%d", &choice) != 1){
            printf(RED"Invalid input. Please enter a valid number.\n"RESET);
            while (getchar() != '\n'); 
            continue;
        }
        if (choice == 4){
            break;
        }
        if (choice != 1 && choice != 2 && choice != 3) {
            printf(RED"Invalid choice. Please select a valid option.\n"RESET);
            continue;
        }
        int playlistIndex;
        printf(YELLOW"Enter the number of the playlist to manage: "RESET);
        if (scanf("%d", &playlistIndex) != 1){
            printf(RED"Invalid input. Please enter a valid number.\n"RESET);
            while (getchar() != '\n'); 
            continue;
        }
        current = playlistHead;
        Playlist* selectedPlaylist = NULL;
        for (int i = 1; current; current = current->next, i++){
            if (i == playlistIndex){
                selectedPlaylist = current;
                break;
            }
        }
        if (!selectedPlaylist){
            printf(RED"Invalid playlist number.\n"RESET);
            continue;
        }

        if (choice == 1){
            addSongToPlaylist(selectedPlaylist);
        }
        else if (choice == 2){
            removeSongFromPlaylist(selectedPlaylist);
        }
        else if (choice == 3){
            removePlaylist(selectedPlaylist->name);
        }
    }
}