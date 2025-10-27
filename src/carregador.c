#include <stdio.h>
#include <stdlib.h>
#include "carregador.h"
#include "forma.h"
#include "strdupi.h"

typedef struct NoCar {
    Forma f;
    struct NoCar* prox;
} NoCar;

typedef struct {
    NoCar* topo;
    int tamanho;
    int id;
} CarregadorStruct;

void inicializaCarregador(Carregador car, int id) {
    if (!car || id < 0) {
        fprintf(stderr, "Erro: parâmetros inválidos em inicializaCarregador\n");
        return;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    c->topo = NULL;
    c->tamanho = 0;
    c->id = id;
}

Carregador criaCarregador(int id) {
    if (id < 0) {
        fprintf(stderr, "Erro: ID do carregador inválido\n");
        return NULL;
    }
    
    CarregadorStruct* car = (CarregadorStruct*)malloc(sizeof(CarregadorStruct));
    if (!car) {
        fprintf(stderr, "Erro: falha na alocação do carregador\n");
        return NULL;
    }
    car->topo = NULL;
    car->tamanho = 0;
    car->id = id;
    return (Carregador)car;
}

void empilhaCarregador(Carregador car, Forma f) {
    if (!car || !f) {
        fprintf(stderr, "Erro: parâmetros inválidos em empilhaCarregador\n");
        return;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    NoCar* no = (NoCar*)malloc(sizeof(NoCar));
 
    if (!no) {
        fprintf(stderr, "Erro: falha na alocação do nó do carregador\n");
        return; 
    }
    
    no->f = f;
    no->prox = c->topo;
    c->topo = no;
    c->tamanho++;
}

Forma desempilhaCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Erro: carregador NULL em desempilhaCarregador\n");
        return NULL;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    if (c->topo == NULL) {
        fprintf(stderr, "Erro: tentativa de desempilhar carregador vazio\n");
        return NULL;
    }

    NoCar* no = c->topo;
    Forma f = no->f;
    c->topo = no->prox;
    free(no);
    c->tamanho--;
    return f;
}

int voidCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Erro: carregador NULL\n");
        return 1;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    return (c->topo == NULL);
}

int tamCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Erro: carregador NULL em tamanhoCarregador\n");
        return 0;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    return c->tamanho;
}

int getIdCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Erro: carregador NULL em getIdCarregador\n");
        return -1;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    return c->id;
}

Forma topoCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Erro: carregador NULL em topoCarregador\n");
        return NULL;
    }
    
    CarregadorStruct* c = (CarregadorStruct*)car;
    if (c->topo == NULL) {
        return NULL;
    }
    return c->topo->f;
}

void limpaCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Aviso: tentativa de limpar carregador NULL\n");
        return;
    }
    CarregadorStruct* c = (CarregadorStruct*)car;
    NoCar* atual = c->topo;
  
    while (atual) {
        NoCar* prox = atual->prox;
        free(atual); 
        atual = prox;
    }
    c->topo = NULL;
    c->tamanho = 0;
}

void freeCarregador(Carregador car) {
    if (!car) {
        fprintf(stderr, "Aviso: tentativa de liberar carregador NULL\n");
        return;
    }
    CarregadorStruct* c = (CarregadorStruct*)car;
    
    NoCar* atual = c->topo;
    while (atual) {
        NoCar* prox = atual->prox;
        if (atual->f) {
            freeForma(atual->f); 
        }
        free(atual);
        atual = prox;
    }
    c->topo = NULL;
    c->tamanho = 0;
    free(c);
}
