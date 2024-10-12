#include "errors.h"
#include <stdio.h>

char *fileNotCreatedError()
{
    return "📢 \033[3;1;31mO arquivo não está criado❗\033[0m\n";
}

int showError(char *errorMessage)
{
    printf("📢 \033[3;1;31m%s❗\033[0m\n", errorMessage);
    return 0;
}

int showWarning(char *warning)
{
    printf("📢 \033[1m\033[3m\033[38;5;208m%s\033[0m\n", warning);
    return 0;
}

int showInfo(char *message)
{
    printf("\033[3;1;38m%s\033[0m\n", message);
    return 0;
}

int showPasswordStrongError()
{
    // Mensagem inicial com ícone
    printf("📢 \033[3;1;31mRegras para a Senha:\n");

    printf(" - A senha deve ter pelo menos 8 caracteres.\n");
    printf(" - A senha deve conter pelo menos uma letra maiúscula.\n");
    printf(" - A senha deve conter pelo menos uma letra minúscula.\n");
    printf(" - A senha deve conter pelo menos um número.\n");
    printf(" - A senha deve conter pelo menos um caractere especial.\n");

    // Resetando a cor do texto
    printf("\033[0m\n");

    return 0;
}