#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../_Auth/login.h"
#include "materies.h"
#include "../helper.h"
#include "../errors.h"

struct Materia handleChoseMatter(struct User *loggedUser)
{
    int currentSizeMateries = 0;
    struct Materia *materias = (struct Materia *)malloc(0 * sizeof(struct Materia));
    int chosenMatter;

    prepareMateries(loggedUser->cursoId, loggedUser->periodo, &currentSizeMateries, &materias);

    while (chosenMatter < 1 || chosenMatter > currentSizeMateries)
    {

        showMateriesNames(currentSizeMateries, materias);

        printf("Escolha uma matéria: ");
        scanf("%d", &chosenMatter);
        cleanConsole();

        showError("Opção Inválida");
    }

    cleanConsole();

    return materias[chosenMatter - 1];
}

void prepareChoosenMateries(char **choosenMateriesNames, struct Materia *materias, int currentSizeMateries, int *choosenMateries)
{
    int countMateries = 0;

    while (countMateries < currentSizeMateries)
    {
        int materiaIndex = choosenMateries[countMateries] - 1; // Ajustar para índice baseado em 0

        if (materiaIndex >= 0 && materiaIndex < currentSizeMateries && materias[materiaIndex].escolhida != 1)
        {
            materias[materiaIndex].escolhida = 1;
            choosenMateriesNames[countMateries] = materias[materiaIndex].nome;
        }

        countMateries++;
    }
}

void showChosenMateries(struct Materia *materias, int currentSizeMateries)
{
    int countMateries = 0;

    while (countMateries < currentSizeMateries)
    {
        if (materias[countMateries].escolhida == 1)
        {
            printf("%s\n", materias[countMateries].nome);
        }

        countMateries++;
    }
}

int prepareMateries(int qCursoId, int qPeriodo, int *currentSizeMateries, struct Materia **materias)
{
    FILE *file = fopen("materias.txt", "r");

    char line[200];
    int materiaId, idCurso, periodo;
    char materia[30];

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int position = *currentSizeMateries;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "ID: %d,IDCURSO: %d,MATERIA: %[^,],PERIODO: %d", &materiaId, &idCurso, materia, &periodo);

        if (idCurso == qCursoId && periodo == qPeriodo)
        {
            (*currentSizeMateries)++;

            struct Materia *temp = (struct Materia *)realloc(*materias, (*currentSizeMateries) * sizeof(struct Materia));

            if (temp == NULL)
            {
                printf("Erro ao realocar memória.\n");
                fclose(file);
                return 1;
            }

            *materias = temp;

            (*materias)[position].id = materiaId;
            (*materias)[position].cursoId = qCursoId;
            strcpy((*materias)[position].nome, materia);
            (*materias)[position].periodo = periodo;

            position++;
        }
    }

    fclose(file);
    return 0;
}

int showMateriesNames(int currentSizeMateries, struct Materia *materias)
{
    int count = 0;

    while (count < currentSizeMateries)
    {
        if (!materias[count].escolhida || materias[count].escolhida != 1)
        {
            printf("%d - %s \n", count + 1, materias[count].nome);
        }

        count++;
    }
}