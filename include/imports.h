#ifndef IMPORTS_H
#define IMPORTS_H

//funcionalidades do programa
#include <stdio.h>
#include "database.h"
#include "professores.h"
#include "turmas.h"
#include "alunos.h"
#include "matriculas.h"
#include "menu.h"

//função de limpar a tela
#include <stdlib.h>
void limpar_tela();
//Callback
int callback(void *data, int argc, char **argv, char **colName);

#endif