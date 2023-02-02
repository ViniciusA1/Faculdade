#include "headers.h"

// Permite adicionar novas disciplinas, além de cadastrar alunos.
void add_subject()
{
	files_t file_name;
	subject_t subject;
	subject.exam_status = subject.given_class = subject.test_amount = subject.task_amount = 0;
	FILE *subject_p, *storage_p = fopen(STORAGE_FILE, "ab");

	// Cria o nome do arquivo com base em um número gerado aleatoriamente.
	do {
		sprintf(file_name.name, "%d",
			(subject.id = rand() % 1000000000));
		strcat(file_name.name, ".dat");
	} while (fopen(file_name.name, "r") != NULL);

	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("======== Adicionar Materia ========\n");
	// Lê dado por dado, facilita verificar erros.
	printf("Nome da disciplina: ");
	scanf(" %[^\n]s", subject.name);

	printf("Semestre: ");
	scanf("%d", &subject.semester);
	integer_detect_input_error(1, 2, &subject.semester);

	printf("Ano: ");
	scanf("%d", &subject.year);
	integer_detect_input_error(2013, 2030, &subject.year);

	printf("Carga horária total: ");
	scanf("%d", &subject.total_workload);
	integer_detect_input_error(0, 200, &subject.total_workload);

	printf("Carga horária de cada aula: ");
	scanf("%d", &subject.class_workload);
	class_workload_input_error(&subject.class_workload, subject.total_workload);

	printf("Quantidade de alunos: ");
	scanf("%d", &subject.student_amount);
	integer_detect_input_error(1, 50, &subject.student_amount);

	printf("Nota mínima para aprovação: ");
	scanf("%f", &subject.minimal_grade);
	floating_detect_input_error(0, 10, &subject.minimal_grade);

	printf("Frequência mínima para aprovação: ");
	scanf("%f", &subject.minimal_freq);
	floating_detect_input_error(0, 100, &subject.minimal_freq);

	// Atribui os dados iniciais para variáveis de controle.
	subject.class_amount = subject.total_workload / subject.class_workload;
	subject.semester_status = 1;

	subject_p = fopen(file_name.name, "wb");

	add_students(&subject);

	subject.classes = calloc(subject.class_amount, sizeof(class_t));

	// *Além de escrever tudo no novo arquivo de disciplina,
	// *abre arquivo de armazenamento ("storage.txt") e escreve o nome do novo arquivo nele.
	fsubjectwrite(&subject, subject_p);
	fwrite(&file_name, sizeof(files_t), 1, storage_p);

	fclose(storage_p);
	fclose(subject_p);
	clear_memory(subject);
}

// Permite que o usuário edite dados de uma certa disciplina.
int edit_subject(char filename[MAX_SIZE])
{
	subject_t subject;
	char useropt;
	FILE *fp;

start:
	fp = fopen(filename, "rb");
	fsubjectread(&subject, fp);
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("Digite:\n"
	       "0) Voltar\n"
	       "D) para deletar %s\n"
	       "E) para editar %s\nR: ",
	       subject.name, subject.name);
	scanf(" %c%*c", &useropt);
	fclose(fp);
	switch (useropt) {
	case '0':
		clear_memory(subject);
		return 0;
	case 'd':
	case 'D':
		printf("Tem certeza que deseja deletar a materia %s ? (s/N)\nR: ",
		       filename);
		scanf(" %c%*c", &useropt);
		if (useropt == 'S' || useropt == 's') {
			delete_subject(filename);
			clear_memory(subject);
			return 1;
		}
		clear_memory(subject);
		return 0;
	case 'e':
	case 'E':
		break;
	default:
		goto start;
	}

	clear_memory(subject);
	//preenche a struct com os dados anteriores
	FILE *fsubject_p = fopen(filename, "rb");
	fsubjectread(&subject, fsubject_p);
	fclose(fsubject_p);

	if(!subject.semester_status) {
		printf("Semestre fechado! Não é possível editá-lo!\n");
		clear_memory(subject);
		press_enter();
		return 0;
	}

	//FILE *subject_p, *storage_p = fopen(STORAGE_FILE, "ab");

	// Lê dado por dado, facilita verificar erros.
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("======== Editar Materia ========\n");
	printf("Caso deseje manter um dado como anteriormente, digite-o novamente\n\n");

	printf("Nome atual da disciplina: %s\nAlterar para: ", subject.name);
	scanf("%[^\n]s", subject.name);

	printf("Semestre atual: %d\nAlterar para: ", subject.semester);
	scanf("%d", &subject.semester);
	integer_detect_input_error(1, 2, &subject.semester);

	printf("Ano atual: %d\nAlterar para: ", subject.year);
	scanf("%d", &subject.year);
	integer_detect_input_error(2013, 2030, &subject.year);

	printf("Carga horária total atual: %d\nAlterar para: ",
	       subject.total_workload);
	scanf("%d", &subject.total_workload);
	integer_detect_input_error(0, 200, &subject.total_workload);

	printf("Carga horária de cada aula atual: %d\nAlterar para: ",
	       subject.class_workload);
	scanf("%d", &subject.class_workload);
	class_workload_input_error(&subject.class_workload, subject.total_workload);

	printf("Quantidade de alunos atual: %d\nAlterar para: ",
	       subject.student_amount);
	scanf("%d", &subject.student_amount);
	integer_detect_input_error(1, 50, &subject.student_amount);

	printf("Nota mínima para aprovação atual: %f\nAlterar para: ",
	       subject.minimal_grade);
	scanf("%f", &subject.minimal_grade);
	floating_detect_input_error(0, 10, &subject.minimal_grade);

	printf("Frequência mínima para aprovação atual: %f\nAlterar para: ",
	       subject.minimal_freq);
	scanf("%f", &subject.minimal_freq);
	floating_detect_input_error(0, 100, &subject.minimal_freq);

	subject.class_amount = subject.total_workload / subject.class_workload;

	printf("Alterar alunos? (S/n)\nR: ");
	scanf(" %c%*c", &useropt);
	if (useropt != 'n') {
		free(subject.students);
		add_students(&subject);
	}

	subject.classes = calloc(subject.class_amount, sizeof(class_t));

	// Abre o arquivo e escreve os novos dados nele.
	fsubject_p = fopen(filename, "wb");
	fsubjectwrite(&subject, fsubject_p);
	fclose(fsubject_p);
	clear_memory(subject);
	return 0;
}

