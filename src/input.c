#include "imports.h"
#include "input.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

static void trim_in_place(char *s) {
  if (!s) return;
  size_t len = strlen(s);
  while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r' || isspace((unsigned char)s[len - 1]))) {
    s[--len] = '\0';
  }
  size_t i = 0;
  while (s[i] && isspace((unsigned char)s[i])) i++;
  if (i > 0) memmove(s, s + i, strlen(s + i) + 1);
}

int read_line(char *buf, size_t buf_size, const char *prompt) {
  if (!buf || buf_size == 0) return 0;
  if (prompt) printf("%s", prompt);
  if (!fgets(buf, (int)buf_size, stdin)) return 0;
  trim_in_place(buf);
  return 1;
}

int read_token(char *buf, size_t buf_size, const char *prompt) {
  char line[256];
  while (1) {
    if (!read_line(line, sizeof(line), prompt)) return 0;
    if (line[0] == '\0') {
      printf("Entrada vazia. Tente novamente.\n");
      continue;
    }
    // token até o primeiro espaço
    size_t i = 0;
    while (line[i] && !isspace((unsigned char)line[i])) i++;
    line[i] = '\0';
    if (strlen(line) >= buf_size) {
      printf("Entrada muito longa. Tente novamente.\n");
      continue;
    }
    strcpy(buf, line);
    return 1;
  }
}

int read_int(int *out, const char *prompt, int min, int max) {
  char line[128];
  while (1) {
    if (!read_line(line, sizeof(line), prompt)) return 0;
    if (line[0] == '\0') {
      printf("Entrada vazia. Digite um número.\n");
      continue;
    }
    char *end = NULL;
    errno = 0;
    long v = strtol(line, &end, 10);
    if (errno != 0 || end == line || *end != '\0') {
      printf("Valor inválido. Digite um número inteiro.\n");
      continue;
    }
    if (v < min || v > max) {
      printf("Valor fora do intervalo (%d a %d). Tente novamente.\n", min, max);
      continue;
    }
    *out = (int)v;
    return 1;
  }
}

int read_float(float *out, const char *prompt, float min, float max) {
  char line[128];
  while (1) {
    if (!read_line(line, sizeof(line), prompt)) return 0;
    if (line[0] == '\0') {
      printf("Entrada vazia. Digite um número.\n");
      continue;
    }
    char *end = NULL;
    errno = 0;
    float v = strtof(line, &end);
    if (errno != 0 || end == line || *end != '\0') {
      printf("Valor inválido. Digite um número (ex: 7.5).\n");
      continue;
    }
    if (v < min || v > max) {
      printf("Valor fora do intervalo (%.2f a %.2f). Tente novamente.\n", min, max);
      continue;
    }
    *out = v;
    return 1;
  }
}

int cpf_normalize(char *out, size_t out_size, const char *in) {
  if (!out || out_size < 12 || !in) return 0;
  size_t n = 0;
  for (const unsigned char *p = (const unsigned char *)in; *p; p++) {
    if (isdigit(*p)) {
      if (n >= 11) return 0;
      out[n++] = (char)*p;
    } else if (*p == '.' || *p == '-' || *p == ' ' || *p == '\t')
      continue;
    else
      return 0;
  }
  if (n != 11) return 0;
  out[11] = '\0';
  return 1;
}

int read_cpf(char *out, size_t out_size, const char *prompt) {
  char line[48];
  if (out_size < 12) return 0;
  while (1) {
    if (!read_line(line, sizeof(line), prompt)) return 0;
    if (line[0] == '\0') {
      printf("Entrada vazia. Tente novamente.\n");
      continue;
    }
    if (!cpf_normalize(out, out_size, line)) {
      printf("CPF inválido. Use 11 dígitos (ex: 12345678901 ou 123.456.789-01).\n");
      continue;
    }
    return 1;
  }
}

int confirm_yes_no(const char *prompt) {
  char ans[16];
  while (1) {
    if (!read_line(ans, sizeof(ans), prompt)) return 0;
    if (ans[0] == '\0') {
      printf("Digite 's' para confirmar ou 'n' para cancelar.\n");
      continue;
    }
    char c = (char)tolower((unsigned char)ans[0]);
    if (c == 's' || c == 'y') return 1;
    if (c == 'n') return 0;
    printf("Opção inválida. Use 's' (sim) ou 'n' (não).\n");
  }
}

int is_valid_cpf(const char *cpf) {
  char tmp[16];
  return cpf && cpf_normalize(tmp, sizeof(tmp), cpf);
}

int is_valid_name(const char *s) {
  if (!s) return 0;
  if (s[0] == '\0') return 0;
  int has_alpha = 0;
  for (size_t i = 0; s[i]; i++) {
    unsigned char c = (unsigned char)s[i];
    if (isdigit(c)) return 0;
    if (isalpha(c)) has_alpha = 1;
    if (isalpha(c) || isspace(c) || c == '-' || c == '\'' ) continue;
    // Permite letras com acento em UTF-8 passando como bytes >= 128
    if (c >= 128) { has_alpha = 1; continue; }
    return 0;
  }
  return has_alpha;
}

