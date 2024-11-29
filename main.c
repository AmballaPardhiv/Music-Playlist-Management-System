#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songs_library.h"
#include "playlists.h"
#include "login.h"
#include "utility.h"

void mainMenu(){
    int choice;
    while (1){
        clearScreen();
        printDivider();
        printCentered(BLUE"Main Menu:\n"RESET);
        printDivider();
        printCentered(YELLOW"1. View Songs\n");
        printCentered("2. Add Song to Library\n");
        printCentered("3. View Playlists\n");
        printCentered("4. Create a new Playlist\n");
        printCentered("5. Remove Song from Library\n");
        printCentered("6. Logout\n"RESET);
        printDivider();
        printf(YELLOW"Enter your choice: "RESET);
        if (scanf("%d", &choice) != 1){
            printf(RED"Invalid input. Please enter a number between 1 and 6.\n"RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choice){
            case 1:
                viewSongs();
                pauseScreen();
                break;
            case 2:
                addSongToLibrary();
                pauseScreen();
                break;
            case 3:
                clearScreen();
                viewPlaylists();
                pauseScreen();
                break;
            case 4:
                clearScreen();
                char playlistName[100];
                    printCentered(YELLOW"Enter Playlist Name: "RESET);
                    getchar();
                    fgets(playlistName, sizeof(playlistName), stdin);
                    playlistName[strcspn(playlistName, "\n")] = '\0';
                    createPlaylist(playlistName);
                    pauseScreen();
                break;
            case 5:
                clearScreen();
                int songID;
                printCentered(YELLOW"Enter the ID of the song you want to remove: "RESET);
                if (scanf("%d", &songID) != 1)
                    {printCentered(RED"Invalid input. Song ID must be a number.\n"RESET);
                        while (getchar() != '\n');
                        break;}
                removeSongFromLibrary(songID);
                pauseScreen();
                break;
            case 6:
                loginMenu();
                return;
            default:
                printf(RED"Invalid choice. Please select a valid option.\n"RESET);
        }
    }
}
int main(){
    initializeLibrary();
    initialize_P_Library();
    loginMenu();
    pauseScreen();
    mainMenu();
    return 0;
}
