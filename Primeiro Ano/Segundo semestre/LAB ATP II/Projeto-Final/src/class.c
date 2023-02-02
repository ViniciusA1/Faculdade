#include "headers.h"
#include <stdio.h>

// Função adiciona nova aula na struct da disciplina.
void add_class(char filename[MAX_SIZE])
{
	subject_t subject;
	int change = 0;
	FILE *fp = fopen(filename, "rb");
	fsubjectread(&subject, fp);
	fclose(fp);

	// Se o semestre está encerrado, retorna.
	if(!subject.semester_status) {
		printf("Semestre fechado, não é possível alterar dados!\n");
		clear_memory(subject);
		press_enter();
		return;
	}

	int cur_id = subject.given_class;
	float sum = 0;

	// Quantidade de aulas dadas * hora de cada aula. Se ultrapassar, retorna.
	if (subject.given_class * subject.class_workload >=
	    subject.total_workload) {
		printf("Não é possível adicionar aula, limite de horas atingido!\n");
		clear_memory(subject);
		return;
	}

	// Recebe o índice crescentemente (de 1 até N).
	subject.classes[cur_id].id = cur_id + 1;

	printf("Dia: ");
	scanf("%d", &subject.classes[cur_id].day);
	integer_detect_input_error(1, 31, &subject.classes[cur_id].day);

	printf("Mês: ");
	scanf("%d", &subject.classes[cur_id].month);
	integer_detect_input_error(1, 12, &subject.classes[cur_id].month);
	subject.classes[cur_id].year =
		subject.year; // recebe ano da disciplina.

	printf("Conteúdo do dia: ");
	scanf(" %[^\n]s", subject.classes[cur_id].content);

	printf("Houve atividade? (s/N): ");
	subject.classes[cur_id].control = check_yes_or_no(0);

	// Conta a quantidade de percentual total para verificação.
	for (int i = 0; i < cur_id; i++) {
		if (subject.classes[i].control)
			sum += subject.classes[i].activity.grade_perc;
	}

	// Se as avaliações foram todas aplicadas e o usuário desejar inserir mais uma, retorna.
	if(subject.classes[cur_id].control && subject.test_amount == 3 && 
	   subject.task_amount == 10 && subject.exam_status) {
		puts("Limite de avaliações atingidos, não é possível adicionar mais!");
		clear_memory(subject);
		press_enter();
		return;
	}

	// Se control == 1, houve atividade na aula.
	if (subject.classes[cur_id].control && (sum < 100 || (sum == 100 && !subject.exam_status))) {
		printf("Nome da atividade: ");
		scanf(" %[^\n]s", subject.classes[cur_id].activity.name);

		printf("Tipo da atividade ('P' para prova, 'T' para trabalho, 'E' para exame): ");
		scanf(" %c", &subject.classes[cur_id].activity.type);
		check_activity_input_error(
			&subject.classes[cur_id].activity.type,
			subject.task_amount, subject.test_amount);

		if(subject.classes[cur_id].activity.type != 'E') {
			printf("Peso da atividade: ");
			scanf("%f", &subject.classes[cur_id].activity.grade_perc);
			grade_perc_input_error(
			sum, &subject.classes[cur_id].activity.grade_perc);
		}

		// Aplica a nota na atividade para todos os alunos.
		for (int i = 0; i < subject.student_amount; i++) {
			if (subject.classes[cur_id].activity.type !=
			    'E') {
				printf("Nota de %s: ",
				       subject.students[i].name);

				if (subject.classes[cur_id].activity.type ==
				    'P') {
					scanf("%f",
					      &subject.students[i].test_grade
						       [subject.test_amount]);
					floating_detect_input_error(0, 10, 
						&subject.students[i].test_grade[subject.test_amount]);
					subject.students[i].average_grade +=
						(subject.students[i].test_grade
							 [subject.test_amount] *
						 (subject.classes[cur_id]
							  .activity.grade_perc /
						  100));
				} else if (subject.classes[cur_id]
						   .activity.type == 'T') {
					scanf("%f",
					      &subject.students[i].task_grade
						       [subject.task_amount]);
					floating_detect_input_error(0, 10, 
						&subject.students[i].task_grade[subject.task_amount]);
					subject.students[i].average_grade +=
						(subject.students[i].task_grade
							 [subject.task_amount] *
						 (subject.classes[cur_id]
							  .activity.grade_perc /
						  100));
				}
			} else if (subject.classes[cur_id].activity.type ==
					   'E') {
				if(subject.students[i].average_grade < subject.minimal_grade) {
					printf("Nota de %s: ",
				       subject.students[i].name);
					scanf("%f", &subject.students[i].exam_grade);
					floating_detect_input_error(0, 10, 
					&subject.students[i].exam_grade);
				}
			}
		}

		// Atualiza quantidade de atividades aplicadas.
		switch (subject.classes[cur_id].activity.type) {
		case 'P':
			subject.test_amount++;
			break;
		case 'T':
			subject.task_amount++;
			break;
		case 'E':
			subject.exam_status = 1;
			change = 1;
		}
	}

	// Se o peso máximo for atingido, não será possível adicionar mais atividades.
	if(sum >= 100 && !subject.exam_status && !change) {
		puts("Não é possível adicionar atividade, peso máximo atingido!");
		subject.classes[cur_id].control = 0;
	}
	
	// Aplica presença para todos os alunos.
	for (int i = 0, aux; i < subject.student_amount; i++) {
		printf("%s estava presente? (S/n): ", subject.students[i].name);
		aux = check_yes_or_no(1);
		subject.classes[cur_id].presence[i] = aux;
		subject.students[i].presence_amount += aux;
	}

	// Atualiza quantidade de aulas realizadas e guarda os dados no arquivo.
	subject.given_class++;
	fp = fopen(filename, "wb");
	fsubjectwrite(&subject, fp);
	fclose(fp);
	clear_memory(subject);
}

