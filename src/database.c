#include "imports.h"

sqlite3 *db; 

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

    sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS alunos (cpf TEXT UNIQUE PRIMARY KEY, nome TEXT);",0,0,0);
    sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS professores (cpf TEXT UNIQUE PRIMARY KEY, nome TEXT, materia TEXT);",0,0,0);
    sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS turmas (codigo TEXT UNIQUE PRIMARY KEY, nome TEXT);",0,0,0);
}

int callback(void *data, int argc, char **argv, char **colName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
    
}