#include "imports.h"

void cadastrar_aluno(){

    char cpf[20];
    char nome[100];
    char sql[200];

    if (!read_cpf(cpf, sizeof(cpf), "Digite o CPF (11 dígitos ou 999.999.999-99): ")) return;
    while (1) {
        if (!read_line(nome, sizeof(nome), "Digite o nome: ")) return;
        if (!is_valid_name(nome)) {
            printf("Nome inválido. Não use números e evite símbolos.\n");
            continue;
        }
        break;
    }

    sprintf (sql,"INSERT INTO alunos (cpf,nome) VALUES ('%s','%s');", cpf, nome);

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();

    db_exec_write(db, sql, "Aluno cadastrado com sucesso!");

}

void listar_alunos(){

    printf("\n------------- Lista de Alunos ------------------\n");
    printf("%-15s | %-30s\n", "CPF", "Nome do Aluno");
    printf("--------------------------------------------------\n");

    db_exec_query(db, "SELECT * FROM alunos;", callback_alunos, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void buscar_cpf_aluno(){

 char cpf[20];
    char sql[200];

    if (!read_cpf(cpf, sizeof(cpf), "Digite o CPF (11 dígitos ou 999.999.999-99): ")) return;

    sprintf(sql, "SELECT * FROM alunos WHERE cpf = '%s';", cpf);

    db_exec_query(db, sql, callback_alunos, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void buscar_nome_aluno(){

    char nome[100];
    char sql[300];

    if (!read_line(nome, sizeof(nome), "Digite o nome: ")) return;
    if (!is_valid_name(nome)) {
        printf("Nome inválido.\n");
        return;
    }

    sprintf(sql, "SELECT * FROM alunos WHERE nome LIKE '%%%s%%';", nome);

    db_exec_query(db, sql, callback_alunos, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();

}

void editar_aluno() {
    char cpf[20];
    char nome[100];
    char sql[400];

    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;

    sprintf(sql, "SELECT 1 FROM alunos WHERE cpf = '%s' LIMIT 1;", cpf);
    if (!db_exists(db, sql)) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    while (1) {
        if (!read_line(nome, sizeof(nome), "Novo nome: ")) return;
        if (!is_valid_name(nome)) {
            printf("Nome inválido.\n");
            continue;
        }
        break;
    }

    if (!confirm_yes_no("Confirmar atualização? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    sprintf(sql, "UPDATE alunos SET nome = '%s' WHERE cpf = '%s';", nome, cpf);
    int rc = db_exec_write(db, sql, "Aluno atualizado com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void remover_aluno() {
    char cpf[20];
    char sql[400];

    if (!read_cpf(cpf, sizeof(cpf), "CPF do aluno (11 dígitos ou 999.999.999-99): ")) return;

    sprintf(sql, "SELECT 1 FROM alunos WHERE cpf = '%s' LIMIT 1;", cpf);
    if (!db_exists(db, sql)) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    printf("Ao remover o aluno, suas matrículas/notas/faltas também serão removidas.\n");
    if (!confirm_yes_no("Confirmar remoção do aluno? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    // Limpa matrículas relacionadas (nota/faltas estão na própria tabela matriculas)
    sprintf(sql, "DELETE FROM matriculas WHERE cpf_aluno = '%s';", cpf);
    int rc = db_exec_sql(db, sql);
    if (rc != SQLITE_OK) return;

    sprintf(sql, "DELETE FROM alunos WHERE cpf = '%s';", cpf);
    rc = db_exec_write(db, sql, "Aluno removido com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void listar_alunos_por_turma() {
    char codigo[20];
    char sql[512];

    if (!read_token(codigo, sizeof(codigo), "Digite o código da turma: ")) return;

    printf("\n--- Alunos da Turma (%s) ---\n", codigo);
    printf("%-15s | %-30s\n", "CPF", "Nome do Aluno");
    printf("--------------------------------------------------\n");

    sprintf(sql,
        "SELECT alunos.cpf, alunos.nome "
        "FROM alunos "
        "INNER JOIN matriculas ON alunos.cpf = matriculas.cpf_aluno "
        "WHERE matriculas.codigo_turma = '%s';", codigo);

    db_exec_query(db, sql, callback_alunos, 0, "Nenhum registro encontrado.");
    printf("--------------------------------------------------\n");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}