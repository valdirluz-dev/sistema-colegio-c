#include "imports.h"


void limpar_tela(){system("clear");}


void trata_sigint(int sig) {
    (void)sig; // Silencia aviso de parâmetro não usado
    printf("\n[!] Encerrando programa com segurança...\n");
    
    if (db) {
        sqlite3_close(db);
        printf("[*] Banco de dados fechado com sucesso.\n");
    }
    
    exit(0); // Sai do programa
}

//nosso programa começa de fato a partir dessa linha

int main(){
// 1. DESATIVA O BUFFER (Vital para Docker/TTYD)
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("\033[2J\033[H");
    printf("SISTEMA ONLINE\n");
    fflush(stdout);

    signal(SIGINT, trata_sigint);
    signal(SIGTERM, trata_sigint);
    
    // 2. EVITE limpar a tela no primeiro milissegundo
    // limpar_tela(); <-- Comente isso por enquanto

    if (db_open() != SQLITE_OK){
        fprintf(stderr, "Erro ao abrir banco de dados\n");
        return 1;
    }

    db_init();
    
    // 3. MENSAGEM DE BOAS-VINDAS IMEDIATA
    printf("Conectado ao servidor...\n");
    sleep(1); // Pequena pausa para o WebSocket estabilizar

    int opcao;

    do{

    limpar_tela();
    printf("============================== \n");
    printf("SISTEMA DE CONTROLE DE COLEGIO \n");
    printf("============================== \n");
    printf("(0) - Sair \n");
    printf("(1) - Gerenciar professores \n");
    printf("(2) - Gerenciar turmas \n");
    printf("(3) - Gerenciar alunos \n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    limpar_tela();

    switch(opcao){
        case 0: break;
        case 1: menu_professores(); break;
        case 2: menu_turmas(); break;
        case 3: menu_alunos(); break;
        default: 
        printf("================================");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE");
        printf("================================");
    }
}while (opcao != 0);

db_close();

printf("Sistema encerrado\n");
return 0;
}