
#include <stdio.h>
#include <stdlib.h>

#include "../_Auth/login.h"
#include "../_Materies/materies.h"
#include "./cronogram.h"
#include "../helper.h"
#include "../errors.h"

int removeCurrentCronogram(struct User *loggedUser)
{
    char filename[50] = "cronogramas.txt";

    FILE *file = fopen("cronogramas.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    char line[200];
    int currentLine = 1;

    if (file == NULL || tempFile == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), file))
    {
        int idUsuario;
        char materias[200] = "";
        char diaSemana[20] = "";

        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        if (idUsuario != loggedUser->id)
        {
            fputs(line, tempFile);
        }

        currentLine++;
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);
}

int createCronogram(struct User *loggedUser)
{
    int contador = 0;
    float horas;
    int registerAgain = 1;
    int *choosenMateries = NULL;
    int currentSizeMateries = 0;
    int deleteCurrentCronogram = 0;

    char **choosenMateriesNames = (char **)malloc(currentSizeMateries * sizeof(char *));

    system("clear");

    if (hasAlreadyCreatedCronogram(loggedUser))
    {
        showWarning("Se continuar vai apagar o cronograma já criado");
        showInfo("1 - Continuar | 2 - Cancelar\n");

        scanf("%d", &deleteCurrentCronogram);

        if (deleteCurrentCronogram == 2)
        {
            return 0;
        }

        removeCurrentCronogram(loggedUser);
    }

    while (registerAgain == 1)
    {
        system("clear");
        printf("===CRIAÇÃO DE CRONOGRAMA===\n\n");

        currentSizeMateries++;
        choosenMateries = realloc(choosenMateries, currentSizeMateries * sizeof(int));
        choosenMateriesNames = realloc(choosenMateriesNames, currentSizeMateries * sizeof(char *));

        showMateriesNames(loggedUser->cursoId, loggedUser->periodo, choosenMateries, currentSizeMateries, choosenMateriesNames);

        printf("Escolha um número de (1 - 6) para matéria: ");
        scanf("%d", &choosenMateries[contador]);

        system("clear");
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar outra (1 - Sim | 2 - Não)? ");
        scanf("%d", &registerAgain);
        showMateriesNames(loggedUser->cursoId, loggedUser->periodo, choosenMateries, currentSizeMateries, choosenMateriesNames);
        system("clear");

        contador++;
    }

    printf("Horas disponíveis: ");
    scanf("%f", &horas);

    char diasSemana[5][30] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};
    int i;
    int count = 0;

    FILE *file = fopen("cronogramas.txt", "a");

    float horasMateria = horas / currentSizeMateries;

    printf("CRIANDO...!\n");

    for (i = 0; i < 5; i++)
    {
        fprintf(file, "\nIDUSUARIO: %ld,", loggedUser->id);
        fprintf(file, "%s,", diasSemana[i]);
        printf("TESTE");

        fprintf(file, "MATERIAS: {");
        count = 0;

        while (count < currentSizeMateries)
        {
            fprintf(file, "%s: %s,", choosenMateriesNames[count], convertNumberToHours(horasMateria));
            count++;
        }

        fprintf(file, "},");
    }

    fclose(file);

    printf("CRONOGRAMA CRIADO!\n");
    printf("====================\n");

    return 0;
}

void consultCronogram(struct User *loggedUser)
{

    system("clear");

    printf("===CONSULTAR CRONOGRAMA===\n");
    char line[400];

    FILE *file = fopen("cronogramas.txt", "r");

    while (fgets(line, sizeof(line), file))
    {
        int idUsuario; // Mudar para int para capturar o IDUSUARIO
        char materias[200] = "";
        char diaSemana[20] = "";

        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        if (idUsuario == loggedUser->id)
        {
            printf("\033[1m\033[3m\033[34m%s\033[0m\n", diaSemana);

            printf("- Matérias - \n");
            printf("%s", replaceCommaWithNewline(materias));

            printf("============================\n");
        }
    }

    fclose(file);
}

int hasAlreadyCreatedCronogram(struct User *loggedUser)
{
    system("clear");

    char line[400];

    FILE *file = fopen("cronogramas.txt", "r");

    while (fgets(line, sizeof(line), file))
    {
        int idUsuario;
        char materias[200] = "";
        char diaSemana[20] = "";

        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        if (idUsuario == loggedUser->id)
        {
            return 1;
            break;
        }
    }

    fclose(file);

    return 0;
}