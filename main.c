#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "nba.h"
#include <stdio.h>
#include <unistd.h>

void animate_text(char *text, unsigned int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay);
    }
    printf("\n");
}





int main(int argc, char *argv[])
{
      // 100000 microsegundos = 0.1 segundos
    // declara ponteiro para arquivo
    FILE *out;
    int n;
    int quant;

    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    // Abre arquivo para leitura e escrita
    int chose = 0;
    int opt = 0;
    do
    {
        animate_text("**********NBA TEAMS**********", 20000);
        animate_text("\n ---------------------------- \n", 20000);
        animate_text("  DIGITE A OPERACAO DESEJADA:\n", 20000);
        animate_text("  1 - CRIAR BASE DE JOGADORES\n", 20000);
        animate_text("  2 - BUSCA SEQUENCIAL\n", 20000);
        animate_text("  3 - BUSCA BINARIO\n", 20000);
        animate_text("  4 - QUICK SORT\n", 20000);
        animate_text("  5 - SELECAO COM SUBSTITUICAO\n", 20000);
        animate_text("  6 - INTERCALACAO OTIMA\n", 20000);
        animate_text("  7 - TABELA HASH\n", 20000);
        animate_text("\n ---------------------------- \n", 20000);
        printf("Opcao: \t");
        scanf("%d", &opt);
        system("cls");
        switch (opt)
        {

        case 1:
        {

            int escolha = 0;
            printf("Escolha um base de time para ser criada :");
            printf("\n ---------------------------- \n");
            printf("1 - Boston Celtics\n");
            printf("2 - Toronto Raptors\n");
            printf("3 - Brooklyn Nets\n");
            printf("4 - Philadelphia Seventy Sixers\n");
            printf("5 - New York Knicks\n");
            printf("6 - Milwaukee Bucks\n");
            printf("7 - Miami Heat\n");
            printf("8 - Orlando Magic\n");
            printf("9 - Indiana Pacers\n");
            printf("10 - Todos os jogadores\n");
            printf("\n ---------------------------- \n");
            printf("Opcao: \t");
            scanf("%d", &escolha);
            if (escolha == 1)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);
                printf("\nGerando a base de dados...\n");

                if (chose == 1)
                {
                    printf("\n---------Boston Celtics---------\n");
                    n = 18;
                    Boston(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    printf("\n---------Boston Celtics---------\n");
                    n = 17;
                    Boston(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 2)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    printf("\n---------Toronto Raptors---------\n");
                    n = 16;
                    Toronto(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    printf("\n---------Toronto Raptors---------\n");
                    n = 15;
                    Toronto(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 3)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    printf("\n---------Brooklyn Nets---------\n");
                    n = 15;
                    Nets(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {

                    printf("\n---------Brooklyn Nets---------\n");
                    n = 14;
                    Nets(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 4)
            {

                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    n = 16;
                    printf("\n---------Philadelphia Seventy Sixers---------\n");
                    Sixers(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    n = 15;
                    printf("\n---------Philadelphia Seventy Sixers---------\n");
                    Sixers(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 5)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    n = 14;
                    printf("\n---------New York Knicks---------\n");
                    Knicks(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    n = 13;
                    printf("\n---------New York Knicks---------\n");
                    Knicks(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 6)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    n = 15;
                    printf("\n---------Milwaukee Bucks---------\n");
                    Bucks(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    n = 14;
                    printf("\n---------Milwaukee Bucks---------\n");
                    Bucks(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 7)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    n = 15;
                    printf("\n---------Miami Heat---------\n");
                    Heat(out, chose);
                    imprimirBase(out, n, chose);
                    break;
                }
                else if (chose == 2)
                {
                    n = 14;
                    printf("\n---------Miami Heat---------\n");
                    Heat(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 8)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    n = 13;
                    printf("\n---------Orlando Magic---------\n");
                    Magic(out, chose);
                    imprimirBase(out, n, chose);
                }
                else if (chose == 2)
                {
                    n = 12;
                    printf("\n---------Orlando Magic---------\n");
                    Magic(out, chose);

                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 9)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);

                printf("\nGerando a base de dados...\n");
                if (chose == 1)
                {
                    printf("\n---------Indiana Pacers---------\n");
                    n = 13;
                    Pacers(out, chose);
                    imprimirBase(out, n, chose);
                }
                else if (chose == 2)
                {
                    printf("\n---------Indiana Pacers---------\n");
                    n = 12;
                    Pacers(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
            if (escolha == 10)
            {
                printf("\nDeseja que se tenha:\n1)Tecnico e time\n2)Time\n");
                scanf("%d", &chose);
                if (chose == 2)
                {
                    n = 127;
                    printf("\nGerando a base de dados...\n");

                    printf("\n---------Todos---------\n");
                    todos(out, chose);
                    imprimirBase(out, n, chose);
                }
            }
        }
        break;
        case 2:
        {
            int escolha = 0;
            printf("Deseja buscar: ");
            printf("\n1)Nome\n2)Numero\n");
            scanf("%d", &escolha);
            if (escolha == 1)
            {
                busca_sequencial_palavra(out);
            }
            else if (escolha == 2)
            {
                busca_sequencial(n, out);
            }
        }
        break;
        case 3:
            busca_binaria(out, n);
            break;
        case 4:
        {
            int arr[n];
            printf("\n\n\nORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO ORDENANDO\n\n\n");
            ordenacao(arr, n, out);
            imprimirBase(out, n, chose);
            break;
        }
        case 5:
        {
            int M;
            printf("\nDigite o tamanho da particao:");
            scanf("%d", &M);
            quant = selecaoSubstituicao(out, M, n, "particao");
            printf("A quantidade de particoes eh: %d\n", quant);
            break;
        }
        case 6:
        {

            // printf("\nDigite o numero de particoes:");
            // scanf("%d", &M);
            intercalacaoOtima(out, "particao", quant + 1);
            unirParticoesOrdenadas("particao", quant + 1);
            printf("Intercalacao otima concluida.\n");
            break;
        }
        //PART.3**********************************************************************************
        case 7:
        {

            FILE *out2;
            FILE *out3;
            int modulo, chosen,rec;
            int *no = malloc(n * sizeof(int)); // n é o número máximo de jogadores que podem ser excluídos
            int excludedCount = 0;
            out2 = fopen("NBA2.dat", "w+b");

            if (out2 == NULL)
            {
                printf("Erro ao abrir arquivo\n");
                exit(1);
            }

            out3 = fopen("NBA3.dat", "w+b");

            if (out3 == NULL)
            {
                printf("Erro ao abrir arquivo\n");
                exit(1);
            }

            // criacao da tabela hash
            printf("Digite a quantidade de compartimentos(Tabela Hash): ");
            scanf("%d", &modulo);
            // inicializacao de tabela hash
            HashTable *ht = createHashTable(modulo);
            // mostrando a tabela hash
            tabela(out, ht, out2, out3, modulo, n);

            printOut2(out2, modulo, ht);
            printOut3(out3, n, modulo, ht);

            printf("\nTabela hash criada com sucesso\n");

            while (chosen != 4)
            {
                system("PAUSE");
                system("cls");
                printf("\n**********TABELA HASH**********");
                printf("\n\nEscolha acao na Tabela Hash\n1)Inserir\n2)Buscar\n3)Excluir\n4)Sair\nEscolha: ");
                scanf("%d", &chosen);

                if (chosen == 1)
                {
                    printf("\n\n****Inserir****\n");
                    fclose(out);
                    out = fopen("nba.dat", "a+b");
                    int no, age, exp;
                    char player[100], pos[15], birthdate[15], school[100];
                    float height, weight;
                    TPlayer *j;
                    // insercao de valores
                    printf("\nDigite as informacoes de um novo jogador");

                    printf("\nNome: ");
                    scanf("%s", player);

                    printf("\nNumero do jogador: ");
                    scanf("%d", &no);

                    printf("\nPosicao: ");
                    scanf("%s", pos);

                    printf("\nAltura: ");
                    scanf("%f", &height);

                    printf("\nPeso: ");
                    scanf("%f", &weight);

                    printf("\nData de nascimento: ");
                    scanf("%s", birthdate);

                    printf("\nIdade: ");
                    scanf("%d", &age);

                    printf("\nExperiencia: ");
                    scanf("%d", &exp);

                    printf("\nUniversidade: ");
                    scanf("%s", school);
                    n += 1;
                    j = jogador(player, no, pos, height, weight, birthdate, age, exp, school);
                    salva(j, out);

                    insertPlayer(ht, j, modulo, out3);
                    printOut2(out2, modulo, ht);
                    printOut3(out3, n, modulo, ht);
                }
                else if (chosen == 2)
                {
                    int no;

                    printf("\n\n****Buscar****\n");
                    printf("Busque o numero do jogador: ");
                    scanf("%d", &no);

                    TPlayer *jog = searchPlayer(ht, no, modulo);

                    if (jog != NULL)
                    {
                        printf("\nJogador encontrado!");
                        printf("\nNome: %s", jog->player);
                        printf("\nNumero do jogador: %d\n", jog->no);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado!\n");
                    }
                }
                else if (chosen == 3)
                {
                    printf("\n\n****Excluir****\n");
                    printf("Exclua o numero do jogador: ");
                    scanf("%d", &rec);
                }

                if (chosen == 3)
                {
                   no[excludedCount] = rec;
                   excludedCount++;
                   removePlayer(ht, rec, modulo, out3, n);
                   print(out3, n, no, excludedCount);
                }
            }
            break;
        }
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opt != 10);

    fclose(out);
    return 0;
}
