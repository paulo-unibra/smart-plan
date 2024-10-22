#ifndef CRONOGRAM_H
#define CRONOGRAM_H

int createCronogram(struct User *loggedUser);
void consultCronogram(struct User *loggedUser);
int hasAlreadyCreatedCronogram(struct User *loggedUser);
int removeCurrentCronogram(struct User *loggedUser);
void handleBlockChosedMatters(char **choosenMateriesNames, struct Materia *matters, int currentSizeMateries, int *choosenMateries);

#endif