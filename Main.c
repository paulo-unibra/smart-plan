#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "helper.h"
#include "errors.h"
#include "validations.h"
#include "./_Login/login.h"

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
void menuLogado()
{
    printf("1 - Consultar Cronograma\n");
    printf("2 - Criar Cronograma\n");
    printf("3 - Iniciar Estudos\n");
    // Perguntar a matéria de estudos
    // Definir tipo de estudos (Questionario|Estudo Livre)

    printf("4 - Verificar Desempenho\n");

    printf("5 - Cadastrar-se na Monitoria\n");
    // Qual matéria
    // Horário disponível
    // Meio de Contato

    printf("6 - Consultar Monitores\n\n");
    // Perguntar a matéria
    // Lista todos os monitores nas materias que eu estou matriculado
}

struct Materia
{
    int id;
    int cursoId;
    char nome[255];
    int periodo;
    int escolhida;
};

int areadyCreated(int arr[], int size, int number)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == number)
        {
            return 1;
        }
    }

    return 0;
}

void getChoosenMateries(char **choosenMateriesNames, struct Materia *materias, int currentSizeMateries, int *choosenMateries, int currentSize)
{
    int countMateries = 0;

    while (countMateries < currentSizeMateries)
    {
        int materiaIndex = choosenMateries[countMateries] - 1;

        if (materiaIndex >= 0 && materiaIndex < currentSize)
        {
            printf("%s\n", materias[materiaIndex].nome);
            materias[materiaIndex].escolhida = 1; // Marca como escolhida

            choosenMateriesNames[countMateries] = materias[materiaIndex].nome;
        }

        countMateries++;
    }
}

int showMateriesNames(int qCursoId, int qPeriodo, int *choosenMateries, int currentSizeMateries, char **choosenMateriesNames)
{
    FILE *file = fopen("materias.txt", "r");

    char line[200];

    int currentSize = 0;

    int materiaId;
    int idCurso;
    char materia[30];
    int periodo;
    int count = 0;

    if (file == NULL)
    {
        system("clear");
        // fileNotCreatedError();
        return 1;
    }

    int position = 0;

    struct Materia *materias = (struct Materia *)malloc(currentSize * sizeof(struct Materia));

    if (materias == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "ID: %d,IDCURSO: %d,MATERIA: %[^,],PERIODO: %d", &materiaId, &idCurso, materia, &periodo);

        if (idCurso == qCursoId && periodo == qPeriodo)
        {
            currentSize++;

            materias = (struct Materia *)realloc(materias, currentSize * sizeof(struct Materia));

            materias[position].id = materiaId;
            materias[position].cursoId = qCursoId;
            strcpy(materias[position].nome, materia);
            materias[position].periodo = periodo;

            position++;
        }
    }

    printf("========Matérias Escolhidas========\n");

    getChoosenMateries(choosenMateriesNames, materias, currentSizeMateries, choosenMateries, currentSize);

    printf("===================================\n");

    count = 0;

    while (count < currentSize - 1)
    {
        if (!materias[count].escolhida)
        {
            printf("%d - %s \n", count + 1, materias[count].nome);
        }

        count++;
    }

    fclose(file);

    return 0;
}

