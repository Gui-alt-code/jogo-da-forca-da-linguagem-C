# 🕹️ Jogo da Forca em C

Bem-vindo ao **Jogo da Forca**, um projeto simples feito em **linguagem C**, com leitura e escrita de palavras via **arquivo `.txt`**, sorteio randômico e controle de tentativas!

Este projeto é ideal para quem está aprendendo a linguagem C e deseja praticar **manipulação de strings**, **leitura de arquivos**, **lógica de jogo**, e **controle de fluxo**.

---

## 📌 Descrição do Projeto

O jogo da forca é um clássico onde o jogador tenta adivinhar uma palavra secreta chutando letras, com um número limitado de erros permitidos (neste caso, 5). A palavra é sorteada de um arquivo de texto, e o jogador tem a opção de adicionar novas palavras ao banco.

O jogo desenha a forca com base na quantidade de erros cometidos e exibe mensagens diferentes ao final, dependendo do resultado.

---

## 🛠️ Tecnologias e Ferramentas Utilizadas

- **Linguagem C**;
- **Compilador GCC**;
- **Arquivo externo**: `palavras.txt` (banco de palavras);
- **Header personalizado**: `forca.h`;
- **Bibliotecas-padrão**:
  - `<stdio.h>` – Entrada/saída;
  - `<stdlib.h>` – Funções utilitárias (como `rand`, `exit`);
  - `<string.h>` – Manipulação de strings;
  - `<time.h>` – Geração de números aleatórios com base no tempo.
 
---

## ⚙️ Funcionalidades

- 🔤 Sorteio randômico de uma palavra secreta do arquivo `palavras.txt`;
- ⌨️ Recebimento de letras digitadas pelo jogador;
- 🧠 Verificação se a letra já foi chutada;
- ❌ Contador de erros e verificação de enforcamento;
- ✅ Verificação de vitória ao acertar todas as letras;
- ✍️ Opção de adicionar novas palavras ao arquivo de forma persistente.

---

# ✅ Pré-requisitos:

Você precisa de um compilador C instalado, como o GCC.

---

# 🔧 Como Testar o Código:

1) Em primeiro lugar, utilize o comando "copy path" no arquivo adivinhacao.c, pressionando a parte direita de seu mouse.
   

   Exemplo de conteúdo esperado ao realizar o copy path: 


   `C:\Users\guilh\OneDrive\Área de Trabalho\Jogo-da-forca-da-linguagem-C\forca.c`


2) Tendo copiado o caminho do arquivo e possuindo um compilador instalado em seu computador, diriga-se para o prompt de comando e digite o seguinte contéudo, fazendo questão de excluir a parte `forca.c`.
   

   Exemplo de contéudo a ser digitado no prompt:


   `cd "C:\Users\guilh\OneDrive\Área de Trabalho\Jogo-da-forca-da-linguagem-C"`


3) Posteriormente, no prompt de comando, digite o comando a seguir.
   

   Exemplo de conteúdo a ser digitado no prompt:


   `gcc forca.c -o forca`

4) Para que terminal do Windows consiga exibir corretamente caracteres especiais, como acentos e cedilhas, digite o conteúdo abaixo:
   

    `chcp 65001`

5) Por fim, digite no prompt de comando o seguinte conteúdo e aproveite o jogo !

   `forca`

## 🎮 Como Jogar

1. Ao iniciar o jogo, será exibida uma mensagem de boas-vindas.

2. O computador escolhe **aleatoriamente uma palavra secreta** do arquivo `palavras.txt`.

3. Você deve **tentar adivinhar a palavra chutando uma letra por vez**.

4. A cada letra digitada:
- ✅ **Se estiver na palavra**, ela será revelada na posição correta.
- ❌ **Se não estiver**, a forca será desenhada com mais um erro.

5. Você tem **até 5 erros antes de ser "enforcado"**.  
O jogo termina quando:
- ✅ Você adivinha todas as letras corretamente (**vitória**).
- ❌ Você atinge o limite de 5 erros (**derrota**).

6. Ao final da partida, o jogo exibe uma **mensagem de vitória ou derrota**, e revela a palavra secreta, caso não tenha sido descoberta.

7. Após o término, será exibida a pergunta:

Você deseja adicionar uma nova palavra no jogo ? (S/N)


- Se você responder `S`, poderá digitar uma nova palavra.
- Ela será **adicionada ao arquivo `palavras.txt`** e poderá aparecer em futuras partidas.

---

# 📄 Licença

Este projeto é de livre uso para fins educacionais. Sinta-se à vontade para modificar, adaptar ou expandir!

