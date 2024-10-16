#ifndef STUDY_H
#define STUDY_H


#include "../_Materies/materies.h"
struct Question
{
    int id;
    int materiaId;
    char description[200];
    char alternatives[200];
    char correct;
};

struct ResultQuestionary {
    int corrects;
    int wrongs;
    int questionsSize;
    float pontuation;
};

int startStudies(struct User *loggedUser);
void startStopwatch();
int removeCurrentCronogram(struct User *loggedUser);
struct ResultQuestionary showMatterQuestion(int selectedMatterId);
void prepareQuestionByMatter(int selectedMatterId, int *questionsSize, struct Question **matterQuestions);
void showPerformance(struct ResultQuestionary *result, struct Materia *selectedMatter);
void mountCompletePerformances(struct User *loggedUser);

#endif 
