#include "helper.h"
#include <stdio.h>

char *convertNumberToHours(float numberHour)
{
    static char timeString[6];
    int hoursToMinutes = (numberHour * 60);
    int minutosEmHoras = hoursToMinutes / 60;
    int minutosRestantes = hoursToMinutes % 60;

    sprintf(timeString, "%02d:%02d", minutosEmHoras, minutosRestantes);

    return timeString;
}