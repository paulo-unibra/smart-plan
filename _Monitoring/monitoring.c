#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../_Auth/login.h"
#include "monitoring.h"
#include "../_Materies/materies.h"
#include "../helper.h"
#include "../main.h"

/**
 * Monitoria*
 * cadastrar na monitoria
 * - matéria
 * - meio de contato(celular)
 * - horário disponivel
 * consultar monitoria disponivel
 * (Mostrar tabela com ás informações acima, 
 * porém, cada matéria cadastrada precisa 
 * informar se tem monitor ou não)
 */
const char* OPERATIONALSYSTEM;
bool accountCreated = false;

void registerForMonitoring(struct User *loggedUser)
{
    OPERATIONALSYSTEM = verifyOperationalSystem();
    FILE *file;
    char pathDirectory[30];
    if(strcmp(OPERATIONALSYSTEM, "Windows") == 0)
    {
      strcpy(pathDirectory, "monitoring.txt");
      file = fopen(pathDirectory, "a");
    }
    else
    {
      file = fopen("monitoring.txt", "a");
    }

    cleanConsole();
    char materia[150];
    long contato;
    int hora, minuto = 0, opcao, confirmarDados;
    bool repetirAcao = true;
    struct Materia selectedMatter = handleChoseMatter(loggedUser);

    rewind(file);
    fprintf(file, "MATÉRIA: %s, ", selectedMatter.nome);
    
    printf("\nDigite um número para contato:\n(81) ");
    scanf("%ld", &contato);
    
    do
    {
        cleanConsole();

        // blocking_mode();
        do
        {
            printf("Digite um horário disponível para você:HH:__\n");
            scanf("%d", &hora);
            printf(":");
            if(hora > 23 || hora < 0)
            {
                cleanConsole();
                printf("Por favor Digite um horário válido!!!\n");
            }
        }while(hora < 0 || hora > 23);
        // blocking_mode();
        cleanConsole();
        
        do
        {
          printf("Digite um horário disponível para você%d:MM:\n%d:", hora, hora);
          scanf("%d", &minuto);
          if(minuto < 0 || minuto > 59)
          {
            cleanConsole();
            printf("Por favor Digite um horário válido!!!\n");
          }
        }while(minuto < 0 || minuto > 59);
        
        
        cleanConsole();
        printf("Horário disponível %.2d:%.2d está certo? \n1 - Sim\n2 - Não\n", hora, minuto);
        scanf("%d", &confirmarDados);
        cleanConsole();
        if(confirmarDados == 1)
        {

          fprintf(file, "CONTATO: %ld,", contato);
          fprintf(file, "HORA DISPONÍVEL: %d:%d", hora, minuto);
          fprintf(file, "\n");
          fclose(file);
          accountCreated = !accountCreated;
          repetirAcao = false;
          break;
        }
        
    }while(repetirAcao);
}

void verifyAccountCreated(struct User *loggedUser)
{
  int newRegister;
  if(accountCreated == true)
  {
    cleanConsole();
    printf("Você já está cadastrado na monitoria.\nSe continuar essa ação seus antigos registros serão perdidos\nDeseja continuar?\n1 - Sim\n2 - Não\nResposta: ");
    scanf("%d", &newRegister);
    if(newRegister == 1)
    {
      accountCreated = !accountCreated;
      registerForMonitoring(loggedUser);
    }
    else if(newRegister == 2)
    {
      cleanConsole();
      printf("Ok!!!\n");
    }
  }
  else
  {
    registerForMonitoring(loggedUser);
  }
}