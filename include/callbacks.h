#ifndef VISUAL_H
#define VISUAL_H

//limpar terminal
void limpar_tela();

//função de segurança, executa caso o programa seja interrompido
void trata_sigint(int sig);

//Callback
int callback_alunos(void *data, int argc, char **argv, char **colName);

// Callback para Professores (CPF, Nome e Matéria)
int callback_professores(void *data, int argc, char **argv, char **colName);

// Callback para Turmas (Código, Disciplina e CPF do Professor)
int callback_turmas(void *data, int argc, char **argv, char **colName);

// Callback para Disciplinas
int callback_boletim(void *data, int argc, char **argv, char **colName);

#endif
