#include <stdio.h>
#include <stdlib.h>
#include "chao.h"
#include "forma.h"

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
    if (!c || !f) return;
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
    if (!c) return NULL;
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
    if (!c) return NULL;
    ChaoStruct* ch = (ChaoStruct*)c;
    if (ch->inicio == NULL) return NULL;
    return ch->inicio->forma;
}

int voidChao(Chao c) {
    if (!c) return 1;
    ChaoStruct* ch = (ChaoStruct*)c;
    return (ch->inicio == NULL);
}

int tamChao(Chao c) {
    if (!c) return 0;
    ChaoStruct* ch = (ChaoStruct*)c;
    return ch->tamanho;
}

void percorreChao(Chao c, void (*funcao)(Forma)) {
    if (!c || !funcao) return;
    ChaoStruct* ch = (ChaoStruct*)c;
    No* atual = ch->inicio;
    
    while (atual) {
        funcao(atual->forma);
        atual = atual->prox;
    }
}

void freeChao(Chao c) {
    if (!c) return;
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
