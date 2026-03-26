#include <stdio.h>
#include "alunos.h"

#include "alunos.h"
#include "professores.h"
#include "turmas.h"
#include "matriculas.h"

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE GERENCIAMENTO DE COLEGIO =====\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Cadastrar professor\n");
        printf("4 - Listar professores\n");
        printf("5 - Criar turma\n");
        printf("6 - Matricular aluno em turma\n");
        printf("7 - Lancar notas\n");
        printf("8 - Registrar faltas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;

            case 2:
                listarAlunos();
                break;

            case 3:
                cadastrarProfessor();
                break;

            case 4:
                listarProfessores();
                break;

            case 5:
                criarTurma();
                break;

            case 6:
                matricularAluno();
                break;

            case 7:
                lancarNotas();
                break;

            case 8:
                registrarFaltas();
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}