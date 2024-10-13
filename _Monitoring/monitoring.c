#include <stdio.h>
#include <stdbool.h>

#include "monitoring.h"
#include "../_Auth/login.h"
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

void registerForMonitoring()
{
    char materia[150];
    long contato;
    int hora, minuto = 0, opcao;
    bool repetirAcao = true;

    do
    {
        printf("Digite o nome da matéria:  \n");
        scanf("%d", &opcao);

        switch(opcao)
        {
          case 1:
            printf("Matéria 1");
            break;
          case 2:
            printf("Matéria 2");
            break;
          case 3:
            printf("Matéria 3");
            break;
          case 4:
            printf("Matéria 4");
            break;
          default:
            printf("Inválido!!!");
        }
    }while(opcao < 1 || opcao > 4);
    
    cleanConsole();
    
    printf("\nDigite um número para contato:\n(81) ");
    scanf("%ld", &contato);
    
    do
    {
        cleanConsole();
        do
        {
            printf("Digite um horário disponível para você:(HH)\n");
            scanf("%d", &hora);
            if(hora > 23 || hora < 0)
            {
                cleanConsole();
                printf("Por favor Digite um horário válido!!!\n");
            }
        }while(hora < 0 || hora > 23);
        
        cleanConsole();
        
        do
        {
          printf("Digite um horário disponível para você:(MM)\n%d:", hora);
          scanf("%d", &minuto);
          if(minuto < 0 || minuto > 59)
          {
            cleanConsole();
            printf("Por favor Digite um horário válido!!!\n");
          }
        }while(minuto < 0 || minuto > 59);
        
        
        cleanConsole();
        printf("Horário disponível %.2d:%.2d está certo? \n1 - Sim\n2 - Não\n", hora, minuto);
        scanf("%d", &opcao);
        
        if(opcao == 1)
        {
          repetirAcao = false;
          break;
        }
        
    }while(repetirAcao);
}