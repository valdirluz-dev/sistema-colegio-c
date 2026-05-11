#include "imports.h"

//menu do controle de professores
void menu_professores(){

    int opcao;

    do{
    printf("==============================\n");
    printf("    CONTROLE DE PROFESSORES   \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar professor \n");
    printf("(2) - listar professores \n");
    printf("(3) - buscar professores por cpf \n");
    printf("(4) - buscar professores por nome \n");
    printf("(5) - editar dados do professor \n");
    printf("(6) - remover professor \n");

    if (!read_int(&opcao, "DIGITE SUA OPCAO: ", 0, 6)) return;

    switch (opcao){
    case 0: break;
    case 1: cadastrar_professor(); break;
    case 2: listar_professores(); break;
    case 3: buscar_cpf_professores(); break;
    case 4: buscar_nome_professores(); break;
    case 5: editar_professor(); break;
    case 6: remover_professor(); break;
    
    default:
        printf("================================\n");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE\n");
        printf("================================\n");    
        break;
    }

    limpar_tela();

    }while (opcao!=0);
    

}

//menu do controle de turmas
void menu_turmas(){

    int opcao;

    do{
    printf("==============================\n");
    printf("      CONTROLE DE TURMAS      \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar turma \n");
    printf("(2) - listar turmas \n");
    printf("(3) - listar alunos da turma\n");
    printf("(4) - listar turmas por professor\n");
    printf("(5) - editar dados da turma\n");
    printf("(6) - remover turma\n");

    if (!read_int(&opcao, "DIGITE SUA OPCAO: ", 0, 6)) return;

    switch (opcao){
    case 0: break;
    case 1: cadastrar_turma(); break;
    case 2: listar_turmas(); break;
    case 3: listar_alunos_turma(); break;
    case 4: listar_turmas_por_professor(); break;
    case 5: editar_turma(); break;
    case 6: remover_turma(); break;
    
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

    int opcao;

    do{
    printf("==============================\n");
    printf("      CONTROLE DE ALUNOS      \n");
    printf("==============================\n");
    printf("(0) - Voltar ao menu anterior \n");
    printf("(1) - Cadastrar aluno \n");
    printf("(2) - listar alunos na escola \n");
    printf("(3) - buscar aluno por cpf\n");
    printf("(4) - buscar aluno por nome\n");
    printf("(5) - listar alunos por turma\n");
    printf("(6) - editar dados do aluno\n");
    printf("(7) - remover aluno\n");
    printf("(8) - realizar matrícula\n");
    printf("(9) - lancar nota\n");
    printf("(10) - lancar falta\n");
    printf("(11) - ver boletim\n");
    

    if (!read_int(&opcao, "DIGITE SUA OPCAO: ", 0, 11)) return;

    switch (opcao){
    case 0: break;
    case 1: cadastrar_aluno(); break;
    case 2: listar_alunos(); break;
    case 3: buscar_cpf_aluno(); break;
    case 4: buscar_nome_aluno(); break;
    case 5: listar_alunos_por_turma(); break;
    case 6: editar_aluno(); break;
    case 7: remover_aluno(); break;
    case 8: realizar_matricula(); break;
    case 9: lancar_nota(); break;
    case 10: lancar_falta(); break;
    case 11: ver_boletim(); break;
    
   
    
    
    default:
        printf("================================");
        printf("OPCAO INVALIDA, DIGITE NOVAMENTE");
        printf("================================");    
        break;
    }

    limpar_tela();

    }while (opcao!=0);

}