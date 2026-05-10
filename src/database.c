#include "imports.h"

sqlite3 *db; 

static int column_exists(sqlite3 *db_conn, const char *table, const char *col) {
    sqlite3_stmt *stmt = NULL;
    char sql[256];
    snprintf(sql, sizeof(sql), "PRAGMA table_info(%s);", table);

    int rc = sqlite3_prepare_v2(db_conn, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL (table_info): %s\n", sqlite3_errmsg(db_conn));
        return 0;
    }

    int found = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *name = sqlite3_column_text(stmt, 1); // coluna "name"
        if (name && strcmp((const char *)name, col) == 0) {
            found = 1;
            break;
        }
    }
    sqlite3_finalize(stmt);
    return found;
}

//código para abrir o banco de dados
int db_open(){
    int codigo_de_retorno = sqlite3_open("database/escola.db", &db);

    //se o código de retorno for diferente de 0 significa que deu erro

    if (codigo_de_retorno){
        printf("erro ao abrir o banco: %s \n", sqlite3_errmsg(db));
        return codigo_de_retorno;
    }

    char *err = 0; //string para armazenar uma mensagem de erro

    //ativa chaves estrangeiras dentro do banco de dados (se não conseguir retorna mensagem de erro)
    if (sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, &err) != SQLITE_OK){
    printf("erro pragma: %s\n", err);
    sqlite3_free(err);
}

    printf("Banco de dados aberto com sucesso! \n");
    return SQLITE_OK;
}

//código para fechar o banco de dados
void db_close(){

   if (db){
        sqlite3_close(db);
        printf("Banco de dados fechado!\n");
    }

}


//criar tabelas dentro do banco de dados escola.db
void db_init(){

    // Tabelas base
    db_exec_sql(db, "CREATE TABLE IF NOT EXISTS alunos (cpf TEXT UNIQUE PRIMARY KEY, nome TEXT);");

    // UNIQUE em materia (regra solicitada)
    db_exec_sql(db,
        "CREATE TABLE IF NOT EXISTS professores ("
        "cpf TEXT UNIQUE PRIMARY KEY, "
        "nome TEXT, "
        "materia TEXT UNIQUE"
        ");");

    // Turmas com professor responsável + UNIQUE na disciplina (matéria/disciplinas)
    db_exec_sql(db,
        "CREATE TABLE IF NOT EXISTS turmas ("
        "codigo TEXT UNIQUE PRIMARY KEY, "
        "disciplina TEXT UNIQUE, "
        "cpf_professor TEXT, "
        "FOREIGN KEY(cpf_professor) REFERENCES professores(cpf)"
        ");");

    // Migração simples: se turmas existir sem cpf_professor, recria preservando dados
    if (!column_exists(db, "turmas", "cpf_professor")) {
        db_exec_sql(db, "BEGIN;");
        // se a tabela não existir, o RENAME falha — mas o CREATE acima já garante que existe,
        // então aqui só entra em DB antigo (schema antigo).
        db_exec_sql(db, "ALTER TABLE turmas RENAME TO turmas_old;");
        db_exec_sql(db,
            "CREATE TABLE turmas ("
            "codigo TEXT UNIQUE PRIMARY KEY, "
            "disciplina TEXT UNIQUE, "
            "cpf_professor TEXT, "
            "FOREIGN KEY(cpf_professor) REFERENCES professores(cpf)"
            ");");
        db_exec_sql(db, "INSERT INTO turmas (codigo, disciplina) SELECT codigo, disciplina FROM turmas_old;");
        db_exec_sql(db, "DROP TABLE turmas_old;");
        db_exec_sql(db, "COMMIT;");
    }

    db_exec_sql(db,
        "CREATE TABLE IF NOT EXISTS matriculas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "cpf_aluno TEXT, "
        "codigo_turma TEXT, "
        "nota REAL DEFAULT 0.0, "
        "faltas INTEGER DEFAULT 0, "
        "FOREIGN KEY(cpf_aluno) REFERENCES alunos(cpf), "
        "FOREIGN KEY(codigo_turma) REFERENCES turmas(codigo)"
        ");");

}

