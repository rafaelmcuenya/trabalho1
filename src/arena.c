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
#include "strdupi.h"
#include "criarSvg.h"
#include "trataNomeArquivo.h"

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
    if (!cor || strlen(cor) != 6) return strdupi("000000");
    
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
            clone = criaForma(Tc, criaCirculo(id + 1000, x, y, raio, corP, corB));
            break;
        }
        case Tr:{
            double largura = getLarguraRetangulo(getRetanguloFromForma(original));
            double altura = getAlturaRetangulo(getRetanguloFromForma(original));
            clone = criaForma(Tr, criaRetangulo(id + 1000, x, y, largura, altura, corP, corB));
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

void desenharArenaSVG(Arena a, const char* filename) {
    if (!a || !filename) return;
    
    FILE* svgFile = fopen(filename, "w");
    if (!svgFile) return;
    
    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    
    ArenaStruct* arena = (ArenaStruct*)a;
    NoArena* atual = arena->inicio;
    
    while (atual != NULL) {
        Forma f = atual->forma;
        if (f) {
            TipoForma tipo = getTipoForma(f);
            switch(tipo) {
                case Tr: {
                    Retangulo r = getRetanguloFromForma(f);
                    double x = getXRetangulo(r);
                    double y = getYRetangulo(r);
                    double w = getLarguraRetangulo(r);
                    double h = getAlturaRetangulo(r);
                    char* corP = getCorPRetangulo(r);
                    char* corB = getCorBRetangulo(r);
                    
                    fprintf(svgFile, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n",
                           x, y, w, h, corP, corB);
                    free(corP);
                    free(corB);
                    break;
                }
                case Tc: {
                    Circulo c = getCirculoFromForma(f);
                    double x = getXCirculo(c);
                    double y = getYCirculo(c);
                    double r = getRaioCirculo(c);
                    char* corP = getCorPCirculo(c);
                    char* corB = getCorBCirculo(c);
                    
                    fprintf(svgFile, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n",
                           x, y, r, corP, corB);
                    free(corP);
                    free(corB);
                    break;
                }
                case Tl: {
                    Linha l = getLinhaFromForma(f);
                    double x1 = getX1Linha(l);
                    double y1 = getY1Linha(l);
                    double x2 = getX2Linha(l);
                    double y2 = getY2Linha(l);
                    char* cor = getCorLinha(l);
                    
                    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"#%s\" stroke-width=\"1\" stroke-opacity=\"0.5\"/>\n",
                           x1, y1, x2, y2, cor);
                    free(cor);
                    break;
                }
                case Tt: {
                    Texto t = getTextoFromForma(f);
                    double x = getXTexto(t);
                    double y = getYTexto(t);
                    char* texto = getTexto(t);
                    char* corP = getCorPTexto(t);
                    char* corB = getCorBTexto(t);
                    
                    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"0.5\" fill-opacity=\"0.5\" stroke-opacity=\"0.5\">%s</text>\n",
                           x, y, corP, corB, texto);
                    free(texto);
                    free(corP);
                    free(corB);
                    break;
                }
            }
        }
        atual = atual->prox;
    }
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
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

void processaArena(Arena a, Chao chao, double* pontuacaoTotal, int* formasEsmagadas, int* formasClonadas, const char* nomeBase){
    if (!a || !chao) return;
    ArenaStruct* arena = (ArenaStruct*)a;

    if (nomeBase) {
        char nomeAntes[256];
        snprintf(nomeAntes, sizeof(nomeAntes), "%s-arena-antes.svg", nomeBase);
        desenharArenaSVG(a, nomeAntes);
        printf("[SVG] Arena antes do processamento: %s\n", nomeAntes);
    }
    
    NoArena* atual = arena->inicio;
    NoArena* anterior = NULL;
    
    while (atual != NULL && atual->prox != NULL){
        Forma forma1 = atual->forma;
        Forma forma2 = atual->prox->forma;
        
        int sobreposicao = formasSobrepoem(forma1, forma2);
        double area1 = areaForma(forma1);
        double area2 = areaForma(forma2);
        
        NoArena* proximo = atual->prox->prox;
        
        if (sobreposicao){
            if (area1 < area2){
                *pontuacaoTotal += area1;
                (*formasEsmagadas)++;
                
                freeForma(forma1);
                inFormaChao(chao, forma2);
                
                if (anterior == NULL){
                    arena->inicio = proximo;
                } else{
                    anterior->prox = proximo;
                }
                
                if (atual->prox == arena->fim){
                    arena->fim = anterior;
                }
                
                free(atual->prox);
                free(atual);
                arena->tamanho -= 2;
                atual = proximo;
                
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
                
                if (anterior == NULL){
                    arena->inicio = proximo;
                } else{
                    anterior->prox = proximo;
                }
                
                if (atual->prox == arena->fim){
                    arena->fim = anterior;
                }
                
                free(atual->prox);
                free(atual);
                arena->tamanho -= 2;
                atual = proximo;
            }
        } else{
            inFormaChao(chao, forma1);
            inFormaChao(chao, forma2);
            
            if (anterior == NULL){
                arena->inicio = proximo;
            } else{
                anterior->prox = proximo;
            }
            
            if (atual->prox == arena->fim){
                arena->fim = anterior;
            }
            
            free(atual->prox);
            free(atual);
            arena->tamanho -= 2;
            atual = proximo;
        }
    }
    if (atual != NULL){
        inFormaChao(chao, atual->forma);
        
        if (anterior == NULL){
            arena->inicio = NULL;
        } else{
            anterior->prox = NULL;
        }
        arena->fim = anterior;
        
        free(atual);
        arena->tamanho--;
    }

    if (nomeBase) {
        char nomeDepois[256];
        snprintf(nomeDepois, sizeof(nomeDepois), "%s-arena-depois.svg", nomeBase);
        desenharArenaSVG(a, nomeDepois);
        printf("[SVG] Arena depois do processamento: %s\n", nomeDepois);
    }
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
        if (atual->forma) {
            freeForma(atual->forma);
        }
        free(atual);
        atual = prox;
    }
    free(arena);
}
