#ifndef TURMAS_H
#define TURMAS_H

typedef struct {
    int id_turma;
    char nome[100];
    int cpf_professor;
} Turma;

// Funções
void cadastrar_turma();
void listar_turmas();
void listar_alunos_turma();

#endif