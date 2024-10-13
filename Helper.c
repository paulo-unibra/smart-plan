#include "helper.h"
#include <stdio.h>
#include <unistd.h>
// #include <termios.h>
#include <windows.h>
#include <conio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char *convertNumberToHours(float numberHour)
{
    static char timeString[6];
    int hoursToMinutes = (numberHour * 60);
    int minutosEmHoras = hoursToMinutes / 60;
    int minutosRestantes = hoursToMinutes % 60;

    sprintf(timeString, "%02d:%02d", minutosEmHoras, minutosRestantes);

    return timeString;
}

// Função que verifica o Sistema Operacional...
const char* verifyOperationalSystem()
{
    #ifdef _WIN32
        return "Windows";
    #elif __linux__
        return "Linux";
    #endif
}

// Função que limpa o console...
void cleanConsole()
{
    printf("executando...");
    const char* operationalSystem = verifyOperationalSystem();
    if(strcmp(operationalSystem, "Windows") == 0)
    {
        system("cls");
    } else if(strcmp(operationalSystem, "Linux") == 0)
    {
        system("clear");
    }
}

// void set_nonblocking_mode(int enable)
// {
//     struct termios t;
//     tcgetattr(STDIN_FILENO, &t);
//     if (enable)
//     {
//         t.c_lflag &= ~(ICANON | ECHO); // Desabilita modo canônico e eco
//         tcsetattr(STDIN_FILENO, TCSANOW, &t);
//         fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK); // Modo não bloqueante
//     }
//     else
//     {
//         t.c_lflag |= (ICANON | ECHO); // Reativa o modo canônico e eco
//         tcsetattr(STDIN_FILENO, TCSANOW, &t);
//         fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK); // Modo bloqueante
//     }
// }

void set_nonblocking_mode(int enable) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); // Obter o handle do console
    DWORD mode;

    // Obter o modo atual do console
    GetConsoleMode(hStdin, &mode);

    if (enable) {
        // Desabilitar modo canônico e eco (equivalente ao ICANON e ECHO no Unix)
        mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        // Definir o console como "não bloqueante" ao desabilitar ENABLE_LINE_INPUT
        mode &= ~ENABLE_PROCESSED_INPUT;
    } else {
        // Reativar modo canônico e eco
        mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        // Voltar ao modo bloqueante
        mode |= ENABLE_PROCESSED_INPUT;
    }

    // Definir o novo modo do console
    SetConsoleMode(hStdin, mode);
}

int main_helper() {
    // Exemplo de uso para desabilitar modo canônico e eco
    set_nonblocking_mode(1);

    printf("Modo não bloqueante e sem eco ativado. Pressione algo...\n");

    while (1) {
        if (_kbhit()) { // Verifica se há entrada pronta
            char ch = _getch(); // Pega a tecla sem eco no console
            printf("Tecla pressionada: %c\n", ch);
            if (ch == 'q') break; // Pressione 'q' para sair
        }
        Sleep(100); // Pausa breve para evitar sobrecarregar a CPU
    }

    // Reativar o modo canônico e eco antes de sair
    set_nonblocking_mode(0);

    return 0;
}

char *replaceCommaWithNewline(char *str)
{
    char *original = str;

    while (*str != '\0')
    {
        if (*str == ',')
        {
            *str = '\n';
        }
        str++;
    }

    return original;
}