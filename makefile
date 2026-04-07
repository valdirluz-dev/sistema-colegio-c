# Nome do executável final
TARGET = sc

# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj

# Localiza todos os arquivos .c dentro de /src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Define os arquivos .o correspondentes dentro de /obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regra principal (Default)
all: $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação de cada arquivo .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria a pasta de objetos se ela não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean