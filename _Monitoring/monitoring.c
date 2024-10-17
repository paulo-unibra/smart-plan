#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include "../_Auth/login.h"
#include "monitoring.h"
#include "../_Materies/materies.h"
#include "../helper.h"
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
char* OPERATIONALSYSTEM;
bool accountCreated = false;
FILE *file;

void queryMonitoring()
{
  OPERATIONALSYSTEM = verifyOperationalSystem();
  file = fopen("monitoring.txt", "r");
  char ch;
  bool repetir = true;
  char *list; // Aqui já é todo o conteudo do .txt ...
  char line[1024];  // Armazena uma linha...
  int newSize = 0; // Aqui é o novo tamanho de cada linha para dar um realloc...

    // Aloca um espaço na mémoria...
    list = (char *)malloc(1);
    list[0] = '\0';  // Cria uma string vazia...

    // Lê linha por linha do .txt e logo em seguida armazena no line...
    while (fgets(line, sizeof(line), file) != NULL) {
        newSize += strlen(line); // Equivalente ao .length em outras linguagens...
        list = (char *)realloc(list, newSize + 1);  // Realoca o espaço na mémoria para armazenar a nova linha, já que cada linha pode variar de tamanho...
        strcat(list, line);  // Concatena a nova linha com a string vázia criando uma réplica do .txt até o final...
    }

  set_nonblocking_mode(1);

    while (repetir)
    {
      sleepOS(1);
        cleanConsole();
        
        showHeader("CONSULTAR MONITORIA");

        printf("%s", list); // Imprime a lista do .txt ...

        printf("\n");
        printf("\nAperte ESC para sair...\n");

        if(strcmp(OPERATIONALSYSTEM, "Windows") == 0)
        {
            if(kbhit()) {
                ch = getChar();
                if (ch == 27)
                { 
                    repetir = false;
                    break;
                }
            }
        } 
        else 
        {
            ch = getChar();
            if (ch == 27)
            { 
                repetir = false;
                break;
            }
        }
    }

    free(list);
    fclose(file);
    set_nonblocking_mode(0);

    cleanConsole();
}

void registerForMonitoring(struct User *loggedUser)
{     
    
    file = fopen("monitoring.txt", "a");

    cleanConsole();

    showHeader("CADASTRO NA MONITORIA");

    char materia[150];
    char contato[100];
    int hora, minuto = 0, opcao, confirmarDados;
    bool repetirAcao = true;
    struct Materia selectedMatter = handleChoseMatter(loggedUser);

    rewind(file);
    fprintf(file, "MATÉRIA: %s, ", selectedMatter.nome);
    
    printf("\nDigite um número para contato:\n(81) ");
    scanf("%s", contato);
    
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

          fprintf(file, "IDUSUARIO: %ld,", loggedUser->id);
          fprintf(file, "NOMEUSUARIO: %s,", loggedUser->name);
          fprintf(file, "CONTATO: %s,", contato);
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