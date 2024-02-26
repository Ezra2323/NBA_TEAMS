#include "nba.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

// Retorna tamanho do funcionario em bytes
int tamanho_registro()
{
    return
        sizeof(char) * 100 +           // player
        sizeof(int) +                  // no
        sizeof(char) * 15 +            // pos
        sizeof(float)+                 // height
        sizeof(float)+                 // weight
        sizeof(char) * 15 +            // birthdate
        sizeof(int) +                  // age
        sizeof(int) +                  // exp
        sizeof(char) * 100;            // school
}

int tamanho_registroT()
{
    return sizeof(char) * 50 +           // player
           sizeof(int) +
           sizeof(int);
}

// Cria funcionario.
TPlayer *jogador(char player[100], int no, char pos[15],float height, float weight, char birthdate[15],int age,int exp,char school[100])
{
    TPlayer *j = (TPlayer *) malloc(sizeof(TPlayer));
    //inicializa espaco de memoria com ZEROS
    if (j)
    {
        memset(j, 0, sizeof(TPlayer));
    }//copia valores para os campos de func

    strcpy(j->player, player);
    j->no = no;
    strcpy(j->pos, pos);
    j->height = height;
    j->weight = weight;
    strcpy(j->birthdate, birthdate);
    j->age = age;
    j->exp =exp;
    strcpy(j->school, school);

    return j;
}


// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TPlayer *j, FILE *out)
{
    fwrite(j->player, sizeof(char), sizeof(j->player), out);
    fwrite(&j->no, sizeof(int), 1, out);
    fwrite(j->pos, sizeof(char), sizeof(j->pos), out);
    fwrite(&j->height, sizeof(float), 1, out);
    fwrite(&j->weight, sizeof(float), 1, out);
    fwrite(j->birthdate, sizeof(char), sizeof(j->birthdate), out);
    fwrite(&j->age, sizeof(int), 1, out);
    fwrite(&j->exp, sizeof(int), 1, out);
    fwrite(j->school, sizeof(char), sizeof(j->school), out);
}


