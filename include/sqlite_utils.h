#ifndef SQLITE_UTILS_H
#define SQLITE_UTILS_H

#include <sqlite3.h>

// Executa SQL sem callback. Em erro, imprime sqlite3_errmsg(db).
int db_exec_sql(sqlite3 *db, const char *sql);

// Executa SQL de escrita e imprime mensagem de sucesso se ok.
int db_exec_write(sqlite3 *db, const char *sql, const char *success_msg);

// Executa SELECT via sqlite3_exec, contando linhas; se 0, imprime empty_msg.
int db_exec_query(sqlite3 *db,
                  const char *sql,
                  int (*row_callback)(void *, int, char **, char **),
                  void *user_data,
                  const char *empty_msg);

// Retorna 1 se SELECT retornar ao menos 1 linha (ex: SELECT 1 ... LIMIT 1).
// Em erro, imprime mensagem e retorna 0.
int db_exists(sqlite3 *db, const char *sql);

// Helpers para erros de constraint
void db_print_constraint_hint(sqlite3 *db);

#endif
