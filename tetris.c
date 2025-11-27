#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tamanho máximo da fila
#define MAX_FILA 5   

// Struct para a peça
typedef struct {
    char nome;   // Tipo da peça ('I', 'O', 'T', 'L')
    int id;      // Identificador único
} Peca;

// Struct para a fila circular
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Protótipo das funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void exibirFila(Fila *f);
Peca gerarPeca();

// Variável global para gerar IDs
int ultimoID = 0;

// Função principal
int main() {
    Fila fila;
    int opcao;
    srand(time(NULL));

    inicializarFila(&fila);

    // Preenche a fila inicialmente
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        printf("\n=============================\n");
        printf("      TETRIS STACK\n");
        printf("=============================\n");
        exibirFila(&fila);

        printf("1. Jogar peça\n");
        printf("2. Inserir nova peça\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            if (!filaVazia(&fila)) {
                Peca jogada = dequeue(&fila);
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
            } else {
                printf("\nA fila está vazia! Não há peça para jogar.\n");
            }
            break;

        case 2:
            if (!filaCheia(&fila)) {
                enqueue(&fila, gerarPeca());
                printf("\nNova peça inserida!\n");
            } else {
                printf("\nFila cheia! Não é possível inserir nova peça.\n");
            }
            break;

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Implementação das funções

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == MAX_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Insere peça no final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;

    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;
}

// Remove peça da frente da fila
Peca dequeue(Fila *f) {
    Peca p = {'X', -1}; // default caso algo dê errado
    if (filaVazia(f)) return p;

    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->quantidade--;

    return p;
}

// Exibe todas as peças da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila de Peças:\n");
    for (int i = 0, pos = f->frente; i < f->quantidade; i++) {
        Peca p = f->itens[pos];
        printf("[%c %d] ", p.nome, p.id);
        pos = (pos + 1) % MAX_FILA;
    }
    printf("\n\n");
}

// Gera peça automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = ultimoID++;

    return nova;
}