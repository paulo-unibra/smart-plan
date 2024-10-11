#include "helper.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

char *convertNumberToHours(float numberHour)
{
    static char timeString[6];
    int hoursToMinutes = (numberHour * 60);
    int minutosEmHoras = hoursToMinutes / 60;
    int minutosRestantes = hoursToMinutes % 60;

    sprintf(timeString, "%02d:%02d", minutosEmHoras, minutosRestantes);

    return timeString;
}

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