FROM debian:latest

RUN apt-get update && apt-get install -y \
    build-essential sqlite3 libsqlite3-dev wget ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Instalação do GoTTY
RUN wget https://github.com/yudai/gotty/releases/download/v1.0.1/gotty_linux_amd64.tar.gz && \
    tar -xzf gotty_linux_amd64.tar.gz && \
    mv gotty /usr/local/bin/ && chmod +x /usr/local/bin/gotty

WORKDIR /app
COPY . .

# Compila seu sistema em C
RUN make && chmod +x ./sistema

# Garante que o index.html está na raiz do WORKDIR
# O GoTTY busca automaticamente por 'index.html' no diretório atual
EXPOSE 8080

# COMANDO DEFINITIVO:
# -w: permite escrita (digitar)
# -p: porta 8080
# --index: aponta explicitamente para o seu arquivo
CMD ["gotty", "-w", "-p", "8080", "--index", "index.html", "./sistema"]