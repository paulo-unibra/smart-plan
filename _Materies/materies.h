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

int showMateriesNames(int qCursoId, int qPeriodo, int *choosenMateries, int currentSizeMateries, char **choosenMateriesNames);

#endif