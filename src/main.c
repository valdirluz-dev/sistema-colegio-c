#include "imports.h"

int main(){

    /* --- CONFIGURAÇÃO DE FLUXO ---
    Remove o "atraso" de escrita. Sem isso, o texto demoraria a aparecer no navegador.*/
    setvbuf(stdout, NULL, _IONBF, 0); 

    /* --- COMANDO ANSI ---
     \033[2J limpa a tela | \033[H move o cursor para o início. 
     É mais rápido e "limpo" que o system("clear") para terminais web.*/
    printf("\033[2J\033[H");
    printf("SISTEMA ONLINE\n");
    fflush(stdout); // Força o envio do texto acima para o terminal imediatamente

    /* --- ESCUTAS DE SINAL ---
    Caso o usuário encerre o programa abruptamente esses comandos fecham o banco de dados*/
    signal(SIGINT, trata_sigint); // 
    signal(SIGTERM, trata_sigint); //

    // --- BANCO DE DADOS ---
    if (db_open() != SQLITE_OK){
        fprintf(stderr, "Erro ao abrir banco de dados\n");
        return 1; //Fecha o programa com erro se o banco de dados não abrir
    }

    db_init(); // cria as tabelas no banco de dados
    
    // 3. MENSAGEM DE BOAS-VINDAS IMEDIATA
    printf("Conectado ao servidor...\n");
    sleep(1); // Pausa de 1s: dá tempo do navegador carregar o CSS antes do menu aparecer

    int opcao;

    // --- LOOP DO MENU ---
    do{

    limpar_tela();
    printf("============================== \n");
    printf("SISTEMA DE CONTROLE DE COLEGIO \n");
    printf("============================== \n");
    printf("(0) - Sair \n");
    printf("(1) - Gerenciar professores \n");
    printf("(2) - Gerenciar turmas \n");
    printf("(3) - Gerenciar alunos \n");

    if (!read_int(&opcao, "DIGITE SUA OPCAO: ", 0, 3)) {
        printf("Entrada encerrada.\n");
        break;
    }

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

db_close(); //fecha o banco de dados quando o programa encerra

printf("Sistema encerrado\n");
return 0;
}