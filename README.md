# 🎓 Sistema de Gerenciamento de Colégio (Full-stack, C + SQLite3 + Web Terminal)

**Stack Tecnológica**

- 🧠 **C (GCC)** — lógica do sistema e interface de terminal (CLI)
- 🗃️ **SQLite3** — persistência local (arquivo `escola.db`)
- 🐳 **Docker + Docker Compose** — ambiente reprodutível e conteinerizado
- 🌐 **Node.js (Express + Socket.io)** — Servidor web para o terminal
- 🖥️ **Xterm.js** — Interface de terminal moderna via navegador.

Projeto desenvolvido para a disciplina de **Residência Tecnológica**, com o objetivo de implementar um sistema de gerenciamento escolar em **C**, com persistência em **SQLite3** e interface em terminal.

---

## 🖥️ Interface Web Terminal

Este projeto **não depende de um terminal local**. Ao subir o container, um servidor **Node.js (Express + Socket.io)** é iniciado e renderiza um **terminal no navegador** usando **Xterm.js**.

- ✅ O executável em C roda dentro do container como um **PTY real** (via `node-pty`).
- ✅ Tudo que você digita no navegador é enviado para o processo C, e toda a saída do C aparece no terminal web.
- 🌍 Acesse em: `http://localhost:8080`

## 📌 Funcionalidades (CRUD + rotinas acadêmicas)

O sistema é um **CRUD completo (Create / Read / Update / Delete)** para os módulos principais:


| Módulo            | Create | Read | Update | Delete | Extras                                                                               |
| ----------------- | ------ | ---- | ------ | ------ | ------------------------------------------------------------------------------------ |
| 👨‍🏫 Professores | ✅      | ✅    | ✅      | ✅      | Busca por CPF/nome; valida vínculo com turmas antes de excluir                       |
| 📚 Alunos         | ✅      | ✅    | ✅      | ✅      | Busca por CPF/nome; listar por turma; remoção limpa matrículas                       |
| 🏫 Turmas         | ✅      | ✅    | ✅      | ✅      | Listar alunos da turma; listar turmas por professor; bloqueia remoção com matrículas |


Também estão disponíveis rotinas acadêmicas:

- 📝 **Matrícula** de aluno em turma
- 📊 **Lançamento de notas**
- 📅 **Controle de faltas**
- 📊 **Boletim** com notas e faltas por disciplina

---

## 🛡️ Robustez, Validações e Tratamento de Erros

O projeto foi refatorado para um padrão mais robusto de execução em terminal:

- 🧹 **Sanitização de input (evita bugs de `scanf`)**:
  - Leituras foram centralizadas em funções como `read_int`, `read_line` e `read_token` (baseadas em `fgets` + validação).
  - Evita loop infinito quando o usuário digita letras onde se espera números.
- 🧾 **Tratamento de erros do SQLite3**:
  - Todas as operações relevantes verificam retorno (`rc != SQLITE_OK`) e exibem a mensagem específica (via `sqlite3_errmsg`/mensagem retornada).
- 🔐 **Regras de negócio:**:
  - CPF como chave primária.
  - Vínculos de integridade referencial (Foreign Keys) ativos via PRAGMA.
  -Flexibilidade: Removida a restrição UNIQUE de matérias para permitir múltiplos docentes na mesma disciplina.
- 🧠 **Feedback ao usuário**:
  - Operações de escrita (Create/Update/Delete) exibem mensagens claras de sucesso.
  - Listagens/buscas vazias retornam mensagem amigável: **“Nenhum registro encontrado.”**
- ⚠️ **Confirmação obrigatória para Update/Delete**:
  - Operações destrutivas solicitam confirmação do usuário antes de persistir no banco.

---

## 🗂️ Estrutura do Projeto

```text
📂 teste-escola
│
├─ 📂 src/               → implementação (.c)
│  ├─ main.c             → loop/menu principal
│  ├─ menu.c             → menus por módulo (professores/turmas/alunos)
│  ├─ database.c         → abertura/init/migrações do banco (SQLite3)
│  ├─ alunos.c           → CRUD de alunos + filtros
│  ├─ professores.c      → CRUD de professores + buscas
│  ├─ turmas.c           → CRUD de turmas + filtros/listagens
│  ├─ matriculas.c       → matrícula, notas, faltas e boletim
│  ├─ callbacks.c           → callbacks de impressão (listas)
│  ├─ input.c            → sanitização de input (read_int/read_line/...)
│  └─ sqlite_utils.c     → helpers SQLite (erros, listas vazias, etc.)
│
├─ 📂 frontend/           → servidor web do terminal (ponte PTY ↔ navegador)
│  ├─ server.js           → Express + Socket.io + node-pty (spawn do executável C)
│  └─ index.html          → UI web + Xterm.js (terminal no browser)
│
├─ 📂 include/            → cabeçalhos (.h)
│  ├─ imports.h           → ✅ centralizador de includes do projeto
│  ├─ alunos.h
│  ├─ professores.h
│  ├─ turmas.h
│  ├─ matriculas.h
│  ├─ visual.h
│  ├─ database.h
│  ├─ menu.h
│  ├─ input.h
│  └─ sqlite_utils.h
│
├─ 📂 obj/                → arquivos objeto (.o) gerados pelo Makefile
├─ 📂 database/            → persistência local do banco
│  └─ escola.db            → tabelas do sistema
│
├─ makefile               → build via Makefile (gera `.o` em `obj/`)
├─ dockerfile             → build do container
└─ docker-compose.yml     → execução via Docker Compose
```

