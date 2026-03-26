#ifndef TURMAS_H
#define TURMAS_H

typedef struct {
    int id;
    char nome[100];
    int idProfessor;
} Turma;

// Funções
void criarTurma();
void listarTurmas();

#endif