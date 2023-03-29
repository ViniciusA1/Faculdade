/*
 * Nome: Vinicius Augusto Toreli Borgue
 * Implementação da lista sequencial: exemplo com um conjunto de alunos de uma escola
 * Funções alteradas/adicionadas foram marcadas com "(*)".
*/

#include "lista.h"

// Constantes editáveis
#define filename "dados.dat"
#define MAXGRADE 10
#define MINAGE 5
#define MAXAGE 18

int main(int argc, char *argv[])
{
  //Preencher aqui um exemplo prático que utilizar parte das operações da lista sequencial
  int opt;
  boolean isRunning = TRUE;

  lista list;
  Definir(&list);

  loadData(&list);

  while(isRunning) {
    // printf que "limpa" o terminal.
    // Dependendo de qual terminal está em uso, pode não funcionar.
    // Alternativa para funções baseadas em sistema (system("cls") e system("clear")).
    printf("\e[1;1H\e[2J");
    mainMenu();
    scanf("%d", &opt);
    isRunning = verifyOpt(opt, &list);
  }

  saveData(&list);
  return 0;
}

// (*) Carrega os dados do arquivo, se existirem.
void loadData(lista *list)
{
  FILE *file_pointer = fopen(filename, "rb");

  // Verifica se o arquivo já existe.
  if(!file_pointer)
    return;

  fread(list, sizeof(lista), 1, file_pointer);

  fclose(file_pointer);
}

// (*) Imprime o menu principal do programa.
void mainMenu()
{
  fputs("===|Menu|===\n"
        "0) Sair\n"
        "1) Verificar lista vazia\n"
        "2) Verificar lista cheia\n"
        "3) Apagar lista\n"
        "4) Inserir de forma ordenada\n"
        "5) Buscar de forma ordenada\n"
        "6) Remover elemento\n"
        "7) Imprimir lista completa\n"
        "8) Verificar tamanho\n"
        "> ", stdout);
}

// (*) Verifica o input feito pelo usuário.
boolean verifyOpt(int userOpt, lista *list)
{
  tipo_chave key;
  tipo_elem elem;
  int posi = 0;

  switch(userOpt) {
    // Sair.
    case 0:
      return FALSE;
    // Verifica se está vazia.
    case 1:
      puts(Vazia(list) ? "Esta vazia" : "Nao esta vazia");
      break;
    // Verifica se está cheia.
    case 2:
      puts(Cheia(list) ? "Esta cheia" : "Nao esta cheia");
      break;
    // Apaga lista.
    case 3:
      Apagar(list);
      puts("Lista apagada!");
      break;
    // Insere elemento.
    case 4:
      getElem(&elem);
      if(Inserir_ord(elem, list))
        puts("Elemento inserido!");
      else
        puts("Lista cheia! Impossivel inserir!");
      break;
    // Busca elemento.
    case 5:
      getKey(&key);
      if(!Busca_bin(key, list, &posi))
        puts("Elemento digitado nao existe na lista!");
      else
        searchForMore(list, posi, FALSE);
      break;
    // Remove elemento.
    case 6:
      getKey(&key);
      if(!Busca_bin(key, list, &posi))
        puts("Elemento digitado nao existe na lista!");
      else {
        searchForMore(list, posi, TRUE);
        puts("Elemento removido!");
      }
      break;
    // Imprime lista.
    case 7:
      Imprimir(list);
      break;
    // Retorna tamanho da lista.
    case 8:
      printf("Tamanho: %d\n", Tamanho(list));
      break;
    // Caso padrão.
    default:
      puts("Erro! Entrada invalida!");
  }

  pressEnter();

  return TRUE;
}

// (*) Lê a chave (string) e guarda ela na struct.
void getKey(tipo_chave *key)
{
  fputs("Digite o nome do aluno: ", stdout);
  scanf(" %[^\n]s", key->string);
}

// (*) Lê os dados do elemento a ser inserido e guarda-os na struct.
void getElem(tipo_elem *elem)
{
  puts("Digite o nome do aluno: ");
  scanf(" %[^\n]s", elem->info.nome);
  strcpy(elem->chave.string, elem->info.nome);
  
  puts("Digite a idade do aluno: ");
  scanf("%d", &elem->info.idade);
  verifyIntError(MINAGE, MAXAGE, &elem->info.idade);

  puts("Digite a media final do aluno: ");
  scanf("%f", &elem->info.media_final);
  verifyFloatError(0, MAXGRADE, &elem->info.media_final);
}

// (*) Verifica possíveis erros de input de dados.
void verifyIntError(int min, int max, int *value)
{
  while(*value < min || *value > max) {
    puts("Erro, entrada invalida! Digite outro: ");
    scanf("%d", value);
  }
}

// (*) Verifica possíveis erros de input de dados.
void verifyFloatError(float min, float max, float *value)
{
  while(*value < min || *value > max) {
    puts("Erro, entrada invalida! Digite outro: ");
    scanf("%f", value);
  }
}

// (*) Verifica se existem mais de dois alunos com mesmo nome e apresenta-os.
void searchForMore(lista *list, int id, boolean isRemoving)
{
  unsigned iterator = 0;
  Impr_elem(list->A[id], id);

  // Procura a direita na lista.
  for(int i = id + 1; i <= list->nelem && 
      !strcmp(list->A[i].chave.string, list->A[id].chave.string);
      i++) {
    Impr_elem(list->A[i], i);
    iterator++;
  }

  // Procura a esquerda na lista.
  for(int i = id - 1; i >= 1 && 
      !strcmp(list->A[i].chave.string, list->A[id].chave.string); 
      i--) {
    Impr_elem(list->A[i], i);
    iterator++;
  }

  if(isRemoving == TRUE) {
    if(iterator > 0)
      chooseElement(list, id);
    else
      Remover_posic(&id, list);
  }
}

// (*) Se a operação for de remover, solicita o id a ser removido.
void chooseElement(lista *list, int first_id)
{
  int cur_id;

  fputs("Foram encontrados mais de um cadastro com o mesmo nome.\n"
        "Digite o ID do aluno que deseja remover: ", stdout);

  scanf("%d", &cur_id);

  // Verifica se o input é válido.
  while(cur_id > list->nelem || cur_id < 1 || 
        strcmp(list->A[first_id].chave.string, list->A[cur_id].chave.string)) 
  {
    fputs("ID invalido! Digite outro: ", stdout);
    scanf("%d", &cur_id);
  }

  Remover_posic(&cur_id, list);
}

// (*) Interrompe o fluxo para melhor visualização do usuário.
void pressEnter()
{
  puts("Pressione enter para continuar...");
  scanf("%*c");
  getchar();
}

// (*) Salva os dados em um arquivo para possível consulta.
void saveData(lista *list)
{
  FILE *file_ptr = fopen(filename, "wb");

  fwrite(list, sizeof(lista), 1, file_ptr);

  fclose(file_ptr);
}
