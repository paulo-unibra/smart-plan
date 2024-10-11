#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"
#include "../errors.h"
#include "../validations.h"

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

    struct User user;

    while (logged == 0)
    {
        initialMenu(&option);

        if (isValidOptionLogin(&option))
        {
            switch (option)
            {
            case 1:
                login(&logged, &user);
                break;
            case 2:
                registerUser(&logged, &user);
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

void registerUser(int *logged, struct User *user)
{
    system("clear");

    printf("======CADASTRO=====\n");

    while (!isCompositeName(user->name))
    {
        printf("Digite o nome do usuário: ");
        scanf(" %[^\n]", user->name);

        system("clear");
        showError("Digite o nome completo");
    }

    system("clear");

    while (!isValidEmail(user->email))
    {
        printf("Digite o e-mail do usuário: ");
        scanf(" %[^\n]", user->email);

        system("clear");
        showError("E-mail inválido");
    }

    while (!isStrongPassword(user->password))
    {
        printf("Digite sua senha: ");
        scanf(" %[^\n]", user->password);
    }

    while (!comparePasswords(user->password, user->conf_password))
    {
        printf("Confirme a sua senha: ");
        scanf(" %[^\n]", user->conf_password);

        system("clear");
        showError("Senha e confirmação precisam ser iguais!");
    }

    system("clear");

    // VALIDAR IGUALDADE COM A SENHA

    // VERIFICAR SE USUARIO JA EXISTE PELO EMAIL

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "a");
    fprintf(bdUser, "\n%s,", user->name);
    fprintf(bdUser, "%s,", user->email);
    fprintf(bdUser, "%s", user->password);
    fclose(bdUser);

    *logged = 1;
}

void login(int *logged, struct User *user)
{
    char line[200];

    printf("======LOGIN=====\n");

    printf("Digite o e-mail do usuário: ");
    scanf(" %s", user->email);

    printf("Digite sua senha: ");
    scanf(" %s", user->password);

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "r");

    if (bdUser == NULL)
    {
        system("clear");
        printf("%s", fileNotCreatedError());
        return;
    }

    while (fgets(line, sizeof(line), bdUser) != NULL)
    {
        char sName[200], sEmail[200], sPass[200];

        sscanf(line, "%[^,],%[^,],%s", sName, sEmail, sPass);

        // printf("%s\n", line);
        // printf("%s\n", sEmail);
        // printf("%s\n", user->email);

        if (strcmp(sEmail, user->email) == 0 && strcmp(sPass, user->password) == 0)
        {
            *logged = 1;
            break;
        }
    }

    if (*logged == 1)
    {
        printf("\033[32mUsuário Logado com Sucesso!\033[0m\n");
    }
    else
    {
        system("clear");
        printf("\033[31mE-MAIL E/OU SENHA INCORRETO(s)\033[0m\n");
    }

    fclose(bdUser);
}
