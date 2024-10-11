#ifndef LOGIN_H
#define LOGIN_H

struct User
{
    char name[255];
    char email[255];
    char password[255];
    char conf_password[255];
};

void initialMenu(int *option);
void menuLogin();
void registerUser(int *logged, struct User *user);
void login(int *logged, struct User *user);

#endif