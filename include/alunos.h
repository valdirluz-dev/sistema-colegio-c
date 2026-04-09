#ifndef ALUNOS_H
#define ALUNOS_H

typedef struct {
    int cpf_aluno;
    char nome[100];
} Aluno;

// Funções
void cadastrar_aluno();
void listar_alunos();
void buscar_aluno();

#endif