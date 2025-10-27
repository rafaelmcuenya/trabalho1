#include "chao.h"
#include "forma.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NoChao{
    Forma forma;
    struct NoChao* prox;
} NoChao;

struct ChaoStruct{
    NoChao* inicio;
    NoChao* fim;
    int tamanho;
};

Chao criaChao(void){
    struct ChaoStruct* chao = malloc(sizeof(struct ChaoStruct));
    if (!chao) return NULL;
    
    chao->inicio = NULL;
    chao->fim = NULL;
    chao->tamanho = 0;
    return chao;
}

void freeChao(Chao chao){
    if (!chao) return;
    
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    NoChao* atual = c->inicio;
    
    while (atual != NULL){
        NoChao* prox = atual->prox;
        if (atual->forma){
            freeForma(atual->forma);
        }
        free(atual);
        atual = prox;
    }
    free(c);
}

void inFormaChao(Chao chao, Forma forma){
    if (!chao || !forma) return;
    
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    NoChao* novo = malloc(sizeof(NoChao));
    if (!novo) return;
    
    novo->forma = forma;
    novo->prox = NULL;
    
    if (c->fim == NULL){
        c->inicio = novo;
    } else{
        c->fim->prox = novo;
    }
    c->fim = novo;
    c->tamanho++;
}

Forma outFormaChao(Chao chao){
    if (!chao) return NULL;
    
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    if (c->inicio == NULL) return NULL;
    
    NoChao* primeiro = c->inicio;
    Forma forma = primeiro->forma;
    
    c->inicio = primeiro->prox;
    if (c->inicio == NULL){
        c->fim = NULL;
    }
    
    free(primeiro);
    c->tamanho--;
    return forma;
}

int voidChao(Chao chao){
    if (!chao) return 1;
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    return c->inicio == NULL;
}

void percorreChao(Chao chao, void (*func)(Forma)){
    if (!chao || !func) return;
    
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    NoChao* atual = c->inicio;
    
    while (atual != NULL){
        func(atual->forma);
        atual = atual->prox;
    }
}

void percorreChaoComFile(Chao chao, FILE* svgFile, void (*func)(FILE*, Forma)){
    if (!chao || !func || !svgFile) return;
    
    struct ChaoStruct* c = (struct ChaoStruct*)chao;
    NoChao* atual = c->inicio;
    
    while (atual != NULL){
        func(svgFile, atual->forma);
        atual = atual->prox;
    }
}