// retorna a quantidade de registros no arquivo
int tamanho_arquivo(FILE *arq)
{
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / (sizeof(TPlayer) + sizeof(TCoach));
    rewind(arq);
    return tam;
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TPlayer *le(FILE *out)
{
    TPlayer *j = (TPlayer *)malloc(sizeof(TPlayer));

    fread(j->player, sizeof(char), sizeof(j->player), out);
    if (0 >= fread(&j->no, sizeof(int), 1, out))
    {
        free(j);
        return NULL;
    }


    fread(j->pos, sizeof(char), sizeof(j->pos), out);
    fread(&j->height, sizeof(float), 1, out);
    fread(&j->weight, sizeof(float), 1, out);
    fread(j->birthdate, sizeof(char), sizeof(j->birthdate), out);
    fread(&j->age, sizeof(int), 1, out);
    fread(&j->exp, sizeof(int), 1, out);
    fread(j->school, sizeof(char), sizeof(j->school), out);

    // Adicione instruções de impressão para verificar os valores lidos
    return j;
}


//-------------------------------------------------------------------------


TCoach *treinador(char nome[50],int exp, int age)
{
    TCoach *j = (TCoach *) malloc(sizeof(TCoach));
    //inicializa espaco de memoria com ZEROS
    if (j)
    {
        memset(j, 0, sizeof(TCoach));
    }//copia valores para os campos de func

    strcpy(j->nome, nome);
    j->age = age;
    j->exp =exp;

    return j;
}
void salvaT(TCoach *j, FILE *out)
{
    fwrite(j->nome, sizeof(char), sizeof(j->nome), out);
    fwrite(&j->age, sizeof(int), 1, out);
    fwrite(&j->exp, sizeof(int), 1, out);
}


TCoach *leT(FILE *out)
{
    TCoach *j = (TCoach *)malloc(sizeof(TCoach));
    fread(j->nome, sizeof(char), sizeof(j->nome), out);
    if (0 >=  fread(&j->age, sizeof(int), 1, out))
    {
        free(j);
        return NULL;
    }
    fread(&j->exp, sizeof(int), 1, out);
    return j;
}


// Imprime funcionario
void imprime(TPlayer *j)
{
    printf("**********************************************\n");
    printf("Nome: %s\n", j->player);
    printf("Numero do jogdor: %d\n", j->no);
    printf("Posicao: %s\n", j->pos);
    printf("Altura: %.2f\n", j->height);
    printf("Peso: %.2f\n", j->weight);
    printf("Data de Nascimento: %s\n", j->birthdate);
    printf("Idade: %d\n", j->age);
    printf("Experiencia: %d\n", j->exp);
    printf("Escola: %s\n", j->school);

    printf("**********************************************\n");
}

void imprimeT(TCoach *coach)
{
    printf("**********************************************\n");
    printf("Nome do treinador: %s\n",coach->nome);
    printf("Idade do treinador: %d\n",coach->age);
    printf("Experiencia do treinador: %d\n", coach->exp);


}

void todos(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }


    TPlayer *player;

    player = jogador("Al Horford", 42, "Center", 2.06, 240, "03/06/1986", 37, 16,"Florida");
    salva(player, out);


    player = jogador("Jrue Holiday",4,	"Guard",1.93,205,"12/06/1990",	33,	14,	"UCLA");
    salva(player, out);


    player = jogador("Jaylen Brown",7,	"Foward",1.98,223,"24/10/1996",	27,	7,	"California");
    salva(player, out);


    player = jogador("Kristaps Porzingis",8,"Foward-Center",2.18,240,"02/08/1995",	28,	7,	"Cajasol Sevilla");
    salva(player, out);


    player = jogador("Jayson Tatum",0,"Foward-Guard",2.03,210, " 03/03/1998",	25,	6,	"Duke");
    salva(player, out);


    player = jogador("Derrick White",9,"Guard",	1.93,190,"02/06/1994",	29,	6,	"Colorado");
    salva(player, out);


    player = jogador("Luke Kornet",40,"Center-Foward",2.16, 250,"15/07/1995",28,	6,	"Vanderbilt");
    salva(player, out);


    player = jogador("Svi Mykhailiuk",50,"Guard-Foward",2.01,205,"10/06/1997",	26,	5,	"Kansas");
    salva(player, out);


    player = jogador("Oshae Brissett",12,"Foward-Guard",2.01,210," 20/06/1998",	25,	4,	"Syracuse");
    salva(player, out);


    player = jogador("Nathan Knight",1,	"Foward-Center",2.03,253, "20/09/1997",	26,	3,	"William & Mary");
    salva(player, out);


    player = jogador("Payton Pritchard",11,"G",	1.85,195," 28/01/1998",25,	3,"Oregon");
    salva(player, out);


    player = jogador("Lamar Stevens", 77, "Foward",2.01, 230,"09/07/1997", 26,	3,	"Penn State");
    salva(player, out);

    player = jogador("Sam Hauser",30,"Foward", 2.01,	217,"08/12/1997",	25,	2,	"Virginia");
    salva(player, out);


    player = jogador("Dalano Banton",45, "Foward",2.03,204,"07/11/1999",	24,	2,	"Nebraska");
    salva(player, out);


    player = jogador("Neemias Queta",88, "Center",	2.13,248, "13/07/1999",	24,	2,	"Utah State");
    salva(player, out);


    player = jogador("JD Davison", 20,"Guard", 1.85, 195,	"03/10/2002",	21,	1,	"Alabama");
    salva(player, out);


    player = jogador("Jordan Walsh", 27, "Guard", 1.98, 205, "03/03/2004", 19, 0,"Arkansas");
    salva(player, out);

    player = jogador("Scottie Barnes", 4, "Forward", 2.01, 240, "01/08/2001", 22, 2, "Florida State");
    salva(player, out);

    player = jogador("Pascal Siakam", 43, "Forward", 2.03, 230, "02/04/1994", 29, 7, "New Mexico");
    salva(player, out);

    player = jogador("OG Anunoby", 3, "Forward", 2.01, 240, "17/07/1997", 26, 6, "Indiana");
    salva(player, out);

    player = jogador("Dennis Schroder", 17, "Guard", 1.85, 170, "15/09/1993", 30, 10, "Alemanha");
    salva(player, out);

    player = jogador("Gary Trent Jr.", 33, "Guard", 1.96, 210, "18/01/1999", 24, 5, "Duke");
    salva(player, out);

    player = jogador("Jakob Poeltl", 19, "Center", 2.16, 229, "15/10/1995", 28, 7, "Utah");
    salva(player, out);

    player = jogador("Precious Achiuwa", 5, "Forward", 2.03, 225, "19/09/1999", 24, 3, "Memphis");
    salva(player, out);

    player = jogador("Chris Boucher", 25, "Forward", 2.06, 193, "11/01/1993", 30, 6, "Oregon");
    salva(player, out);

    player = jogador("Malachi Flynn", 22, "Guard", 1.85, 180, "09/05/1998", 25, 3, "San Diego");
    salva(player, out);

    player = jogador("Gradey Dick", 1, "Guard", 2.03, 205, "20/11/2003", 19, 0, "Kansas");
    salva(player, out);

    player = jogador("Otto Porter Jr.", 32, "Forward", 2.03, 200, "03/06/1993", 30, 10, "Georgetown");
    salva(player, out);

    player = jogador("Garrett Temple", 14, "Guard", 1.96, 190, "08/05/1986", 37, 13, "LSU");
    salva(player, out);

    player = jogador("Markquis Nowell", 24, "Guard", 1.73, 160, "25/12/1999", 23, 0, "Kansas");
    salva(player, out);

    player = jogador("Jalen McDaniels", 2, "Forward", 2.06, 200, "31/01/1998", 25, 4, "San Diego");
    salva(player, out);

    player = jogador("Thaddeus Young", 21, "Forward", 2.03, 220, "21/06/1988", 35, 16, "Georgia");
    salva(player, out);

    player = jogador("Cam Thomas", 24, "Guard", 1.91, 210, "13/10/2001", 22, 2, "LSU");
    salva(player, out);

    player = jogador("Mikal Bridges", 1, "Forward", 1.98, 210, "30/08/1996", 27, 5, "Villanova");
    salva(player, out);

    player = jogador("Lonnie Walker IV", 8, "Guard", 1.93, 200, "14/12/1998", 24, 5, "Miami");
    salva(player, out);

    player = jogador("Cam Johnson", 2, "Forward", 2.03, 210, "03/03/1996", 27, 4, "North Carolina");
    salva(player, out);

    player = jogador("Spencer Dinwiddie", 26, "Guard", 1.98, 220, "06/04/1993", 30, 9, "Colorado");
    salva(player, out);

    player = jogador("Dorian Finney-Smith", 28, "Forward", 2.01, 220, "04/05/1993", 30, 7, "Virginia");
    salva(player, out);

    player = jogador("Nic Claxton", 33, "Center", 2.11, 220, "17/04/1999", 24, 4, "Georgia");
    salva(player, out);

    player = jogador("Royce O'Neale", 0, "Forward", 1.96, 227, "05/06/1993", 30, 8, "Baylor");
    salva(player, out);

    player = jogador("Trendon Watford", 9, "Forward", 2.03, 237, "09/11/2000", 23, 2, "LSU");
    salva(player, out);

    player = jogador("Day'Ron Sharpe", 20, "Center", 2.06, 265, "06/11/2001", 22, 2, "North Carolina");
    salva(player, out);

    player = jogador("Ben Simmons", 10, "Guard", 2.08, 240, "20/07/1996", 27, 7, "Luisiana");
    salva(player, out);

    player = jogador("Harry Giles", 14, "Forward", 2.11, 240, "22/04/1998", 25, 6, "Duke");
    salva(player, out);

    player = jogador("Dennis Smith", 4, "Guard", 1.88, 200, "25/11/1997", 25, 6, "North Carolina");
    salva(player, out);

    player = jogador("Armoni Brooks", 13, "Guard", 1.91, 190, "05/06/1998", 25, 4, "McNeil");
    salva(player, out);

    player = jogador("Joel Embiid", 21, "Center", 2.13, 280, "16/03/1994", 29, 9, "Kansas");
    salva(player, out);

    player = jogador("Tyrese Maxey", 0, "Guard", 1.88, 200, "04/11/2000", 23, 3, "Kentucky");
    salva(player, out);

    player = jogador("Tobias Harris", 12, "Forward", 2.01, 236, "15/07/1992", 31, 12, "Tennessee");
    salva(player, out);

    player = jogador("Kelly Oubre Jr.", 9, "Guard", 1.98, 200, "09/12/1995", 27, 8, "Kansas");
    salva(player, out);

    player = jogador("De'Anthony Melton", 8, "Guard", 1.88, 190, "28/05/1998", 25, 5, "South California");
    salva(player, out);

    player = jogador("Kenyon Martin", 1, "Forward", 2.01, 220, "06/01/2001", 22, 3, "Sierra Canyon");
    salva(player, out);

    player = jogador("Paul Reed", 44, "Forward", 2.06, 210, "14/06/1999", 24, 3, "Orlando");
    salva(player, out);

    player = jogador("Jaden Springer", 11, "Guard", 1.93, 200, "25/09/2002", 21, 2, "Tennessee");
    salva(player, out);

    player = jogador("Danuel House", 25, "Forward", 1.98, 220, "07/06/1993", 30, 7, "Texas");
    salva(player, out);

    player = jogador("Robert Covington", 33, "Forward", 2.01, 210, "14/12/1990", 32, 10, "Tennessee");
    salva(player, out);

    player = jogador("Nicolas Batum", 40, "Forward", 2.03, 200, "14/12/1988", 34, 15, "France");
    salva(player, out);

    player = jogador("Furkan Korkmaz", 30, "Forward", 2.01, 200, "24/07/1997", 26, 7, "Turkey");
    salva(player, out);

    player = jogador("Patrick Beverley", 22, "Guard", 1.85, 180, "12/07/1988", 35, 14, "Arkansas");
    salva(player, out);

    player = jogador("Mo Bamba", 7, "Center", 2.13, 231, "12/05/1998", 25, 5, "Texas");
    salva(player, out);

    player = jogador("Marcus Morris", 5, "Forward", 2.03, 236, "02/09/1989", 34, 12, "Kansas");
    salva(player, out);

    player = jogador("Jalen Brunson", 11, "Guard", 1.85, 190, "31/08/1996", 27, 5, "Villanova");
    salva(player, out);

    player = jogador("RJ Barrett", 9, "Forward", 1.95, 210, "14/06/2000", 23, 4, "Duke");
    salva(player, out);

    player = jogador("Julius Randle", 30, "Forward", 2.03, 249, "29/11/1994", 28, 9, "Kentucky");
    salva(player, out);

    player = jogador("Immanuel Quickley", 5, "Guard", 1.91, 190, "17/06/1999", 24, 3, "Kentucky");
    salva(player, out);

    player = jogador("Donte DiVincenzo", 0, "Guard", 1.93, 200, "31/01/1997", 26, 5, "Villanova");
    salva(player, out);

    player = jogador("Quentin Grimes", 6, "Guard", 1.93, 210, "08/05/2000", 23, 2, "Kansas");
    salva(player, out);

    player = jogador("Josh Hart", 3, "Forward", 1.96, 210, "06/03/1995", 28, 6, "Villanova");
    salva(player, out);

    player = jogador("Isaiah Hartenstein", 55, "Center", 2.13, 250, "05/05/1998", 25, 6, "Germany");
    salva(player, out);

    player = jogador("Mitchell Robinson", 23, "Center", 2.13, 233, "01/04/1998", 25, 5, "Kentucky");
    salva(player, out);

    player = jogador("Miles McBride", 2, "Guard", 1.85, 190, "08/09/2000", 23, 2, "West Virginia");
    salva(player, out);

    player = jogador("Evan Fournier", 13, "Forward", 2.01, 210, "29/10/1992", 31, 11, "France");
    salva(player, out);

    player = jogador("DaQuan Jeffries", 8, "Forward", 1.96, 222, "30/08/1997", 26, 4, "Texas");
    salva(player, out);

    player = jogador("Dylan Windler", 20, "Guard", 1.98, 200, "22/09/1996", 27, 4, "Belmont");
    salva(player, out);

    player = jogador("Jericho Sims", 45, "Center", 2.06, 250, "20/10/1998", 25, 2, "Texas");
    salva(player, out);

    player = jogador("Giannis Antetokounmpo", 34, "Forward", 2.11, 243, "06/12/1994", 28, 10, "Greece");
    salva(player, out);

    player = jogador("Damian Lillard", 0, "Guard", 1.88, 180, "15/07/1990", 33, 11, "Weber State");
    salva(player, out);

    player = jogador("Bobby Portis", 9, "Forward", 2.08, 250, "10/02/1995", 28, 8, "Arkansas");
    salva(player, out);

    player = jogador("Khris Middleton", 22, "Forward", 2.01, 222, "12/08/1991", 32, 11, "Texas");
    salva(player, out);

    player = jogador("Malik Beasley", 0, "Guard", 1.93, 190, "26/11/1996", 26, 7, "Florida");
    salva(player, out);

    player = jogador("Brook Lopez", 11, "Center", 2.13, 282, "01/04/1988", 35, 15, "Stanford");
    salva(player, out);

    player = jogador("Jae Crowder", 99, "Forward", 1.98, 234, "06/07/1990", 33, 11, "Marquette");
    salva(player, out);

    player = jogador("MarJon Beauchamp", 3, "Forward", 1.98, 200, "12/10/2000", 23, 1, "Yakima Valley");
    salva(player, out);

    player = jogador("Cameron Payne", 15, "Guard", 1.85, 180, "08/08/1994", 29, 8, "Murray State");
    salva(player, out);

    player = jogador("Pat Connaughton", 24, "Guard", 1.96, 210, "06/01/1993", 30, 8, "Notre Dame");
    salva(player, out);

    player = jogador("AJ Green", 20, "Guard", 1.93, 190, "27/09/1999", 24, 1, "Wi  sconsin");
    salva(player, out);

    player = jogador("Chris Livingston", 7, "Forward", 1.98, 220, "15/10/2003", 20, 0, "Kentucky");
    salva(player, out);

    player = jogador("Thanasis Antetokounmpo", 43, "Forward", 1.98, 220, "18/07/1992", 31, 9, "Greece");
    salva(player, out);

    player = jogador("Robin Lopez", 42, "Center", 2.13, 281, "01/04/1988", 35, 15, "Stanford");
    salva(player, out);

    player = jogador("Tyler Herro", 14, "Guard", 1.96, 190, "20/01/2000", 23, 4, "Kentucky");
    salva(player, out);

    player = jogador("Bam Adebayo", 13, "Center", 2.06, 255, "18/07/1997", 26, 6, "Kentucky");
    salva(player, out);

    player = jogador("Jimmy Butler", 22, "Forward", 2.01, 230, "14/09/1989", 34, 12, "Marquette");
    salva(player, out);

    player = jogador("Duncan Robinson", 55, "Guard", 2.01, 220, "22/04/1994", 29, 5, "Michigan");
    salva(player, out);

    player = jogador("Jaime Jaquez", 11, "Forward", 2.01, 225, "18/02/2001", 22, 0, "UCLA");
    salva(player, out);

    player = jogador("Josh Richardson", 2, "Guard", 1.96, 200, "15/09/1993", 30, 8, "Tennessee");
    salva(player, out);

    player = jogador("Kevin Love", 42, "Forward", 2.03, 251, "07/09/1988", 35, 15, "UCLA");
    salva(player, out);

    player = jogador("Haywood Highsmith", 24, "Forward", 1.93, 220, "09/12/1996", 26, 5, "Wheeling");
    salva(player, out);

    player = jogador("Kyle Lowry", 7, "Guard", 1.83, 200, "25/10/1986", 37, 17, "Villanova");
    salva(player, out);

    player = jogador("Nikola Jovic", 5, "Forward", 2.08, 200, "09/06/2003", 20, 1, "Serbia");
    salva(player, out);

    player = jogador("Dru Smith", 9, "Guard", 1.91, 200, "30/12/1997", 25, 2, "Evansville");
    salva(player, out);

    player = jogador("Orlando Robinson", 25, "Center", 2.13, 235, "10/07/2000", 23, 1, "Fresno State");
    salva(player, out);

    player = jogador("Thomas Bryant", 31, "Center", 2.08, 248, "31/07/1997", 26, 6, "Indiana");
    salva(player, out);

    player = jogador("Caleb Martin", 16, "Forward", 1.96, 200, "28/09/1995", 28, 4, "North Carolina");
    salva(player, out);

    player = jogador("Paolo Banchero", 5, "Forward", 2.08, 249, "12/11/2002", 21, 1, "Duke");
    salva(player, out);

    player = jogador("Franz Wagner", 22, "Forward", 2.08, 220, "27/08/2001", 22, 2, "Germany");
    salva(player, out);

    player = jogador("Cole Anthony", 50, "Guard", 1.91, 190, "15/05/2000", 23, 3, "North Carolina");
    salva(player, out);

    player = jogador("Jalen Suggs", 4, "Guard", 1.96, 200, "03/06/2001", 22, 2, "Gonzaga");
    salva(player, out);

    player = jogador("Moritz Wagner", 21, "Center", 2.11, 245, "26/04/1997", 26, 5, "Michigan");
    salva(player, out);

    player = jogador("Markelle Fultz", 20, "Guard", 1.93, 200, "29/05/1998", 25, 6, "Washington");
    salva(player, out);

    player = jogador("Wendell Carter Jr.", 34, "Center", 2.08, 270, "16/04/1999", 24, 5, "Duke");
    salva(player, out);

    player = jogador("Gary Harris", 14, "Guard", 1.93, 210, "14/09/1994", 29, 9, "Michigan");
    salva(player, out);

    player = jogador("Goga Bitadze", 35, "Center", 2.13, 250, "20/07/1999", 24, 4, "Georgia");
    salva(player, out);

    player = jogador("Jonathan Isaac", 1, "Forward", 2.08, 230, "03/10/1997", 26, 6, "Florida");
    salva(player, out);

    player = jogador("Anthony Black", 0, "Guard", 2.01, 200, "20/01/2004", 19, 0, "Arkansas");
    salva(player, out);

    player = jogador("Joe Ingles", 7, "Forward", 2.06, 227, "02/10/1987", 36, 14, "Australia");
    salva(player, out);

    player = jogador("Tyrese Haliburton", 0, "Guard", 1.96, 190, "29/02/2000", 23, 3, "Iowa");
    salva(player, out);

    player = jogador("Myles Turner", 33, "Center", 2.11, 250, "24/03/1996", 27, 8, "Texas");
    salva(player, out);

    player = jogador("Bennedict Mathurin", 0, "Guard", 1.98, 210, "19/06/2002", 21, 1, "Arizona");
    salva(player, out);

    player = jogador("Buddy Hield", 7, "Guard", 1.93, 210, "17/12/1992", 30, 7, "Oklahoma");
    salva(player, out);

    player = jogador("Bruce Brown", 11, "Forward", 1.93, 200, "15/08/1996", 27, 5, "Miami");
    salva(player, out);

    player = jogador("Jalen Smith", 25, "Forward", 2.08, 220, "16/03/2000", 23, 3, "Maryland");
    salva(player, out);

    player = jogador("Obi Toppin", 1, "Forward", 2.06, 220, "04/03/1998", 25, 3, "Dayton");
    salva(player, out);

    player = jogador("Aaron Nesmith", 23, "Guard", 1.96, 220, "16/10/1999", 24, 3, "Vanderbilt");
    salva(player, out);

    player = jogador("Jordan Nwora", 13, "Forward", 2.03, 205, "09/09/1998", 25, 3, "Louisville");
    salva(player, out);

    player = jogador("T.J. McConnell", 9, "Guard", 1.85, 190, "25/03/1992", 31, 8, "Arizona");
    salva(player, out);

    player = jogador("Andrew Nembhard", 2, "Guard", 1.96, 190, "16/01/2000", 23, 1, "Gonzaga");
    salva(player, out);

    player = jogador("Isaiah Jackson", 22, "Forward", 2.08, 200, "10/01/2002", 21, 2, "Kentucky");
    salva(player, out);


    free(player);

}

