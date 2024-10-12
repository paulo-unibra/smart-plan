#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "materies.h"

void getChoosenMateries(char **choosenMateriesNames, struct Materia *materias, int currentSizeMateries, int *choosenMateries, int currentSize)
{
    int countMateries = 0;

    while (countMateries < currentSizeMateries)
    {
        int materiaIndex = choosenMateries[countMateries] - 1;

        if (materiaIndex >= 0 && materiaIndex < currentSize && materias[materiaIndex].escolhida != 1)
        {
            printf("%s\n", materias[materiaIndex].nome);
            materias[materiaIndex].escolhida = 1; // Marca como escolhida

            choosenMateriesNames[countMateries] = materias[materiaIndex].nome;
        }

        countMateries++;
    }
}

int showMateriesNames(int qCursoId, int qPeriodo, int *choosenMateries, int currentSizeMateries, char **choosenMateriesNames)
{
    FILE *file = fopen("materias.txt", "r");

    char line[200];

    int currentSize = 0;

    int materiaId;
    int idCurso;
    char materia[30];
    int periodo;
    int count = 0;

    if (file == NULL)
    {
        system("clear");
        return 1;
    }

    int position = 0;

    struct Materia *materias = (struct Materia *)malloc(currentSize * sizeof(struct Materia));

    if (materias == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "ID: %d,IDCURSO: %d,MATERIA: %[^,],PERIODO: %d", &materiaId, &idCurso, materia, &periodo);

        if (idCurso == qCursoId && periodo == qPeriodo)
        {
            currentSize++;

            materias = (struct Materia *)realloc(materias, currentSize * sizeof(struct Materia));

            materias[position].id = materiaId;
            materias[position].cursoId = qCursoId;
            strcpy(materias[position].nome, materia);
            materias[position].periodo = periodo;

            position++;
        }
    }

    printf("========Matérias Escolhidas========\n");

    getChoosenMateries(choosenMateriesNames, materias, currentSizeMateries, choosenMateries, currentSize);

    printf("===================================\n");

    count = 0;

    while (count < currentSize)
    {

        if (!materias[count].escolhida || materias[count].escolhida != 1)
        {
            printf("%d - %s \n", count + 1, materias[count].nome);
        }

        count++;
    }

    fclose(file);

    return 0;
}
