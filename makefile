# ==========================================
# Makefile - Sistema Colégio C
# ==========================================

TARGET = sistema
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lsqlite3

SRC_DIR = src
OBJ_DIR = obj
DB_DIR = database

# Localiza arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Alvos que não são arquivos
.PHONY: all clean cleanall

all: $(OBJ_DIR) $(DB_DIR) $(TARGET)

# Linkagem - O TAB antes do $(CC) é obrigatório
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação - O TAB antes do $(CC) é obrigatório
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criação de Diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DB_DIR):
	mkdir -p $(DB_DIR)

clean:
	@echo "Limpando arquivos temporários..."
	-rm -rf $(OBJ_DIR) $(TARGET)

cleanall: clean
	@echo "Limpando o conteúdo do banco de dados..."
	-rm -f $(DB_DIR)/*
	@echo "Conteúdo do banco de dados removido!"