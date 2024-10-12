#ifndef LOGIN_H
#define LOGIN_H

struct User
{   
    long id;
    char name[255];
    char email[255];
    char password[255];
    char conf_password[255];
    int cursoId;
    int periodo;
};

void initialMenu(int *option);
void menuLogin(struct User *user);
void registerUser(int *logged, struct User *user);
void login(int *logged, struct User *user);

#endif