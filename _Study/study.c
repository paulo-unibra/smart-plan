#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep()

#include "../_Auth/login.h" // Aqui está a definição da `struct User`
#include "study.h"
#include "../validations.h"
#include "../helper.h"
#include "../errors.h"
#include "../_Materies/materies.h"

int startStudies(struct User *loggedUser)
{

    int option = 0;

    system("clear");

    showHeader("ÁREA DE ESTUDOS");

    while (!isValidTwoOption(&option))
    {
        printf("1 - Estudo Livre\n");
        printf("2 - Questionário\n");

        printf("Tipo de estudo: ");
        scanf("%d", &option);

        system("clear");
        showError("Opção Inválida");
    }

    system("clear");

    if (option == 1)
    {
        startStopwatch(); // Inicia o cronômetro
    }
    else
    {
        int contador = 0;
        float horas;
        int registerAgain = 1;
        int *choosenMateries = NULL;
        int currentSizeMateries = 0;
        int deleteCurrentCronogram = 0;
        struct Materia *materias = (struct Materia *)malloc(0 * sizeof(struct Materia));

        int selectedMatery = 0;

        char **choosenMateriesNames = (char **)malloc(currentSizeMateries * sizeof(char *));

        struct Materia selectedMatter = handleChoseMatter(loggedUser);
         
        printf("%s", selectedMatter.nome);

        sleepOS(5);

    }

    return 1;
}

void startStopwatch()
{
    int segundos = 0;
    int minutos = 0;
    int horas = 0;
    char ch;

    set_nonblocking_mode(1);

    while (1)
    {
        sleep(1);
        system("clear");

        printf("Tempo de Estudo: ");
        printf("\n⏱︎  %02d:%02d:%02d\n", horas, minutos, segundos);
        printf("Aperte ESC para parar\n");

        ch = getchar();
        if (ch == 27)
        { // Verifica se ESC foi pressionado
            printf("==================================\n");
            printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
            printf("==================================\n");
            break;
        }

        segundos++;

        if (segundos == 60)
        {
            minutos++;
            segundos = 0;
        }

        if (minutos == 60)
        {
            horas++;
            minutos = 0;
            segundos = 0;
        }
    }

    set_nonblocking_mode(0);
}
