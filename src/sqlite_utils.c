#include "imports.h"
#include "sqlite_utils.h"

typedef struct {
  int (*row_callback)(void *, int, char **, char **);
  void *user_data;
  int rows;
} CountingCtx;

static int counting_callback(void *ctx, int argc, char **argv, char **colName) {
  CountingCtx *c = (CountingCtx *)ctx;
  c->rows++;
  if (c->row_callback) return c->row_callback(c->user_data, argc, argv, colName);
  return 0;
}

int db_exec_sql(sqlite3 *db, const char *sql) {
  char *errMsg = NULL;
  int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro SQL: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
    if (errMsg) sqlite3_free(errMsg);
    db_print_constraint_hint(db);
    return rc;
  }
  return SQLITE_OK;
}

int db_exec_write(sqlite3 *db, const char *sql, const char *success_msg) {
  char *errMsg = NULL;
  int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro SQL: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
    if (errMsg) sqlite3_free(errMsg);
    db_print_constraint_hint(db);
    return rc;
  }
  if (success_msg && success_msg[0]) printf("%s\n", success_msg);
  return SQLITE_OK;
}

int db_exec_query(sqlite3 *db,
                  const char *sql,
                  int (*row_callback)(void *, int, char **, char **),
                  void *user_data,
                  const char *empty_msg) {
  CountingCtx ctx = {.row_callback = row_callback, .user_data = user_data, .rows = 0};
  char *errMsg = NULL;
  int rc = sqlite3_exec(db, sql, counting_callback, &ctx, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro SQL: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
    if (errMsg) sqlite3_free(errMsg);
    db_print_constraint_hint(db);
    return rc;
  }
  if (ctx.rows == 0 && empty_msg && empty_msg[0]) printf("%s\n", empty_msg);
  return SQLITE_OK;
}

int db_exists(sqlite3 *db, const char *sql) {
  sqlite3_stmt *stmt = NULL;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Erro SQL: %s\n", sqlite3_errmsg(db));
    return 0;
  }
  rc = sqlite3_step(stmt);
  int found = (rc == SQLITE_ROW);
  if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
    fprintf(stderr, "Erro SQL: %s\n", sqlite3_errmsg(db));
  }
  sqlite3_finalize(stmt);
  return found;
}

void db_print_constraint_hint(sqlite3 *db) {
  int ext = sqlite3_extended_errcode(db);
  switch (ext) {
    case SQLITE_CONSTRAINT_PRIMARYKEY:
    case SQLITE_CONSTRAINT_UNIQUE:
      fprintf(stderr, "Dica: já existe um registro com a mesma chave/valor UNIQUE.\n");
      break;
    case SQLITE_CONSTRAINT_FOREIGNKEY:
      fprintf(stderr, "Dica: referência inválida (FK). Verifique se o registro relacionado existe.\n");
      break;
    case SQLITE_CONSTRAINT_NOTNULL:
      fprintf(stderr, "Dica: campo obrigatório não pode ser vazio.\n");
      break;
    default:
      (void)db;
      break;
  }
}

