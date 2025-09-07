#include <stdio.h>      // Inclui a biblioteca para funções de entrada/saída (como printf e scanf)
#include <time.h>       // Inclui a biblioteca para usar o tempo (para gerar números aleatórios diferentes)
#include <stdlib.h>     // Inclui a biblioteca para funções gerais (como exit e rand/srand)
#include <string.h>     // Inclui a biblioteca para funções de string (como strlen)
#include "forca.h"      // Inclui o cabeçalho do nosso próprio jogo (onde estão as definições de funções e a constante TAMANHO_PALAVRA)

// --- VARIÁVEIS GLOBAIS (ACESSÍVEIS EM TODAS AS FUNÇÕES) ---
char palavrasecreta[TAMANHO_PALAVRA]; // Array que guarda a palavra a ser adivinhada
char chutes[26];                      // Array que guarda todas as letras que o jogador já chutou
int chutesdados = 0;                  // Contador de quantos chutes foram dados até agora

// --- FUNÇÕES ---

void abertura() {
    // Imprime a tela de boas-vindas do jogo.
    printf("****************\n");
    printf("* Jogo de Forca *\n");
    printf("****************\n\n");
}

void chuta() {
    // Declara uma variável para guardar o chute do usuário
    char chute;
    
    printf("Qual é o seu chute? ");
    // Lê um caractere do usuário e armazena em 'chute'
    // O espaço antes de %c ignora espaços em branco ou 'Enter' do buffer
    scanf(" %c", &chute); 

    // Armazena o novo chute no array de chutes, na próxima posição livre
    chutes[chutesdados] = chute;
    // Incrementa o contador de chutes dados
    chutesdados++;
}

void desenhaforca() {

    // Chama a função para contar quantos erros o jogador cometeu
    int erros = chuteserrados();

    // Desenha o mastro da forca
    printf("  _______      \n");
    printf(" |/      |     \n");
    
    // Desenha a cabeça (usa o operador ternário: se erros>=1? mostra '(' : senão ' ')
    printf(" |      %c%c%c \n", (erros>=1?'(':' '), 
    (erros>=1?'_':' '), (erros>=1?')':' '));
    
    // Desenha os braços (se erros>=3: mostra '\' e '/'; se erros>=2: mostra o '|')
    printf(" |      %c%c%c \n", (erros>=3?'\\': ' '), (erros>=2? '|': ' '), (erros>=3? '/': ' '));
    
    // Desenha o tronco (se erros>=2: mostra o '|'
    printf(" |       %c   \n", (erros>=2? '|':' '));
    
    // Desenha as pernas (se erros>=4: mostra '/' e '\')
    printf(" |      %c %c  \n", (erros>=4? '/': ' '), (erros>=4? '\\': ' '));
    
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    // --- MOSTRAR A PALAVRA SECRETA (PARCIAL) ---
    
    // Loop que percorre cada letra da palavra secreta
    for (int i = 0; i < strlen(palavrasecreta); i++) {

        // Verifica se a letra da palavra secreta (palavrasecreta[i]) já foi chutada
        int achou = jachutou(palavrasecreta[i]);

        // Se a letra foi encontrada entre os chutes (achou é 1)
        if (achou) {
            printf("%c", palavrasecreta[i]); // Mostra a letra
        } else {
            printf("_ "); // Senão, mostra um underscore e um espaço
        }
    }
    printf("\n"); // Pula para a próxima linha após mostrar a palavra
}

void adicionarpalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo ? (S/N)");
    scanf(" %c", &quer); // Lê a resposta do usuário

    if(quer == 'S') {

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra); // Lê a nova palavra do usuário

        FILE* f; // Declara um ponteiro para o arquivo

        // Abre o arquivo "palavras.txt" no modo "r+" (ler e escrever)
        f = fopen("palavras.txt", "r+"); 
        if(f == 0) { // Verifica se a abertura falhou
            printf("Desculpe, banco de dados não disponível\n\n");
            exit(1);
        }

        // --- ATUALIZA A QUANTIDADE DE PALAVRAS NO INÍCIO DO ARQUIVO ---
        int qtd;
        // Lê a quantidade atual de palavras (que é o primeiro número no arquivo)
        fscanf(f, "%d", &qtd);
        qtd++; // Incrementa a quantidade

        // Posiciona o 'cursor' do arquivo de volta ao início (posição 0)
        fseek(f, 0, SEEK_SET); 
        // Escreve a nova quantidade atualizada de palavras
        fprintf(f, "%d", qtd);

        // --- ADICIONA A NOVA PALAVRA AO FINAL DO ARQUIVO ---
        // Posiciona o 'cursor' no final do arquivo
        fseek(f, 0, SEEK_END);
        // Escreve a nova palavra, começando com '\n' para garantir que ela vá para uma nova linha
        fprintf(f, "\n%s", novapalavra); 

        fclose(f); // Fecha o arquivo
    }
}

