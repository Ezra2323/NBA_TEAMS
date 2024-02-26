#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nba.h"

HashTable *createHashTable(int modulo)
{
    // Início do registro do tempo
    clock_t inicio = clock();

    // Alocação de memória para a tabela hash
    HashTable *ht = malloc(sizeof(HashTable));
    if (ht == NULL)
    {
        printf("Erro na alocação de memória para a tabela hash.\n");
        return NULL;
    }

    // Alocação de memória para os jogadores na tabela hash
    ht->players = malloc(modulo * sizeof(TPlayer *));
    if (ht->players == NULL)
    {
        printf("Erro na alocação de memória para os jogadores.\n");
        free(ht);
        return NULL;
    }

    // Inicialização dos compartimentos da tabela hash
    for (int i = 0; i < modulo; i++)
    {
        ht->players[i] = NULL;
    }

    // Fim do registro do tempo e cálculo do tempo de execução
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Retorno do ponteiro para a tabela hash criada
    return ht;
}

int hashFunction(int id, int modulo)
{
    return id % modulo;
}

void insertPlayer(HashTable *ht, TPlayer *player, int modulo, FILE *out3)
{
    int index = hashFunction(player->no, modulo);

    TPlayer *newNode = malloc(sizeof(TPlayer));
    if (newNode == NULL)
    {
        printf("Erro na alocação de memória para o novo nó.\n");
        return;
    }

    memcpy(newNode, player, sizeof(TPlayer));

    if (ht->players[index] != NULL)
    {
        TPlayer *currentNode = ht->players[index];
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
    else
    {
        ht->players[index] = newNode;
    }

    fseek(out3, 0, SEEK_END);
    fwrite(newNode, sizeof(TPlayer), 1, out3);
}

void tabela(FILE *out, HashTable *ht, FILE *out2, FILE *out3, int modulo, int n)
{
    clock_t inicio = clock();
    int comparacao = 0;

    rewind(out);
    int index = 0;
    int out3Position = 0;

    int *firstNodeIndices = malloc(modulo * sizeof(int));
    int *lastNodeIndices = malloc(modulo * sizeof(int));
    if (firstNodeIndices == NULL || lastNodeIndices == NULL)
    {
        printf("Erro na alocação de memória para os índices dos nós.\n");
        return;
    }
    for (int i = 0; i < modulo; i++)
    {
        firstNodeIndices[i] = -1;
        lastNodeIndices[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        fseek(out, i * tamanho_registro(), SEEK_SET);
        TPlayer *aux = le(out);

        index = hashFunction(aux->no, modulo);

        TPlayer *newNode = malloc(sizeof(TPlayer));
        if (newNode == NULL)
        {
            printf("Erro na alocação de memória para o novo nó.\n");
            return;
        }

        // Copie todos os campos do registro para o novo nó
        memcpy(newNode, aux, sizeof(TPlayer));
        newNode->next = NULL;

        if (ht->players[index] != NULL)
        {
            TPlayer *currentNode = ht->players[index];
            while (currentNode->next != NULL)
            {
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;
        }
        else
        {
            ht->players[index] = newNode;
            firstNodeIndices[index] = out3Position;
        }

        lastNodeIndices[index] = out3Position;

        fseek(out3, out3Position * sizeof(TPlayer), SEEK_SET);
        fwrite(newNode, sizeof(TPlayer), 1, out3);

        out3Position++;
    }

    for (int i = 0; i < modulo; i++)
    {
        fseek(out2, i * sizeof(int), SEEK_SET);
        fwrite(&firstNodeIndices[i], sizeof(int), 1, out2);
    }

    free(firstNodeIndices);
    free(lastNodeIndices);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);
}

TPlayer *searchPlayer(HashTable *ht, int id, int modulo)
{
    clock_t inicio = clock();
    int comparacao = 0;

    // Calcular o endereço aplicando a função h(x)
    int index = hashFunction(id, modulo);

    // Percorrer a lista encadeada associada ao endereço
    TPlayer *player = ht->players[index];
    while (player != NULL)
    {
        // Comparar a chave de cada nó da lista encadeada com a chave x, até encontrar o nó desejado
        comparacao++;
        if (player->no == id)
        {
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\nTempo de execucao: %f segundos\n", tempo);
            printf("Numero de comparacoes: %d\n\n\n", comparacao);
            return player;
        }

        player = player->next;
    }

    // Se o nó não foi encontrado, retorna NULL
    return NULL;
}

void removePlayer(HashTable *ht, int id, int modulo, FILE *out3, int n)
{

    clock_t inicio = clock();
    int comparacao = 0;

    int index = hashFunction(id, modulo);
    TPlayer *player = ht->players[index];
    TPlayer *prev = NULL;
    while (player != NULL && player->no != id)
    {
        prev = player;
        player = player->next;
    }

    if (player == NULL)
    {
        printf("Erro: Registro não encontrado.\n");
        return;
    }

    // Update the next pointer of the previous node before freeing the current node
    if (prev == NULL)
    {
        ht->players[index] = player->next;
    }
    else
    {
        prev->next = player->next;
    }

    // Now it's safe to free the current node
    free(player);

    for (int i = 0; i < modulo; i++)
    {
        TPlayer *player = ht->players[i];
        printf("Index %d: ", i);
        while (player != NULL)
        {
            printf("%d -> ", player->no);
            player = player->next;
        }
        printf("NULL\n");
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);
}

void printOut2(FILE *out2, int modulo, HashTable *ht)
{
    printf("Nós iniciais de cada compartimento:\n");
    for (int i = 0; i < modulo; i++)
    {
        if (ht->players[i] != NULL)
        {
            printf("Compartimento %d: %d\n", i, ht->players[i]->no);
        }
        else
        {
            printf("Compartimento %d: -1\n", i);
        }
    }
}

void printOut3(FILE *out3, int n, int modulo, HashTable *ht)
{
    rewind(out3);

    for (int i = 0; i < modulo; i++)
    {
        TPlayer *player = ht->players[i];
        printf("Index %d: ", i);
        while (player != NULL)
        {
            printf("%d -> ", player->no);
            player = player->next;
        }
        printf("NULL\n");
    }

    printf("Registros no arquivo out3:\n");
    for (int i = 0; i < n; i++)
    {
        TPlayer *player = malloc(sizeof(TPlayer));
        if (player == NULL)
        {
            printf("Erro na alocação de memória para o jogador.\n");
            return;
        }

        fseek(out3, i * sizeof(TPlayer), SEEK_SET);
        fread(player, sizeof(TPlayer), 1, out3);

        printf("%d) No: || Player:         ||\n    %d      %s           ", i, player->no, player->player);
        printf("\n");

        free(player);
    }
}

void print(FILE *out3, int n, int *no, int excludedCount)
{
    clock_t inicio = clock();
    int comparacao = 0;
    rewind(out3);

    printf("Registros no arquivo out3:\n");
    for (int i = 0; i < n; i++)
    {
        TPlayer *player = malloc(sizeof(TPlayer));
        if (player == NULL)
        {
            printf("Erro na alocação de memória para o jogador.\n");
            return;
        }

        fseek(out3, i * sizeof(TPlayer), SEEK_SET);
        fread(player, sizeof(TPlayer), 1, out3);

        bool excluded = false;
        for (int j = 0; j < excludedCount; j++)
        {
            if (player->no == no[j])
            {
                excluded = true;
                break;
            }
        }

        if (!excluded)
        {
            printf("%d) No: || Player:         ||\n    %d      %s           ", i, player->no, player->player);
            printf("\n");
        }

        comparacao++; // Incrementa o contador de comparações

        free(player);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);
}


void printWithDelay(char *str, unsigned int delay) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(delay);
    }
}