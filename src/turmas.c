#include "imports.h"

void cadastrar_turma(){

    char codigo[20];
    char disciplina[100];
    char cpf_professor[20];
    char sql[300];

    if (!read_token(codigo, sizeof(codigo), "Digite o código da turma: ")) return;
    while (1) {
        if (!read_line(disciplina, sizeof(disciplina), "Digite a disciplina da turma: ")) return;
        if (!is_valid_name(disciplina)) {
            printf("Disciplina inválida. Não use números e evite símbolos.\n");
            continue;
        }
        break;
    }
    if (!read_cpf(cpf_professor, sizeof(cpf_professor), "CPF do professor (11 dígitos ou 999.999.999-99): "))
        return;

    sprintf(sql, "INSERT INTO turmas (codigo, disciplina, cpf_professor) VALUES ('%s','%s','%s');",
            codigo, disciplina, cpf_professor);

    db_exec_write(db, sql, "Turma cadastrada com sucesso!");

}

void listar_turmas(){

    printf("\n--- Lista de Turmas ---\n");
    printf("%-10s | %-25s | %-15s\n", "Codigo", "Disciplina", "CPF Professor");
    printf("--------------------------------------------------------------\n");

    db_exec_query(db, "SELECT * FROM turmas;", callback_turmas, 0, "Nenhum registro encontrado.");

}

void listar_alunos_turma() {
    char codigo[20];
    char sql[512];
    char nome_disciplina[100] = "Não encontrada"; // Valor padrão caso não ache
    sqlite3_stmt *stmt;

    if (!read_token(codigo, sizeof(codigo), "Digite o código da turma: ")) return;

    // 1. Buscar o nome da disciplina baseado no código
    const char *sql_nome = "SELECT disciplina FROM turmas WHERE codigo = ?;";
    int rc = sqlite3_prepare_v2(db, sql_nome, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_text(stmt, 1, codigo, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *res = sqlite3_column_text(stmt, 0);
        if (res) strcpy(nome_disciplina, (char *)res);
    } else {
        sqlite3_finalize(stmt);
        printf("Nenhum registro encontrado.\n");
        return;
    }
    sqlite3_finalize(stmt);

    // 2. Agora o printf usa o nome que buscamos
    printf("\n--- Lista de Alunos da Turma: %s (%s) ---\n", nome_disciplina, codigo);
    printf("%-15s | %-30s\n", "CPF", "Nome do Aluno");
    printf("--------------------------------------------------\n");

    // 3. Executa o JOIN normal para listar os alunos
    sprintf(sql, 
        "SELECT alunos.cpf, alunos.nome "
        "FROM alunos "
        "INNER JOIN matriculas ON alunos.cpf = matriculas.cpf_aluno "
        "WHERE matriculas.codigo_turma = '%s';", codigo);

    db_exec_query(db, sql, callback_alunos, 0, "Nenhum registro encontrado.");
    printf("--------------------------------------------------\n");
}

void listar_turmas_por_professor() {
    char cpf[20];
    char sql[256];

    if (!read_cpf(cpf, sizeof(cpf), "CPF do professor (11 dígitos ou 999.999.999-99): ")) return;

    printf("\n--- Turmas do Professor (%s) ---\n", cpf);
    printf("%-10s | %-25s | %-15s\n", "Codigo", "Disciplina", "CPF Professor");
    printf("--------------------------------------------------------------\n");

    sprintf(sql, "SELECT * FROM turmas WHERE cpf_professor = '%s';", cpf);
    db_exec_query(db, sql, callback_turmas, 0, "Nenhum registro encontrado.");
}

void editar_turma() {
    char codigo[20];
    char disciplina[100];
    char cpf_professor[20];
    char sql[512];

    if (!read_token(codigo, sizeof(codigo), "Código da turma: ")) return;

    sprintf(sql, "SELECT 1 FROM turmas WHERE codigo = '%s' LIMIT 1;", codigo);
    if (!db_exists(db, sql)) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    while (1) {
        if (!read_line(disciplina, sizeof(disciplina), "Nova disciplina: ")) return;
        if (!is_valid_name(disciplina)) {
            printf("Disciplina inválida.\n");
            continue;
        }
        break;
    }

    if (!read_cpf(cpf_professor, sizeof(cpf_professor), "Novo CPF do professor (11 dígitos ou 999.999.999-99): "))
        return;

    if (!confirm_yes_no("Confirmar atualização da turma? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    sprintf(sql,
        "UPDATE turmas SET disciplina = '%s', cpf_professor = '%s' WHERE codigo = '%s';",
        disciplina, cpf_professor, codigo);

    int rc = db_exec_write(db, sql, "Turma atualizada com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }
}

void remover_turma() {
    char codigo[20];
    char sql[400];

    if (!read_token(codigo, sizeof(codigo), "Código da turma: ")) return;

    sprintf(sql, "SELECT 1 FROM turmas WHERE codigo = '%s' LIMIT 1;", codigo);
    if (!db_exists(db, sql)) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    // Validar se há alunos matriculados
    sprintf(sql, "SELECT 1 FROM matriculas WHERE codigo_turma = '%s' LIMIT 1;", codigo);
    if (db_exists(db, sql)) {
        printf("Não é possível remover: há alunos matriculados nesta turma.\n");
        return;
    }

    if (!confirm_yes_no("Confirmar remoção da turma? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    sprintf(sql, "DELETE FROM turmas WHERE codigo = '%s';", codigo);
    int rc = db_exec_write(db, sql, "Turma removida com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }
}