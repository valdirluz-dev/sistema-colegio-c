#include "imports.h"

void cadastrar_professor(){

    char cpf[20];
    char nome[100];
    char materia[20];
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
    while (1) {
        if (!read_line(materia, sizeof(materia), "Digite a matéria: ")) return;
        if (!is_valid_name(materia)) {
            printf("Matéria inválida. Não use números e evite símbolos.\n");
            continue;
        }
        break;
    }

    sprintf (sql,"INSERT INTO professores (cpf,nome,materia) VALUES ('%s','%s','%s');", cpf, nome, materia);

    db_exec_write(db, sql, "Professor cadastrado com sucesso!");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();

}

void listar_professores(){

    printf("\n------------------ Lista de Professores ------------------------\n");
    printf("%-15s | %-25s | %-20s\n", "CPF", "Nome", "Materia");
    printf("------------------------------------------------------------------\n");

    db_exec_query(db, "SELECT * FROM professores;", callback_professores, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void buscar_cpf_professores(){

    char cpf[20];
    char sql[200];

    if (!read_cpf(cpf, sizeof(cpf), "Digite o CPF (11 dígitos ou 999.999.999-99): ")) return;
    limpar_tela();

    sprintf(sql, "SELECT * FROM professores WHERE cpf = '%s';", cpf);

    db_exec_query(db, sql, callback_professores, 0, "Nenhum registro encontrado.");
    
    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void buscar_nome_professores(){

    char nome[100];
    char sql[300];

    if (!read_line(nome, sizeof(nome), "Digite o nome: ")) return;
    if (!is_valid_name(nome)) {
        printf("Nome inválido.\n");
        return;
    }

    limpar_tela();

    sprintf(sql, "SELECT * FROM professores WHERE nome LIKE '%%%s%%';", nome);

    db_exec_query(db, sql, callback_professores, 0, "Nenhum registro encontrado.");

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}

void editar_professor() {
    char cpf[20];
    char nome[100];
    char materia[20];
    char sql[400];

    if (!read_cpf(cpf, sizeof(cpf), "CPF do professor (11 dígitos ou 999.999.999-99): ")) return;

    sprintf(sql, "SELECT 1 FROM professores WHERE cpf = '%s' LIMIT 1;", cpf);
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

    while (1) {
        if (!read_line(materia, sizeof(materia), "Nova matéria: ")) return;
        if (!is_valid_name(materia)) {
            printf("Matéria inválida.\n");
            continue;
        }
        break;
    }

    if (!confirm_yes_no("Confirmar atualização? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    sprintf(sql, "UPDATE professores SET nome = '%s', materia = '%s' WHERE cpf = '%s';", nome, materia, cpf);
    int rc = db_exec_write(db, sql, "Professor atualizado com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();

}

void remover_professor() {
    char cpf[20];
    char sql[400];

    if (!read_cpf(cpf, sizeof(cpf), "CPF do professor (11 dígitos ou 999.999.999-99): ")) return;

    sprintf(sql, "SELECT 1 FROM professores WHERE cpf = '%s' LIMIT 1;", cpf);
    if (!db_exists(db, sql)) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    // Não remover se estiver vinculado a alguma turma
    sprintf(sql, "SELECT 1 FROM turmas WHERE cpf_professor = '%s' LIMIT 1;", cpf);
    if (db_exists(db, sql)) {
        printf("Não é possível remover: professor vinculado a uma ou mais turmas.\n");
        return;
    }

    if (!confirm_yes_no("Confirmar remoção do professor? (s/n): ")) {
        printf("Operação cancelada.\n");
        return;
    }

    sprintf(sql, "DELETE FROM professores WHERE cpf = '%s';", cpf);
    int rc = db_exec_write(db, sql, "Professor removido com sucesso!");
    if (rc == SQLITE_OK && sqlite3_changes(db) == 0) {
        printf("Nenhum registro encontrado.\n");
    }

    (void)read_line((char[4]){0}, 4, "\nPressione ENTER para continuar...");
    limpar_tela();
}