// Permite deletar uma disciplina que já existe.
void delete_subject(char filename[MAX_SIZE])
{
	rename(STORAGE_FILE, "tmp.dat");

	FILE *foldstorage_p = fopen("tmp.dat", "rb");
	FILE *fnewstorage_p = fopen(STORAGE_FILE, "wb");
	files_t file;
	while (fread(&file, sizeof(files_t), 1, foldstorage_p)) {
		if (strcmp(file.name, filename) == 0)
			continue;

		fwrite(&file, sizeof(files_t), 1, fnewstorage_p);
	}

	remove("tmp.dat");
	remove(filename);
	fclose(foldstorage_p);
	fclose(fnewstorage_p);
}

// Mostra os atributos da disciplina escolhida.
void show_subject_attributes(char filename[MAX_SIZE])
{
	subject_t subject;
	FILE *fp = fopen(filename, "rb");
	fsubjectread(&subject, fp);
	fclose(fp);
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("Código: %d\n"
	       "Nome: %s\n"
	       "Semestre: %d\n"
	       "Ano: %d\n"
	       "Número de estudantes: %d\n"
	       "Número de provas realizadas: %d / %d\n"
	       "Número de trabalhos realizados: %d / %d\n"
	       "Carga horária total: %d\n"
	       "Carga horária de cada aula: %d\n"
	       "Nota mínima para aprovação: %.2f\n"
	       "Frequência mínima para aprovação: %.2f%%\n",
	       subject.id, subject.name, subject.semester, subject.year,
	       subject.student_amount, subject.test_amount, subject.test_amount,
	       subject.task_amount, subject.task_amount, subject.total_workload,
	       subject.class_workload, subject.minimal_grade,
	       subject.minimal_freq);
	clear_memory(subject);
	press_enter();
}

// Escreve os dados recém modificados no arquivo novamente.
void fsubjectwrite(subject_t *subject, FILE *fp)
{
	fwrite(subject, sizeof(subject_t), 1, fp);
	fwrite(subject->students, subject->student_amount * sizeof(student_t),
	       1, fp);
	fwrite(subject->classes, subject->class_amount * sizeof(class_t), 1,
	       fp);
}

// Lê os dados do arquivo de disciplinas e coloca-os adequadamente na struct.
int fsubjectread(subject_t *subject, FILE *fp)
{
	//se conseguiu ler a struct certo
	if (fread(subject, sizeof(subject_t), 1, fp) == 1) {
		//define os tamanhos
		long long unsigned student_size =
			subject->student_amount * sizeof(student_t);
		long long unsigned class_size =
			subject->class_amount * sizeof(class_t);
		//aloca memoria para os campos dinâmicos
		subject->students = calloc(1, student_size);
		subject->classes = calloc(1, class_size);

		//lê eles dos arquivos
		fread(subject->students, student_size, 1, fp);
		fread(subject->classes, class_size, 1, fp);
		return 1;
	}
	return 0;
}

// Fecha o semestre para um determinado ano.
// Quando fechado, encerra todas as disciplinas que estão atrelados a ele.
void close_semester()
{
	FILE *storage_pointer = fopen(STORAGE_FILE, "rb");
	FILE *subject_pointer;
	char user_opt;
	files_t storage_subjects;
	subject_t subject;
	int chosen_semester, chosen_year, count = 0;
	float test_perc[3], task_perc[10];

	printf("Ano: ");
	scanf("%d", &chosen_year);
	printf("Semestre: ");
	scanf("%d", &chosen_semester);

	printf("Tem certeza que deseja encerrar o semestre?\n"
	       "Depois de encerrado, não poderá mais ser editado!! (S / n)\nR: ");
	scanf(" %c", &user_opt);

	// Verifica se os dados do arquivo coincidem com o ano e semestre escolhido.
	while(fread(&storage_subjects, sizeof(files_t), 1, storage_pointer) == 1) {
		subject_pointer = fopen(storage_subjects.name, "rb");
		fsubjectread(&subject, subject_pointer);
	        fclose(subject_pointer);

		// Fecha o semestre se o ano e semestre forem os escolhidos.
		if(subject.semester == chosen_semester && subject.year == chosen_year) {
			subject.semester_status = 0;
			verify_approval(&subject);
			fill_grade_perc_array(subject, task_perc, test_perc);
			
			for(int i = 0; i < subject.student_amount; i++) {
				calculate_average_grade(&subject, i, task_perc, test_perc);
				if(subject.students[i].average_grade - subject.students[i].exam_grade < subject.minimal_grade)
					subject.students[i].average_grade /= 2;
			}
			
			count++;
		}

		subject_pointer = fopen(storage_subjects.name, "wb");
		fsubjectwrite(&subject, subject_pointer);
		fclose(subject_pointer);
		clear_memory(subject);
	}

	// Se não encontrou correspondência, mostra o erro.
	if(count == 0) {
		puts("Não existe esse semestre e ano cadastrados! Tente novamente!");
		press_enter();
	}
}