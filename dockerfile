# Usa uma imagem Linux leve e estável
FROM debian:latest

# Evita perguntas interativas durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# Instala as ferramentas necessárias: GCC, Make e as bibliotecas do SQLite3
RUN apt-get update && apt-get install -y \
    build-essential \
    sqlite3 \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Copia todo o seu projeto para dentro do container
COPY . .

# Usa o SEU Makefile para compilar o sistema
RUN make

# Define o comando que será executado ao iniciar o container
CMD ["./sistema"]