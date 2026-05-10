FROM debian:latest

RUN apt-get update && apt-get install -y \
    build-essential sqlite3 libsqlite3-dev \
    curl python3 make g++ \
    && curl -sL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copia o código primeiro
COPY . .

# Instala dependências do Node (isso demora, então deixamos no build)
RUN cd frontend && ( [ -f package.json ] || npm init -y ) && npm install xterm socket.io node-pty express

# Prepara a pasta do banco se não existir
RUN mkdir -p database

EXPOSE 8080

# O PULO DO GATO:
# Colocamos o 'make' aqui dentro do CMD. 
# Assim, toda vez que o container ligar, ele compila o código C atualizado.
CMD ["sh", "-c", "make && chmod +x ./sistema && cd frontend && node server.js"]