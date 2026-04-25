# 🎓 Sistema de Gerenciamento de Colégio

Projeto desenvolvido para a disciplina de **Residência Tecnológica**, com o objetivo de implementar um sistema de gerenciamento escolar utilizando a linguagem C.

---

## 📌 Funcionalidades

- 📚 Cadastro de alunos
- 📚 listar alunos
- 📚 buscar alunos por cpf
- 👨‍🏫 Cadastro de professores
- 👨‍🏫 listar professores
- 👨‍🏫 buscar professores por cpf
- 🏫 Criação de turmas/disciplina  
- 🏫 listagem de turmas/disciplinas  
- 🏫 listagem de alunos matrículados numa turma/disciplina específica  
- 📝 Matrícula de alunos em turmas  
- 📊 Lançamento de notas  
- 📅 Controle de faltas  
- 📊 Geração de boletim com notas e faltas 

---

## 🗂️ Estrutura do Projeto

```text
📂 sistema-de-gerenciamento-de-colegio
│
├─ 📂 src            → arquivos .c (implementação)
│   ├─ main.c        → Loop que chama o menu principal
│   ├─ menu.c        → Lista opções e chama funções correspondentes
|   └─ database.c    → Funções relacionadas ao banco de dados
│   ├─ alunos.c      → Implementa cadastro e manipulação de alunos
│   ├─ professores.c → Implementa cadastro e manipulação de professores
│   ├─ turmas.c      → Criação de turmas e associação de professores
│   └─ matriculas.c  → Matrícula de alunos, lançamento de notas e faltas
│
├─ 📂 include        → arquivos .h (declarações)
│   ├─ alunos.h      → Declara funções de alunos
│   ├─ professores.h → Declara funções de professores
│   ├─ turmas.h      → Declara funções de turmas
│   └─ matriculas.h  → Declara funções de matrículas
│   └─ database.h  → Declara funções do database.c
│
├─ 📂 database    → arquivo com o banco de dados
│   └─ escola.db  → contém as tabelas alunos, professores, turmas e matrículas.
```
---
<h1> ⚙️ Compilação do Sistema (Makefile) </h1>

No terminal:

`make` -> Compila todos os arquivos

`./sistema_colegio` -> Executa o sistema

`make clean` -> Limpa arquivos gerados pelo make (.o e executável)

---

<h1> 🧠 Funcionamento do Sistema </h1>

O sistema utiliza o arquivo escola.db para armazenar os dados permanentemente em várias tabelas

<b> Relação entre dados: </b>

- Um aluno pode estar em várias turmas

- Cada turma possui um professor

- Matrícula liga aluno + turma

- Notas e faltas são armazenadas na matrícula

<b>🔗 Exemplo de Matrícula</b>

```
ID_Matricula  CPF_Aluno ID_Turma  Nota  Faltas
2001          1001      1         8.5   2
2002          1001      2         7.0   1
```
---
<h1>👥 Equipe</h1>

- Valdir

- Henrique

- Celine

- Arthur

---

<h1>🚀 Observações</h1>

Projeto desenvolvido para fins educacionais

Código organizado por módulos para facilitar manutenção

Uso de arquivos para persistência de dados

<h1> 💻 Tutorial de Configuração do Windows / Makefile </h1>

Este arquivo (Makefile) serve para compilar o código de maneira mais rápida dentro de cada computador.

Passo a passo:

- Instale o MSYS2 no Windows.

- Vá até a pasta C:\tools\msys64 e abra o arquivo msys2.exe.

- No terminal que abrir, digite: `pacman -S make`

- Quando aparecer para confirmar, digite Y.

- Pesquise no Windows: "Editar as variáveis de ambiente do sistema" e abra.

- Clique em Variáveis de Ambiente.

<img width="1042" height="586" alt="Captura de tela 2026-03-21 114020" src="https://github.com/user-attachments/assets/5e2ebb1d-c2fb-4251-8f48-45d732c392e3" />

- Localize a variável Path e duplo clique.

- Se houver algum caminho relativo ao MinGW, exclua.

- Clique em Novo e adicione: `C:\tools\msys64\ucrt64\bin` e `C:\tools\msys64\usr\bin`

- Repita o mesmo passo no outro Path em “Variáveis de Sistema” (ou vice-versa).

- Se o VSCode estiver aberto, feche e abra novamente.

<h3> ✅ Comandos liberados no terminal do VSCode </h3>

`make` → cria a pasta obj com todos os arquivos .c compilados e gera o executável sistema_colegio.exe

`make clean` → apaga a pasta obj e o executável

Sempre usar make clean antes de subir o projeto para o GitHub, pois cada computador deve compilar o executável localmente.

<h3>🔹 Executando o programa </h3>

Para compilar e rodar: `gcc -Wall -Wextra -g -Iinclude -o sistema obj/*.o -lsqlite3`

Para compilar com make: `make`

Para executar novamente (sem recompilar): `.\sistema_colegio.exe`

<h3>💡 Vantagens do Makefile</h3>

- Compilação rápida → programa recompila apenas os arquivos alterados

- Mantém a pasta raiz limpa → arquivos temporários vão para obj/

<h1> Antes de usar make </h1>
<img width="1301" height="659" alt="Captura de tela 2026-03-21 121351" src="https://github.com/user-attachments/assets/a7a1cbad-4a98-48be-8031-3ef1b8caa16b" />

<h1> Após usar make </h1>
<img width="1304" height="664" alt="Captura de tela 2026-03-21 121624" src="https://github.com/user-attachments/assets/209bf595-4d82-4bec-ab6d-39aa765c1ee7" />

---
