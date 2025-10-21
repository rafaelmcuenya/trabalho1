
#include <stdio.h>
#include <stdlib.h>
#include "chao.h"

typedef struct No {
    Forma forma;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} ChaoStruct;

Chao criaChao() {
    ChaoStruct* c = (ChaoStruct*)malloc(sizeof(ChaoStruct));
    if (!c) return NULL;
    c->inicio = NULL;
    c->fim = NULL;
    c->tamanho = 0;
    return (Chao)c;
}

void inFormaChao(Chao c, Forma f) {
    ChaoStruct* ch = (ChaoStruct*)c;
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return;
    novo->forma = f;
    novo->prox = NULL;

    if (ch->fim == NULL) {
        ch->inicio = novo;
    } else {
        ch->fim->prox = novo;
    }
    ch->fim = novo;
    ch->tamanho++; 
}

Forma outFormaChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    if (ch->inicio == NULL) return NULL;

    No* aux = ch->inicio;
    Forma f = aux->forma;
    ch->inicio = aux->prox;

    if (ch->inicio == NULL) {
        ch->fim = NULL;
    }

    free(aux);
    ch->tamanho--; 
    return f;
}

Forma seePFChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    if (ch->inicio == NULL) return NULL;
    return ch->inicio->forma;
}

int voidChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    return (ch->inicio == NULL);
}

int tamanhoChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    return ch->tamanho;
}

void freeChao(Chao c) {
    ChaoStruct* ch = (ChaoStruct*)c;
    No* atual = ch->inicio;
    while (atual) {
        No* prox = atual->prox;
        liberaForma(atual->forma);
        free(atual);
        atual = prox;
    }
    free(ch);
}

