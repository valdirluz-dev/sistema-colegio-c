FROM debian:latest

RUN apt-get update && apt-get install -y \
    build-essential sqlite3 libsqlite3-dev \
    curl python3 make g++ \
    && curl -sL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copia os arquivos de dependência primeiro para garantir que o node_modules seja criado
COPY . .

# Instala as dependências dentro da pasta frontend
RUN cd frontend && ( [ -f package.json ] || npm init -y ) && npm install xterm socket.io node-pty express

# Compila o C na raiz
RUN chmod +x /app/sistema || true
RUN make cleanall || true && make

EXPOSE 8080

# Forçamos o Node a iniciar EXATAMENTE onde o arquivo está
# O comando 'ls' ajudará a gente a ver se o arquivo sumiu no log
CMD ["sh", "-c", "ls -l frontend/server.js && cd frontend && node server.js"]