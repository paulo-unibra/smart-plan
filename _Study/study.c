#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "../_Auth/login.h"
#include "study.h"
#include "../validations.h"
#include "../helper.h"
#include "../errors.h"
#include "../_Materies/materies.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#endif

void prepareQuestionByMatter(int selectedMatterId, int *questionsSize, struct Question **matterQuestions)
{
    FILE *questionFile = fopen("./_Study/questions.txt", "r");
    char line[500];

    if (questionFile == NULL)
    {
        showError("Erro ao abrir o arquivo");
        return; 
    }

    struct Question question;

    while (fgets(line, sizeof(line), questionFile))
    {
        sscanf(line, "ID: %d,DESCRICAO:%[^,],, ALTERNATIVAS {%[^}]},CORRETA: %c,MATERIAID: %d",
               &question.id,
               question.description,
               question.alternatives,
               &question.correct,
               &question.materiaId);

        if (selectedMatterId == question.materiaId)
        {
            (*questionsSize)++; 

            struct Question *temp = realloc(*matterQuestions, (*questionsSize) * sizeof(struct Question));
            if (temp == NULL)
            {
                showError("Erro ao realocar memória");
                fclose(questionFile);
                return; 
            }
            *matterQuestions = temp;

            (*matterQuestions)[*questionsSize - 1] = question;
        }
    }

    fclose(questionFile);
}

struct ResultQuestionary showMatterQuestion(int selectedMatterId)
{
    int questionsSize = 0;
    struct Question *matterQuestions = NULL; // Inicialmente, NULL
    char userResponse;
    struct ResultQuestionary result;

    result.corrects = 0;
    result.pontuation = 0;
    result.wrongs = 0;

    prepareQuestionByMatter(selectedMatterId, &questionsSize, &matterQuestions);

    int currentQuestion = 0;

    result.questionsSize = questionsSize;

    while (currentQuestion < questionsSize)
    {

        if (questionsSize > 0 && matterQuestions != NULL)
        {
            printf("%s\n\n", matterQuestions[currentQuestion].description);
            printf("%s\n", replaceCommaWithNewline(matterQuestions[currentQuestion].alternatives));

            printf("Escolha uma opção: ");
            scanf(" %c", &userResponse);

            char chUpper = toupper((unsigned char)userResponse);

            if (chUpper == matterQuestions[currentQuestion].correct)
            {
                showSucces("RESPOSTA CORRETA!");
                result.corrects++;
            }
            else
            {
                showError("RESPOSTA INCORRETA");
                result.wrongs++;
            }

            sleepOS(1);
            cleanConsole();
        }
        else
        {
            printf("Nenhuma questão encontrada.\n");
        }

        currentQuestion++;
    }

    result.pontuation = (10 / questionsSize) * result.corrects;

    free(matterQuestions);

    return result;
}

void showPerformance(struct ResultQuestionary *result, struct Materia *selectedMatter)
{
    printf("===========================\n");

    printf("- Exercício de %s -\n", selectedMatter->nome);
    printf("Respostas Corretas: %d\n", result->corrects);
    printf("Respostas Incorretas: %d\n", result->wrongs);

    char message[20];

    snprintf(message, sizeof(message), "Pontuação: %2.f\n", result->pontuation);

    if (result->pontuation >= 7)
    {
        showSucces(message);
    }
    else
    {
        showDanger(message);
    }
}

void mountCompletePerformances(struct User *loggedUser)
{
    FILE *userQuestionFile = fopen("_Study/user_questionary.txt", "r");

    if (userQuestionFile == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[300];
    struct ResultQuestionary result;
    struct Materia materia;
    long userId;

    cleanConsole();
    showHeader("SEU DESEMPENHO: ");
    while (fgets(line, sizeof(line), userQuestionFile))
    {
        sscanf(line, "IDUSUARIO: %ld,MATERIAID: %d,MATERIANOME: %[^,],CORRETAS: %d,ERRADAS: %d,PONTUACAO: %f",
               &userId, &materia.id, materia.nome, &result.corrects, &result.wrongs, &result.pontuation);

        if (userId == loggedUser->id)
        {
            showPerformance(&result, &materia); // Mostra a performance do usuário
        }
    }

    fclose(userQuestionFile);
}
int startStudies(struct User *loggedUser)
{

    int option = 0;

    cleanConsole();

    showHeader("ÁREA DE ESTUDOS");

    while (!isValidTwoOption(&option))
    {
        printf("1 - Estudo Livre\n");
        printf("2 - Questionário\n");

        printf("Tipo de estudo: ");
        scanf("%d", &option);

        cleanConsole();
        showError("Opção Inválida");
    }

    cleanConsole();

    if (option == 1)
    {
        startStopwatch(); // Inicia o cronômetro
    }
    else
    {
        int contador = 0;
        float horas;
        int registerAgain = 1;
        int *choosenMateries = NULL;
        int currentSizeMateries = 0;
        int deleteCurrentCronogram = 0;
        struct Materia *materias = (struct Materia *)malloc(0 * sizeof(struct Materia));

        char **choosenMateriesNames = (char **)malloc(currentSizeMateries * sizeof(char *));

        struct Materia selectedMatter = handleChoseMatter(loggedUser);

        struct ResultQuestionary result = showMatterQuestion(selectedMatter.id);

        FILE *userQuestionFile = fopen("_Study/user_questionary.txt", "a");

        fprintf(userQuestionFile, "\nIDUSUARIO: %ld,", loggedUser->id);
        fprintf(userQuestionFile, "MATERIAID: %d,", selectedMatter.id);
        fprintf(userQuestionFile, "MATERIANOME: %s,", selectedMatter.nome);
        fprintf(userQuestionFile, "CORRETAS: %d,", result.corrects);
        fprintf(userQuestionFile, "ERRADAS: %d,", result.wrongs);
        fprintf(userQuestionFile, "PONTUACAO: %2.f", result.pontuation);

        fclose(userQuestionFile);

        showInfo("SEU RESULTADO: ");
        showPerformance(&result, &selectedMatter);

        sleepOS(1);
    }

    return 1;
}

void startStopwatch()
{
    char* OPERATIONALSYSTEM = verifyOperationalSystem();
    int segundos = 0;
    int minutos = 0;
    int horas = 0;
    char ch;

    set_nonblocking_mode(1);

    while (1)
    {
        sleepOS(1);
        cleanConsole();

        printf("Tempo de Estudo: ");
        printf("\n⏱︎  %02d:%02d:%02d\n", horas, minutos, segundos);
        printf("Aperte ESC para parar\n");

        if(strcmp(OPERATIONALSYSTEM, "Windows") == 0)
        {
            if(kbhit()) {
                ch = getChar();
                if (ch == 27)
                { // Verifica se "Enter" foi pressionado
                    printf("==================================\n");
                    printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
                    printf("==================================\n");
                    break;
                }
            }
        } 
        else 
        {
            ch = getChar();
            if (ch == 27)
            { // Verifica se "Enter" foi pressionado
                printf("==================================\n");
                printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
                printf("==================================\n");
                break;
            }
        }

        segundos++;

        if (segundos == 60)
        {
            minutos++;
            segundos = 0;
        }

        if (minutos == 60)
        {
            horas++;
            minutos = 0;
            segundos = 0;
        }
    }

    set_nonblocking_mode(0);
}
