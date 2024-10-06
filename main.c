#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

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

void criarCronograma(loggedUser)
{
    int quantidadeMaterias;
    int contador;
    float horas;

    system("clear");

    printf("CRIAÇÃO DE CRONOGRAMA\n");

    printf("Quantidade de Matérias: ");
    scanf("%d", &quantidadeMaterias);

    char nomesMaterias[quantidadeMaterias][200];

    for (contador = 0; contador < quantidadeMaterias; contador++)
    {
        printf("Nome da Matéria %d: ", contador + 1);
        scanf("%s", nomesMaterias[contador]);
    }

    printf("Horas disponíveis: ");
    scanf("%f", &horas);                                                                            

    int horasEmMinutos = (horas * 60) / quantidadeMaterias;
    int minutosEmHoras = horasEmMinutos / 60;

    int minutosRestantes = horasEmMinutos % 60;

    char diasSemana[5][30] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};
    int i;
    int count = 0;

    printf("CRONOGRAMA CRIADO!\n");
    printf("====================\n");

    FILE *arquivo = fopen("cronogramas.txt", "a");

    for (i = 0; i < 5; i++)
    {
        fprintf(arquivo, "\nIDUSUARIO: 1,");
        fprintf(arquivo, "%s,", diasSemana[i]);

        fprintf(arquivo, "MATERIAS: [");
        while (count < quantidadeMaterias)
        {
            fprintf(arquivo, "%s,", nomesMaterias[count]);

            count++;
        }
        fprintf(arquivo, "],");

        fprintf(arquivo, "HORASMATERIAS: %d:%d", minutosEmHoras, minutosRestantes);

        count = 0;
    }

    fclose(arquivo);

    // for (i = 0; i < 5; i++)
    // {
    //     printf("%s\n", diasSemana[i]);

    //     while (count < quantidadeMaterias)
    //     {
    //         printf("--- %s - %d:%d horas por dia\n", nomesMaterias[count], minutosEmHoras, minutosRestantes);
    //         count++;
    //     }

    //     count = 0;
    // }
}

void consultarCronograma()
{

    system("clear");

    printf("===CONSULTAR CRONOGRAMA===\n");
    char line[400];

    FILE *arquivo = fopen("cronogramas.txt", "r");

    while (fgets(line, sizeof(line), arquivo)) {
        // Remover o caractere de nova linha
        // line[strcspn(line, "\n")] = 0;

        int idUsuario; //Mudar para int para capturar o IDUSUARIO
        char materias[200] = "";
        char diaSemana[20] = "";


        // // Ajustar o sscanf para usar %d para ler um inteiro
        // sscanf(line, "IDUSUARIO: %d%[^,]", &idUsuario); // Note o uso de &idUsuario
        // sscanf(line, );
        sscanf(line, "IDUSUARIO: %d,%[^,],MATERIAS: {%[^\n}] ,", &idUsuario, diaSemana, materias);

        printf("Dia: %s\n", diaSemana); // Mudar para %d
        printf("Matérias: %s\n", materias); // Mudar para %d
        printf("============================\n");

    }
    
    fclose(arquivo);
}

void verificarDesempenho()
{
    printf("VERIFICAR DESEMPENHO");
}

int main()
{
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