void Boston(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    TPlayer *player;
    TCoach *coach;
    if(chose == 1)
    {

        coach = treinador("Joe Mazzulla", 0, 35);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Al Horford", 42, "Center", 2.06, 240, "03/06/1986", 37, 16,"Florida");
    salva(player, out);


    player = jogador("Jrue Holiday",4,	"Guard",1.93,205,"12/06/1990",	33,	14,	"UCLA");
    salva(player, out);


    player = jogador("Jaylen Brown",7,	"Foward",1.98,223,"24/10/1996",	27,	7,	"California");
    salva(player, out);


    player = jogador("Kristaps Porzingis",8,"Foward Center",2.18,240,"02/08/1995",	28,	7,	"Cajasol Sevilla");
    salva(player, out);


    player = jogador("Jayson Tatum",0,"Foward Guard",2.03,210, " 03/03/1998",	25,	6,	"Duke");
    salva(player, out);


    player = jogador("Derrick White",9,"Guard",	1.93,190,"02/06/1994",	29,	6,	"Colorado");
    salva(player, out);


    player = jogador("Luke Kornet",40,"Center Foward",2.16, 250,"15/07/1995",28,	6,	"Vanderbilt");
    salva(player, out);


    player = jogador("Svi Mykhailiuk",50,"Guard Foward",2.01,205,"10/06/1997",	26,	5,	"Kansas");
    salva(player, out);


    player = jogador("Oshae Brissett",12,"Foward Guard",2.01,210," 20/06/1998",	25,	4,	"Syracuse");
    salva(player, out);


    player = jogador("Nathan Knight",1,	"Foward Center",2.03,253, "20/09/1997",	26,	3,	"William & Mary");
    salva(player, out);


    player = jogador("Payton Pritchard",11,"Guard",	1.85,195," 28/01/1998",25,	3,"Oregon");
    salva(player, out);


    player = jogador("Lamar Stevens", 77, "Foward",2.01, 230,"09/07/1997", 26,	3,	"Penn State");
    salva(player, out);

    player = jogador("Sam Hauser",30,"Foward", 2.01,	217,"08/12/1997",	25,	2,	"Virginia");
    salva(player, out);


    player = jogador("Dalano Banton",45, "Foward",2.03,204,"07/11/1999",	24,	2,	"Nebraska");
    salva(player, out);


    player = jogador("Neemias Queta",88, "Center",	2.13,248, "13/07/1999",	24,	2,	"Utah State");
    salva(player, out);


    player = jogador("JD Davison", 20,"Guard", 1.85, 195,	"03/10/2002",	21,	1,	"Alabama");
    salva(player, out);


    player = jogador("Jordan Walsh", 27, "Guard", 1.98, 205, "03/03/2004", 19, 0,"Arkansas");
    salva(player, out);

    free(player);
}

void Toronto(FILE *out, int chose)
{
    TPlayer *player;

    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Darko Rajaković", 0, 44);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Scottie Barnes", 4, "Forward", 2.01, 240, "01/08/2001", 22, 2, "Florida State");
    salva(player, out);

    player = jogador("Pascal Siakam", 43, "Forward", 2.03, 230, "02/04/1994", 29, 7, "New Mexico");
    salva(player, out);

    player = jogador("OG Anunoby", 3, "Forward", 2.01, 240, "17/07/1997", 26, 6, "Indiana");
    salva(player, out);

    player = jogador("Dennis Schroder", 17, "Guard", 1.85, 170, "15/09/1993", 30, 10, "Alemanha");
    salva(player, out);

    player = jogador("Gary Trent Jr.", 33, "Guard", 1.96, 210, "18/01/1999", 24, 5, "Duke");
    salva(player, out);

    player = jogador("Jakob Poeltl", 19, "Center", 2.16, 229, "15/10/1995", 28, 7, "Utah");
    salva(player, out);

    player = jogador("Precious Achiuwa", 5, "Forward", 2.03, 225, "19/09/1999", 24, 3, "Memphis");
    salva(player, out);

    player = jogador("Chris Boucher", 25, "Forward", 2.06, 193, "11/01/1993", 30, 6, "Oregon");
    salva(player, out);

    player = jogador("Malachi Flynn", 22, "Guard", 1.85, 180, "09/05/1998", 25, 3, "San Diego");
    salva(player, out);

    player = jogador("Gradey Dick", 1, "Guard", 2.03, 205, "20/11/2003", 19, 0, "Kansas");
    salva(player, out);

    player = jogador("Otto Porter Jr.", 32, "Forward", 2.03, 200, "03/06/1993", 30, 10, "Georgetown");
    salva(player, out);

    player = jogador("Garrett Temple", 14, "Guard", 1.96, 190, "08/05/1986", 37, 13, "LSU");
    salva(player, out);

    player = jogador("Markquis Nowell", 24, "Guard", 1.73, 160, "25/12/1999", 23, 0, "Kansas");
    salva(player, out);

    player = jogador("Jalen McDaniels", 2, "Forward", 2.06, 200, "31/01/1998", 25, 4, "San Diego");
    salva(player, out);

    player = jogador("Thaddeus Young", 21, "Forward", 2.03, 220, "21/06/1988", 35, 16, "Georgia");
    salva(player, out);


    free(player);
}

