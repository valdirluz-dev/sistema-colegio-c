#include "menu.h"

int opcao;

//menu do controle de professores
void menu_professores(){

    do{
    printf("==============================\n");
    printf("    CONTROLE DE PROFESSORES   \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar professor \n");
    printf("(2) - listar professores \n");
    printf("(3) - buscar professores \n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: break;
    case 1: cadastrar_professor(); break;
    case 2: listar_professores(); break;
    case 3: buscar_professor(); break;
    
    default:
        printf("================================\n");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE\n");
        printf("================================\n");    
        break;
    }

    }while (opcao!=0);
    

}

//menu do controle de turmas
void menu_turmas(){

    do{
    printf("==============================\n");
    printf("      CONTROLE DE TURMAS      \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar turma \n");
    printf("(2) - listar turmas \n");
    printf("(3) - listar alunos da turma\n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: break;
    case 1: cadastrar_turma(); break;
    case 2: listar_turmas(); break;
    case 3: listar_alunos_turma(); break;
    
    default:
        printf("================================");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE");
        printf("================================");    
        break;
    }
    
    
    }while (opcao!=0);

}

//menu do controle de alunos
void menu_alunos(){

    do{
    printf("==============================\n");
    printf("      CONTROLE DE ALUNOS      \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar aluno \n");
    printf("(2) - listar alunos na escola \n");
    printf("(3) - buscar aluno por cpf\n");
    printf("(4) - lançar nota\n");
    printf("(5) - lançar falta\n");
    printf("(6) - ver boletim\n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: break;
    case 1: cadastrar_aluno(); break;
    case 2: listar_alunos(); break;
    case 3: buscar_aluno(); break;
    case 4: lancar_nota(); break;
    case 5: lancar_falta(); break;
    case 6: ver_boletim(); break;
    
    default:
        printf("================================");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE");
        printf("================================");    
        break;
    }
    system("cls");
    }while (opcao!=0);

}