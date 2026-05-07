const express = require('express');
const http = require('http');
const path = require('path');
const pty = require('node-pty');
const { Server } = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

io.on('connection', (socket) => {
    // Inicia o seu executável em C como um processo de terminal real
   const term = pty.spawn('/app/sistema', [], { 
    name: 'xterm-color',
    cols: 80,
    rows: 24,
    cwd: '/app',
    env: process.env
});

term.onExit(({ exitCode }) => {
    console.log("Programa em C fechou. Avisando frontend...");
    io.emit('server-closed'); // Envia o sinal para o HTML
    
    setTimeout(() => {
        console.log("Encerrando container...");
        process.exit(0); 
    }, 200); // Aguarda o envio da mensagem antes de matar o processo
});

    // Envia a saída do C para o Navegador
    term.onData((data) => socket.emit('output', data));

    // Recebe o que você digita no Navegador e envia para o C
    socket.on('input', (data) => term.write(data));

    socket.on('disconnect', () => term.kill());
});

server.listen(8080, '0.0.0.0', () => {
    console.log('Servidor rodando em http://localhost:8080');
});