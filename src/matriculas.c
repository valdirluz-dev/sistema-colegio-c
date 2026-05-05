#include "imports.h"

void realizar_matricula() {
    char cpf[20];
    char codigo_turma[20];
    char sql[256];

    printf("\n--- Nova Matrícula ---\n");
    printf("Digite o CPF do aluno: ");
    scanf("%19s", cpf);
    printf("Digite o código da turma: ");
    scanf("%19s", codigo_turma);


    sprintf(sql, "INSERT INTO matriculas (cpf_aluno, codigo_turma, nota, faltas) VALUES ('%s', '%s', 0.0, 0);", cpf, codigo_turma);

    sqlite3_exec(db, sql, 0, 0, 0);
    printf("Aluno matriculado com sucesso!\n");
}

void lancar_nota() {
    char cpf[20];
    char codigo_turma[20];
    float nota;
    char sql[256];

    printf("\n--- Lançar Nota ---\n");
    printf("CPF do aluno: ");
    scanf("%19s", cpf);
    printf("Código da turma: ");
    scanf("%19s", codigo_turma);
    printf("Digite a nota: ");
    scanf("%f", &nota);

    sprintf(sql, "UPDATE matriculas SET nota = %.2f WHERE cpf_aluno = '%s' AND codigo_turma = '%s';", nota, cpf, codigo_turma);

    sqlite3_exec(db, sql, 0, 0, 0);
    printf("Nota atualizada!\n");
}


void lancar_falta() {
    char cpf[20];
    char codigo_turma[20];
    char sql[256];

    printf("\n--- Registrar Falta ---\n");
    printf("CPF do aluno: ");
    scanf("%19s", cpf);
    printf("Código da turma: ");
    scanf("%19s", codigo_turma);

    
    sprintf(sql, "UPDATE matriculas SET faltas = faltas + 1 WHERE cpf_aluno = '%s' AND codigo_turma = '%s';", cpf, codigo_turma);

    sqlite3_exec(db, sql, 0, 0, 0);
    printf("Falta registrada com sucesso!\n");
}

void ver_boletim() {
    char cpf[20];
    char sql[512];

    printf("\n--- Boletim do Aluno ---\n");
    printf("Digite o CPF do aluno: ");
    scanf("%19s", cpf);

   
    sprintf(sql, 
    "SELECT turmas.disciplina, matriculas.nota, matriculas.faltas "
    "FROM matriculas "
    "JOIN turmas ON matriculas.codigo_turma = turmas.codigo "
    "WHERE matriculas.cpf_aluno = '%s';", cpf);

    printf("\nDisciplinas | Nota | Faltas\n");
    printf("----------------------------\n");
    sqlite3_exec(db, sql, callback, 0, 0);
}