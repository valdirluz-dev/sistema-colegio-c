#ifndef PROFESSORES_H
#define PROFESSORES_H

typedef struct {
    int id;
    char nome[100];
    char disciplina[100];
} Professor;

// Funções
void cadastrarProfessor();
void listarProfessores();

#endif