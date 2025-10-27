#include "criarSvg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "strdupi.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "arena.h"  

void adicionarFormaSvg(FILE* svgFile, Forma f){
    if (!svgFile || !f) return;
    
    TipoForma tipo = getTipoForma(f);
    switch(tipo){
        case Tr:{ 
            Retangulo r = getRetanguloFromForma(f);
            double x = getXRetangulo(r);
            double y = getYRetangulo(r);
            double w = getLarguraRetangulo(r);
            double h = getAlturaRetangulo(r);
            char* corP = getCorPRetangulo(r);
            char* corB = getCorBRetangulo(r);
            
            fprintf(svgFile, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n", x, y, w, h, corP, corB);
            free(corP);
            free(corB);
            break;
        }
        case Tc:{  
            Circulo c = getCirculoFromForma(f);
            double x = getXCirculo(c);
            double y = getYCirculo(c);
            double r = getRaioCirculo(c);
            char* corP = getCorPCirculo(c);
            char* corB = getCorBCirculo(c);
            
            fprintf(svgFile, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n", x, y, r, corP, corB);
            free(corP);
            free(corB);
            break;
        }
        case Tl:{  
            Linha l = getLinhaFromForma(f);
            double x1 = getX1Linha(l);
            double y1 = getY1Linha(l);
            double x2 = getX2Linha(l);
            double y2 = getY2Linha(l);
            char* cor = getCorLinha(l);
            
            fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"#%s\" stroke-width=\"1\" stroke-opacity=\"0.5\"/>\n", x1, y1, x2, y2, cor);
            free(cor);
            break;
        }
        case Tt:{  
            Texto t = getTextoFromForma(f);
            double x = getXTexto(t);
            double y = getYTexto(t);
            char* texto = getTexto(t);
            char* corP = getCorPTexto(t);
            char* corB = getCorBTexto(t);
            
            fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" fill=\"#%s\" stroke=\"#%s\" stroke-width=\"0.5\" fill-opacity=\"0.5\" stroke-opacity=\"0.5\">%s</text>\n", x, y, corP, corB, texto);
            free(texto);
            free(corP);
            free(corB);
            break;
        }
    }
}

void svgArena(const char* caminhoCompleto, Arena arena){
    if (!arena){
        printf("[ERRO] Arena NULL em svgArena\n");
        return;
    }
    
    FILE* svgFile = fopen(caminhoCompleto, "w");
    if (!svgFile){
        printf("[ERRO] Não foi possível criar arquivo SVG da arena: %s\n", caminhoCompleto);
        return;
    }
    
    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    
    printf("[DEBUG] Gerando SVG da arena com formas...\n");
    percorreArena(arena, svgFile, adicionarFormaSvg);
    
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
    printf("[SVG] Arquivo da arena gerado: %s\n", caminhoCompleto);
}

void svgGeo(const char* caminhoCompleto, Chao chao){
    FILE* svgFile = fopen(caminhoCompleto, "w");
    if (!svgFile) return;
    
    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    
    if (chao){
        percorreChaoComFile(chao, svgFile, adicionarFormaSvg);
    }
    
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
}

void svgQry(const char* caminhoCompleto, Chao chao){
    FILE* svgFile = fopen(caminhoCompleto, "w");
    if (!svgFile) return;
    
    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    
    if (chao){
        percorreChaoComFile(chao, svgFile, adicionarFormaSvg);
    }
    
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
}

void svgAnotarDimensoesDisparo(FILE* svgFile, double xOrigem, double yOrigem, double dx, double dy){
    if (!svgFile) return;
    
    double xDestino = xOrigem + dx;
    double yDestino = yOrigem + dy;

    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"blue\" stroke-dasharray=\"5,5\" stroke-width=\"1\"/>\n", 
            xOrigem, yOrigem, xDestino, yDestino);
    
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"3\" fill=\"blue\">dx=%.2f dy=%.2f</text>\n", 
            (xOrigem + xDestino)/2, (yOrigem + yDestino)/2 - 5, dx, dy);
}

void svgAsteriscoEsmagada(FILE* svgFile, double x, double y){
    if (!svgFile){
        printf("[ERRO] SVG file NULL em svgAsteriscoEsmagada\n");
        return;
    }
    
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"8\" fill=\"red\">*</text>\n", x, y);
    printf("[DEBUG] Asterisco desenhado em (%.2f, %.2f)\n", x, y);
}