void escolhepalavra() {

    FILE* f; // Declara um ponteiro para o arquivo

    // Abre o arquivo "palavras.txt" no modo "r" (somente leitura)
    f = fopen("palavras.txt", "r");
    if(f == 0) { // Verifica se a abertura falhou
        printf("Desculpe, banco de dados não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    // Lê a primeira linha do arquivo, que contém a quantidade de palavras
    fscanf(f, "%d", &qtddepalavras);

    // Usa o tempo atual como semente para o gerador aleatório
    srand(time(0));
    // Gera um número aleatório entre 0 e (qtddepalavras - 1)
    int randomico = rand() % qtddepalavras;

    // Loop que percorre o arquivo o número de vezes do valor randomico
    for(int i = 0; i <= randomico; i++) {
        // A cada repetição, lê a próxima palavra, ignorando as anteriores
        fscanf(f,"%s", palavrasecreta);
    }

    fclose(f); // Fecha o arquivo
}

int acertou() {
    // Percorre cada letra da palavra secreta
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        // Se UMA letra da palavra secreta não tiver sido chutada ainda (!jachutou)
        if(!jachutou(palavrasecreta[i])) { 
            return 0; // O jogador NÃO acertou a palavra (ainda falta letra)
        }
    }
    return 1; // Se o loop terminou sem encontrar letras faltando, o jogador acertou
}

// extraímos pra cá o pedaço daquela função 
// que contava a quantidade de erros
int chuteserrados() {
    int erros = 0;

    // Loop que percorre todos os chutes que o jogador deu
    for(int i = 0; i < chutesdados; i++) {

        int existe = 0; // Flag para verificar se o chute 'chutes[i]' existe na palavra secreta

        // Loop aninhado que percorre cada letra da palavra secreta
        for(int j = 0; j < strlen(palavrasecreta); j++) {
            // Compara o chute com a letra da palavra secreta
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1; // Encontrou!
                break;      // Sai do loop aninhado para o próximo chute
            }
        }

        // Se a flag 'existe' for 0 (o chute não foi encontrado na palavra)
        if(!existe) erros++;
    }

    return erros; // Retorna o número total de chutes errados
}

int enforcou() {
    // Retorna 1 (verdadeiro) se a quantidade de erros for maior ou igual a 5
    return chuteserrados() >= 5;
}

int jachutou(char letra) {

    int achou = 0; // Começa como 'falso' (0)

    // Percorre todos os chutes dados
    for (int j = 0; j < chutesdados; j++) {
        // Compara a letra que queremos verificar com cada chute
        if (chutes[j] == letra) {
            achou = 1; // A letra foi encontrada
            break;
        }
    }
    return achou; // Retorna 1 se achou, 0 se não achou
}

int main() {

    escolhepalavra(); // Escolhe a palavra secreta do arquivo
    abertura();       // Imprime a tela de boas-vindas

    // Loop principal: O jogo continua ENQUANTO o jogador NÃO acertou E NÃO foi enforcado
    do {

        desenhaforca(); // Desenha o boneco e mostra a palavra parcial
        chuta();        // Pede e registra o chute do usuário

    } while (!acertou() && !enforcou()); 
    
    // --- FIM DO JOGO: VERIFICA O RESULTADO ---
    
    if(acertou()) {
        // Se o loop parou porque 'acertou()' é verdadeiro
        printf("\nParabéns, você ganhou!\n\n");
        // Desenha a imagem de vitória
        printf("          ___________     \n");
        printf("        '._==_==_=_.'     \n");
        printf("        .-\\:      /-.    \n");
        printf("       | (|:.      |) |    \n");
        printf("        '-|:.      |-'     \n");
        printf("          \\::.    /      \n");
        printf("           '::. .'         \n");
        printf("             ) (           \n");
        printf("           _.' '._         \n");
        printf("         '-------'         \n\n");

    } else {
        // Se o loop parou porque 'enforcou()' é verdadeiro
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta); // Mostra a palavra
        
        // Desenha a forca e a pessoa enforcada
        printf("      _______________       \n");
        printf("     /               \\      \n");  
        printf("    /                 \\     \n");
        printf("//                    \\/\\ \n");
        printf("\\|    XXXX      XXXX   | /  \n");
        printf(" |    XXXX      XXXX   |/   \n");
        printf(" |    XXX        XXX   |    \n");
        printf(" |                     |    \n");
        printf(" \\__      XXX      __/      \n");
        printf("   |\\      XXX      /|        \n");
        printf("   | |             | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_              _/        \n");
        printf("     \\_          _/          \n");
        printf("       \\_______/            \n");

    }
    // A função 'adicionarpalavra' pode ser chamada aqui se você quiser dar a opção
    // de adicionar uma palavra nova após o término do jogo.
}