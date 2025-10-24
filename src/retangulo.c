#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "retangulo.h"

typedef struct {
    int id;
    double x, y;
    double largura, altura;
    char corB[8];
    char corP[8];
} RetStruct;

int validaRetangulo(void* r) {
    if (!r) return 0;
    RetStruct* rect = (RetStruct*)r;
    return (rect->id > 0) && (rect->largura > 0) && (rect->altura > 0) &&
           (rect->x == rect->x && rect->y == rect->y &&
            rect->largura == rect->largura && rect->altura == rect->altura) &&
           (!isinf(rect->x) && !isinf(rect->y) && !isinf(rect->largura) && !isinf(rect->altura)) &&
           (rect->corB[0] != '\0') && (rect->corP[0] != '\0');
}

Retangulo criaRet(int i, double x, double y, double w, double h, char* corb, char* corp) {
    if (i <= 0) {
        fprintf(stderr, "Erro: ID do retângulo inválido\n");
        return NULL;
    }
    
    if (!corb || !corp) {
        fprintf(stderr, "Erro: cores inválidas\n");
        return NULL;
    }
    
    if (w <= 0 || h <= 0) {
        fprintf(stderr, "Erro: largura e/ou altura inválida(s)\n");
        return NULL;
    }
    
    if (x != x || y != y || isinf(x) || isinf(y) ||
        w != w || h != h || isinf(w) || isinf(h)) {
        fprintf(stderr, "Erro: coordenadas e/ou dimensões inválida(s)\n");
        return NULL;
    }
    
    RetStruct* r = (RetStruct*)malloc(sizeof(RetStruct));
    if (!r) {
        fprintf(stderr, "Erro: falha na alocação do retângulo\n");
        return NULL;
    }
    
    r->id = i;
    r->x = x;
    r->y = y;
    r->largura = w;
    r->altura = h;
  
    if (corb && strlen(corb) >= 6) {
        strncpy(r->corB, corb, 6);
        r->corB[6] = '\0';
    } else {
        fprintf(stderr, "Aviso: cor de borda inválida, usando cor base: Preto\n");
        strcpy(r->corB, "000000"); 
    }
    r->corB[7] = '\0';
    
    if (corp && strlen(corp) >= 6) {
        strncpy(r->corP, corp, 6);
        r->corP[6] = '\0';
    } else {
        fprintf(stderr, "Aviso: cor de preenchimento inválida, usando cor base: Branco\n");
        strcpy(r->corP, "FFFFFF"); 
    }
    r->corP[7] = '\0'; 
    return (Retangulo)r;
}

double areaRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em areaRet\n");
        return -1.0;
    }
    
    RetStruct* rect = (RetStruct*)r;
    return rect->largura * rect->altura;
}

int idRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em idRet\n");
        return -1;
    }
    RetStruct* rect = (RetStruct*)r;
    return rect->id;
}

void moveRet(Retangulo r, double dx, double dy) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em moveRet\n");
        return;
    }
    
    if (dx != dx || dy != dy || isinf(dx) || isinf(dy)) {
        fprintf(stderr, "Erro: parâmetros inválidos em moveRet\n");
        return;
    }
    
    RetStruct* rect = (RetStruct*)r;
    double orig_x = rect->x;
    double orig_y = rect->y;
    rect->x += dx;
    rect->y += dy;
    
    if (rect->x != rect->x || rect->y != rect->y || isinf(rect->x) || isinf(rect->y)) {
        fprintf(stderr, "Erro: coordenadas corrompidas após movimento\n");
        rect->x = orig_x;
        rect->y = orig_y;
    }
}

Retangulo clonaRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: tentativa de clonagem de retângulo NULL\n");
        return NULL;
    }
    
    RetStruct* rect = (RetStruct*)r;
    int novoId = rect->id + 300;
    Retangulo clone = criaRet(novoId, rect->x, rect->y, rect->largura, rect->altura, rect->corB, rect->corP);
    
    if (!clone) {
        fprintf(stderr, "Erro: falha ao clonar retângulo %d\n", rect->id);
    }
    return clone;
}

TipoForma getTipo(Retangulo r) {
    (void)r; 
    return Tr;
}

double getXRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em getXRet\n");
        return -1000.0;
    }
    
    RetStruct* rect = (RetStruct*)r;
    return rect->x;
}

double getYRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em getYRet\n");
        return -1000.0;
    }
    
    RetStruct* rect = (RetStruct*)r;
    return rect->y;
}

char* getCorBRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em getCorBRet\n");
        return NULL;
    }
    
    RetStruct* rect = (RetStruct*)r;
    char* temp = strdup(rect->corB);
    
    if (!temp) {
        fprintf(stderr, "Erro: falha na alocação da cor de borda\n");
    }
    return temp;
}

char* getCorPRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Erro: retângulo NULL em getCorPRet\n");
        return NULL;
    }
    
    RetStruct* rect = (RetStruct*)r;
    char* temp = strdup(rect->corP);
    
    if (!temp) {
        fprintf(stderr, "Erro: falha na alocação da cor de preenchimento\n");
    }
    return temp;
}

void liberaRet(Retangulo r) {
    if (!r) {
        fprintf(stderr, "Aviso: tentativa de liberar retângulo NULL\n");
        return;
    }
    RetStruct* rect = (RetStruct*)r;
    free(rect);
}
