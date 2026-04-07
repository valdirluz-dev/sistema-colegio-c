#ifndef ALUNOS_H
#define ALUNOS_H

typedef struct {
    int id;
    char nome[100];
} Aluno;

// Funções
void cadastrar_aluno();
void listar_alunos();
void buscar_aluno();

#endif