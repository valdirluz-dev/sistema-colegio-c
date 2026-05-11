#include "imports.h"

void realizar_matricula() {
    char cpf[20];
    char codigo_turma[20];
    char sql[256];

    printf("\n--- Nova Matrícula ---\n");
    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;
    if (!read_token(codigo_turma, sizeof(codigo_turma), "Digite o código da turma: ")) return;


    sprintf(sql, "INSERT INTO matriculas (cpf_aluno, codigo_turma, nota, faltas) VALUES ('%s', '%s', 0.0, 0);", cpf, codigo_turma);

    db_exec_write(db, sql, "Aluno matriculado com sucesso!");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void lancar_nota() {
    char cpf[20];
    char codigo_turma[20];
    float nota;
    char sql[256];

    printf("\n--- Lançar Nota ---\n");
    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;
    if (!read_token(codigo_turma, sizeof(codigo_turma), "Código da turma: ")) return;
    if (!read_float(&nota, "Digite a nota (0 a 10): ", 0.0f, 10.0f)) return;

    sprintf(sql, "UPDATE matriculas SET nota = %.2f WHERE cpf_aluno = '%s' AND codigo_turma = '%s';", nota, cpf, codigo_turma);

    int rc = db_exec_write(db, sql, "Nota atualizada!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}


void lancar_falta() {
    char cpf[20];
    char codigo_turma[20];
    char sql[256];

    printf("\n--- Registrar Falta ---\n");
    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;
    if (!read_token(codigo_turma, sizeof(codigo_turma), "Código da turma: ")) return;

    
    sprintf(sql, "UPDATE matriculas SET faltas = faltas + 1 WHERE cpf_aluno = '%s' AND codigo_turma = '%s';", cpf, codigo_turma);

    int rc = db_exec_write(db, sql, "Falta registrada com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void ver_boletim() {
    char cpf[20];
    char sql[512];

    printf("\n--- Boletim do Aluno ---\n");
    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;

   
    sprintf(sql, 
    "SELECT turmas.disciplina, matriculas.nota, matriculas.faltas "
    "FROM matriculas "
    "JOIN turmas ON matriculas.codigo_turma = turmas.codigo "
    "WHERE matriculas.cpf_aluno = '%s';", cpf);

    printf("\n%-20s | %-6s | %-6s\n", "Disciplina", "Nota", "Faltas");
    printf("--------------------------------------------\n");
    db_exec_query(db, sql, callback_boletim, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}