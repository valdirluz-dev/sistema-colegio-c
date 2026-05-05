#include "imports.h"

void cadastrar_turma(){

    char codigo[20];
    char disciplina[100];
    char sql[200];

    printf("Digite o codigo da turma: ");
    scanf("%19s", codigo);
    printf("Digite a disciplina da turma: ");
    scanf(" %99[^\n]", disciplina);

    sprintf(sql, "INSERT INTO turmas (codigo, disciplina) VALUES ('%s','%s');", codigo, disciplina);

    sqlite3_exec(db, sql, 0, 0, 0);

    printf("Turma cadastrada com sucesso!\n");

}

void listar_turmas(){

    sqlite3_exec(db, "SELECT * FROM turmas;", callback, 0, 0);

}

void listar_alunos_turma(){

    char codigo[20];
    char sql[300];

    printf("Digite o codigo da turma: ");
    scanf("%19s", codigo);

    sprintf(sql, "SELECT alunos.cpf, alunos.nome FROM alunos INNER JOIN matriculas ON alunos.cpf = matriculas.cpf_aluno WHERE matriculas.codigo_turma = '%s';", codigo);

    sqlite3_exec(db, sql, callback, 0, 0);

}