---

## ⚙️ Compilação e execução do Sistema

### 🐳 Para uso (Docker)

```bash
chmod +x entrypoint.sh
docker compose up
```

#### 🔁 Build/execução automatizados no container

O `CMD` do `dockerfile` foi configurado para **automatizar o ciclo completo** em um único comando ao iniciar o container:

1. `make clean` → limpa binários/objetos
2. `make` → compila o código C (gerando `obj/*.o` e o executável `./sistema`)
3. inicia o servidor web em `frontend/server.js` → expõe o terminal via navegador

Isso permite que alterações no código C sejam refletidas no próximo start do container (ideal para desenvolvimento).

### 🧱 Para uso (compilação manual)

> 📌 **Dependência**: no Linux, instale a biblioteca de desenvolvimento do SQLite3 (`libsqlite3-dev`) para compilar manualmente.

Linux/macOS:

```bash
mkdir -p database && gcc -Wall -Wextra -g -Iinclude src/*.c -o sistema -lsqlite3 && ./sistema
```

Windows:

```bash
mkdir -p database && gcc -Wall -Wextra -g -Iinclude src\*.c -o sistema -lsqlite3 && .\sistema
```

### 🛠️ Para desenvolvimento (Docker + Makefile)

```bash
chmod +x entrypoint.sh
docker compose up -d
docker exec -it sistema_escola bash
```

Dentro do container:

```bash
make          # compila (obj/*.o + binário)
./sistema     # executa o sistema
make clean    # remove obj/ e executável
make cleanall # retorna o comando para limpar o banco de dados
```

📌 Observações:

- `make clean` antes de subir o projeto (cada máquina recompila localmente).
- Para usar os comandos bash fora do container (Linux): `sudo chown -R $USER:$USER . && chmod -R 775 database/`

---

## 💾 Persistência, Volumes e Isolamento de Dependências

O Docker Compose usa volumes para manter o ambiente consistente:

- 📦 **Código e banco persistem**: o bind mount `.:/app` garante que o diretório `database/` (incluindo `database/escola.db`) permaneça no host e **sobreviva a reinícios do container**.
-`./database:/app/database`: O arquivo escola.db fica salvo na pasta local, permitindo backups e persistência total.
- 🧩 **Dependências do Node isoladas**: o volume `/app/frontend/node_modules` mantém os módulos instalados **dentro do container**, evitando conflitos com `node_modules` do host e garantindo previsibilidade.
- `/app/frontend/node_modules`: Volume anônimo para isolar as dependências do Node.js, otimizando a performance entre diferentes SOs.

## 🧠 Lógica de Dados (SQLite3)

O sistema usa o arquivo `database/escola.db` como persistência.

### 🔗 Relações principais

- 📚 **Alunos** (`alunos`) são identificados por `cpf` (PK/UNIQUE).
- 👨‍🏫 **Professores** (`professores`) são identificados por `cpf` (PK/UNIQUE).
- 🏫 **Turmas** (`turmas`) são identificadas por `codigo` (PK/UNIQUE) e possuem:
  - `disciplina` (UNIQUE)
  - `cpf_professor` (FK → `professores.cpf`)
- 📝 **Matrículas** (`matriculas`) fazem a ponte **N:N** entre alunos e turmas:
  - `cpf_aluno` (FK → `alunos.cpf`)
  - `codigo_turma` (FK → `turmas.codigo`)
  - **nota** e **faltas** ficam armazenadas **na própria matrícula** (isto é, no vínculo aluno↔turma)

### 🧾 Exemplo (matrícula armazena nota/faltas)

```text
id  cpf_aluno     codigo_turma   nota   faltas
1   12345678901   T001           8.5    2
2   12345678901   T002           7.0    1
```

---

## 👥 Equipe

- Valdir
- Henrique
- Celina
- Arthur

