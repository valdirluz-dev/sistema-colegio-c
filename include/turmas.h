#ifndef TURMAS_H
#define TURMAS_H

typedef struct {
    int id;
    char nome[100];
    int idProfessor;
} Turma;

// Funções
void cadastrar_turma();
void listar_turmas();
void listar_alunos_turma();

#endif