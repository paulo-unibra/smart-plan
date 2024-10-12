#ifndef CRONOGRAM_H
#define CRONOGRAM_H

int createCronogram(struct User *loggedUser);
void consultCronogram(struct User *loggedUser);
int hasAlreadyCreatedCronogram(struct User *loggedUser);
int removeCurrentCronogram(struct User *loggedUser);

#endif