void Nets(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    TPlayer *player;

    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Adrian Griffin", 13, 48);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Cam Thomas", 24, "Guard", 1.91, 210, "13/10/2001", 22, 2, "LSU");
    salva(player, out);

    player = jogador("Mikal Bridges", 1, "Forward", 1.98, 210, "30/08/1996", 27, 5, "Villanova");
    salva(player, out);

    player = jogador("Lonnie Walker IV", 8, "Guard", 1.93, 200, "14/12/1998", 24, 5, "Miami");
    salva(player, out);

    player = jogador("Cam Johnson", 2, "Forward", 2.03, 210, "03/03/1996", 27, 4, "North Carolina");
    salva(player, out);

    player = jogador("Spencer Dinwiddie", 26, "Guard", 1.98, 220, "06/04/1993", 30, 9, "Colorado");
    salva(player, out);

    player = jogador("Dorian Finney-Smith", 28, "Forward", 2.01, 220, "04/05/1993", 30, 7, "Virginia");
    salva(player, out);

    player = jogador("Nic Claxton", 33, "Center", 2.11, 220, "17/04/1999", 24, 4, "Georgia");
    salva(player, out);

    player = jogador("Royce O'Neale", 0, "Forward", 1.96, 227, "05/06/1993", 30, 8, "Baylor");
    salva(player, out);

    player = jogador("Trendon Watford", 9, "Forward", 2.03, 237, "09/11/2000", 23, 2, "LSU");
    salva(player, out);

    player = jogador("Day'Ron Sharpe", 20, "Center", 2.06, 265, "06/11/2001", 22, 2, "North Carolina");
    salva(player, out);

    player = jogador("Ben Simmons", 10, "Guard", 2.08, 240, "20/07/1996", 27, 7, "Luisiana");
    salva(player, out);

    player = jogador("Harry Giles", 14, "Forward", 2.11, 240, "22/04/1998", 25, 6, "Duke");
    salva(player, out);

    player = jogador("Dennis Smith", 4, "Guard", 1.88, 200, "25/11/1997", 25, 6, "North Carolina");
    salva(player, out);

    player = jogador("Armoni Brooks", 13, "Guard", 1.91, 190, "05/06/1998", 25, 4, "McNeil");
    salva(player, out);


    free(player);

}