void startStudies()
{
    int segundos = 0;
    int minutos = 0;
    int horas = 0;
    char ch;

    set_nonblocking_mode(1);

    while (1)
    {
        sleep(1);
        system("clear");

        printf("Tempo de Estudo: ");
        printf("\n⏱︎  %02d:%02d:%02d\n", horas, minutos, segundos);
        printf("Aperte ESC para parar\n");

        ch = getchar();
        if (ch == 27)
        { // Verifica se "Enter" foi pressionado
            printf("==================================\n");
            printf("Você estudou %02d:%02d:%02d...\n", horas, minutos, segundos);
            printf("==================================\n");
            break;
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

int createCronogram()
{
    int contador = 0;
    float horas;
    int registerAgain = 1;
    int *choosenMateries = NULL;
    int currentSizeMateries = 0;

    char **choosenMateriesNames = (char **)malloc(currentSizeMateries * sizeof(char *));

    system("clear");

    printf("===CRIAÇÃO DE CRONOGRAMA===\n\n");

    while (registerAgain == 1)
    {
        system("clear");
        printf("===CRIAÇÃO DE CRONOGRAMA===\n\n");

        currentSizeMateries++;
        choosenMateries = realloc(choosenMateries, currentSizeMateries * sizeof(int));
        choosenMateriesNames = realloc(choosenMateriesNames, currentSizeMateries * sizeof(char *));

        showMateriesNames(1, 2, choosenMateries, currentSizeMateries, choosenMateriesNames);

        printf("Escolha um número de (1 - 6) para matéria: ");
        scanf("%d", &choosenMateries[contador]);

        system("clear");
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar outra (1 - Sim | 2 - Não)? ");
        scanf("%d", &registerAgain);
        showMateriesNames(1, 2, choosenMateries, currentSizeMateries, choosenMateriesNames);
        system("clear");

        contador++;
    }

    printf("Horas disponíveis: ");
    scanf("%f", &horas);

    char diasSemana[5][30] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};
    int i;
    int count = 0;

    FILE *file = fopen("cronogramas.txt", "a");

    float horasMateria = horas / currentSizeMateries;

    printf("CRIANDO...!\n");

    for (i = 0; i < currentSizeMateries; i++)
    {
        fprintf(file, "\nIDUSUARIO: 1,");
        fprintf(file, "%s,", diasSemana[i]);

        fprintf(file, "MATERIAS: {");
        count = 0;

        while (count < currentSizeMateries)
        {
            fprintf(file, "%s: %s,", choosenMateriesNames[count], convertNumberToHours(horasMateria));
            count++;
        }

        fprintf(file, "},");
    }

    fclose(file);

    printf("CRONOGRAMA CRIADO!\n");
    printf("====================\n");

    return 0;
}

void consultCronogram()
{

    system("clear");

    printf("===CONSULTAR CRONOGRAMA===\n");
    char line[400];

    FILE *file = fopen("cronogramas.txt", "r");

    while (fgets(line, sizeof(line), file))
    {
        int idUsuario; // Mudar para int para capturar o IDUSUARIO
        char materias[200] = "";
        char diaSemana[20] = "";

        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        printf("\033[1m\033[3m\033[34m%s\033[0m\n", diaSemana);

        printf("- Matérias - \n");
        printf("%s", replaceCommaWithNewline(materias));

        printf("============================\n");
    }

    fclose(file);
}

void verificarDesempenho()
{
    printf("VERIFICAR DESEMPENHO");
}

struct User
{
    char name[255];
    char email[255];
    char password[255];
    char conf_password[255];
};

int isValidOption(int *option)
{
    return (*option == 1 || *option == 2);
}

void registerUser(int *logged)
{
    system("clear");
    struct User user;
    printf("======CADASTRO=====\n");

    while (!isCompositeName(user.name))
    {
        printf("Digite o nome do usuário: ");
        scanf(" %[^\n]", user.name);

        system("clear");
        showError("Digite o nome completo");
    }

    system("clear");

    while (!isValidEmail(user.email))
    {
        printf("Digite o e-mail do usuário: ");
        scanf(" %[^\n]", user.email);

        system("clear");
        showError("E-mail inválido");
    }

    while (!isStrongPassword(user.password))
    {
        printf("Digite sua senha: ");
        scanf(" %[^\n]", user.password);
    }

    while (!comparePasswords(user.password, user.conf_password))
    {
        printf("Confirme a sua senha: ");
        scanf(" %[^\n]", user.conf_password);

        system("clear");
        showError("Senha e confirmação precisam ser iguais!");
    }

    system("clear");

    // VALIDAR IGUALDADE COM A SENHA

    // VERIFICAR SE USUARIO JA EXISTE PELO EMAIL

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "a");
    fprintf(bdUser, "\n%s,", user.name);
    fprintf(bdUser, "%s,", user.email);
    fprintf(bdUser, "%s", user.password);
    fclose(bdUser);

    *logged = 1;
}

void login(int *logged)
{
    struct User user;
    char line[200];

    printf("======LOGIN=====\n");

    printf("Digite o e-mail do usuário: ");
    scanf(" %s", user.email);

    printf("Digite sua senha: ");
    scanf(" %s", user.password);

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "r");

    if (bdUser == NULL)
    {
        system("clear");
        printf("%s", fileNotCreatedError());
        return;
    }

    while (fgets(line, sizeof(line), bdUser) != NULL)
    {
        char sName[200], sEmail[200], sPass[200];

        sscanf(line, "%[^,],%[^,],%s", sName, sEmail, sPass);

        // printf("%s\n", line);
        // printf("%s\n", sEmail);
        // printf("%s\n", user.email);

        if (strcmp(sEmail, user.email) == 0 && strcmp(sPass, user.password) == 0)
        {
            *logged = 1;
            break;
        }
    }

    if (*logged == 1)
    {
        printf("\033[32mUsuário Logado com Sucesso!\033[0m\n");
    }
    else
    {
        system("clear");
        printf("\033[31mE-MAIL E/OU SENHA INCORRETO(s)\033[0m\n");
    }

    fclose(bdUser);
}

int main()
{
    menuLogin();

    int opcao = 5;
    system("clear");

    // char loggedUser[200] = "ID: 1,NOME:Paulo,EMAIL:pr838908@gmail.com,SENHA:z8618190,IDCURSO: 1,PERIODO: 2";

    while (1)
    {
        menuLogado();
        printf("Escolha uma opção:  ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            consultCronogram();
        }
        else if (opcao == 2)
        {
            createCronogram();
        }
        else if (opcao == 3)
        {
            startStudies();
        }
        else if (opcao == 4)
        {
            verificarDesempenho();
        }
        else
        {
            system("clear");
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");

            break;
        }

        // if(opcao > 4){
        // system("clear");
        // }
    }

    return 0;
}