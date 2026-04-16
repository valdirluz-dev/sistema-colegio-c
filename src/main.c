#include "imports.h"

/* o comando a seguir serve para limpar a tela do console
    após cada execução do menu.
    
    Pelo comando ser diferente nos sistemas operacionais o programa
    verifica o sistema operacional antes de executar o comando 
    que limpa a tela lá no terminal.

    se for Windows: executa "cls" 
    se for linux ou aple: executa "clean" 
    se não for nenhum dos 3: não limpa a tela e manda uma mensagem

    a partir de agora sempre que quisermos limpar 
    o console chamaremos a função "limpartela()"
    
    */

void limpar_tela(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        system("clear");
    #else
        printf("Sistema não suportado\n");
    #endif
}

//nosso programa começa de fato a partir dessa linha

int main(){

    limpar_tela();

    if (db_open() != SQLITE_OK){
        return 1;
    }

    db_init();

    int opcao;

    do{
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