// Função mostra atributos de uma certa aula especificada pelo usuário.
void show_class_attributes(char file_name[MAX_SIZE], int chosen_id)
{
	FILE *subject_file = fopen(file_name, "rb");
	subject_t temp;
	int total_presence = 0;
	fsubjectread(&temp, subject_file);

	// Conta a participação total que houve na respectiva aula.
	for(int i = 0; i < temp.student_amount; i++)
		total_presence += temp.classes[chosen_id].presence[i];

	// Mostra os atributos da aula.
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("Código: %d\n"
	       "Data: %d / %d / %d\n"
	       "Conteúdo: %s\n"
	       "Quantidade de alunos presentes: %d / %d\n",
	       temp.classes[chosen_id].id, temp.classes[chosen_id].day,
	       temp.classes[chosen_id].month, temp.classes[chosen_id].year,
	       temp.classes[chosen_id].content, total_presence, temp.student_amount);

	// Se control == 1, mostra a atividade que ocorreu na aula.
	if (temp.classes[chosen_id].control) {
		printf("Essa aula possui uma avaliação.\n");
		show_activity_attribute(temp, chosen_id);
	}

	// Fecha o arquivo e limpa memória.
	fclose(subject_file);
	clear_memory(temp);
}

// Função mostra dados de uma certa atividade especificada pelo usuário.
void show_activity_attribute(subject_t temp, int current_id)
{
	// Mostra os atributos da atividade.
	printf("Nome: %s\n", temp.classes[current_id].activity.name);
	printf("Tipo de atividade: ");

	switch (temp.classes[current_id].activity.type) {
	case 'P':
		puts("Prova");
		break;
	case 'T':
		puts("Trabalho");
		break;
	default:
		puts("Exame");
	}

	printf("Peso na média final: %.2f\n",
	       temp.classes[current_id].activity.grade_perc);
}

