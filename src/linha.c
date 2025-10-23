#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"

static int proximoIdLinha = 300;

typedef struct {
    int id;
    double x1, y1, x2, y2;
    char cor[8];
} LinhaStruct;

Linha criaLinha(int i, double x1, double y1, double x2, double y2, char* cor) {
    LinhaStruct* l = (LinhaStruct*)malloc(sizeof(LinhaStruct));
    if (!l) return NULL;
    l->id = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    strncpy(l->cor, cor, 7);
    l->cor[7] = '\0';
    
    if (i >= proximoIdLinha) {
        proximoIdLinha = i + 1;
    }
    return (Linha)l;
}

double areaLinha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    double comp = sqrt(pow(linha->x2 - linha->x1, 2) + pow(linha->y2 - linha->y1, 2));
    return 2 * comp;
}

int idLinha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    return linha->id;
}

void moveLinha(Linha l, double dx, double dy) {
    LinhaStruct* linha = (LinhaStruct*)l;
    linha->x1 += dx;
    linha->x2 += dx;
    linha->y1 += dy;
    linha->y2 += dy;
}

Linha clonaLinha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
  
    int novoId = proximoIdLinha++;
    return criaLinha(novoId, linha->x1, linha->y1, linha->x2, linha->y2, linha->cor);
}

double getX1Linha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    return linha->x1;
}

double getY1Linha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    return linha->y1;
}

double getX2Linha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    return linha->x2;
}

double getY2Linha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    return linha->y2;
}

char* getCorLinha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    char* copia = (char*)malloc(8 * sizeof(char));
    if (copia) {
        strcpy(copia, linha->cor);
    }
    return copia;
}

void liberaLinha(Linha l) {
    LinhaStruct* linha = (LinhaStruct*)l;
    free(linha);
}
