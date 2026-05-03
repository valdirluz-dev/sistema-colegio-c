#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

int db_open();
void db_close();
void db_init();

extern sqlite3 *db;

#endif