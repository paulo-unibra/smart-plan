#include <stdbool.h>

#ifndef HELPER_H
#define HELPER_H

char *convertNumberToHours(float numberHour);
int getChar();
void useSecondsMicroseconds(int time);
void sleepOS(int time);
char* verifyOperationalSystem();
void cleanConsole();


void set_nonblocking_mode(int enable);
#ifdef __linux__
bool kbhit();
#endif
char *replaceCommaWithNewline(char *str);


void showHeader(char *str);
int showSucces(char *message);
int showDanger(char *errorMessage);

#endif