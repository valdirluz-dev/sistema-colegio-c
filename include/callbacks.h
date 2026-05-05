#ifndef CALLBACKS_H
#define CALLBACKS_H

//Callback
int callback_alunos(void *data, int argc, char **argv, char **colName);

// Callback para Professores (CPF, Nome e Matéria)
int callback_professores(void *data, int argc, char **argv, char **colName);

// Callback para Turmas (Código e Disciplina)
int callback_turmas(void *data, int argc, char **argv, char **colName);

// Callback para Disciplinas
int callback_boletim(void *data, int argc, char **argv, char **colName);

#endif
