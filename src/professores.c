#include "imports.h"

void cadastrar_professor(){

    char cpf[20];
    char nome[100];
    char materia[20];
    char sql[200];

    printf ("digite o cpf: ");
    scanf("%19s", cpf);
    printf("digite o nome: ");
    scanf(" %99[^\n]", nome);
    printf("digite a materia: ");
    scanf(" %19[^\n]", materia);

    sprintf (sql,"INSERT INTO professores (cpf,nome,materia) VALUES ('%s','%s','%s');", cpf, nome, materia);

sqlite3_exec(db,sql,0,0,0);

}

void listar_professores(){

    printf("\n------------------ Lista de Professores ------------------------\n");
    printf("%-15s | %-25s | %-20s\n", "CPF", "Nome", "Materia");
    printf("------------------------------------------------------------------\n");

    char *errMsg = 0;

    if (sqlite3_exec(db, "SELECT * FROM professores;", callback_professores, 0, &errMsg) != SQLITE_OK) {
        printf("Erro: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void buscar_cpf_professores(){

    char cpf[20];
    char sql[200];

    printf("Digite o CPF: ");
    scanf("%19s", cpf);

    sprintf(sql, "SELECT * FROM professores WHERE cpf = '%s';", cpf);

    sqlite3_exec(db, sql, callback_turmas, 0, 0);
    
}

void buscar_nome_professores(){

    char nome[100];
    char sql[300];

    printf("Digite o nome: ");
    scanf(" %99[^\n]", nome);

    sprintf(sql, "SELECT * FROM professores WHERE nome LIKE '%%%s%%';", nome);

    sqlite3_exec(db, sql, callback_professores, 0, 0);
    
}