#include "helper.h"
#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *convertNumberToHours(float numberHour)
{
    static char timeString[6];
    int hoursToMinutes = (numberHour * 60);
    int minutosEmHoras = hoursToMinutes / 60;
    int minutosRestantes = hoursToMinutes % 60;

    sprintf(timeString, "%02d:%02d", minutosEmHoras, minutosRestantes);

    return timeString;
}

void useSecondsMicroseconds(int time)
{
    #ifdef _WIN32
    Sleep(time);
    #else
    usleep(time);
    #endif
}

void sleepOS(int time)
{
    #ifdef _WIN32
    Sleep(time * 1000);
    #else
    sleep(time);
    #endif
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
    const char* operationalSystem = verifyOperationalSystem();
    if(strcmp(operationalSystem, "Windows") == 0)
    {
        system("cls");
    } else if(strcmp(operationalSystem, "Linux") == 0)
    {
        system("clear");
    }
}

#ifdef __linux__
void set_nonblocking_mode(int enable)
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    if (enable)
    {
        t.c_lflag &= ~(ICANON | ECHO); // Desabilita modo canônico e eco
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK); // Modo não bloqueante
    }
    else
    {
        t.c_lflag |= (ICANON | ECHO); // Reativa o modo canônico e eco
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK); // Modo bloqueante
    }
}

bool kbhit() {
    struct termios oldt, newt;
    int oldf;
    char ch;
    bool isPressed = false;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desabilita modo canônico e eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    if (read(STDIN_FILENO, &ch, 1) > 0) {
        isPressed = true;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return isPressed;
}

#else

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

#endif


int main_helper() {
    set_nonblocking_mode(1);

    printf("Modo não bloqueante e sem eco ativado. Pressione algo...\n");

    while (1) {
        if (kbhit()) { // Verifica se há entrada pronta
            char ch = getchar(); // Lê um caractere sem eco no console
            printf("Tecla pressionada: %c\n", ch);
            if (ch == 'q') // Pressione 'q' para sair
                break; 
        }
        useSecondsMicroseconds(100000); // Pausa breve para evitar sobrecarregar a CPU (100ms)
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