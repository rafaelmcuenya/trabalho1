#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "circulo.h"

typedef struct{
    int id;
    double x, y;
    double r;
    char corB[8];
    char corP[8];
} CircleStruct;

int validaCirculo(void* circ){
    if (!circ) return 0;
    CircleStruct* circle = (CircleStruct*)circ;
  
    return (circle->id > 0) && 
           (circle->r > 0) && (circle->x == circle->x && circle->y == circle->y && circle->r == circle->r) &&
           (!isinf(circle->x) && !isinf(circle->y) && !isinf(circle->r)) &&
           (circle->corB[0] != '\0') && (circle->corP[0] != '\0');
}

Circulo criaCircle(int i, double x, double y, double r, char* corb, char* corp){
    if (i <= 0){
        fprintf(stderr, "Erro: ID do círculo inválido\n");
        return NULL;
    }
    
    if (!corb || !corp){
        fprintf(stderr, "Erro: cor(es) do círculo inválida(s)\n");
        return NULL;
    }
    
    if (r <= 0){
        fprintf(stderr, "Erro: raio do círculo inválido\n");
        return NULL;
    }
    
    if (x != x || y != y || isinf(x) || isinf(y) ||
        r != r || isinf(r)){
        fprintf(stderr, "Erro: coordenada(s) e/ou raio inválido(s)\n");
        return NULL;
    }
    
    CircleStruct* c = (CircleStruct*)malloc(sizeof(CircleStruct));
    if (!c){
        fprintf(stderr, "Erro: falha na alocação do círculo\n");
        return NULL;
    }
    
    c->id = i;
    c->x = x;
    c->y = y;
    c->r = r;
    
    if (corb && strlen(corb) >= 6){
        strncpy(c->corB, corb, 6);
        c->corB[6] = '\0';
    } else{
        fprintf(stderr, "Erro: cor de borda inválida, usando cor base: Preto\n");
        strcpy(c->corB, "000000");
    }
    c->corB[7] = '\0';
    
    if (corp && strlen(corp) >= 6){
        strncpy(c->corP, corp, 6);
        c->corP[6] = '\0';
    } else{
        fprintf(stderr, "Erro: cor de preenchimento inválida, usando cor base: Branco\n");
        strcpy(c->corP, "FFFFFF"); 
    }
    c->corP[7] = '\0'; 
    return (Circulo)c;
}

double areaCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em areaCircle\n");
        return -1.0;
    }
    CircleStruct* circle = (CircleStruct*)c;
    return circle->r * circle->r * 3.14;
}

int idCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em idCircle\n");
        return -1;
    }
    CircleStruct* circle = (CircleStruct*)c;
    return circle->id;
}

void moveCircle(Circulo c, double dx, double dy){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em moveCircle\n");
        return;
    }
    
    if (dx != dx || dy != dy || isinf(dx) || isinf(dy)){
        fprintf(stderr, "Erro: parâmetros inválidos em moveCircle\n");
        return;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    double orig_x = circle->x;
    double orig_y = circle->y;
    circle->x += dx;
    circle->y += dy;
  
    if (circle->x != circle->x || circle->y != circle->y || 
        isinf(circle->x) || isinf(circle->y)){
        fprintf(stderr, "Erro: coordenadas corrompidas após movimento\n");
        circle->x = orig_x;
        circle->y = orig_y;
    }
}

Circulo clonaCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: tentativa de clonar círculo NULL\n");
        return NULL;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    int novoId = circle->id * 1000 + (int)(circle->x + circle->y + circle->r);
    if (novoId <= circle->id) novoId = circle->id + 1000;
    Circulo clone = criaCircle(novoId, circle->x, circle->y, circle->r, circle->corB, circle->corP);
    
    if (!clone){
        fprintf(stderr, "Erro: falha ao clonar círculo %d\n", circle->id);
    }
    return clone;
}

double getXCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em getXCircle\n");
        return -1000.0;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    return circle->x;
}

double getYCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em getYCircle\n");
        return -1000.0;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    return circle->y;
}

char* getCorBCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em getCorBCircle\n");
        return NULL;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    char* copia = strdup(circle->corB);
    
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da cor de borda\n");
    }
    return copia; 
}

char* getCorPCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em getCorPCircle\n");
        return NULL;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    char* copia = strdup(circle->corP);
    
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da cor de preenchimento\n");
    }
    return copia; 
}

double getRaioCirculo(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: círculo NULL em getRaioCirculo\n");
        return -1.0;
    }
    
    CircleStruct* circle = (CircleStruct*)c;
    return circle->r;
}

void setCorBCirculo(Circulo c, char* novaCor){
    if (!c || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorBCirculo\n");
        return;
    }
    CircleStruct* circle = (CircleStruct*)c;
    if (strlen(novaCor) >= 6){
        strncpy(circle->corB, novaCor, 6);
        circle->corB[6] = '\0';
    }
}

void setCorPCirculo(Circulo c, char* novaCor){
    if (!c || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorPCirculo\n");
        return;
    }
    CircleStruct* circle = (CircleStruct*)c;
    if (strlen(novaCor) >= 6){
        strncpy(circle->corP, novaCor, 6);
        circle->corP[6] = '\0';
    }
}

void liberaCircle(Circulo c){
    if (!c){
        fprintf(stderr, "Erro: tentativa de liberar círculo NULL\n");
        return;
    }
    CircleStruct* circle = (CircleStruct*)c;
    free(circle);
}
