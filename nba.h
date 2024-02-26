#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
#define tama 100
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct Jogador
{
    char player[100];
    int no;
    char pos[15];
    float height;
    float weight;
    char birthdate[15];
    int age;
    int exp;
    char school[100];
    int nextIndex;
    struct Jogador *next;
} TPlayer;


typedef struct Treinador{
    char nome[50];
    int exp;
    int age;
}TCoach;


typedef struct HashTable {
    TPlayer **players;

} HashTable;


// Retorna tamanho do funcionario em bytes
int tamanho_registro();

// Cria jogador.
TPlayer *jogador( char player[100], int no, char pos[10],float height, float weight, char birthdate[15],int age,int exp,char school[100]);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TPlayer *j, FILE *out);

// retorna a quantidade de registros no arquivo
int tamanho_arquivo(FILE *out);

int tamanho_registroT();

TPlayer *le(FILE *out);

//Criando treinador
TCoach *treinador(char nome[50],int exp, int age);

void salvaT(TCoach *j, FILE *out);

TCoach *leT(FILE *out);

// Imprime funcionario
void imprime(TPlayer *j);

void imprimeT(TCoach *t);

// Cria a base de dados
void todos(FILE *out, int chose);

void Boston(FILE *out, int chose);

void Toronto(FILE *out, int chose);

void Nets(FILE *out, int chose);

void imprimeParticoesFinal(FILE *file, char nomeParticao[]);

void Sixers(FILE *out, int chose);

void Knicks(FILE *out, int chose);

void Bucks(FILE *out, int chose);

void Heat(FILE *out, int chose);

void Magic(FILE *out, int chose);

void Pacers(FILE *out, int chose);

void imprimirBase(FILE *out, int tam, int chose);

TPlayer *busca_sequencial(int no, FILE *out);

TPlayer *busca_binaria(FILE *out, int tam);

TPlayer *busca_sequencial_palavra(FILE *out);

//PART.2**********************************************************************************
void ordenacao(int arr[], int n, FILE *out);

int selecaoSubstituicao (FILE *out,int m,int n, char nameFilePartition[]);

int sizeFile(FILE *out);

void imprime_jog(FILE *out,int n, char nomeParticao[]);

int registroMemoria (int vet[], int m);

void intercalacaoOtima(FILE *out, char nomeDaParticao[], int qtdParticoes);

void imprimeParticoes(FILE *out, char nomeParticao[]);

void unirParticoesOrdenadas(char nomeDaParticao[], int numParticoes);

//PART.3**********************************************************************************
HashTable *createHashTable(int modulo);

int hashFunction(int id, int modulo);

void insertPlayer(HashTable *ht, TPlayer *player, int modulo, FILE *out3);

void tabela(FILE *out, HashTable *ht, FILE *out2, FILE *out3, int modulo, int n);

TPlayer* searchPlayer(HashTable *ht, int id, int modulo);

void removePlayer(HashTable *ht, int id, int modulo, FILE *out3, int n);

void printOut2(FILE *out2, int modulo, HashTable *ht);

void printOut3(FILE *out3, int n, int modulo,HashTable *ht);

void print(FILE *out3, int n, int *no, int excludedCount);

void printWithDelay(char *str, unsigned int delay) ;

#endif // FUNCIONARIO_H_INCLUDED