void Sixers(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    TPlayer *player;

    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Nick Nurse", 5, 56);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Joel Embiid", 21, "Center", 2.13, 280, "16/03/1994", 29, 9, "Kansas");
    salva(player, out);

    player = jogador("Tyrese Maxey", 0, "Guard", 1.88, 200, "04/11/2000", 23, 3, "Kentucky");
    salva(player, out);

    player = jogador("Tobias Harris", 12, "Forward", 2.01, 236, "15/07/1992", 31, 12, "Tennessee");
    salva(player, out);

    player = jogador("Kelly Oubre Jr.", 9, "Guard", 1.98, 200, "09/12/1995", 27, 8, "Kansas");
    salva(player, out);

    player = jogador("De'Anthony Melton", 8, "Guard", 1.88, 190, "28/05/1998", 25, 5, "South California");
    salva(player, out);

    player = jogador("Kenyon Martin", 1, "Forward", 2.01, 220, "06/01/2001", 22, 3, "Sierra Canyon");
    salva(player, out);

    player = jogador("Paul Reed", 44, "Forward", 2.06, 210, "14/06/1999", 24, 3, "Orlando");
    salva(player, out);

    player = jogador("Jaden Springer", 11, "Guard", 1.93, 200, "25/09/2002", 21, 2, "Tennessee");
    salva(player, out);

    player = jogador("Danuel House", 25, "Forward", 1.98, 220, "07/06/1993", 30, 7, "Texas");
    salva(player, out);

    player = jogador("Robert Covington", 33, "Forward", 2.01, 210, "14/12/1990", 32, 10, "Tennessee");
    salva(player, out);

    player = jogador("Nicolas Batum", 40, "Forward", 2.03, 200, "14/12/1988", 34, 15, "France");
    salva(player, out);

    player = jogador("Furkan Korkmaz", 30, "Forward", 2.01, 200, "24/07/1997", 26, 7, "Turkey");
    salva(player, out);

    player = jogador("Patrick Beverley", 22, "Guard", 1.85, 180, "12/07/1988", 35, 14, "Arkansas");
    salva(player, out);

    player = jogador("Mo Bamba", 7, "Center", 2.13, 231, "12/05/1998", 25, 5, "Texas");
    salva(player, out);

    player = jogador("Marcus Morris", 5, "Forward", 2.03, 236, "02/09/1989", 34, 12, "Kansas");
    salva(player, out);


    free(player);
}

void Knicks(FILE *out, int chose)
{
    TPlayer *player;

    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Tom Thibodeau", 41, 65);
        salvaT(coach, out);
        free(coach);
    }
    player = jogador("Jalen Brunson", 11, "Guard", 1.85, 190, "31/08/1996", 27, 5, "Villanova");
    salva(player, out);

    player = jogador("RJ Barrett", 9, "Forward", 1.95, 210, "14/06/2000", 23, 4, "Duke");
    salva(player, out);

    player = jogador("Julius Randle", 30, "Forward", 2.03, 249, "29/11/1994", 28, 9, "Kentucky");
    salva(player, out);

    player = jogador("Immanuel Quickley", 5, "Guard", 1.91, 190, "17/06/1999", 24, 3, "Kentucky");
    salva(player, out);

    player = jogador("Donte DiVincenzo", 0, "Guard", 1.93, 200, "31/01/1997", 26, 5, "Villanova");
    salva(player, out);

    player = jogador("Quentin Grimes", 6, "Guard", 1.93, 210, "08/05/2000", 23, 2, "Kansas");
    salva(player, out);

    player = jogador("Josh Hart", 3, "Forward", 1.96, 210, "06/03/1995", 28, 6, "Villanova");
    salva(player, out);

    player = jogador("Isaiah Hartenstein", 55, "Center", 2.13, 250, "05/05/1998", 25, 6, "Germany");
    salva(player, out);

    player = jogador("Mitchell Robinson", 23, "Center", 2.13, 233, "01/04/1998", 25, 5, "Kentucky");
    salva(player, out);

    player = jogador("Miles McBride", 2, "Guard", 1.85, 190, "08/09/2000", 23, 2, "West Virginia");
    salva(player, out);

    player = jogador("Evan Fournier", 13, "Forward", 2.01, 210, "29/10/1992", 31, 11, "France");
    salva(player, out);

    player = jogador("DaQuan Jeffries", 8, "Forward", 1.96, 222, "30/08/1997", 26, 4, "Texas");
    salva(player, out);

    player = jogador("Dylan Windler", 20, "Guard", 1.98, 200, "22/09/1996", 27, 4, "Belmont");
    salva(player, out);

    player = jogador("Jericho Sims", 45, "Center", 2.06, 250, "20/10/1998", 25, 2, "Texas");
    salva(player, out);


    free(player);
}

void Bucks(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    TPlayer *player;

    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Adrian Griffin", 0, 49);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Giannis Antetokounmpo", 34, "Forward", 2.11, 243, "06/12/1994", 28, 10, "Greece");
    salva(player, out);

    player = jogador("Damian Lillard", 0, "Guard", 1.88, 180, "15/07/1990", 33, 11, "Weber State");
    salva(player, out);

    player = jogador("Bobby Portis", 9, "Forward", 2.08, 250, "10/02/1995", 28, 8, "Arkansas");
    salva(player, out);

    player = jogador("Khris Middleton", 22, "Forward", 2.01, 222, "12/08/1991", 32, 11, "Texas");
    salva(player, out);

    player = jogador("Malik Beasley", 0, "Guard", 1.93, 190, "26/11/1996", 26, 7, "Florida");
    salva(player, out);

    player = jogador("Brook Lopez", 11, "Center", 2.13, 282, "01/04/1988", 35, 15, "Stanford");
    salva(player, out);

    player = jogador("Jae Crowder", 99, "Forward", 1.98, 234, "06/07/1990", 33, 11, "Marquette");
    salva(player, out);

    player = jogador("MarJon Beauchamp", 3, "Forward", 1.98, 200, "12/10/2000", 23, 1, "Yakima Valley");
    salva(player, out);

    player = jogador("Cameron Payne", 15, "Guard", 1.85, 180, "08/08/1994", 29, 8, "Murray State");
    salva(player, out);

    player = jogador("Pat Connaughton", 24, "Guard", 1.96, 210, "06/01/1993", 30, 8, "Notre Dame");
    salva(player, out);

    player = jogador("AJ Green", 20, "Guard", 1.93, 190, "27/09/1999", 24, 1, "Wi  sconsin");
    salva(player, out);

    player = jogador("Chris Livingston", 7, "Forward", 1.98, 220, "15/10/2003", 20, 0, "Kentucky");
    salva(player, out);

    player = jogador("Thanasis Antetokounmpo", 43, "Forward", 1.98, 220, "18/07/1992", 31, 9, "Greece");
    salva(player, out);

    player = jogador("Robin Lopez", 42, "Center", 2.13, 281, "01/04/1988", 35, 15, "Stanford");
    salva(player, out);



    free(player);
}

void Heat(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    TPlayer *player;
    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Erick Spoelstra", 15, 53);
        salvaT(coach, out);
        free(coach);
    }
    player = jogador("Tyler Herro", 14, "Guard", 1.96, 190, "20/01/2000", 23, 4, "Kentucky");
    salva(player, out);

    player = jogador("Bam Adebayo", 13, "Center", 2.06, 255, "18/07/1997", 26, 6, "Kentucky");
    salva(player, out);

    player = jogador("Jimmy Butler", 22, "Forward", 2.01, 230, "14/09/1989", 34, 12, "Marquette");
    salva(player, out);

    player = jogador("Duncan Robinson", 55, "Guard", 2.01, 220, "22/04/1994", 29, 5, "Michigan");
    salva(player, out);

    player = jogador("Jaime Jaquez", 11, "Forward", 2.01, 225, "18/02/2001", 22, 0, "UCLA");
    salva(player, out);

    player = jogador("Josh Richardson", 2, "Guard", 1.96, 200, "15/09/1993", 30, 8, "Tennessee");
    salva(player, out);

    player = jogador("Kevin Love", 42, "Forward", 2.03, 251, "07/09/1988", 35, 15, "UCLA");
    salva(player, out);

    player = jogador("Haywood Highsmith", 24, "Forward", 1.93, 220, "09/12/1996", 26, 5, "Wheeling");
    salva(player, out);

    player = jogador("Kyle Lowry", 7, "Guard", 1.83, 200, "25/10/1986", 37, 17, "Villanova");
    salva(player, out);

    player = jogador("Nikola Jovic", 5, "Forward", 2.08, 200, "09/06/2003", 20, 1, "Serbia");
    salva(player, out);

    player = jogador("Dru Smith", 9, "Guard", 1.91, 200, "30/12/1997", 25, 2, "Evansville");
    salva(player, out);

    player = jogador("Orlando Robinson", 25, "Center", 2.13, 235, "10/07/2000", 23, 1, "Fresno State");
    salva(player, out);

    player = jogador("Thomas Bryant", 31, "Center", 2.08, 248, "31/07/1997", 26, 6, "Indiana");
    salva(player, out);

    player = jogador("Caleb Martin", 16, "Forward", 1.96, 200, "28/09/1995", 28, 4, "North Carolina");
    salva(player, out);

    free(player);
}

