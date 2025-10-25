#include "comandos.h"
#include "forma.h"
#include "chao.h"
#include "disparador.h"
#include "carregador.h"
#include "arena.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "sobrepor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Chao chao = NULL;
static Arena arena = NULL;
static Disparador disparadores[100] = {0};
static Carregador carregadores[100] = {0};

static double pontuacaoFinal = 0.0;
static int totalInstrucoes = 0;
static int totalDisparos = 0;
static int totalEsmagadas = 0;
static int totalClonadas = 0;

static char currentFontFamily[32] = "sans";
static char currentFontWeight[8] = "n";
static double currentFontSize = 12.0;

void inicializarSistema(void) {
    chao = criaChao();
    arena = criaArena();
    printf("[SISTEMA] Sistema inicializado\n");
}

void finalizarSistema(void) {
    if (chao) freeChao(chao);
    if (arena) liberaArena(arena);
    
    for (int i = 0; i < 100; i++) {
        if (disparadores[i]) freeDisparador(disparadores[i]);
        if (carregadores[i]) freeCarregador(carregadores[i]);
    }
    printf("[SISTEMA] Sistema finalizado\n");
}

void cmdCriaCircle(int id, double x, double y, double r, char corb[], char corp[]) {
    totalInstrucoes++;
    Circulo circulo = criaCircle(id, x, y, r, corb, corp);
    if (circulo && chao) {
        Forma forma = criaForma(Tc, circulo);
        inFormaChao(chao, forma);
        printf("[GEO] Círculo %d criado em (%.2f, %.2f) raio %.2f\n", id, x, y, r);
    }
}

void cmdCriaRet(int id, double x, double y, double w, double h, char corb[], char corp[]) {
    totalInstrucoes++;
    Retangulo retangulo = criaRet(id, x, y, w, h, corb, corp);
    if (retangulo && chao) {
        Forma forma = criaForma(Tr, retangulo);
        inFormaChao(chao, forma);
        printf("[GEO] Retângulo %d criado em (%.2f, %.2f) dim %.2fx%.2f\n", id, x, y, w, h);
    }
}

void cmdCriaLinha(int id, double x1, double y1, double x2, double y2, char cor[]) {
    totalInstrucoes++;
    Linha linha = criaLinha(id, x1, y1, x2, y2, cor);
    if (linha && chao) {
        Forma forma = criaForma(Tl, linha);
        inFormaChao(chao, forma);
        printf("[GEO] Linha %d criada de (%.2f,%.2f) até (%.2f,%.2f)\n", id, x1, y1, x2, y2);
    }
}

void cmdCriaTexto(int id, double x, double y, char corb[], char corp[], char anchor, char texto[]) {
    totalInstrucoes++;
    Texto textoObj = criaTexto(id, x, y, corb, corp, anchor, texto);
    if (textoObj && chao) {
        aplicaStyleTexto(textoObj, currentFontFamily, currentFontWeight, currentFontSize);
        Forma forma = criaForma(Tt, textoObj);
        inFormaChao(chao, forma);
        printf("[GEO] Texto %d: '%s' em (%.2f,%.2f) anchor=%c\n", id, texto, x, y, anchor);
    }
}

void cmdTextoStyle(char family[], char weight[], double size) {
    totalInstrucoes++;
    strcpy(currentFontFamily, family);
    strcpy(currentFontWeight, weight);
    currentFontSize = size;
    printf("[GEO] Estilo texto: family=%s weight=%s size=%.1f\n", family, weight, size);
}

void cmdPD(int idDisp, double x, double y) {
    totalInstrucoes++;
    if (idDisp >= 0 && idDisp < 100) {
        disparadores[idDisp] = criaDisparador(idDisp, x, y);
        printf("[QRY] Disparador %d posicionado em (%.2f, %.2f)\n", idDisp, x, y);
    }
}

void cmdATCH(int idDisp, int idCesq, int idCdir) {
    totalInstrucoes++;
    if (disparadores[idDisp] && carregadores[idCesq] && carregadores[idCdir]) {
        encaixaCarregadores(disparadores[idDisp], carregadores[idCesq], carregadores[idCdir]);
        printf("[QRY] Disparador %d: carregadores %d(esq) e %d(dir) encaixados\n", 
               idDisp, idCesq, idCdir);
    } else {
        printf("[ERRO] Disparador %d ou carregadores %d/%d não encontrados\n", 
               idDisp, idCesq, idCdir);
    }
}

