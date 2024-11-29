#ifndef LOGIN_H
#define LOGIN_H

typedef struct User{
    char studentID[40];
    char password[40];
    struct User* next;
}User;

extern User* userHead;
extern User* loggedInUser;

void saveNewUserToFile(User* user);
void loadUsersFromFile();
void signup(const char* studentID, const char* password);
int login(const char* studentID, const char* password);
User* getLoggedInUser();
void loginMenu();
#endif