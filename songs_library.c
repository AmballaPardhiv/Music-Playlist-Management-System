#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "songs_library.h"
#include "utility.h"

Song* songHead = NULL;
int nextSongID = 1;

void saveSongsToFile(){
    FILE* file = fopen("songs.dat", "wb");
    if (!file){
        printf(RED"Error: Could not open songs.dat for writing.\n"RESET);
        return;
    }
    Song* current = songHead;
    while (current){
        fwrite(current, sizeof(Song), 1, file);
        current = current->next;
    }
    fclose(file);
    printf(GREEN"Songs saved successfully!\n"RESET);
}
void loadSongsFromFile(){
    FILE* file = fopen("songs.dat", "rb");
    if (!file){
        printf(RED"No songs file found. Starting with an empty library.\n"RESET);
        return;
    }
    Song* newSong;
    while ((newSong = (Song*)malloc(sizeof(Song))) && fread(newSong, sizeof(Song), 1, file)){
        newSong->next = songHead;
        songHead = newSong;
        if (newSong->id >= nextSongID){
            nextSongID = newSong->id + 1;
        }
    }
    fclose(file);
    printf(GREEN"Songs loaded successfully.\n"RESET);
}
void addSongToLibrary(){
    clearScreen();
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (!newSong){
        printf(RED"Memory allocation failed.\n"RESET);
        return;
    }
    getchar();
    printDivider();
    printCentered(YELLOW"Enter song title(enter first letter in capital): "RESET);
    fgets(newSong->title, sizeof(newSong->title), stdin);
    newSong->title[strcspn(newSong->title, "\n")] = '\0';
    printCentered(YELLOW"Enter artist name(enter first letter in capital): "RESET);
    fgets(newSong->artist, sizeof(newSong->artist), stdin);
    newSong->artist[strcspn(newSong->artist, "\n")] = '\0';
    printCentered(YELLOW"Enter song duration(in seconds): "RESET);
    scanf("%d", &newSong->duration);
    printCentered(YELLOW"Enter song release year: "RESET);
    scanf("%d", &newSong->year);
    printDivider();
    newSong->id = nextSongID++;
    newSong->next = songHead;
    songHead = newSong;
    printf(GREEN"Song added successfully!\n"RESET);
    saveSongsToFile();
    printf(YELLOW"Press enter to go back...."RESET);
    pauseScreen();
}

