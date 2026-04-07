#include "menu.h"

int main(){

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

return 0;
}