void Magic(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    TPlayer *player;
    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Jamahl Mosley", 18, 45);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Paolo Banchero", 5, "Forward", 2.08, 249, "12/11/2002", 21, 1, "Duke");
    salva(player, out);

    player = jogador("Franz Wagner", 22, "Forward", 2.08, 220, "27/08/2001", 22, 2, "Germany");
    salva(player, out);

    player = jogador("Cole Anthony", 50, "Guard", 1.91, 190, "15/05/2000", 23, 3, "North Carolina");
    salva(player, out);

    player = jogador("Jalen Suggs", 4, "Guard", 1.96, 200, "03/06/2001", 22, 2, "Gonzaga");
    salva(player, out);

    player = jogador("Moritz Wagner", 21, "Center", 2.11, 245, "26/04/1997", 26, 5, "Michigan");
    salva(player, out);

    player = jogador("Markelle Fultz", 20, "Guard", 1.93, 200, "29/05/1998", 25, 6, "Washington");
    salva(player, out);

    player = jogador("Wendell Carter Jr.", 34, "Center", 2.08, 270, "16/04/1999", 24, 5, "Duke");
    salva(player, out);

    player = jogador("Gary Harris", 14, "Guard", 1.93, 210, "14/09/1994", 29, 9, "Michigan");
    salva(player, out);

    player = jogador("Goga Bitadze", 35, "Center", 2.13, 250, "20/07/1999", 24, 4, "Georgia");
    salva(player, out);

    player = jogador("Jonathan Isaac", 1, "Forward", 2.08, 230, "03/10/1997", 26, 6, "Florida");
    salva(player, out);

    player = jogador("Anthony Black", 0, "Guard", 2.01, 200, "20/01/2004", 19, 0, "Arkansas");
    salva(player, out);

    player = jogador("Joe Ingles", 7, "Forward", 2.06, 227, "02/10/1987", 36, 14, "Australia");
    salva(player, out);




    free(player);
}

