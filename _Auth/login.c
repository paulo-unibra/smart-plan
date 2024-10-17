#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"
#include "../errors.h"
#include "../validations.h"
#include "../helper.h"

void initialMenu(int *option)
{
    cleanConsole();
    showHeader("SEU SISTEMA DE ESTUDOS");

    printf("1 - Login\n");
    printf("2 - Cadastro\n\n");
    printf("Digite uma opção para continuar: ");

    if (scanf("%d", option) != 1)
    {
        while (getchar() != '\n')
            ;
    }
}

void menuLogin(struct User *loggedUser)
{
    int option = 3;
    int logged = 0;

    while (logged == 0)
    {
        cleanConsole();
        initialMenu(&option);
        cleanConsole();

        if (isValidOptionLogin(&option))
        {
            switch (option)
            {
            case 1:
                login(&logged, loggedUser);
                break;
            case 2:
                registerUser(&logged, loggedUser);
                break;
            default:
                printf("❌ \033[31mOpção inválida!!!\033[0m\n");
            }

            printf("======================================\n");
            // break;
        }
        else
        {
            cleanConsole();
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");
        }
    }
}

void registerUser(int *logged, struct User *user)
{
    cleanConsole();
    showHeader("CADASTRO");

    while (!isCompositeName(user->name))
    {
        printf("Digite o nome do usuário: ");
        scanf(" %[^\n]", user->name);

        cleanConsole();
        showError("Digite o nome completo");
    }

    cleanConsole();

    while (!isValidEmail(user->email))
    {
        printf("Digite o e-mail do usuário: ");
        scanf(" %[^\n]", user->email);

        cleanConsole();
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

        cleanConsole();
        showError("Senha e confirmação precisam ser iguais!");
    }

    cleanConsole();

    while (user->cursoId < 1 || user->cursoId > 2)
    {
        printf("1 - TADS: \n");
        printf("2 - REDES: \n");
        printf("Selecione uma opção de curso: ");

        scanf("%d", &user->cursoId);

        cleanConsole();
        showError("Opção Inválida");
    }

    cleanConsole();

    while (user->periodo < 1 || user->periodo > 6)
    {
        printf("Período (1-6): ");

        scanf("%d", &user->periodo);

        cleanConsole();
        showError("Opção Inválida");
    }

    cleanConsole();

    char line[200];
    user->id = 1;

    FILE *bdUser = fopen("users.txt", "a+");

    if (bdUser != NULL)
    {
        while (fgets(line, sizeof(line), bdUser))
        {
            user->id++;
        }
    }

    rewind(bdUser);

    if (user->id > 1)
    {
        fprintf(bdUser, "\n");
    }

    fprintf(bdUser, "IDUSUARIO: %ld,", user->id);
    fprintf(bdUser, "CURSOID: %d,", user->cursoId);
    fprintf(bdUser, "PERIODO: %d,", user->periodo);
    fprintf(bdUser, "%s,", user->name);
    fprintf(bdUser, "%s,", user->email);
    fprintf(bdUser, "%s", user->password);

    fclose(bdUser);

    *logged = 1;
}

void login(int *logged, struct User *user)
{
    char line[200];

    showHeader("LOGIN");

    printf("Digite o e-mail do usuário: ");
    scanf(" %s", user->email);

    printf("Digite sua senha: ");
    scanf(" %s", user->password);

    FILE *bdUser = fopen("users.txt", "r");

    if (bdUser == NULL)
    {
        cleanConsole();
        printf("%s", fileNotCreatedError());
        return;
    }

    while (fgets(line, sizeof(line), bdUser) != NULL)
    {
        char sName[200], sEmail[200], sPass[200];

        sscanf(line, "IDUSUARIO: %ld,CURSOID: %d, PERIODO: %d,%[^,],%[^,],%s", &user->id, &user->cursoId, &user->periodo, sName, sEmail, sPass);

        if (strcmp(sEmail, user->email) == 0 && strcmp(sPass, user->password) == 0)
        {
            *logged = 1;
            break;
        }
    }

    cleanConsole();

    if (*logged == 1)
    {
        printf("\033[32mUsuário Logado com Sucesso!\033[0m\n");
    }
    else
    {
        showError("E-MAIL E/OU SENHA INCORRETO(s)");
    }

    sleepOS(1);
    fclose(bdUser);
}
