#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

int db_open();
void db_close();
void db_init();



//ponteiro global para o banco de dados
extern sqlite3 *db;

#endif