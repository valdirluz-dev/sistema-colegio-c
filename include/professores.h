#ifndef PROFESSORES_H
#define PROFESSORES_H

typedef struct {
    int cpf_professor;
    char nome[100];
    char disciplina[100];
} Professor;

// Funções
void cadastrar_professor();
void listar_professores();
void buscar_professor();

#endif