//arquivo .h que liga todas as partes do programa
#ifndef MATRICULAS_H
#define MATRICULAS_H

typedef struct {
    int id;
    int idAluno;
    int idTurma;
    float nota;
    int faltas;
} Matricula;

// Funções
void matricularAluno();
void lancarNotas();
void registrarFaltas();
void listarMatriculas();

#endif