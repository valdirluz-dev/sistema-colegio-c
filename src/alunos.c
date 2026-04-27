#include "imports.h"

void cadastrar_aluno(){

    char cpf[20];
    char nome[100];
    char sql[200];

    printf ("digite o cpf: ");
    scanf("%19s", cpf);
    printf("digite o nome: ");
    scanf(" %99[^\n]", nome);

    sprintf (sql,"INSERT INTO alunos (cpf,nome) VALUES ('%s','%s');", cpf, nome);

sqlite3_exec(db,sql,0,0,0);

}

void listar_alunos(){

sqlite3_exec(db, "SELECT * FROM alunos;", callback, 0, 0);

}

void buscar_cpf_aluno(){

 char cpf[20];
    char sql[200];

    printf("Digite o CPF: ");
    scanf("%19s", cpf);

    sprintf(sql, "SELECT * FROM alunos WHERE cpf = '%s';", cpf);

    sqlite3_exec(db, sql, callback, 0, 0);
}

void buscar_nome_aluno(){

    char nome[100];
    char sql[300];

    printf("Digite o nome: ");
    scanf(" %99[^\n]", nome);

    sprintf(sql, "SELECT * FROM alunos WHERE nome LIKE '%%%s%%';", nome);

    sqlite3_exec(db, sql, callback, 0, 0);

}