// Função edita dados de uma certa aula especificada pelo usuário.
int edit_class(char filename[MAX_SIZE], int id){
        subject_t subject;
        int op, aux, sum = 0, activ_id;
	float test_perc[3], task_perc[10];
        FILE *fp = fopen(filename, "rb");
        fsubjectread(&subject, fp);
        fclose(fp);

	// Se o semestre está encerrado, não é possivel editar os dados.
	if(!subject.semester_status) {
		printf("Semestre fechado, não é possível editar dados!\n");
		clear_memory(subject);
		press_enter();
		return 0;
	}

	// Passa por todos os dados, mostrando os anteriores e possibilitando edição.
	printf("Dia atual: %d\nAlterar para: ", subject.classes[id].day);
	scanf("%d", &subject.classes[id].day);
	integer_detect_input_error(1, 31, &subject.classes[id].day);

	printf("Mês atual: %d\nAlterar para: ", subject.classes[id].month);
	scanf("%d", &subject.classes[id].month);

	printf("Ano atual: %d\nAlterar para: ", subject.classes[id].year);
	scanf("%d", &subject.classes[id].year);
	
	printf("Conteúdo do dia atual: %s\nAlterar para: ", subject.classes[id].content);
	scanf(" %[^\n]s", subject.classes[id].content);

	// Guarda a soma do percentual de cada atividade.
	for(int i = 0; i < subject.given_class; i++) {
		if(subject.classes[i].control)
			sum += subject.classes[i].activity.grade_perc;
	}

	// Permite edição se control == 1 e a soma for menor que 100.
	if (subject.classes[id].control && (sum <= 100 || (sum == 100 && !subject.exam_status))) {
		printf("Nome da atividade atual: %s\nAlterar para: ", subject.classes[id].activity.name);
		scanf(" %[^\n]s", subject.classes[id].activity.name);

		printf("Tipo da atividade atual: %c\n('P' para prova, 'T' para trabalho, 'E' para exame)\nAlterar para: ",subject.classes[id].activity.type);
		scanf(" %c", &subject.classes[id].activity.type);
		check_activity_input_error(
			&subject.classes[id].activity.type,
			subject.test_amount, subject.test_amount);

		if(subject.classes[id].activity.type != 'E') {
			printf("Peso da atividade atual: %f\nAlterar para: ",subject.classes[id].activity.grade_perc);
			scanf("%f", &subject.classes[id].activity.grade_perc);
			sum -= subject.classes[id].activity.grade_perc;
			grade_perc_input_error(sum, 
                        &subject.classes[id].activity.grade_perc);
			sum += subject.classes[id].activity.grade_perc;
		}

		// Procura o ID correto para a atividade que deseja ser alterada.
		for(int i = 0; i < id; i++) {
			if(subject.classes[i].control && 
			subject.classes[i].activity.type == subject.classes[id].activity.type)
				activ_id++;
		}

		// Aplica a nota para cada estudante.
		for(int i = 0; i < subject.student_amount; i++) {
			printf("Nota de %s atual: ", subject.students[i].name);
			
			if(subject.classes[id].activity.type == 'P') {
				printf("%.2f\nAlterar para: ", subject.students[i].test_grade[activ_id]);
				scanf("%f", &subject.students[i].test_grade[activ_id]);
			}
			else if(subject.classes[id].activity.type == 'T') {
				printf("%.2f\nAlterar para: ", subject.students[i].task_grade[activ_id]);
				scanf("%f", &subject.students[i].task_grade[activ_id]);
			}
		}
	}

	// Aplica as presenças para cada estudante.
	for(int i = 0, j; i < subject.student_amount; i++) {
		subject.students[i].presence_amount = 0;
		printf("%s estava presente? (s/N)\n", subject.students[i].name);
		aux = check_yes_or_no(1);
		subject.classes[id].presence[i] = aux;
		
		for(j = 0; j < subject.given_class; j++)
			subject.students[i].presence_amount += subject.classes[j].presence[i];
	}

	// Preenche o vetor com as porcentagens de cada atividade.
	fill_grade_perc_array(subject, task_perc, test_perc);
	// Calcula a média final de todos os alunos.
	calculate_average_grade(&subject, id, task_perc, test_perc);

	// Abre o arquivo para gravar os dados alterados e limpa memória.
        fp = fopen(filename, "wb");
	fsubjectwrite(&subject, fp);
	fclose(fp);
	clear_memory(subject);
        return 1;
}