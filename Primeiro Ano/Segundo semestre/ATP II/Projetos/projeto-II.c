#include <stdio.h>

// =============== Prototipos =============== //

void add_vec(int[][3], int);
void soma_conjunto(int, int, int *, int[][3], int, int *);
void le_imprime_conjunto(int, int);

// =============== Principal =============== //

int main()
{
        int N, M;

        scanf("%d %d", &N, &M);
        // Chama a função que lê e imprime os conjuntos resultantes da recursiva.
        le_imprime_conjunto(M, N);

        return 0;
}

/* Função copia os elementos atuais armazenados no vetor
 * de acúmulo para o de maiores elementos. */
void add_vec(int transfer[][3], int max_id)
{
        int i;

        for (i = max_id - 1; i >= 0; i--)
                transfer[max_id - i - 1][2] = transfer[i][1];
}

/* Função recursiva que realiza o trabalho principal do programa.
 * Modifica a variável contadora e constroi o subconjunto com maior quantidade de elementos. */
void soma_conjunto(int wish, int max, int *count, int arr[][3], int qtd, int *q_maior)
{
        if (wish == 0)
        {
                (*count)++; // Caso a soma seja válida, aumenta a contagem de quantidade de soluções.

                if (qtd >= *q_maior)
                { // Se a quantidade de elementos for maior, copia o vetor para o de maior elementos.
                        add_vec(arr, qtd);
                        *q_maior = qtd; // Recebe a nova maior quantidade de elementos do vetor.
                }

                return;
        }
        else if (max == 0 || wish < 0) // Se o conjunto acabar ou o valor da soma for estourado, retorna.
                return;

        soma_conjunto(wish, max - 1, count, arr, qtd, q_maior);                       // Realiza a opção de não subtrair o elemento do conjunto.
        arr[qtd][1] = arr[max - 1][0];                                                // Guarda o elemento atual no vetor.
        soma_conjunto(wish - arr[max - 1][0], max - 1, count, arr, qtd + 1, q_maior); // Realiza a opção de subtrair o elemento.
}

/* Função lê o conjunto inicial e imprime os resultados obtidos da recursão.*/
void le_imprime_conjunto(int max_conj, int max_num)
{
        int i, j, num, ctd, quant_elem, vec_conj[max_conj][3];
        // Colunas da matriz: 0 -> Inicial / 1 -> Temporário / 2 -> Maior quantidade de elementos.

        for (i = 0; i < max_conj; i++)
                scanf("%d", &vec_conj[i][0]);

        for (i = 0; i < max_num; i++)
        {
                ctd = quant_elem = 0;
                scanf("%d", &num);
                soma_conjunto(num, max_conj, &ctd, vec_conj, 0, &quant_elem);
                printf("%d ", ctd);
                for (j = 0; j < quant_elem; j++)
                        printf("%d ", vec_conj[j][2]);

                printf("\n");
        }
}