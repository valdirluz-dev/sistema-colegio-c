#include "imports.h"

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
    printf("(3) - buscar professores por cpf \n");
    printf("(4) - buscar professores por nome \n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: break;
    case 1: cadastrar_professor(); break;
    case 2: listar_professores(); break;
    case 3: buscar_cpf_professores(); break;
    case 4: buscar_nome_professores(); break;
    
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
    
    limpar_tela();
    
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
    printf("(4) - buscar aluno por nome\n");
    printf("(5) - lancar nota\n");
    printf("(6) - lancar falta\n");
    printf("(7) - ver boletim\n");

    printf("DIGITE SUA OPCAO: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: break;
    case 1: cadastrar_aluno(); break;
    case 2: listar_alunos(); break;
    case 3: buscar_cpf_aluno(); break;
    case 4: buscar_nome_aluno(); break;
    case 5: lancar_nota(); break;
    case 6: lancar_falta(); break;
    case 7: ver_boletim(); break;
    
    default:
        printf("================================");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE");
        printf("================================");    
        break;
    }

    }while (opcao!=0);

}