# ==========================================
# Makefile - Sistema Colégio C
# ==========================================

# Nome do executável final
TARGET = sistema

# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lsqlite3

# Pastas
SRC_DIR = src
OBJ_DIR = obj
DB_DIR = database

# Localiza todos os arquivos .c dentro de /src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Define os arquivos .o correspondentes dentro de /obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Regras Principais ---

# O 'all' agora garante que as pastas existam antes de compilar o target
all: $(OBJ_DIR) $(DB_DIR) $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação de cada arquivo .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Criação de Diretórios ---

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DB_DIR):
	mkdir -p $(DB_DIR)

# --- Limpeza ---

clean:
	@echo "Limpando arquivos temporários..."
	rm -rf $(OBJ_DIR) $(TARGET)

# Limpeza total (incluindo o banco de dados)
cleanall: clean
	@echo "Limpando banco de dados..."
	rm -rf $(DB_DIR)
	@echo "Banco de dados removido com sucesso!"
.PHONY: all clean cleanall