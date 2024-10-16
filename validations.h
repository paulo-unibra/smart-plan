#ifndef VALIDATIONS_H
#define VALIDATIONS_H

int isCompositeName(char name[]);
int isValidEmail(char email[]);
int isStrongPassword(char password[]);
int comparePasswords(const char *password, const char *confirmPassword);
int isValidOptionLogin(int *option);
int isValidTwoOption(int *option);

#endif