#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct {
    int id;
    double x, y;
    char corB[8];
    char corP[8];
    char a;      
    char* txto; 
} TextoStruct;

Texto criaTexto(int i, double x, double y, char* corb, char* corp, char a, char* txto) {
    TextoStruct* t = (TextoStruct*)malloc(sizeof(TextoStruct));
    if (!t) return NULL;
    t->id = i;
    t->x = x;
    t->y = y;
    t->a = a;
    strncpy(t->corB, corb, 7);
    t->corB[7] = '\0';
    strncpy(t->corP, corp, 7);
    t->corP[7] = '\0';
    t->txto = (char*)malloc(strlen(txto) + 1);
    if (!t->txto) {
        free(t);
        return NULL;
    }
    strcpy(t->txto, txto);
    return (Texto)t;
}

double areaTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return 20.0 * strlen(Texto->txto);
}

int idTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->id;
}

void moveTexto(Texto t, double dx, double dy) {
    TextoStruct* Texto = (TextoStruct*)t;
    Texto->x += dx;
    Texto->y += dy;
}

Texto clonaTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return criaTexto(Texto->id, Texto->x, Texto->y, Texto->corB, Texto->corP, Texto->a, Texto->txto);
}

TipoForma getTipo(Texto t) {
    (void)t; // ignorado, pois o tipo é fixo
    return Tt;
}

double getXTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->x;
}

double getYTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->y;
}

char* getCorBTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->corB;
}

char* getCorPTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->corP;
}

char getAncoraTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    return Texto->a;
}

void liberaTexto(Texto t) {
    TextoStruct* Texto = (TextoStruct*)t;
    free(Texto->txto);
    free(Texto);
}