void cmdLC(int idCarregador, int n) {
    totalInstrucoes++;
    if (idCarregador >= 0 && idCarregador < 100) {
        carregadores[idCarregador] = criaCarregador(idCarregador);
        if (chao && carregadores[idCarregador]) {
            for (int i = 0; i < n && !voidChao(chao); i++) {
                Forma forma = outFormaChao(chao);
                if (forma) {
                    empilhaCarregador(carregadores[idCarregador], forma);
                }
            }
            printf("[QRY] Carregador %d: %d formas carregadas do chão\n", idCarregador, n);
        }
    }
}

void cmdSHFT(int idDisp, char botao, int n) {
    totalInstrucoes++;
    if (disparadores[idDisp]) {
        shftDisparador(disparadores[idDisp], botao, n);
        Forma forma = getPosDisparo(disparadores[idDisp]);
        if (forma) {
            printf("[QRY] Shift %c: forma %d em posição de disparo\n", 
                   botao, getIdForma(forma));
        }
    }
}

void cmdDSP(int idDisp, double dx, double dy, bool svgFlag) {
    totalInstrucoes++;
    totalDisparos++;
    
    if (disparadores[idDisp] && arena) {
        Forma forma = disparaForma(disparadores[idDisp], dx, dy);
        if (forma) {
            insereFormaArena(arena, forma);
            printf("[QRY] Disparo: forma %d em arena com offset (%.2f,%.2f)\n", 
                   getIdForma(forma), dx, dy);
            
            if (svgFlag) {
                printf("[SVG] Anotar dimensões do disparo\n");
            }
        }
    }
}

void cmdRJD(int idDisp, double dx, double dy, double ix, double iy) {
    totalInstrucoes++;
    if (disparadores[idDisp] && arena) {
        printf("[QRY] Rajada no disparador %d\n", idDisp);
        
        int i = 0;
        Carregador carregador = (getPosDisparo(disparadores[idDisp])) ? 
                               carregadores[getIdCarregador(getPosDisparo(disparadores[idDisp]))] : NULL;
        
        while (carregador && !voidCarregador(carregador)) {
            shftDisparador(disparadores[idDisp], 'd', 1);
          
            double currentDx = dx + i * ix;
            double currentDy = dy + i * iy;
            Forma forma = disparaForma(disparadores[idDisp], currentDx, currentDy);
            
            if (forma) {
                insereFormaArena(arena, forma);
                printf("[QRY] Rajada %d: forma %d disparada\n", i, getIdForma(forma));
            }
            i++;
            totalDisparos++;
        }
    }
}

void cmdCALC(void) {
    totalInstrucoes++;
    if (arena) {
        printf("[QRY] Calculando sobreposições na arena...\n");
        
        double pontuacaoRound = 0.0;
        int esmagadasRound = 0;
        int clonadasRound = 0;
        
        processaArena(arena, chao, &pontuacaoRound, &esmagadasRound, &clonadasRound);
        
        pontuacaoFinal += pontuacaoRound;
        totalEsmagadas += esmagadasRound;
        totalClonadas += clonadasRound;
        
        printf("[CALC] Área esmagada neste round: %.2f\n", pontuacaoRound);
        printf("[CALC] Formas esmagadas: %d\n", esmagadasRound);
        printf("[CALC] Formas clonadas: %d\n", clonadasRound);
    }
}
double getPontuacaoFinal(void) { return pontuacaoFinal; }
int getTotalInstrucoes(void) { return totalInstrucoes; }
int getTotalDisparos(void) { return totalDisparos; }
int getTotalEsmagadas(void) { return totalEsmagadas; }
int getTotalClonadas(void) { return totalClonadas; }

void salvarSVG(const char* nomeArquivo, bool final) {
    printf("[SVG] Salvando arquivo %s (%s)\n", nomeArquivo, final ? "final" : "inicial");
    // continuar dps
}
