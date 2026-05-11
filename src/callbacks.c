#include "imports.h"

//função para limpar o terminal
void limpar_tela(){system("clear");}


//essa função serve para encerrar o programa com segurança (fechando o banco de dados)
void trata_sigint(int sig) {
    (void)sig; // Silencia aviso de parâmetro não usado
    printf("\n[!] Encerrando programa com segurança...\n");
    
    if (db) {
        sqlite3_close(db);
        printf("[*] Banco de dados fechado com sucesso.\n");
    }
    
    exit(0); // Sai do programa
}


int callback_alunos(void *data, int argc, char **argv, char **colName) {
    
    // Silencia avisos de parâmetros não usados
    (void)data; (void)argc; (void)colName;
    
    printf("%-15s | %-30s\n", 
           argv[0] ? argv[0] : "---", 
           argv[1] ? argv[1] : "---");
    return 0;
}

// Callback para Professores (CPF, Nome e Matéria)
int callback_professores(void *data, int argc, char **argv, char **colName) {
    
    // Silencia avisos de parâmetros não usados
    (void)data; (void)argc; (void)colName;
    
    printf("%-15s | %-25s | %-20s\n", 
           argv[0] ? argv[0] : "---", 
           argv[1] ? argv[1] : "---", 
           argv[2] ? argv[2] : "---");
    return 0;
}

// Callback para Turmas (Código, Disciplina e CPF do Professor)
int callback_turmas(void *data, int argc, char **argv, char **colName) {
    
    // Silencia avisos de parâmetros não usados
    (void)data; (void)argc; (void)colName;
    
    printf("%-10s | %-25s | %-20s\n", 
        argv[0] ? argv[0] : "---", 
        argv[1] ? argv[1] : "---",
        argv[2] ? argv[2] : "---");

    return 0;
}

int callback_boletim(void *data, int argc, char **argv, char **colName) {
    // %-20s  -> Coluna de 20 caracteres, alinhada à esquerda (disciplina)
    // %-6s   -> Coluna de 6 caracteres, alinhada à esquerda (nota)
    // %-6s   -> Coluna de 6 caracteres, alinhada à esquerda (faltas)

    // Silencia avisos de parâmetros não usados
    (void)data; (void)argc; (void)colName;

    printf("%-20s | %-6s | %-6s\n", 
           argv[0] ? argv[0] : "---", 
           argv[1] ? argv[1] : "0.0", 
           argv[2] ? argv[2] : "0");
    return 0;
}