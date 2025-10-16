#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct {
    int id;
    double x, y;
    double largura, altura;
    char corB[8];
    char corP[8];
} RetStruct;

Retangulo criaRet(int i, double x, double y, double w, double h, char* corb, char* corp) {
    RetStruct* r = (RetStruct*)malloc(sizeof(RetStruct));
    if (!r) return NULL;
    r->id = i;
    r->x = x;
    r->y = y;
    r->largura = w;
    r->altura = h;
    strncpy(r->corB, corb, 7);
    r->corB[7] = '\0';
    strncpy(r->corP, corp, 7);
    r->corP[7] = '\0';
    return (Retangulo)r;
}

double areaRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->largura * rect->altura;
}

int idRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->id;
}

void moveRet(Retangulo r, double dx, double dy) {
    RetStruct* rect = (RetStruct*)r;
    rect->x += dx;
    rect->y += dy;
}

Retangulo clonaRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return criaRet(rect->id, rect->x, rect->y, rect->largura, rect->altura, rect->corB, rect->corP);
}

TipoForma getTipo(Retangulo r) {
    (void)r; 
    return Tr;
}

double getXRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->x;
}

double getYRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->y;
}

char* getCorBRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->corB;
}

char* getCorPRet(Retangulo r) {
    RetStruct* rect = (RetStruct*)r;
    return rect->corP;
}

void liberaRet(Retangulo r) {
    free(rect);
}
