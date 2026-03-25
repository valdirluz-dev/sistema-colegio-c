#include <stdio.h>
#include "alunos.h"

int cadastroAlunos() {
    char nome[100];
    int idade;
    char cpf[20];
    char nomePai[100];
    char nomeMae[100];
    char sexo;

    // Entrada de dados
    printf("Digite seu nome: ");
    fgets(nome, 100, stdin);

    printf("Digite sua idade: ");
    scanf("%d", &idade);

    printf("Digite seu CPF: ");
    scanf("%s", cpf);

    printf("Digite o nome do pai: ");
    fgets(nomePai, 100, stdin);

    printf("Digite o nome da mãe: ");
    fgets(nomeMae, 100, stdin);

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &sexo);

    // Saída de dados
    printf("\n--- Dados Informados ---\n");
    printf("Nome: %s", nome);
    printf("Idade: %d\n", idade);
    printf("CPF: %s\n", cpf);
    printf("Nome do Pai: %s", nomePai);
    printf("Nome da Mãe: %s", nomeMae);
    printf("Sexo: %c\n", sexo);

    return 0;
}