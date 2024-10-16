#include "validations.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

int isCompositeName(char name[])
{
    int spaces = 0;

    // Percorre a string e conta o número de espaços
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == ' ')
        {
            spaces++;
        }
    }

    if (spaces >= 1)
    {
        return 1; // Tem dois ou mais nomes
    }
    else
    {
        return 0; // Não tem dois nomes
    }
}

int isValidEmail(char email[])
{
    int atSymbol = -1;
    int dotAfterAt = -1;

    // Percorre o e-mail para verificar o '@' e o '.'
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atSymbol = i; // Armazena a posição do '@'
        }
        // Verifica se há um '.' após o '@'
        if (atSymbol != -1 && email[i] == '.')
        {
            dotAfterAt = i;
        }
    }

    // Validação: precisa ter um '@' e um '.' depois do '@'
    if (atSymbol > 0 && dotAfterAt > atSymbol + 1)
    {
        return 1; // E-mail válido
    }

    return 0; // E-mail inválido
}

int isStrongPassword(char password[])
{
    system("clear");

    int length = 0, hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    length = strlen(password);

    if (length < 8)
    {
        showError("A senha deve ter pelo menos 8 caracteres");
        return 0; // Senha fraca se tiver menos de 8 caracteres
    }

    for (int i = 0; i < length; i++)
    {
        if (isupper(password[i]))
        {
            hasUpper = 1; // Tem letra maiúscula
        }
        else if (islower(password[i]))
        {
            hasLower = 1; // Tem letra minúscula
        }
        else if (isdigit(password[i]))
        {
            hasDigit = 1; // Tem número
        }
        else if (ispunct(password[i]))
        {
            hasSpecial = 1; // Tem caractere especial
        }
    }

    if (hasUpper != 1)
    {
        return showError("A senha deve conter pelo menos uma letra maiúscula");
    }

    if (hasLower != 1)
    {
        return showError("A senha deve conter pelo menos uma letra minúscula");
    }

    if (hasDigit != 1)
    {
        return showError("A senha deve conter pelo menos um número");
    }

    if (hasSpecial != 1)
    {
        return showError("A senha deve conter pelo menos um caractere especial");
    }

    // Verifica se a senha atende a todos os critérios
    if (hasUpper && hasLower && hasDigit && hasSpecial)
    {
        return 1; // Senha forte
    }
}

int comparePasswords(const char *password, const char *confirmPassword) {
    // Compara as duas senhas
    if (strcmp(password, confirmPassword) == 0) {
        return 1;  // As senhas coincidem
    } else {
        return 0;  // As senhas não coincidem
    }
}

int isValidOptionLogin(int *option)
{
    return (*option == 1 || *option == 2);
}

int isValidTwoOption(int *option)
{
    return (*option == 1 || *option == 2);
}