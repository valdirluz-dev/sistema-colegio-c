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

    printf("\n--- Lista de Turmas ---\n");
    printf("%-10s | %-25s\n", "Codigo", "Disciplina");
    printf("-------------------------------------------\n");

    sqlite3_exec(db, "SELECT * FROM turmas;", callback_turmas, 0, 0);

}

void listar_alunos_turma() {
    char codigo[20];
    char sql[512];
    char nome_disciplina[100] = "Não encontrada"; // Valor padrão caso não ache
    sqlite3_stmt *stmt;

    printf("Digite o codigo da turma: ");
    scanf("%19s", codigo);

    // 1. Buscar o nome da disciplina baseado no código
    const char *sql_nome = "SELECT disciplina FROM turmas WHERE codigo = ?;";
    if (sqlite3_prepare_v2(db, sql_nome, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, codigo, -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Copia o nome da disciplina para a nossa variável
            const unsigned char *res = sqlite3_column_text(stmt, 0);
            if (res) strcpy(nome_disciplina, (char *)res);
        }
        sqlite3_finalize(stmt);
    }

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

    sqlite3_exec(db, sql, callback_alunos, 0, 0);
    printf("--------------------------------------------------\n");
}