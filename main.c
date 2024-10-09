#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

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

void showMateriesNames(int qCursoId, int qPeriodo, int *choosenMateries, int currentSizeMateries, char **choosenMateriesNames)
{
    FILE *file = fopen("materias.txt", "r");

    char line[200];

    int currentSize = 1;

    int materiaId;
    int idCurso;
    char materia[30];
    int periodo;
    int count = 0;

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
            materias[position].id = materiaId;
            materias[position].cursoId = qCursoId;
            strcpy(materias[position].nome, materia);
            materias[position].periodo = periodo;

            currentSize++;
            materias = (struct Materia *)realloc(materias, currentSize * sizeof(struct Materia));
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
}

void iniciarEstudos()
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

char *convertNumberToHours(float numberHour)
{
    static char timeString[6];
    int hoursToMinutes = (numberHour * 60);
    int minutosEmHoras = hoursToMinutes / 60;
    int minutosRestantes = hoursToMinutes % 60;

    sprintf(timeString, "%02d:%02d", minutosEmHoras, minutosRestantes);

    return timeString;
}

void criarCronograma(loggedUser)
{
    int contador = 0;
    float horas;
    int registerAgain = 1;
    int currentSizeMateries = 0;
    int *choosenMateries = NULL;
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

    FILE *arquivo = fopen("cronogramas.txt", "a");

    float horasMateria = horas / currentSizeMateries;

    printf("CRIANDO...!\n");

    for (i = 0; i < currentSizeMateries; i++)
    {
        fprintf(arquivo, "\nIDUSUARIO: 1,");
        fprintf(arquivo, "%s,", diasSemana[i]);

        fprintf(arquivo, "MATERIAS: {");
        count = 0;

        while (count < currentSizeMateries)
        {
            fprintf(arquivo, "%s: %s,", choosenMateriesNames[count], convertNumberToHours(horasMateria));
            count++;
        }

        fprintf(arquivo, "},");
    }

    fclose(arquivo);

    printf("CRONOGRAMA CRIADO!\n");
    printf("====================\n");
}

void consultarCronograma()
{

    system("clear");

    printf("===CONSULTAR CRONOGRAMA===\n");
    char line[400];

    FILE *arquivo = fopen("cronogramas.txt", "r");

    while (fgets(line, sizeof(line), arquivo))
    {
        int idUsuario; // Mudar para int para capturar o IDUSUARIO
        char materias[200] = "";
        char diaSemana[20] = "";

        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        printf("Dia: \033[1;34m%s\033[0m\n", diaSemana);
        printf("- Matérias - \n");
        printf("%s", replaceCommaWithNewline(materias));

        printf("============================\n");
    }

    fclose(arquivo);
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

void initialMenu(int *option)
{   
    printf("Digite uma opção para continuar: \n");
    printf("1 - Login\n");
    printf("2 - Cadastro\n");

    if (scanf("%d", option) != 1)
    {
        while (getchar() != '\n')
            ;
    }
}

int isValidOption(int *option)
{
    return (*option == 1 || *option == 2);
}

void registerUser()
{
    system("clear");
    struct User user;
    printf("======CADASTRO=====\n");

    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", user.name);
    // VALIDAR TEM PELO MENOS 2 NOMES

    printf("Digite o e-mail do usuário: ");
    scanf(" %s", user.email);
    // VALIDAR EMAIL

    printf("Digite sua senha: ");
    scanf(" %s", user.password);
    // VALIDAR FORÇA DA SENHA

    printf("Confirme a sua senha: ");
    scanf(" %s", user.conf_password);
    // VALIDAR IGUALDADE COM A SENHA

    // VERIFICAR SE USUARIO JA EXISTE PELO EMAIL

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "a");
    fprintf(bdUser, "\n%s,", user.name);
    fprintf(bdUser, "%s,", user.email);
    fprintf(bdUser, "%s", user.password);
    fclose(bdUser);
}

void login()
{
    system("clear");
    struct User user;
    char line[200];
    int authorizated = 0;

    printf("======LOGIN=====\n");

    printf("Digite o e-mail do usuário: ");
    scanf(" %s", user.email);

    printf("Digite sua senha: ");
    scanf(" %s", user.password);

    // TUDO VALIDO - CADASTRAR NO BANCO
    FILE *bdUser = fopen("users.txt", "r");

    if (bdUser == NULL)
    {
        printf("Arquivo não está criado!");
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
            authorizated = 1;
            break;
        }
    }

    if (authorizated == 1)
    {
        printf("Usuário Logado com Sucesso!\n");
    }
    else
    {
        printf("\033[31mE-MAIL E/OU SENHA INCORRETO(s)\033[0m\n");
    }

    fclose(bdUser);
}

void menuLogin()
{
    int option = 3;

    while (1)
    {
        initialMenu(&option);

        if (isValidOption(&option))
        {
            switch (option)
            {
            case 1:
                login();
                break;

            case 2:
                registerUser();
                break;
            default:
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");
            }

            printf("======================================\n");
            break;
        }
        else
        {
            system("clear");
            printf("❌ \033[31mOpção inválida!!!\033[0m\n");
        }
    }
}

int main()
{
    menuLogin();

    int opcao = 5;
    system("clear");

    char loggedUser[200] = "ID: 1,NOME:Paulo,EMAIL:pr838908@gmail.com,SENHA:z8618190,IDCURSO: 1,PERIODO: 2";

    while (1)
    {
        menuLogado();
        printf("Escolha uma opção:  ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            consultarCronograma();
        }
        else if (opcao == 2)
        {
            criarCronograma(loggedUser);
        }
        else if (opcao == 3)
        {
            iniciarEstudos();
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
        //     system("clear");
        // }
    }

    return 0;
}