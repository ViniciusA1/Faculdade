#include <stdio.h>

// ===========|Protótipos|=========== //

void preenche_cod(FILE *);
void preenche_plvr(FILE *);
void le_arquivo(FILE *);
void print_and_scan(FILE *, FILE *, FILE *);
void escreve_seg(int, FILE *, FILE *, long int[], int *);
void escreve_ant(int, FILE *, FILE *);
void teste_final(FILE *, FILE *, FILE *);

// ============|Principal|============ //

int main()
{
    int resp;
    FILE *cod_ptr = fopen("codigos.dat", "r");
    FILE *plvr_ptr = fopen("palavras.dat", "r"); // FILE utilizados para abrir arquivos.
    FILE *lin_ptr = fopen("linhas.dat", "w+");

    // Testa se os arquivos "palavras.dat" e "codigos.dat" existem.
    if (cod_ptr == NULL || plvr_ptr == NULL)
    {
        printf("Algum dos arquivos de leitura não existe!\n");
        cod_ptr = fopen("codigos.dat", "w+"); // Reabre os arquivos para escrita.
        plvr_ptr = fopen("palavras.dat", "w+");
        preenche_cod(cod_ptr); // Chama funções de escrita.
        preenche_plvr(plvr_ptr);
        fseek(cod_ptr, 0, SEEK_SET); // Volta os ponteiros, após escrita.
        fseek(plvr_ptr, 0, SEEK_SET);
    }

    // Permite ao usuário editar os arquivos sem acessá-los diretamente.
    printf("Deseja editar os arquivos de leitura?\n1- Sim\n2- Não\n");
    do
    {
        scanf("%d", &resp);
    } while (resp < 1 || resp > 2);

    if (resp == 1)
    {
        freopen("codigos.dat", "w+", cod_ptr);
        freopen("palavras.dat", "w+", plvr_ptr);
        preenche_cod(cod_ptr);
        preenche_plvr(plvr_ptr);
        fseek(cod_ptr, 0, SEEK_SET); // Volta os ponteiros, após escrita.
        fseek(plvr_ptr, 0, SEEK_SET);
    }

    resp = 0; // Zera a variável para utilizá-la novamente.

    // Chama a função que lê e imprime nos arquivos.
    print_and_scan(cod_ptr, plvr_ptr, lin_ptr);

    // Permite que o usuário leia o arquivo sem acessá-lo diretamente.
    printf("Deseja ler o arquivo criado?\n1- Sim\n2- Não\n");
    do
    {
        scanf("%d", &resp);
    } while (resp < 1 || resp > 2);

    if (resp == 1)
        le_arquivo(lin_ptr);

    // Fecha e salva os arquivos.
    fclose(lin_ptr);
    fclose(cod_ptr);
    fclose(plvr_ptr);

    return 0;
}

/* Função recebe o ponteiro do arquivo de códigos.
 * Preenche o arquivo com códigos digitados pelo usuário.*/
void preenche_cod(FILE *cod_add)
{
    int op, max_cod, i, aux = 0; // Armazenamento e controle de laço.

    printf("Aberto arquivo de códigos para escrita!\n");
    printf("Valores negativos só são permitidos a partir da quinta palavra!\n");
    printf("Digite quantos códigos deseja colocar no arquivo: ");
    do
    {
        scanf("%d", &max_cod);
    } while (max_cod < 0);

    for (i = 0; i < max_cod; i++)
    {
        printf("Digite um valor entre -5 e 5: ");
        scanf("%d", &op);

        // Verifica se o número está no intervalo desejado.
        while (op < -5 || op > 5 || (aux < 5 && op < 0))
        {
            printf("Inválido! Digite outro: ");
            scanf("%d", &op);
        }

        if (op > 0)
            aux += op; // Variável que guarda a soma dos números digitados.
        fprintf(cod_add, "%d ", op);
    }
}

/* Função recebe ponteiro do arquivo de palavras.
 * Preenche o arquivo com palavras digitadas pelo usuário.*/
void preenche_plvr(FILE *plvr_add)
{
    char palavra[50]; // Armazena palavras para imprimir no arquivo.
    int max_plvr, i;  // Armazenamento e controle de laço.

    printf("Aberto arquivo de palavras para escrita!\n");
    printf("Digite quantas palavras deseja colocar no arquivo: ");
    do
    {
        scanf("%d", &max_plvr);
    } while (max_plvr < 0);

    for (i = 0; i < max_plvr; i++)
    {
        printf("Digite uma palavra: ");
        scanf("%s", palavra);
        fprintf(plvr_add, "%s ", palavra);
    }
}

