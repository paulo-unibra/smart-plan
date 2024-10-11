#include "login.h"
#include <stdio.h>

void initialMenu(int *option)
{
    printf("Digite uma opção para continuar: \n");
    printf("1 - Login\n");
    printf("2 - Cadastro\n");

    if (scanf("%d", option) != 1)
    {
        while (getchar() != '\n')
            ;
    }
}

void menuLogin()
{
    int option = 3;
    int logged = 0;

    while (logged == 0)
    {
        initialMenu(&option);

        if (isValidOption(&option))
        {
            switch (option)
            {
            case 1:
                login(&logged);
                break;
            case 2:
                registerUser(&logged);
                break;
            default:
                printf("❌ \033[31mOpção inválida!!!\033[0m\n");
            }

            printf("======================================\n");
            // break;
        }
        else
        {
            system("clear");
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");
        }
    }
}
