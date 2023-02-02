#include "headers.h"
#include <stdio.h>

// ====|Principal|==== //
int main(int argc, char *argv[])
{
	verify_user();
	FILE *storage_p = fopen(STORAGE_FILE, "rb");

	if (storage_p == NULL)
		storage_p = fopen(STORAGE_FILE, "wb");
	fclose(storage_p);

	menu_subjects();
	return 0;
}

// Detecta se o número digitado está fora do intervalo proposto (inteiros).
void integer_detect_input_error(int begin, int end, int *target)
{
	while (*target < begin || *target > end) {
		printf("Valor inválido, digite outro: ");
		scanf("%d", target);
	}
}

// Detecta se o número digitado está fora do intervalo proposto (float).
void floating_detect_input_error(int begin, int end, float *target)
{
	while (*target < begin || *target > end) {
		printf("Valor inválido, digite outro: ");
		scanf("%f", target);
	}
}

// Verifica se a letra digitada é inválida ou se o usuário quer aplicar exame sem ter concluído as provas.
void check_activity_input_error(char *target, int task_amount,
				int test_amount)
{
	while ((*target != 'P' && *target != 'T' && *target != 'E') ||
	       (*target == 'E' && test_amount == 0 && task_amount == 0) ||
		(*target == 'P' && test_amount == 3) || (*target == 'T' &&
		task_amount == 10)) {
		printf("Dado inválido! Digite novamente: ");
		scanf(" %c", target);
	}
}

// Verifica se o peso percentual da prova na nota final não passa dos limites estabelecidos.
void grade_perc_input_error(int current_perc, float *target)
{
	while (*target <= 0 || *target > 100 || (*target + current_perc > 100)) {
		printf("Valor inválido! Digite outro: ");
		scanf("%f", target);
	}
}

// Verifica erros no input de dados para os horários de cada aula.
void class_workload_input_error(int *target, int maximum_workload)
{
	while(*target <= 0 || *target > maximum_workload || 
	     (maximum_workload % (*target) != 0)) {
		if(maximum_workload % (*target) != 0)
			printf("Valor inválido! A quantidade total de horas precisa ser um múltiplo da quantidade de horas de cada aula: ");
		else
			printf("Valor inválido! Digite outro: ");
		scanf("%d", target);
	     }
}

// Verifica se o usuário digitou uma entrada positiva (S) ou negativa (n).
int check_yes_or_no(int def)
{
	char target;
	scanf(" %c", &target);
	switch (target) {
	case 'S':
	case 's':
		return 1;
	case 'n':
	case 'N':
		return 0;

	default:
		if (def != 0)
			return 1;
		else
			return 0;
	}
}

// Limpa a memória dinamicamente alocada na struct alunos e aulas.
void clear_memory(subject_t clear_target)
{
	free(clear_target.students);
	free(clear_target.classes);
}

// Pausa o output e aguarda o usuário digitar algo para continuar.
void press_enter()
{
	printf("Pressione Enter para continuar...\n");
	scanf("%*c");
	getchar();
}