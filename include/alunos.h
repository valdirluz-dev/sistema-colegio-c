#ifndef ALUNOS_H
#define ALUNOS_H

typedef struct {
    int id;
    char nome[100];
    int idade;
} Aluno;

// Funções
void cadastrarAluno();
void listarAlunos();

#endif