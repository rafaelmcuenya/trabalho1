#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "disparador.h"
#include "carregador.h"
#include "forma.h"

typedef struct {
    int id;
    double x;
    double y;
    Carregador cesq; 
    Carregador cdir;   
    Forma posDisparo;
} DisparadorStruct;

Disparador criaDisparador(int id, double x, double y) {
    if (id <= 0) {
        fprintf(stderr, "Erro: ID do disparador inválido\n");
        return NULL;
    }
    
    if (x != x || y != y || isinf(x) || isinf(y)) {
        fprintf(stderr, "Erro: coordenadas do disparador inválidas\n");
        return NULL;
    }
    
    DisparadorStruct* dis = (DisparadorStruct*)malloc(sizeof(DisparadorStruct));
    if (!dis) {
        fprintf(stderr, "Erro: falha na alocação do disparador\n");
        return NULL;
    }
    
    dis->id = id;
    dis->x = x;
    dis->y = y;
    dis->cesq = NULL;
    dis->cdir = NULL;
    dis->posDisparo = NULL;
    return (Disparador)dis;
}

void liberaDisparador(Disparador d) {
    if (!d) {
        fprintf(stderr, "Erro: Disparador inválido\n");
        return;
    }
    DisparadorStruct* dis = (DisparadorStruct*)d;

    Forma formaSalva = NULL;
    if (dis->posDisparo) {
        formaSalva = dis->posDisparo; 
    }
    limpaDisparador(d);
    
    if (dis->posDisparo != NULL) {
        fprintf(stderr, "Erro na liberação da forma\n");
        if (dis->posDisparo) {
            liberaForma(dis->posDisparo);
            dis->posDisparo = NULL;
        }
    }
    free(dis);
}

void inicializaDisparador(Disparador d, int id, double x, double y) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return;
    
    if (id <= 0) {
        fprintf(stderr, "Erro: ID do disparador inválido\n");
        return;
    }
    
    if (x != x || y != y || isinf(x) || isinf(y)) {
        fprintf(stderr, "Erro: coordenadas do disparador inválidas\n");
        return;
    }
    dis->id = id;
    dis->x = x;
    dis->y = y;
    dis->cesq = NULL;
    dis->cdir = NULL;
    dis->posDisparo = NULL;
}

void encaixaCarregadores(Disparador d, Carregador cesq, Carregador cdir) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return;
  
    if (cesq == cdir && cesq != NULL) {
        fprintf(stderr, "Erro: tentativa de acoplamento de um mesmo carregador\n");
        return;
    }
    dis->cesq = cesq;
    dis->cdir = cdir;
}

void setPosDisparador(Disparador d, double x, double y) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return;

    if (x != x || y != y || isinf(x) || isinf(y)) {
        fprintf(stderr, "Erro: coordenadas inválidas para mover o disparador\n");
        return;
    }
    
    dis->x = x;
    dis->y = y;
}

static void pressionaBotaoOnce(DisparadorStruct* dis, char lado) {
    if (!dis) return;
    if (dis->cesq == NULL || dis->cdir == NULL) return; 
  
    if (lado != 'd' && lado != 'e') {
        fprintf(stderr, "Erro: botão inexistente no disparador\n");
        return;
    }
  
    if (lado == 'd' && estaVazioCarregador(dis->cesq)) {
        fprintf(stderr, "Erro: carregador esquerdo vazio\n");
        return;
    }
    
    if (lado == 'e' && estaVazioCarregador(dis->cdir)) {
        fprintf(stderr, "Erro: carregador direito vazio\n");
        return;
    }
    
    if (lado == 'd') {
        Forma nova = desempilhaCarregador(dis->cesq);
        if (!nova) {
            fprintf(stderr, "Erro: falha ao descarregar do carregador esquerdo\n");
            return;
        }
        if (dis->posDisparo != NULL) {
            empilhaCarregador(dis->cdir, dis->posDisparo);
        }
        dis->posDisparo = nova;
    } else if (lado == 'e') {
        Forma nova = desempilhaCarregador(dis->cdir);
        if (!nova) {
            fprintf(stderr, "Erro: falha ao descarregar do carregador direito\n");
            return;
        }
        if (dis->posDisparo != NULL) {
            empilhaCarregador(dis->cesq, dis->posDisparo);
        }
        dis->posDisparo = nova;
    }
}

void shftDisparador(Disparador d, char lado, int n) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return;
        fprintf(stderr, "Erro:parâmetro inválido\n");
        return;
    }
    
    if (lado != 'd' && lado != 'e') {
        fprintf(stderr, "Erro: parâmetro inválido\n");
        return;
    }
  
    if (dis->cesq == NULL || dis->cdir == NULL) {
        fprintf(stderr, "Erro: ausência de um ou mais carregadores acoplados\n");
        return;
    }

    int operacoesBemSucedidas = 0;
    Forma backupPosDisparo = dis->posDisparo;
    
    for (int i = 0; i < n; i++) {
        Forma estadoAntes = dis->posDisparo;
        pressionaBotaoOnce(dis, lado);
      
        if (dis->posDisparo != estadoAntes) {
            operacoesBemSucedidas++;
        } else {
            fprintf(stderr, "Erro: falha na operação %d%d\n", i + 1, n);
        }
    }
    
    if (operacoesBemSucedidas == 0) {
        fprintf(stderr, "Erro: nenhuma operação de shift foi bem-sucedida\n");
    }
}

Forma disparaForma(Disparador d, double dx, double dy) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return NULL;
  
    if (dis->posDisparo == NULL) {
        fprintf(stderr, "Erro: nenhuma forma em posição de disparo\n");
        return NULL;
    }
    
    if (dx != dx || dy != dy || isinf(dx) || isinf(dy)) {
        fprintf(stderr, "Erro: deslocamentos inválidos\n");
        return NULL;
    }

    Forma f = dis->posDisparo;
    dis->posDisparo = NULL;
    double alvoX = dis->x + dx;
    double alvoY = dis->y + dy;
    double curX = getXForma(f);
    double curY = getYForma(f);
    
    if (curX != curX || curY != curY || isinf(curX) || isinf(curY)) {
        fprintf(stderr, "Erro: coordenadas atuais da forma são inválidas\n");
        return f;
    }
    
    double movX = alvoX - curX;
    double movY = alvoY - curY;
    double xAntes = getXForma(f);
    double yAntes = getYForma(f);
    moveForma(f, movX, movY);
    double xDepois = getXForma(f);
    double yDepois = getYForma(f);

    if (xDepois == xAntes && yDepois == yAntes) {
        fprintf(stderr, "Erro: possível erro de movimento do disparador\n");
    }
    return f;
}

int possuiCarregadorEsq(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return 0;
    return (dis->cesq != NULL);
}

int possuiCarregadorDir(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return 0;
    return (dis->cdir != NULL);
}

int getIdDisparador(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*)d;
    if (!dis) return -1;
    return dis->id;
}

double getXDisparador(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*)d;
    if (!dis) return -1000.0; 
    return dis->x;
}

double getYDisparador(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*)d;
    if (!dis) return -1000.0; 
    return dis->y;
}

Forma getPosDisparo(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*)d;
    if (!dis) return NULL;
    return dis->posDisparo;
}

void limpaDisparador(Disparador d) {
    DisparadorStruct* dis = (DisparadorStruct*) d;
    if (!dis) return;
    
    if (dis->posDisparo) {
        liberaForma(dis->posDisparo);
        dis->posDisparo = NULL;
    }
    dis->cesq = NULL;
    dis->cdir = NULL;
    dis->x = 0;
    dis->y = 0;
    dis->id = 0;
}
