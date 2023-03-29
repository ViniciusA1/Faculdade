#include "lista.h"  //Carrega o arquivo .h criado

//Implementação: lista seq.

//Operações
//-------------------------------------------
boolean Vazia(lista *L)
{
   //Retorna true (1): se vazia, false (0): caso contrário
   return (L->nelem == 0);
}

boolean Cheia(lista *L)
{
   //Retorna true (1): se cheia, false (0): caso contrário
   return (L->nelem == MAX);
}

void Definir(lista *L)
{
   /*Cria uma lista vazia. Este procedimento deve ser chamado
   para cada nova lista antes de qualquer outra operação.*/
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
   /*Insere x, que é um novo elemento na posição p da lista
   Se L = a_1, a_2,... a_n então temos a_1, a_2, ... 
   a_{p-1}, x, a_{p+1}, ... an.
   Devolve true se sucesso, false c.c. (isto é: L não tem nenhuma 
   posição p ou lista cheia). Obs: Operação para LISTA NÃO-ORDENADA */
   
   int q;

   if (Cheia(L) || p > L->nelem+1 || p < 1)
   {
      //Lista cheia ou posição não existe
      return FALSE;
   } 
   else 
   {
      for(q = L->nelem; q>=p; q--) //Copia vizinho p/ direita
	     L->A[q+1] = L->A[q];
      
			L->A[p] = x;
      L->nelem++;
      
	  return TRUE; //Inserção feita com sucesso
   }
}

boolean Buscar(tipo_chave x, lista *L, int *p)
{   
   /*Retorna true, se x ocorre na posição p. Se x ocorre mais de
   uma vez, retorna a posição da primeira ocorrência. Se x não
   ocorre, retorna false. Para listas NÃO-ORDENADAS*/

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
   return FALSE; //Retorna false se não encontrou
}

void Remover_posic(int *p, lista *L)
{
   /*Só é ativada após a busca ter retornado a posição p
   do elemento a ser removido - Nro de Mov = (nelem – p)*/
   
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
   //Imprime os elementos na sua ordem de precedência
   
   int i;
   
   if (!Vazia(L))
      for (i = 1; i <= L->nelem; i++)
         Impr_elem(L->A[i], i);
}


int Tamanho(lista *L)
{
   //Retorna o tamanho da lista. Se L é vazia retorna 0
   
   return L->nelem;
}


//Implementações para listas ordenadas
//-------------------------------------------
/* (*) Insere ordenado na lista.
 *	A variável "posi" guarda a posição que o elemento deve ser inserido.
 *  Como a inserção é ordenada, pode-se usar a busca binária para achar essa posição.
 *	Em vez de percorrer a lista inteira, pode-se determinar o local da inserção
 *	através da comparação (por exemplo, se é necessário inserir o elemento 5 e
 *	o elemento do meio é 4, então o 5 só pode ser inserido depois do meio).
 *	Após isso, chama a função que insere na posição. O tratamento de erro é
 *	feito na função de inserção e na main. */

boolean Inserir_ord(tipo_elem x, lista *L)
{
   /*Insere novo elemento de forma a manter a lista ordenada
   (crescente). Devolve true (se sucesso), false (c.c.)*/
	int posi = 1;

	// Faz uma busca binária para saber a posição ideal do elemento.
	Busca_bin(x.chave, L, &posi);


	return Inserir_posic(x, posi, L);
}


boolean Busca_bin(tipo_chave x, lista *L, int *p)
{
   /*Retorna em p a posição de x na lista ORDENADA e true. 
   //Se x não ocorre, retorna false*/
   
   //Implementação de busca binária
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

	 // Caso para ser usado na inserção ordenada.
   *p = inf;

   return FALSE;
}

boolean Remover_ch(tipo_chave x, lista *L)
{
   /*Remoção dada a chave. Retorna true, se removeu, ou
   false, c.c.*/
   
   int posi;
   boolean removeu = FALSE;
   
   if (Busca_bin(x, L, &posi)) //Procura via busca binária
   {        
       Remover_posic(&posi, L);
       removeu = TRUE;
   }
   
   return removeu;
}
//-------------------------------------------
