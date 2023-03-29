#include "lista.h"  //Carrega o arquivo .h criado

//Implementa��o: lista seq.

//Opera��es
//-------------------------------------------
boolean Vazia(lista *L)
{
   //Retorna true (1): se vazia, false (0): caso contr�rio
   return (L->nelem == 0);
}

boolean Cheia(lista *L)
{
   //Retorna true (1): se cheia, false (0): caso contr�rio
   return (L->nelem == MAX);
}

void Definir(lista *L)
{
   /*Cria uma lista vazia. Este procedimento deve ser chamado
   para cada nova lista antes de qualquer outra opera��o.*/
   L->nelem = 0;
   L->A[0].chave.string[0] = '\0';
}

void Apagar(lista *L) 
{
   //Apaga "logicamente" uma lista
   L->nelem = 0;
}

boolean Inserir_posic(tipo_elem x, int p, lista *L)
{
   /*Insere x, que � um novo elemento na posi��o p da lista
   Se L = a_1, a_2,... a_n ent�o temos a_1, a_2, ... 
   a_{p-1}, x, a_{p+1}, ... an.
   Devolve true se sucesso, false c.c. (isto �: L n�o tem nenhuma 
   posi��o p ou lista cheia). Obs: Opera��o para LISTA N�O-ORDENADA */
   
   int q;

   if (Cheia(L) || p > L->nelem+1 || p < 1)
   {
      //Lista cheia ou posi��o n�o existe
      return FALSE;
   } 
   else 
   {
      for(q = L->nelem; q>=p; q--) //Copia vizinho p/ direita
	     L->A[q+1] = L->A[q];
      
			L->A[p] = x;
      L->nelem++;
      
	  return TRUE; //Inser��o feita com sucesso
   }
}

boolean Buscar(tipo_chave x, lista *L, int *p)
{   
   /*Retorna true, se x ocorre na posi��o p. Se x ocorre mais de
   uma vez, retorna a posi��o da primeira ocorr�ncia. Se x n�o
   ocorre, retorna false. Para listas N�O-ORDENADAS*/

   if (!Vazia(L))
   {
      int i = 1;
      while (i <= L->nelem) {
         if (!strcmp(L->A[i].info.nome, x.string))
         {
             *p = i;
             return TRUE;
         } else
             i++;
      }
   }
   return FALSE; //Retorna false se n�o encontrou
}

void Remover_posic(int *p, lista *L)
{
   /*S� � ativada ap�s a busca ter retornado a posi��o p
   do elemento a ser removido - Nro de Mov = (nelem � p)*/
   
   for (int i = *p+1; i <= L->nelem; i++)
      L->A[i-1] = L->A[i];
   
   L->nelem--;
}

// (*) Alterei para imprimir dados de um aluno.
void Impr_elem(tipo_elem t, int cur_ID)
{
	puts("===|Dados do Aluno|===");
	printf("ID: %d\n"
				 "Nome: %s\n"
			   "Idade: %d\n"
			   "Media: %.2f\n",
			   cur_ID, t.info.nome, t.info.idade, t.info.media_final);
}

void Imprimir(lista *L)
{
   //Imprime os elementos na sua ordem de preced�ncia
   
   int i;
   
   if (!Vazia(L))
      for (i = 1; i <= L->nelem; i++)
         Impr_elem(L->A[i], i);
}


int Tamanho(lista *L)
{
   //Retorna o tamanho da lista. Se L � vazia retorna 0
   
   return L->nelem;
}


//Implementa��es para listas ordenadas
//-------------------------------------------
/* (*) Insere ordenado na lista.
 *	A vari�vel "posi" guarda a posi��o que o elemento deve ser inserido.
 *  Como a inser��o � ordenada, pode-se usar a busca bin�ria para achar essa posi��o.
 *	Em vez de percorrer a lista inteira, pode-se determinar o local da inser��o
 *	atrav�s da compara��o (por exemplo, se � necess�rio inserir o elemento 5 e
 *	o elemento do meio � 4, ent�o o 5 s� pode ser inserido depois do meio).
 *	Ap�s isso, chama a fun��o que insere na posi��o. O tratamento de erro �
 *	feito na fun��o de inser��o e na main. */

boolean Inserir_ord(tipo_elem x, lista *L)
{
   /*Insere novo elemento de forma a manter a lista ordenada
   (crescente). Devolve true (se sucesso), false (c.c.)*/
	int posi = 1;

	// Faz uma busca bin�ria para saber a posi��o ideal do elemento.
	Busca_bin(x.chave, L, &posi);


	return Inserir_posic(x, posi, L);
}


boolean Busca_bin(tipo_chave x, lista *L, int *p)
{
   /*Retorna em p a posi��o de x na lista ORDENADA e true. 
   //Se x n�o ocorre, retorna false*/
   
   //Implementa��o de busca bin�ria
   int inf = 1;
   int sup = L->nelem;
   int meio;
   
   while (sup >= inf)
   {
      meio = (inf + sup)/2;

      if (!strcmp(L->A[meio].info.nome, x.string))
      {
					*p = meio; //Sai da busca
          return TRUE;
      } 
      
      if (strcmp(L->A[meio].info.nome, x.string) < 0)
        inf = meio+1;
      else
        sup = meio-1;
   }

	 // Caso para ser usado na inser��o ordenada.
   *p = inf;

   return FALSE;
}

boolean Remover_ch(tipo_chave x, lista *L)
{
   /*Remo��o dada a chave. Retorna true, se removeu, ou
   false, c.c.*/
   
   int posi;
   boolean removeu = FALSE;
   
   if (Busca_bin(x, L, &posi)) //Procura via busca bin�ria
   {        
       Remover_posic(&posi, L);
       removeu = TRUE;
   }
   
   return removeu;
}
//-------------------------------------------
