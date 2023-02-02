#include "headers.h"

// Permite ao usuário adicionar alunos à disciplina recém criada.
void add_students(subject_t *subject)
{
	subject->students = calloc(subject->student_amount, sizeof(student_t));
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("======== Adicionar Estudantes ========\n");
	printf("Informe caracteristicas dos alunos: \n");
	for (int i = 0; i < subject->student_amount; i++) {
		printf("----Aluno %d----\n", i + 1);
		printf("Número: ");
		scanf("%d", &subject->students[i].id);
		integer_detect_input_error(1, 50, &subject->students->id);
		printf("Nome: ");
		scanf("%s", subject->students[i].name);

		//zera as notas inicialmente
		for (int j = 0; j < 3; j++)
			subject->students[i].test_grade[j] = 0;

		//zera os trabalhos inicialmente
		for (int j = 0; j < 10; j++)
			subject->students[i].task_grade[j] = 0;
	}
}

// Mostra os dados de um aluno especificado pelo usuário.
void student_show_data(char filename[], int id)
{
	FILE *student_ptr = fopen(filename, "rb");
	subject_t subject;
	fsubjectread(&subject, student_ptr);
	fclose(student_ptr);

	printf("\e[1;1H\e[2J");
	printf("Nome: %s\n"
	       "ID: %d\n"
	       "Presença: %d / %d\n", 
	       subject.students[id].name, subject.students[id].id,
	       subject.students[id].presence_amount, subject.class_amount);
	
	printf("Notas de prova: ");
	for(int i = 0; i < subject.test_amount; i++)
		printf("|%.2f| ", subject.students[id].test_grade[i]);
	puts("");

	printf("Notas de trabalho: ");
	for(int i = 0; i < subject.task_amount; i++)
		printf("|%.2f| ", subject.students[id].task_grade[i]);
	puts("");

	printf("Nota no exame: %.2f\n", subject.students[id].exam_grade);

	printf("Média atual: %.2f\n", subject.students[id].average_grade);
	if(subject.semester_status)
		printf("Situação: Semestre em andamento!\n");
	else
		printf("Situação: %s", subject.students[id].approve ? "Aprovado!\n" : "Reprovado\n");

	press_enter();
	clear_memory(subject);
}

// Permite ao usuário modificar os dados atualmente atribuídos para um aluno específico.
void student_modify_data(char filename[MAX_SIZE], int id)
{
	FILE *fp = fopen(filename, "rb");
	subject_t subject;
	float test_perc[3], task_perc[10];
	fsubjectread(&subject, fp);
	fclose(fp);

	if(!subject.semester_status) {
		printf("Semestre fechado, não é possível editar dados!\n");
		clear_memory(subject);
		press_enter();
		return;
	}

	printf("Editando dados de %s! Se quiser manter algum, copie-o.\n", 
	       subject.students[id].name);

	printf("Nome atual: %s\nNovo nome: ", subject.students[id].name);
	scanf("%s", subject.students[id].name);
	
	printf("Presença atual: %d\nNova presença: ", subject.students[id].presence_amount);
	scanf("%d", &subject.students[id].presence_amount);
	integer_detect_input_error(0, subject.class_amount, &subject.students[id].presence_amount);

	printf("==Provas==\n");
	for(int i = 0; i < subject.test_amount; i++) {
		printf("Nota %d: %.2f\nNova nota: ", i+1, subject.students[id].test_grade[i]);
		scanf("%f", &subject.students[id].test_grade[i]);
		floating_detect_input_error(0, 10, &subject.students[id].test_grade[i]);
	}

	printf("==Trabalhos==\n");
	for(int i = 0; i < subject.task_amount; i++) {
		printf("Nota %d: %.2f\n Nova nota: ", i+1, subject.students[id].task_grade[i]);
		scanf("%f", &subject.students[id].task_grade[i]);
		floating_detect_input_error(0, 10, &subject.students[id].task_grade[i]);
	}

	// Preenche os vetores com as porcentagens de nota em cada atividade.
	fill_grade_perc_array(subject, task_perc, test_perc);
	// Recalcula as médias para cada aluno.
	calculate_average_grade(&subject, id, task_perc, test_perc);

	// Escreve no arquivo e limpa memória.
	fp = fopen(filename, "wb");
	fsubjectwrite(&subject, fp);
	fclose(fp);
	clear_memory(subject);
}

// Verifica se cada um dos alunos foram ou não aprovados na disciplina.
void verify_approval(subject_t *subject) {
	if(subject->given_class < subject->class_amount)
		subject->class_amount = subject->given_class;
	
	for(int i = 0; i < subject->student_amount; i++) {
		if(subject->students[i].average_grade >= subject->minimal_grade && (100 * subject->students[i].presence_amount) / subject->class_amount >= subject->minimal_freq)
      			subject->students[i].approve = 1;
    		else subject->students[i].approve = 0;
  	}
}

// Recolhe o peso de cada uma das atividades e coloca no vetor.
void fill_grade_perc_array(subject_t subject, float task_perc[], float test_perc[])
{
        int control_test, control_task;
	control_test = control_task = 0;
        
	for(int i = 0; i < subject.given_class; i++) {
		if(subject.classes[i].control) {
			if(subject.classes[i].activity.type == 'P') {
				test_perc[control_test] = subject.classes[i].activity.grade_perc;
				control_test++;
			}
			else if(subject.classes[i].activity.type == 'T') {
				task_perc[control_task] = subject.classes[i].activity.grade_perc;
				control_task++;
			}
		}
	}
}

// Calcula média final.
void calculate_average_grade(subject_t *subject, int id, float task_grade_perc[], float test_grade_perc[])
{
	subject->students[id].average_grade = 0;

	for(int i = 0; i < subject->test_amount; i++)
		subject->students[id].average_grade += (subject->students[id].test_grade[i] 
		* (test_grade_perc[i] / 100));

	for(int i = 0; i < subject->task_amount; i++)
		subject->students[id].average_grade += (subject->students[id].task_grade[i]
		* (task_grade_perc[i] / 100));


	// Se as provas ja acabaram e a nota ainda é menor, calcula com exame.
	if(subject->students[id].average_grade < subject->minimal_grade)
		subject->students[id].average_grade += subject->students[id].exam_grade;
}