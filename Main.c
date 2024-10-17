#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include "helper.h"
#include "errors.h"
#include "validations.h"
#include "./_Auth/login.h"
#include "./_Cronogram/cronogram.h"
#include "./_Materies/materies.h"
#include "./_Study/study.h"

#include "./_Monitoring/monitoring.h"

#include "./_Study/study.h"


void menuLogado()
{   
    showHeader("ÁREA LOGADA");

    printf("1 - Consultar Cronograma\n");
    printf("2 - Criar Cronograma\n");
    printf("3 - Iniciar Estudos\n");
    printf("4 - Verificar Desempenho\n");
    printf("5 - Cadastrar-se na Monitoria\n");
    printf("6 - Consultar Monitores\n\n");
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
            startStudies(&loggedUser);
        }
        else if (opcao == 4)
        {
            mountCompletePerformances(&loggedUser);
        }
        else if(opcao == 5)
        {
            // verifyAccountCreated(&loggedUser);
            registerForMonitoring(&loggedUser);
        }
        else if(opcao == 6)
        {
            queryMonitoring();
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