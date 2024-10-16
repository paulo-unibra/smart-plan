#ifndef MATERIES_H
#define MATERIES_H


struct Materia
{
    int id;
    int cursoId;
    char nome[255];
    int periodo;
    int escolhida;
};

int prepareMateries(int qCursoId, int qPeriodo, int *currentSizeMateries, struct Materia **materias);
int showMateriesNames(int currentSizeMateries, struct Materia *materias);
void prepareChoosenMateries(char **choosenMateriesNames, struct Materia *materias, int currentSizeMateries, int *choosenMateries);
void showChosenMateries(struct Materia *materias, int currentSizeMateries);
struct Materia handleChoseMatter(struct User *loggedUser);

#endif