#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "utility.h"
#include "main.h"

User* userHead = NULL;
User* loggedInUser = NULL;

void saveNewUserToFile(User* user){
    FILE* file = fopen("users.txt", "a");
    if (!file){
        printf(RED"Error opening users file for appending.\n"RESET);
        return;
    }
    fprintf(file, "%s|%s\n", user->studentID, user->password);
    fclose(file);
}

void loadUsersFromFile(){
    FILE* file = fopen("users.txt", "r");
    if (!file){
        printf(RED"No users file found. Starting with no users.\n"RESET);
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)){
        User* newUser = (User*)malloc(sizeof(User));
        if (!newUser){
            printf(RED"Memory allocation failed.\n"RESET);
            fclose(file);
            return;
        }
        sscanf(line, "%[^|]|%s", newUser->studentID, newUser->password);
        newUser->next = userHead;
        userHead = newUser;
    }
    fclose(file);
}
void signup(const char* studentID, const char* password){
    User* current = userHead;
    while (current){
        if (strcmp(current->studentID, studentID) == 0){
            printf(RED"This ID already exists. Try again.\n"RESET);
            pauseScreen();
            return;
        }
        current = current->next;
    }
    User* newUser = (User*)malloc(sizeof(User));
    if (!newUser){
        printf(RED"Memory allocation failed.\n"RESET);
        pauseScreen();
        return;
    }
    strcpy(newUser->studentID, studentID);
    strcpy(newUser->password, password);
    newUser->next = userHead;
    userHead = newUser;
    saveNewUserToFile(newUser);
    printDivider();
    printf(GREEN"Sign-up successful! You can now log in.\n"RESET);
    printDivider();
    printf(YELLOW"Press enter to continue...."RESET);
    pauseScreen();
}
int login(const char* studentID, const char* password){
    User* current = userHead;
    while (current){
        if (strcmp(current->studentID, studentID) == 0 && strcmp(current->password, password) == 0){
            loggedInUser = current;
            printDivider();
            printf(GREEN"Login successful! Welcome, %s.\n"RESET, studentID);
            printDivider();
            printf(YELLOW"Press enter to continue...."RESET);
            pauseScreen();
            mainMenu();
            return 1;
        }
        current = current->next;
    }
    printf(RED"Login failed. Check your credentials.\n"RESET);
    printf(YELLOW"Press enter to go back...."RESET);
    pauseScreen();
    return 0;
}

User* getLoggedInUser(){
    return loggedInUser;
}

void loginMenu(){
    loadUsersFromFile();
    int choice;
    while (1){
        clearScreen();
        printDivider();
        printCentered(BLUE"Please either login to enter or signup if you do not have an account.\n"RESET);
        printDivider();
        printCentered(YELLOW"1. Sign Up\n");
        printCentered("2. Login\n");
        printCentered("3. Exit\n"RESET);
        printDivider();
        printf(YELLOW"Enter your choice: "RESET);
        scanf("%d", &choice);
        switch (choice){
            case 1:{
                char studentID[40];
                char password[40];
                printDivider();
                printf(YELLOW"Enter University ID: "RESET);
                scanf("%s", studentID);
                getchar();
                printf(YELLOW"Enter Password: "RESET);
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0';
                printDivider();
                signup(studentID, password);
                break;
            }
            case 2:{
                char studentID[40];
                char password[40];
                printDivider();
                printf(YELLOW"Enter University ID: "RESET);
                scanf("%s", studentID);
                getchar();
                printf(YELLOW"Enter Password: "RESET);
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0';
                printDivider();
                if (login(studentID, password))
                    {return;}
                break;
            }
            case 3:
                clearScreen();
                printDivider();
                printCentered(GREEN"Thank You!\n"RESET);
                printDivider();
                exit(0);
        }
    }
    
}