#ifndef HELPER_H
#define HELPER_H

char *convertNumberToHours(float numberHour);
void set_nonblocking_mode(int enable);
char *replaceCommaWithNewline(char *str);
void useSecondsMicroseconds(int time);
void sleepOS(int time);
const char* verifyOperationalSystem();
void cleanConsole();
void showHeader(char *str);
int showSucces(char *message);
int showDanger(char *errorMessage);

#endif