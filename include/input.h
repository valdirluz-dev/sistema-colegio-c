#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

// Lê uma linha (fgets), remove newline e espaços laterais.
// Retorna 1 em sucesso, 0 em EOF/erro.
int read_line(char *buf, size_t buf_size, const char *prompt);

// Lê um token (sem espaços). Rejeita vazio.
int read_token(char *buf, size_t buf_size, const char *prompt);

// Lê um inteiro com validação (sem loop infinito em input inválido).
int read_int(int *out, const char *prompt, int min, int max);

// Lê um float com validação.
int read_float(float *out, const char *prompt, float min, float max);

// Confirmação para operações destrutivas (Update/Delete).
// Retorna 1 para "sim" e 0 para "não".
int confirm_yes_no(const char *prompt);

// Validações simples de domínio
// CPF: aceita 11 dígitos contínuos ou formatado (ex: 999.999.999-99); valida/normaliza em 11 dígitos.
int cpf_normalize(char *out, size_t out_size, const char *in);
int read_cpf(char *out, size_t out_size, const char *prompt);
int is_valid_cpf(const char *cpf);      // igual a cpf_normalize em buffer temporário com sucesso
int is_valid_name(const char *s);       // letras/espacos/-/' (sem dígitos)

#endif