void removeSongFromLibrary(int songID){
    Song* current = songHead;
    Song* previous = NULL;
    
    while (current != NULL && current->id != songID){
        previous = current;
        current = current->next;
    }
    
    if (current == NULL){
        printf(RED"Song with ID %d not found.\n"RESET, songID);
        return;
    }

    if (previous == NULL){
        songHead = current->next;
    } 
    else{
        previous->next = current->next;
    }
    
    free(current);
    printDivider();
    printf(GREEN"Song removed successfully!\n"RESET);
    saveSongsToFile();
    printf(YELLOW"Press enter to go back...."RESET);
    pauseScreen();
}
Song* findSongInLibrary(int songID){
    Song* current = songHead;
    while (current){
        if (current->id == songID){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void sortSongsByTitle(){
    if (!songHead || !songHead->next){
        return;
    }
    for (Song* current = songHead; current; current = current->next){
        for (Song* index = current->next; index; index = index->next){
            if (strcmp(current->title, index->title) > 0){
                char tempTitle[100];
                strcpy(tempTitle, current->title);
                strcpy(current->title, index->title);
                strcpy(index->title, tempTitle);
                char tempArtist[100];
                strcpy(tempArtist, current->artist);
                strcpy(current->artist, index->artist);
                strcpy(index->artist, tempArtist);
                float tempDuration = current->duration;
                current->duration = index->duration;
                index->duration = tempDuration;
                int tempYear = current->year;
                current->year = index->year;
                index->year = tempYear;
                int tempID = current->id;
                current->id = index->id;
                index->id = tempID;
            }
        }
    }
}

void sortSongsByArtist(){
    if (!songHead || !songHead->next) {
        return;
    }
    for(Song* current = songHead; current; current = current->next){
        for(Song* index = current->next; index; index = index->next){
            if(strcmp(current->artist, index->artist) > 0){
                char tempTitle[100];
                strcpy(tempTitle, current->title);
                strcpy(current->title, index->title);
                strcpy(index->title, tempTitle);
                char tempArtist[100];
                strcpy(tempArtist, current->artist);
                strcpy(current->artist, index->artist);
                strcpy(index->artist, tempArtist);
                float tempDuration = current->duration;
                current->duration = index->duration;
                index->duration = tempDuration;
                int tempYear = current->year;
                current->year = index->year;
                index->year = tempYear;
                int tempID = current->id;
                current->id = index->id;
                index->id = tempID;
            }
        }
    }
}

void sortSongsByOldestToNewest(){
    if (!songHead || !songHead->next){
        return;
    }
    for(Song* current = songHead; current; current = current->next){
        for(Song* index = current->next; index; index = index->next){
            if(current->year > index->year || 
                (current->year == index->year && strcmp(current->title, index->title) > 0)){
                char tempTitle[100];
                strcpy(tempTitle, current->title);
                strcpy(current->title, index->title);
                strcpy(index->title, tempTitle);
                char tempArtist[100];
                strcpy(tempArtist, current->artist);
                strcpy(current->artist, index->artist);
                strcpy(index->artist, tempArtist);
                float tempDuration = current->duration;
                current->duration = index->duration;
                index->duration = tempDuration;
                int tempYear = current->year;
                current->year = index->year;
                index->year = tempYear;
                int tempID = current->id;
                current->id = index->id;
                index->id = tempID;
            }
        }
    }
}

void sortSongsByNewestToOldest(){
    if (!songHead || !songHead->next){
        return;
    }
    for(Song* current = songHead; current; current = current->next){
        for(Song* index = current->next; index; index = index->next){
            if(current->year < index->year ||
                (current->year == index->year && strcmp(current->title, index->title) > 0)){
                char tempTitle[100];
                strcpy(tempTitle, current->title);
                strcpy(current->title, index->title);
                strcpy(index->title, tempTitle);
                char tempArtist[100];
                strcpy(tempArtist, current->artist);
                strcpy(current->artist, index->artist);
                strcpy(index->artist, tempArtist);
                float tempDuration = current->duration;
                current->duration = index->duration;
                index->duration = tempDuration;
                int tempYear = current->year;
                current->year = index->year;
                index->year = tempYear;
                int tempID = current->id;
                current->id = index->id;
                index->id = tempID;
            }
        }
    }
}

void sortSongsByDuration(){
    if(!songHead || !songHead->next){
        return;
    }
    for(Song* current = songHead; current; current = current->next){
        for(Song* index = current->next; index; index = index->next){
            if(current->duration > index->duration){
                char tempTitle[100];
                strcpy(tempTitle, current->title);
                strcpy(current->title, index->title);
                strcpy(index->title, tempTitle);
                char tempArtist[100];
                strcpy(tempArtist, current->artist);
                strcpy(current->artist, index->artist);
                strcpy(index->artist, tempArtist);
                float tempDuration = current->duration;
                current->duration = index->duration;
                index->duration = tempDuration;
                int tempYear = current->year;
                current->year = index->year;
                index->year = tempYear;
                int tempID = current->id;
                current->id = index->id;
                index->id = tempID;
            }
        }
    }
}

void initializeLibrary(){
    if(!songHead){
        loadSongsFromFile();
    }
}

void viewSongs(){
    clearScreen();
    int choice;
    while (1){
        printDivider();
        printCentered(BLUE"Choose how to sort the songs:\n"RESET);
        printDivider();
        printCentered(YELLOW"1. By Artist (Alphabetical)\n");
        printCentered("2. By Title (Alphabetical)\n");
        printCentered("3. By Newest to Oldest (Year)\n");
        printCentered("4. By Oldest to Newest (Year)\n");
        printCentered("5. By Duration (Ascending)\n");
        printCentered("6. Exit to main menu\n"RESET);
        printDivider();
        printf(YELLOW"Enter your choice (1-6): "RESET);
        
        if(scanf("%d", &choice) != 1){
            printf(RED"Invalid input. Please enter a number between 1 and 6.\n"RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choice){
            case 1:
                clearScreen();
                sortSongsByArtist();
                break;
            case 2:
                clearScreen();
                sortSongsByTitle();
                break;
            case 3:
                clearScreen();
                sortSongsByNewestToOldest();
                break;
            case 4:
                clearScreen();
                sortSongsByOldestToNewest();
                break;
            case 5:
                clearScreen();
                sortSongsByDuration();
                break;
            case 6:
                clearScreen();
                printf(YELLOW"Press enter to go back ...."RESET);
                return;
            default:
                printf(RED"Invalid choice. Please try again.\n"RESET);
                continue;
        }
        Song* current = songHead;
        if (!current){
            printf(RED"No songs available.\n"RESET);
        }
        else{
            while(current){
                printf(YELLOW"ID: %d, Title: %s, Artist: %s, Duration: %d seconds, Year: %d\n"RESET,
                       current->id, current->title, current->artist, current->duration, current->year);
                current = current->next;
            }
        }
    }
    pauseScreen();
}
