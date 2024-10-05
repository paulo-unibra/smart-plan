#include <stdio.h>
#include <unistd.h>

void menuLogado()
{
    printf("1 - Consultar Cronograma\n");
    printf("2 - Criar Cronograma\n");
    printf("3 - Iniciar Estudos\n");
    // Perguntar a matéria de estudos
    // Definir tipo de estudos (Questionario|Estudo Livre)

    printf("4 - Verificar Desempenho\n");

    printf("5 - Cadastrar-se na Monitoria");
    // Qual matéria
    // Horário disponível
    // Meio de Contato

    printf("6 - Consultar Monitores");
    // Perguntar a matéria
    // Lista todos os monitores nas materias que eu estou matriculado    
}

void iniciarEstudos()
{
    int segundos = 0;
    int minutos = 0;
    int horas = 0;
    char ch;

    while (1)
    {
        sleep(1);
        system("clear");

        printf("Tempo de Estudo: ");
        printf("\n⏱︎  %02d:%02d:%02d\n", horas, minutos, segundos);
        printf("Aperte ESC para parar\n");

        ch = getchar();

        if (ch == "\n")
        {
            printf("TESTE");
            break;
        }

        segundos++;

        if (segundos == 60)
        {
            minutos++;
            segundos = 0;
        }

        if (minutos == 59)
        {
            horas++;
            minutos = 0;
            segundos = 0;
        }
    }
    // TERMINAR
}

void criarCronograma()
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

    printf("CONSULTAR CRONOGRAMA");
}

void verificarDesempenho()
{
    printf("VERIFICAR DESEMPENHO");
}

int main()
{
    int opcao = 5;

    while (opcao > 4)
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
            criarCronograma();
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
        }

        // if(opcao > 4){
        //     system("clear");
        // }
    }

    return 0;
}