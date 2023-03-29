//TAD: lista seq.
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX 5    //estimativa do tamanho máximo da lista
#define TRUE 1     //define tipo boleano – não existe em C
#define FALSE 0
#define boolean int

//------------------------------------------------------

/* Estruturas e tipos empregados (Obs: aqui não está usando 
encapsulamento... definido aqui apenas p/ facilitar a implementação */

//-------------------------------------------

// (*) Alterado para uma string (buscar pelo nome do aluno).
typedef struct  {
        char string[30];
} tipo_chave;

//Tipo registro
typedef struct
{
   char nome[30];
   int idade;
   float media_final;
   //... (caso tenha mais campos)
} tipo_dado;

//Tipo elemento (registro + chave)

typedef struct
{
   tipo_chave chave;
   tipo_dado info;
} tipo_elem;

//Tipo lista (seq. encadeada)

typedef struct
{
   int nelem; //nro de elementos
   tipo_elem A[MAX+1];
} lista;


//-------------------------------------------

//Operações
//-------------------------------------------

// Funções contidas no arquivo "lista.c"

boolean Vazia(lista *L);
boolean Cheia(lista *L);
void Definir(lista *L);
void Apagar(lista *L);
boolean Inserir_posic(tipo_elem x, int p, lista *L);
boolean Inserir_ord(tipo_elem x, lista *L);           // modificada
boolean Buscar(tipo_chave x, lista *L, int *p);
boolean Buscar_ord(tipo_chave x, lista *L, int *p);  // modificada
boolean Busca_bin(tipo_chave x, lista *L, int *p);
void Remover_posic(int *p, lista *L);
boolean Remover_ch(tipo_chave x, lista *L);
void Impr_elem(tipo_elem t, int id);               // modificada (imprime o id)
void Imprimir(lista *L);
int Tamanho(lista *L);

// Funções contidas no arquivo "main.c" (adicionadas)

void loadData(lista *);
void mainMenu();
boolean verifyOpt(int, lista *);
void getKey(tipo_chave *);
void getElem(tipo_elem *);
void verifyIntError(int, int, int *);
void verifyFloatError(float, float, float *);
void searchForMore(lista *, int, boolean);
void chooseElement(lista *, int);
void pressEnter();
void saveData(lista *);

//-------------------------------------------
