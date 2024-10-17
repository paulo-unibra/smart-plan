
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../_Auth/login.h"
#include "../_Materies/materies.h"
#include "./cronogram.h"
#include "../helper.h"
#include "../errors.h"

int removeCurrentCronogram(struct User *loggedUser)
{
    char filename[50] = "_Cronogram/cronogramas.txt";

    FILE *file = fopen("_Cronogram/cronogramas.txt", "r");
    FILE *tempFile = fopen("_Cronogram/temp.txt", "w");

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
    rename("_Cronogram/temp.txt", filename);
}

int createCronogram(struct User *loggedUser)
{
    int count = 0;
    float horas;
    int registerAgain = 1;
    int *choosenMateries = NULL;
    int currentSizeMateries = 0;
    int currentSizeToChoseMateries = 0;
    int deleteCurrentCronogram = 0;

    cleanConsole();

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

    struct Materia *materias = NULL;
    prepareMateries(loggedUser->cursoId, loggedUser->periodo, &currentSizeMateries, &materias);

    choosenMateries = (int *)malloc(currentSizeMateries * sizeof(int));
    if (choosenMateries == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    char **choosenMateriesNames = (char **)malloc(currentSizeMateries * sizeof(char *));
    if (choosenMateriesNames == NULL)
    {
        printf("Erro ao alocar memória!\n");
        free(choosenMateries);
        return 1;
    }

    while (registerAgain == 1)  
    {
        cleanConsole();
        showHeader("CRIAÇÃO DE CRONOGRAMA");

        showMateriesNames(currentSizeMateries, materias);

        printf("========Matérias Escolhidas========\n");

        prepareChoosenMateries(choosenMateriesNames, materias, currentSizeMateries, choosenMateries);
        showChosenMateries(materias, currentSizeMateries);
        
        printf("===================================\n");

        printf("Escolha um número de (1 - %d) para matéria: ", currentSizeMateries);
        scanf("%d", &choosenMateries[count]);

        int chosenIndex = choosenMateries[count] - 1;  // Corrige o índice (se a escolha é de 1 a currentSizeMateries)
        if (chosenIndex >= 0 && chosenIndex < currentSizeMateries)
        {
            choosenMateriesNames[count] = strdup(materias[chosenIndex].nome);
        }
        else
        {
            printf("Escolha inválida!\n");
            continue;
        }

        system("clear");
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar outra (1 - Sim | 2 - Não)? ");
        scanf("%d", &registerAgain);
        
        count++;
    }

    printf("Horas disponíveis: ");
    scanf("%f", &horas);

    char diasSemana[5][30] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};
    int i;

    FILE *file = fopen("_Cronogram/cronogramas.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    float horasMateria = horas / currentSizeMateries;

    printf("CRIANDO...!\n");

    for (i = 0; i < 5; i++)
    {
        fprintf(file, "\nIDUSUARIO: %ld,", loggedUser->id);
        fprintf(file, "%s,", diasSemana[i]);

        fprintf(file, "MATERIAS: {");
        for (int j = 0; j < count; j++)
        {
            fprintf(file, "%s: %s,", choosenMateriesNames[j], convertNumberToHours(horasMateria));
        }
        fprintf(file, "},");
    }

    fclose(file);

    // // Libera a memória alocada
    // for (int j = 0; j < count; j++)
    // {
    //     free(choosenMateriesNames[j]);
    // }ajustar
    free(choosenMateriesNames);
    free(choosenMateries);
    free(materias);

    showInfo("CRONOGRAMA CRIADO!");
    printf("====================\n");

    return 0;
}

void consultCronogram(struct User *loggedUser)
{

    cleanConsole();

    showHeader("CONSULTAR CRONOGRAMA");
    char line[400];

    FILE *file = fopen("_Cronogram/cronogramas.txt", "r");

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
    cleanConsole();

    char line[400];

    FILE *file = fopen("_Cronogram/cronogramas.txt", "r");

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