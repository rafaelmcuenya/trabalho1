#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arena.h"
#include "forma.h"
#include "chao.h"
#include "sobrepor.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct NoArena{
    Forma forma;
    struct NoArena* prox;
} NoArena;

typedef struct{
    NoArena* inicio;
    NoArena* fim;
    int tamanho;
} ArenaStruct;

static char* calculaCorComplementar(const char* cor){
    if (!cor || strlen(cor) != 6) return strdup("000000");
    
    char* complementar = malloc(7);
    if (!complementar) return NULL;
    
    for (int i = 0; i < 6; i += 2){
        char hex[3] ={cor[i], cor[i+1], '\0'};
        int valor = (int)strtol(hex, NULL, 16);
        int complemento = 255 - valor;
        sprintf(&complementar[i], "%02X", complemento);
    }
    complementar[6] = '\0';
    return complementar;
}

static Forma clonaFormaComCoresTrocadas(Forma original){
    if (!original) return NULL;
    
    TipoForma tipo = getTipoForma(original);
    int id = getIdForma(original);
    double x = getXForma(original);
    double y = getYForma(original);
    char* corB = getCorBForma(original);
    char* corP = getCorPForma(original);
    Forma clone = NULL;
    
    switch (tipo){
        case Tc:{
            double raio = getRaioCirculo(getCirculoFromForma(original));
            clone = criaForma(Tc, criaCircle(id + 1000, x, y, raio, corP, corB));
            break;
        }
        case Tr:{
            double largura = getLarguraRetangulo(getRetanguloFromForma(original));
            double altura = getAlturaRetangulo(getRetanguloFromForma(original));
            clone = criaForma(Tr, criaRet(id + 1000, x, y, largura, altura, corP, corB));
            break;
        }
        case Tl:{
            Linha linha_orig = getLinhaFromForma(original);
            double x1 = getX1Linha(linha_orig);
            double y1 = getY1Linha(linha_orig);
            double x2 = getX2Linha(linha_orig);
            double y2 = getY2Linha(linha_orig);
            char* cor_complementar = calculaCorComplementar(corP);
            clone = criaForma(Tl, criaLinha(id + 1000, x1, y1, x2, y2, cor_complementar));
            free(cor_complementar);
            break;
        }
        case Tt:{
            Texto texto_orig = getTextoFromForma(original);
            char ancora = getAncoraTexto(texto_orig);
            char* texto_str = getTexto(texto_orig);
            clone = criaForma(Tt, criaTexto(id + 1000, x, y, corP, corB, ancora, texto_str));
            free(texto_str);
            break;
        }
    }
    free(corB);
    free(corP);
    return clone;
}

Arena criaArena(){
    ArenaStruct* a = malloc(sizeof(ArenaStruct));
    if (!a) return NULL;
    a->inicio = NULL;
    a->fim = NULL;
    a->tamanho = 0;
    return a;
}

void insereFormaArena(Arena a, Forma f){
    if (!a || !f) return;
    
    ArenaStruct* arena = (ArenaStruct*)a;
    NoArena* novo = malloc(sizeof(NoArena));
    if (!novo) return;
    
    novo->forma = f;
    novo->prox = NULL;
    
    if (arena->fim == NULL){
        arena->inicio = novo;
    } else{
        arena->fim->prox = novo;
    }
    arena->fim = novo;
    arena->tamanho++;
}

void processaArena(Arena a, Chao chao, double* pontuacaoTotal, int* formasEsmagadas, int* formasClonadas){
    if (!a || !chao) return;
    ArenaStruct* arena = (ArenaStruct*)a;
    NoArena* atual = arena->inicio;
    
    while (atual != NULL && atual->prox != NULL){
        Forma forma1 = atual->forma;
        Forma forma2 = atual->prox->forma;
        
        int sobreposicao = formasSobrepoem(forma1, forma2);
        double area1 = areaForma(forma1);
        double area2 = areaForma(forma2);
        
        if (sobreposicao){
            if (area1 < area2){
                *pontuacaoTotal += area1;
                (*formasEsmagadas)++;
                
                freeForma(forma1);
                inFormaChao(chao, forma2);
              
                NoArena* proximo_par = atual->prox->prox;
                free(atual->prox); 
                atual->forma = NULL; 
                atual->prox = proximo_par;
                
            } else{
                char* corPreenchimento1 = getCorPForma(forma1);
    
                switch (getTipoForma(forma2)){
                    case Tc:
                        setCorBCirculo(getCirculoFromForma(forma2), corPreenchimento1);
                        break;
                    case Tr:
                        setCorBRetangulo(getRetanguloFromForma(forma2), corPreenchimento1);
                        break;
                    case Tl:{
                        char* cor_complementar = calculaCorComplementar(corPreenchimento1);
                        setCorLinha(getLinhaFromForma(forma2), cor_complementar);
                        free(cor_complementar);
                        break;
                    }
                    case Tt:
                        setCorBTexto(getTextoFromForma(forma2), corPreenchimento1);
                        break;
                }
                
                free(corPreenchimento1);
                inFormaChao(chao, forma1);
                inFormaChao(chao, forma2);
                
                Forma clone = clonaFormaComCoresTrocadas(forma1);
                if (clone){
                    inFormaChao(chao, clone);
                    (*formasClonadas)++;
                }
              
                NoArena* proximo_par = atual->prox->prox;
                free(atual->prox);
                free(atual);
                atual = proximo_par;
                continue;
            }
        } else{
            inFormaChao(chao, forma1);
            inFormaChao(chao, forma2);
            NoArena* proximo_par = atual->prox->prox;
            free(atual->prox);
            free(atual);
            atual = proximo_par;
            continue;
        }
        atual = atual->prox;
    }

    if (atual != NULL){
        inFormaChao(chao, atual->forma);
        free(atual);
    }
    arena->inicio = NULL;
    arena->fim = NULL;
    arena->tamanho = 0;
}

int getNumFormasArena(Arena a){
    if (!a) return 0;
    ArenaStruct* arena = (ArenaStruct*)a;
    return arena->tamanho;
}

void liberaArena(Arena a){
    if (!a) return;
    ArenaStruct* arena = (ArenaStruct*)a;
    NoArena* atual = arena->inicio;
    
    while (atual != NULL){
        NoArena* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(arena);
}
