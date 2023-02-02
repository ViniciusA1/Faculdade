#include "headers.h"
#include <stdio.h>

// Mostra todas as disciplinas que o usuário cadastrou, possibilitando a
// mudança ou output dos dados.
void menu_subjects()
{
	int i, useropt;
	files_t storage_subjects;
	FILE *fstorage_p, *fsubject_p;
	subject_t subject;

start:
	fstorage_p = fopen(STORAGE_FILE, "rb");
	printf("\e[1;1H\e[2J"); // limpa o terminal.
	printf("======== Menu Materias ========\n");
	printf("0) Sair do programa\n1) Adicionar diciplina\n2) Encerrar semestre\n");
	for (i = 3;
	     fread(&storage_subjects, sizeof(files_t), 1, fstorage_p) == 1;
	     i++) {
		fsubject_p = fopen(storage_subjects.name, "rb");
		if (fsubject_p == NULL)
			continue;

		//trava se não existe.
		if (!fsubjectread(&subject, fsubject_p)) {
			fclose(fsubject_p);
			continue;
		}

		// Mostra dados básicos da disciplina.
		printf("%d) Semestre %d de %d, %s, %s\n", i, subject.semester,
		       subject.year, subject.name, subject.semester_status ? "aberto" : "fechado");
		fclose(fsubject_p);
		clear_memory(subject);
	}
	rewind(fstorage_p);

	printf("R: ");
	scanf("%d", &useropt);

	if (useropt == 0) {
		fclose(fstorage_p);
		return;
	}
	if (useropt == 1) {
		add_subject();
		goto end;
	}
	if(useropt == 2) {
		close_semester();
		goto end;
	}

	while (useropt >= 3 &&
	       fread(&storage_subjects, sizeof(files_t), 1, fstorage_p) == 1)
		useropt--;

	menu_subject_options(storage_subjects.name);

end:
	fclose(fstorage_p);
	goto start;
}

// Mostra as opções que existem para a disciplina especificada pelo usuário.
void menu_subject_options(char filename[MAX_SIZE])
{
	int useropt;
	for (;;) {
		printf("\e[1;1H\e[2J"); // limpa o terminal.
		printf("======== Opções Materia ========\n");
		printf("0) Voltar\n"
		       "1) Aulas\n"
		       "2) Alunos\n"
		       "3) Editar materia\n"
		       "4) Mostrar caracteristicas da materia\n"
		       "R: ");
		scanf("%d", &useropt);
		switch (useropt) {
		case 0:
			return;
		case 1:
			menu_class(filename);
			break;
		case 2:
			menu_students(filename);
			break;
		case 3:
			if (edit_subject(filename))
				return;
			break;
		case 4:
			show_subject_attributes(filename);
			break;
		default:
			printf("Opção invalida, tente novamente.\n");
			press_enter();
		}
	}
}

// Mostra todas as aulas realizadas na disciplina e permite ao usuário
// escolher uma específica para mostrar/editá-la.
void menu_class(char filename[MAX_SIZE])
{
	int useropt;
	subject_t subject;
	for (;;) {
		FILE *fp = fopen(filename, "rb");
		fsubjectread(&subject, fp);
		fclose(fp);
		printf("\e[1;1H\e[2J"); // limpa o terminal.
		printf("======== Opções Aulas ========\n");
		printf("0) Voltar\n"
		       "1) Adicionar aulas\n");
		for (int i = 0; i < subject.given_class; i++) {
			printf("%d) Aula %d/%d/%d, %s\n", i + 2,
			       subject.classes[i].day, subject.classes[i].month,
			       subject.classes[i].year,
			       (subject.classes[i].control ?
					(subject.classes[i].activity.type ==
							 'P' ?
						 "Prova" :
						 (subject.classes[i].activity
									  .type ==
								  'E' ?
							  "Exame" :
							  "Trabalho")) :
					" "));
		}
		printf("R: ");
		scanf("%d", &useropt);
		clear_memory(subject);

		if (useropt == 0)
			return;
		else if (useropt == 1)
			add_class(filename);
		else if (useropt - 2 >= subject.given_class || useropt - 2 < 0) {
			printf("Opção invalida. Tente novamente\n");
			press_enter();
		}
		else
			menu_class_options(filename, useropt - 2);
	}
}

// Mostra as opções que existem para a aula especificada pelo usuário.
void menu_class_options(char filename[MAX_SIZE], int id)
{
	int useropt;
	for (;;) {
		printf("\e[1;1H\e[2J"); // limpa o terminal.
		printf("======== Opções Aula ========\n");
		printf("0) Voltar\n"
		       "1) Editar aula\n"
		       "2) Mostrar caracteristicas da aula\n"
		       "R: ");
		scanf("%d", &useropt);
		switch (useropt) {
		case 0:
			return;
		case 1:
			if(edit_class(filename, id))
                                return;
			break;
		case 2:
			show_class_attributes(filename, id);
			press_enter();
			break;
		default:
			printf("Opção invalida, tente novamente.\n");
			press_enter();
		}
	}
}

// Mostra todos os alunos matriculados na disciplina e permite o usuário escolher
// qual deles deseja mostrar/editar dados.
void menu_students(char filename[MAX_SIZE])
{
	for(;;) {
	FILE *fp = fopen(filename, "rb");
	subject_t subject;
	int user_opt;
	fsubjectread(&subject, fp);
	fclose(fp);
	
	printf("\e[1;1H\e[2J");
	printf("======== Menu Alunos ========\n");
	printf("0) Voltar\n");
	for(int i = 0; i < subject.student_amount; i++)
		printf("%d) %s\n", i+1, subject.students[i].name);

	printf("R: ");
	scanf("%d", &user_opt);
	integer_detect_input_error(0, subject.student_amount, &user_opt);

	clear_memory(subject);
	if(user_opt == 0) return;
	else menu_students_option(filename, user_opt - 1);
	}
}

// Mostra as opções para o aluno especificado no menu anterior.
void menu_students_option(char filename[MAX_SIZE], int chosen_id)
{
	int user_opt;

	for(;;) {
	printf("\e[1;1H\e[2J");
	printf("======== Opções Aluno ========\n");
	printf("0) Voltar\n"
	       "1) Editar dados\n"
	       "2) Mostrar dados\nR: ");
	scanf("%d", &user_opt);
	
	integer_detect_input_error(0, 2, &user_opt);

	switch(user_opt) {
		case 0: return;
		case 1: student_modify_data(filename, chosen_id); break;
		case 2: student_show_data(filename, chosen_id); break;
		default: printf("Erro! Digite novamente!"); press_enter();
	}
	}
}

// Verifica se o arquivo do usuário existe.
// Se não, cria-o e pede o nome a ser utilizado.
void verify_user()
{
	user_t user;
	FILE *user_p = fopen("user.dat", "rb");

	printf("\e[1;1H\e[2J"); // limpa o terminal.
	if (user_p == NULL) {
		printf("======== Bem Vindo! ========\n");
		printf("Atenção! Usuário inexistente, realize seu cadastro!\nDigite seu nome de usuário: ");
		scanf("%s", user.name);

		user_p = fopen("user.dat", "wb");
		fwrite(&user, sizeof(user_t), 1, user_p);
	} else {
		fread(&user, sizeof(user_t), 1, user_p);
		printf("====|Bem Vindo, %s!|====\n", user.name);
		press_enter();
	}
	printf("\n\n");

	fclose(user_p);
}