/* Função recebe o ponteiro do arquivo de linhas.
 * Lê e printa o conteúdo do arquivo.*/
void le_arquivo(FILE *lin_read)
{
    char store;
    fseek(lin_read, 0, SEEK_SET); // Volta pro começo do arquivo, preparando-o para leitura.

    // Lê o arquivo até que ele acabe.
    while (fscanf(lin_read, "%c", &store) != EOF)
        printf("%c", store);

    printf("\n");
}

/* Função recebe número do código, ponteiros de arquivos, armazenamento de endereço e contador.
 * Imprime 'n' palavras no arquivo final, de acordo com o número presente no código. */
void escreve_seg(int n, FILE *plvr_seg, FILE *lin_seg, long int guarda_seg[5], int *cdt)
{
    int i;
    char receive[50]; // Utilizada para ler palavras do arquivo.

    // Laço executa o número de vezes contidas no arquivo de código.
    for (i = 0; i < n; i++)
    {
        guarda_seg[(*cdt)] = ftell(plvr_seg); // Guarda a posição das cinco últimas palavras lidas.
        if (fscanf(plvr_seg, "%s", receive) == EOF)
        { // Se acabarem palavras, retorna.
            fprintf(lin_seg, "\n");
            return;
        }
        fprintf(lin_seg, "%s ", receive);
        (*cdt) = ((*cdt) + 1) % 5; // Utilizada para controlar o armazenamento de endereços no vetor.
    }

    // Realiza um último teste, já que feof() funciona quando tenta-se ler depois do fim de arquivo.
    fseek(plvr_seg, 1, SEEK_CUR);
    if (fgetc(plvr_seg) != EOF)
        fseek(plvr_seg, -1, SEEK_CUR);

    fprintf(lin_seg, "\n");
}

/* Função recebe os ponteiros de arquivos.
 * Escreve as palavras anteriores sem salvar no vetor de endereços.*/
void escreve_ant(int nm, FILE *plvr_ant, FILE *lin_ant)
{
    int i;
    char recebe[50]; // Guarda palavra do arquivo.

    for (i = 0; i < nm; i++)
    {
        fscanf(plvr_ant, "%s", recebe);
        fprintf(lin_ant, "%s ", recebe);
    }

    fprintf(lin_ant, "\n");
}

/* Função recebe os ponteiros de arquivos. Lê o arquivo de códigos e, de acordo com as condições,
 * imprime palavras no arquivo final através de funções auxiliares.*/
void print_and_scan(FILE *cod_aux, FILE *plvr_aux, FILE *lin_aux)
{
    int num, count = 1;     // Armazena números e controla laços.
    long int guarda_end[5]; // Guarda a posição das últimas cinco palavras impressas.

    // Executa o laço até que o arquivo de palavras ou de códigos se esgote.
    while (fscanf(cod_aux, "%d", &num) != EOF && !feof(plvr_aux))
    {
        if (num == 0)
        {
            fprintf(lin_aux, "0\n");
        }
        else if (num > 0)
        {
            escreve_seg(num, plvr_aux, lin_aux, guarda_end, &count);
        }
        else
        {
            // Volta a quantidade de palavras desejadas.
            fseek(plvr_aux, guarda_end[(count + 5 + num) % 5], SEEK_SET);
            escreve_ant(-num, plvr_aux, lin_aux);
        }
    }

    // Volta pro número anterior, já que o laço foi interrompido.
    if (!feof(cod_aux))
        fseek(cod_aux, -2, SEEK_CUR);

    // Chama a função que fará o teste final para encerrar o programa.
    teste_final(cod_aux, lin_aux, plvr_aux);
}

/* Função recebe ponteiros de arquivos e testa as condições finais para impressão.*/
void teste_final(FILE *cod_temp, FILE *lin_temp, FILE *plvr_temp)
{
    char guarda_string[50]; // Guarda palavra do arquivo.
    int guarda_num, i = 0;  // Guarda número e contador.

    while (fscanf(cod_temp, "%d", &guarda_num) != -1) // Palavra acabou, mas código não.
        fprintf(lin_temp, "%d ", guarda_num);

    while (fscanf(plvr_temp, "%s", guarda_string) != -1)
    { // Código acabou, mas palavra não.
        fprintf(lin_temp, "%s ", guarda_string);
        i++;
        if (i % 5 == 0)
            fprintf(lin_temp, "\n");
    }
}