void Pacers(FILE *out, int chose)
{
    fclose(out);
    out = fopen("nba.dat", "w+b");

    if (out == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    TPlayer *player;
    if(chose == 1)
    {
        TCoach *coach;
        coach = treinador("Rick Carlisle", 29, 64);
        salvaT(coach, out);
        free(coach);
    }

    player = jogador("Tyrese Haliburton", 0, "Guard", 1.96, 190, "29/02/2000", 23, 3, "Iowa");
    salva(player, out);

    player = jogador("Myles Turner", 33, "Center", 2.11, 250, "24/03/1996", 27, 8, "Texas");
    salva(player, out);

    player = jogador("Bennedict Mathurin", 0, "Guard", 1.98, 210, "19/06/2002", 21, 1, "Arizona");
    salva(player, out);

    player = jogador("Buddy Hield", 7, "Guard", 1.93, 210, "17/12/1992", 30, 7, "Oklahoma");
    salva(player, out);

    player = jogador("Bruce Brown", 11, "Forward", 1.93, 200, "15/08/1996", 27, 5, "Miami");
    salva(player, out);

    player = jogador("Jalen Smith", 25, "Forward", 2.08, 220, "16/03/2000", 23, 3, "Maryland");
    salva(player, out);

    player = jogador("Obi Toppin", 1, "Forward", 2.06, 220, "04/03/1998", 25, 3, "Dayton");
    salva(player, out);

    player = jogador("Aaron Nesmith", 23, "Guard", 1.96, 220, "16/10/1999", 24, 3, "Vanderbilt");
    salva(player, out);

    player = jogador("Jordan Nwora", 13, "Forward", 2.03, 205, "09/09/1998", 25, 3, "Louisville");
    salva(player, out);

    player = jogador("T.J. McConnell", 9, "Guard", 1.85, 190, "25/03/1992", 31, 8, "Arizona");
    salva(player, out);

    player = jogador("Andrew Nembhard", 2, "Guard", 1.96, 190, "16/01/2000", 23, 1, "Gonzaga");
    salva(player, out);

    player = jogador("Isaiah Jackson", 22, "Forward", 2.08, 200, "10/01/2002", 21, 2, "Kentucky");
    salva(player, out);


    free(player);
}

void imprimirBase(FILE *out, int tam, int chose)
{
    int n = tam;
    printf("Tam: %d", tam);
    TPlayer *p;
    TCoach *t;
    printf("\nImprimindo a base de dados...\n");
    rewind(out);


    for (int i = 0; i<n; i++)
    {
        if(chose == 1 && i ==0)
        {
            t = leT(out);
            imprimeT(t);
            free(t);
        }
        else
        {
            p = le(out);
            imprime(p);
            free(p);
        }
    }

}

TPlayer *busca_binaria(FILE *out, int tam)
{

    int no=0;
    int left = 0, right = tam - 1;
    int cont = 0;

    clock_t inicio = clock();
    printf("---------Busca binaria---------");
    printf("\nInforme o numero do jogador: ");
    scanf("%d", &no);

    while (left <= right)
    {
        int middle = (left + right) / 2;
        fseek(out, middle * tamanho_registro(), SEEK_SET);
        TPlayer *player = le(out);


        if (no == player->no)
        {
            printf("\nJogador Encontrado!\n");
            imprime(player);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo de execução: %.2f segundos\n", tempo);
            printf("Número de comparações: %d\n", cont);
            free(player);
            return player;
        }
        else if (no < player->no)
        {
            right = middle - 1;
            cont++;
        }
        else
        {
            left = middle + 1;
            cont++;
        }

        free(player);
    }

    printf("Jogador não pertence à base de dados!...\n");
    printf("Numero de comparacoes: %d\n", cont);
    cont++;
    return NULL;
}

TPlayer *busca_sequencial(int no, FILE *out)
{
    TPlayer *player;
    int compare = 0;
    int found = 0;
    int noSearch;
    rewind(out);
    fseek(out, 0, SEEK_SET);

    clock_t inicio = clock();
    printf("---------Busca sequencial---------\n");
    printf("Digite o numero do jogador: ");
    scanf("%d", &noSearch);


    while ((player = le(out)) != NULL)
    {
        compare++;
        if (player->no == noSearch)
        {
            imprime(player);
            found = 1;
        }
        free(player);
    }

    if (found == 1)
    {
        printf("\nO número de comparacoes foi : %d\n", compare);


        FILE *arq;
        arq = fopen("resultados_busca_sequencial_jogadores.txt", "a");
        if (arq != NULL)
        {
            clock_t fim = clock();

            double tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo decorrido: %.2f\n", tempoTotal);

            fprintf(arq, "Numero procurado: %d\n", noSearch);
            fprintf(arq, "Tempo em segundos: %f\n", tempoTotal);
            fprintf(arq, "Número de comparacoes: %d\n", compare);
            fclose(arq);
        }

        return player;
    }
    else
    {
        printf("\nO número de comparações foi: %d\n", compare);
        printf("\nJogador não encontrado\n");
        return NULL;
    }
}

TPlayer *busca_sequencial_palavra(FILE *out)
{
    TPlayer *player;
    int compare = 0;
    int found = 0;
    char noSearch[100];
    rewind(out);
    fseek(out, 0, SEEK_SET);

    clock_t inicio = clock();
    printf("---------Busca sequencial---------\n");
    printf("Digite o nome do jogador: ");
    scanf(" %[^\n]s", noSearch);


    while ((player = le(out)) != NULL)
    {
        compare++;
        if (strcmp(player->player, noSearch) == 0)
        {
            printf("\nJogador Encontrado!\n");
            imprime(player);
            found = 1;
            break; // Não é necessário continuar a busca após encontrar o jogador
        }
        free(player);
    }

    if (found == 1)
    {
        printf("\nO número de comparações foi : %d\n", compare);

        FILE *arq;
        arq = fopen("resultados_busca_sequencial_jogadores.txt", "a");
        if (arq != NULL)
        {
            clock_t fim = clock();
            double tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Tempo decorrido: %.2f segundos\n", tempoTotal);

            fprintf(arq, "Nome procurado: %s\n", noSearch);
            fprintf(arq, "Tempo em segundos: %f\n", tempoTotal);
            fprintf(arq, "Número de comparações: %d\n", compare);
            fclose(arq);
        }

        return player;
    }
    else
    {
        printf("\nO número de comparações foi: %d\n", compare);
        printf("\nJogador não encontrado\n");
        return NULL;
    }
}

// Função para comparar dois jogadores com base em seus números
int comparar_jogadores(const void *a, const void *b)
{
    TPlayer *playerA = (TPlayer *)a;
    TPlayer *playerB = (TPlayer *)b;

    if (playerA->no < playerB->no) {
        return -1;
    } else if (playerA->no > playerB->no) {
        return 1;
    } else {
        return 0;
    }
}


void ordenacao(int arr[], int n, FILE *out)
{
    clock_t inicio = clock();
    int comparacao = 0;
    rewind(out);
    TPlayer registros[100];  // Assumindo que o máximo de registros é 100. Ajuste conforme necessário.

    // Passo 1: Ler todos os registros e armazená-los em uma matriz
    for (int i = 0; i < n; i++)
    {
        fseek(out, i * tamanho_registro(), SEEK_SET);
        TPlayer *p = le(out);
        registros[i] = *p;  // Copiar o registro lido para a matriz
        free(p);
    }

    // Passo 2: Ordenar a matriz com base no vetor 'arr'
    qsort(registros, n, sizeof(TPlayer), comparar_jogadores);

    // Passo 3: Salvar os registros ordenados de volta no arquivo
    for (int i = 0; i < n; i++)
    {
        fseek(out, i * tamanho_registro(), SEEK_SET);
        salva(&registros[i], out);
    }

    // Passo 4: Imprimir os registros ordenados
    printf("Registros ordenados:\n");
    fseek(out, 0, SEEK_SET);
    for (int i = 0; i < n; i++)
    {
        TPlayer *p = le(out);
        imprime(p);  // Utilizando a função imprime para imprimir cada registro

        free(p);



    }
      clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao do QuickSort: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);

    FILE *log_file = fopen("Log_jogadores.txt", "a"); // Modo de adição ao invés de escrita
    if (log_file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    fprintf(log_file, "INTERCALACAO OTIMA");
    fprintf(log_file, "\nTempo de execucao do metodo de selecao: %.2f segundos\n", tempo);
    fprintf(log_file, "Numero de comparacoes: %d\n", comparacao);

    fclose(log_file);


}

int selecaoSubstituicao (FILE *out,int m,int n, char nameFilePartition[]) {

    clock_t inicio = clock();
    int comparacao = 0;

    rewind(out);
    int numeroDeParticoes = 0, position = m;
    int smallElementPosition = 0, smallElement = 999999, sizeFileAux = 0;
    TPlayer player[m];
    int auxVetFunc[m];
    int nFunc = m;

    sizeFileAux = sizeFile(out);
    //printf("%d", sizeFileAux);

    printf("\nRealizando substituicao por selecao...");

    for (int i = 0; i < nFunc; ++i) {
        fseek(out, i *tamanho_registro(), SEEK_SET);

        TPlayer *aux = le(out);
        player[i] = *aux;

    }

    for (int i = 0; i < nFunc; ++i) {
        auxVetFunc[i] = player[i].no;
        //printf("\nAuxvet:%d\n",player[i].no);
    }

    while (position != sizeFileAux) {

        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(numeroDeParticoes, str1, 10);
        strcat(strcpy(nomeParticao, nameFilePartition), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);



        FILE *filePartition = fopen(nomeParticao, "wb+");

        int auxVetFrozen[m];

        while (position != sizeFileAux) {

            smallElement = 9999999;

            for (int i = 0; i < nFunc; ++i) {

                if (smallElement > auxVetFunc[i] && auxVetFrozen[i] != 1) {
                    smallElement = auxVetFunc[i];
                    smallElementPosition = i;
                }
            }

            salva(&player[smallElementPosition], filePartition);

            fseek(out, (position)*tamanho_registro(), SEEK_SET);

            TPlayer *auxiliar = le(out);
            //printf("\nAuxiliar: %d\n", auxiliar->no);
            position++;

            auxVetFunc[smallElementPosition] = auxiliar->no;
            player[smallElementPosition] = *auxiliar;

            if (auxiliar->no < smallElement) {
                auxVetFrozen[smallElementPosition] = 1;
            }

            if(registroMemoria(auxVetFrozen, m) == 1) {
                numeroDeParticoes++;
                break;
            }

        }

        fclose(filePartition);

        if (position >= sizeFileAux) {
            break;
        }

    }

    char nomeParticao[100];
    char str1[100];
    char str2[100] = ".dat";

    itoa(numeroDeParticoes, str1, 10);
    strcat(strcpy(nomeParticao, nameFilePartition), str1);
    strcat(strcpy(nomeParticao, nomeParticao), str2);

    FILE *filePartitionFinal = fopen(nomeParticao, "ab+");

    int k, j;

    TPlayer funcAux;

    for (k = 1; k < m; k++) {

        for (j = 0; j < m - 1; j++) {

            if (player[j].no > player[j + 1].no) {
                funcAux = player[j];
                player[j] = player[j + 1];
                player[j + 1] = funcAux;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        salva(&player[i], out);
    }

    fclose(filePartitionFinal);
    printf("Numero %d", numeroDeParticoes);

    for (int i = 0; i <= numeroDeParticoes; ++i) {


    itoa(i, str1, 10);  // Use 'i' como índice ao invés de 'numeroDeParticoes'
    strcat(strcpy(nomeParticao, nameFilePartition), str1);
    strcat(strcpy(nomeParticao, nomeParticao), str2);


        FILE *filePartition = fopen(nomeParticao, "rb+");

        imprime_jog(filePartition,n, nomeParticao);

        fclose(filePartition);
    }
    fclose(out);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao do metodo de intercalacao otima: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);

    FILE *log_file = fopen("Log_jogadores.txt", "a"); // Modo de adição ao invés de escrita
    if (log_file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    fprintf(log_file, "INTERCALACAO OTIMA");
    fprintf(log_file, "\nTempo de execucao do metodo de selecao: %.2f segundos\n", tempo);
    fprintf(log_file, "Numero de comparacoes: %d\n", comparacao);

    fclose(log_file);
    return numeroDeParticoes;

}

int sizeFile(FILE *out) {
    int contSizeFile = 0;
    int i = 0;
      // Garantir que o ponteiro do arquivo está no início

    while (1) {
        fseek(out,(i)*sizeof(TPlayer), SEEK_SET);
        TPlayer *aux = le(out);
        if (aux == NULL) {
            break;
        }
        free(aux);
        contSizeFile++;
        i++;
    }

    return contSizeFile;
}

void imprime_jog(FILE *out,int n, char nomeParticao[]) {
    printf("\nJogador da particao %s: \n", nomeParticao);

    int i;

    for(i = 0; i<n; i++){
        fseek(out, i*tamanho_registro(), SEEK_SET);
        TPlayer *aux = le(out);
        if(aux != NULL){
        printf(" %d ", aux->no);
           free(aux);
        }
    }
    printf("\n");
}


int registroMemoria(int vet[], int m) {
    int cont = 0;

    for (int i = 0; i < m; ++i) {


        if (vet[i] == 1) {
            cont++;
            //printf("\nElemento %d eh 1\n", i);
        }
    }

    if (cont == m) {
        //printf("\nTodos os elementos sao 1.\n");
        return 1;
    } else {
        //printf("\nNao todos os elementos sao 1.\n");
        return 0;
    }
}

void intercalacaoOtima(FILE *out, char nomeDaParticao[], int qtdParticoes) {
    FILE *particoes[qtdParticoes + 1];
    TPlayer *registros[qtdParticoes + 1];

    clock_t inicio = clock();
    int comparacao = 0;

    for (int i = 0; i < qtdParticoes; i++) {
        char nomeArqParticao[20];
        snprintf(nomeArqParticao, sizeof(nomeArqParticao), "%s%d.dat", nomeDaParticao, i);
        particoes[i] = fopen(nomeArqParticao, "rb"); // Leitura dos arquivos de partição
        if (particoes[i] == NULL) {
            printf("Erro ao abrir o arquivo da partição %s\n", nomeArqParticao);
            exit(1);
        }

        registros[i] = le(particoes[i]);
    }

    int grupoSize = 4; // Tamanho do grupo de partições a intercalar
    int numGrupos = qtdParticoes / grupoSize;

    // Looping para intercalar grupos de partições
    for (int grupo = 0; grupo < qtdParticoes; grupo += 4) {
        TPlayer *grupoRegistros[4 * qtdParticoes];
        int idx = 0;

        // Carrega os registros do grupo de 4 partições
        for (int i = grupo; i < grupo + 4 && i < qtdParticoes; i++) {
            while (registros[i] != NULL) {
                comparacao = comparacao + 1;
                grupoRegistros[idx++] = registros[i];
                registros[i] = le(particoes[i]);

                if (idx >= 4 * qtdParticoes) {
                    break;
                }
            }
        }

        // Ordena o grupo de registros
        for (int i = 0; i < idx - 1; i++) {
            for (int j = i + 1; j < idx; j++) {
                if (grupoRegistros[i]->no > grupoRegistros[j]->no) {
                    comparacao = comparacao + 1;
                    TPlayer *temp = grupoRegistros[i];
                    grupoRegistros[i] = grupoRegistros[j];
                    grupoRegistros[j] = temp;
                }
            }
        }

        // Cria o nome da partição de saída
        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        int numeroParticao = qtdParticoes + 1 + grupo / 4; // Nomear a partir do número da última partição + 1
        itoa(numeroParticao, str1, 10);
        strcat(strcpy(nomeParticao, nomeDaParticao), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        // Grava o grupo ordenado na partição
        FILE *filePartition = fopen(nomeParticao, "wb+");
        if (filePartition == NULL) {
            printf("Erro ao criar a partição %s\n", nomeParticao);
            exit(1);
        }

        for (int i = 0; i < idx; i++) {
            salva(grupoRegistros[i], filePartition);
        }

        fclose(filePartition);
    }

     // Looping para imprimir o conteúdo de cada partição gerada após a concatenação
    for (int grupo = 0; grupo < qtdParticoes; grupo += 4) {
        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        int numeroParticao = qtdParticoes + 1 + grupo / 4; // Nomear a partir do número da última partição + 1
        itoa(numeroParticao, str1, 10);
        strcat(strcpy(nomeParticao, nomeDaParticao), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        FILE *filePartition = fopen(nomeParticao, "rb+");
        if (filePartition == NULL) {
            printf("Erro ao abrir a partição %s para impressão\n", nomeParticao);
            exit(1);
        }

        imprimeParticoes(filePartition, nomeParticao);

        fclose(filePartition);
    }


    // Fecha os arquivos e libera memória
    for (int i = 0; i < qtdParticoes; i++) {
        fclose(particoes[i]);
        free(registros[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo de execucao do metodo de intercalacao otima: %.2f segundos\n", tempo);
    printf("Numero de comparacoes: %d\n\n\n", comparacao);

    FILE *log_file = fopen("Log_jogadores.txt", "a"); // Modo de adição ao invés de escrita
    if (log_file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    fprintf(log_file, "INTERCALACAO OTIMA");
    fprintf(log_file, "\nTempo de execucao do metodo de selecao: %.2f segundos\n", tempo);
    fprintf(log_file, "Numero de comparacoes: %d\n", comparacao);

    fclose(log_file);


}

void unirParticoesOrdenadas(char nomeDaParticao[], int numParticoes) {
    FILE *saidaFinal = fopen("saida_final_ordenada.dat", "wb+");
    if (saidaFinal == NULL) {
        printf("Erro ao criar o arquivo de saída final ordenada.\n");
        exit(1);
    }

    TPlayer *registros[numParticoes];
    FILE *particoes[numParticoes];

    // Abrir todas as partições
    for (int i = 0; i < numParticoes; i++) {
        char nomeArqParticao[20];
        snprintf(nomeArqParticao, sizeof(nomeArqParticao), "%s%d.dat", nomeDaParticao, i);
        particoes[i] = fopen(nomeArqParticao, "rb"); // Leitura dos arquivos de partição
        if (particoes[i] == NULL) {
            printf("Erro ao abrir o arquivo da partição %s\n", nomeArqParticao);
            exit(1);
        }

        registros[i] = le(particoes[i]);
    }

    // Merge sort para unir as partições ordenadas
    while (1) {
        int menorId = INT_MAX;
        int idxMenor = -1;

        // Encontrar o menor registro entre as partições
        for (int i = 0; i < numParticoes; i++) {
            if (registros[i] != NULL && registros[i]->no < menorId) {
                menorId = registros[i]->no;
                idxMenor = i;
            }
        }

        if (idxMenor == -1) {
            // Todos os registros foram unidos

            break;
        }

        // Salvar o registro no arquivo final
        salva(registros[idxMenor], saidaFinal);

        // Ler o próximo registro da partição correspondente
        registros[idxMenor] = le(particoes[idxMenor]);
    }

    // Fechar e remover as partições
    for (int i = 0; i < numParticoes; i++) {
        fclose(particoes[i]);
        char nomeArqParticao[20];
        snprintf(nomeArqParticao, sizeof(nomeArqParticao), "%s%d.dat", nomeDaParticao, i);
        remove(nomeArqParticao);
    }

    fclose(saidaFinal);

    // Abrir o arquivo final ordenado para impressão
    FILE *saidaFinalOrdenada = fopen("saida_final_ordenada.dat", "rb");
    if (saidaFinalOrdenada == NULL) {
        printf("Erro ao abrir o arquivo de saída final ordenada para impressão.\n");
        exit(1);
    }

    // Imprimir o conteúdo do arquivo final ordenado
    imprimeParticoesFinal(saidaFinalOrdenada, "saida_final_ordenada.dat");

    fclose(saidaFinalOrdenada);
}

//IMPRIMIR ID JOGADOR
void imprimeParticoes(FILE *file, char nomeParticao[]) {
    printf("PARTICAO: %s \n\n", nomeParticao);

    int totalPlayers = sizeFile(file);

    for (int i = 0; i < totalPlayers; ++i) {
        fseek(file, i * tamanho_registro(), SEEK_SET);
        TPlayer *aux = le(file);

        if (aux != NULL) {
            printf("%d ", aux->no);
            free(aux); // Liberar a memória alocada por le()
        }
    }

    printf("\n");
    printf("\n**********************************************************************************************\n");

}

//IMPRIMIR SAIDA FINAL
void imprimeParticoesFinal(FILE *file, char nomeParticao[]) {
    printf("PARTICAO: %s \n\n", nomeParticao);

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int totalPlayers = fileSize / tamanho_registro();

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < totalPlayers; ++i) {
        TPlayer *aux = le(file);

        if (aux != NULL) {
            printf("%d ", aux->no);
            free(aux); // Liberar a memória alocada por le()
        }
    }

    printf("\n");
    printf("\n********************************************************************************************\n");

}
