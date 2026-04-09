//arquivo .h que liga todas as partes do programa
#ifndef MATRICULAS_H
#define MATRICULAS_H

typedef struct {
    int numero_matricula;
    int cpf_aluno;
    int id_turma;
    float nota;
    int faltas;
} Matricula;

// Funções
void lancar_nota();
void lancar_falta();
void ver_boletim();

#endif