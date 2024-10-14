#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include "helper.h"
#include "errors.h"
#include "validations.h"
#include "./_Auth/login.h"
#include "./_Cronogram/cronogram.h"
#include "./_Materies/materies.h"
#include "./_Monitoring/monitoring.h"

const char* OPERATIONALSYSTEM;

void menuLogado()
{
    printf("1 - Consultar Cronograma\n");
    printf("2 - Criar Cronograma\n");
    printf("3 - Iniciar Estudos\n");
    // Perguntar a matéria de estudos
    // Definir tipo de estudos (Questionario|Estudo Livre)

    printf("4 - Verificar Desempenho\n");

    printf("5 - Cadastrar-se na Monitoria\n");
    // Qual matéria
    // Horário disponível
    // Meio de Contato

    printf("6 - Consultar Monitores\n\n");
    // Perguntar a matéria
    // Lista todos os monitores nas materias que eu estou matriculado
}

int areadyCreated(int arr[], int size, int number)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == number)
        {
            return 1;
        }
    }

    return 0;
}

void startStudies()
{
    OPERATIONALSYSTEM = verifyOperationalSystem();
    int segundos = 0;
    int minutos = 0;
    int horas = 0;
    char ch;

    set_nonblocking_mode(1);

    while (1)
    {
        sleepOS(1);
        cleanConsole();

        printf("Tempo de Estudo: ");
        printf("\n⏱︎  %02d:%02d:%02d\n", horas, minutos, segundos);
        printf("Aperte ESC para parar\n");

        if(strcmp(OPERATIONALSYSTEM, "Windows") == 0)
        {
            if(kbhit()) {
                ch = getChar();
                if (ch == 27)
                { // Verifica se "Enter" foi pressionado
                    printf("==================================\n");
                    printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
                    printf("==================================\n");
                    break;
                }
            }
        } 
        else 
        {
            ch = getChar();
            if (ch == 27)
            { // Verifica se "Enter" foi pressionado
                printf("==================================\n");
                printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
                printf("==================================\n");
                break;
            }
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

void verificarDesempenho()
{
    printf("VERIFICAR DESEMPENHO\n");
}

int main()
{
    const char* OperationalSystem = verifyOperationalSystem();
    struct User loggedUser;

    menuLogin(&loggedUser);

    int opcao = 5;
    cleanConsole();

    while (1)
    {
        menuLogado();
        printf("Escolha uma opção:  ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            consultCronogram(&loggedUser);
        }
        else if (opcao == 2)
        {
            createCronogram(&loggedUser);
        }
        else if (opcao == 3)
        {
            startStudies();
        }
        else if (opcao == 4)
        {
            verificarDesempenho();
        }
        else if(opcao == 5)
        {
            verifyAccountCreated();
        }
        else
        {
            cleanConsole();
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");

            break;
        }

        // if(opcao > 4){
        // system("clear");
        // }
    }

    return 0;
}