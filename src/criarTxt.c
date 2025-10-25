#include "criarTxt.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdupi.h"

static FILE* txtFile = NULL;

void iniciarTxt(const char* baseNome) {
    char filename[256];
    sprintf(filename, "%s.txt", baseNome);
    txtFile = fopen(filename, "w");
}

void fecharTxt() {
    if (txtFile) fclose(txtFile);
}

char* getDescricaoDetalhada(Forma f) {
    char* desc = malloc(512);
    TipoForma tipo = getTipoForma(f);
    
    switch(tipo) {
        case Tc: {
            Circulo c = getCirculoFromForma(f);
            double raio = getRaioCirculo(c);
            char* corP = getCorPCirculo(c);
            char* corB = getCorBCirculo(c);
            sprintf(desc, "círculo\nâncora em (%.3f, %.3f)\nraio: %.2f\npreenchimento: %s\nborda: %s",
                   getXCirculo(c), getYCirculo(c), raio, corP, corB);
            free(corP);
            free(corB);
            break;
        }
        case Tr: {
            Retangulo r = getRetanguloFromForma(f);
            double w = getLarguraRetangulo(r);
            double h = getAlturaRetangulo(r);
            char* corP = getCorPRet(r);
            char* corB = getCorBRet(r);
            sprintf(desc, "retângulo\nâncora em (%.3f, %.3f)\nlargura: %.2f\naltura: %.2f\npreenchimento: %s\nborda: %s",
                   getXRet(r), getYRet(r), w, h, corP, corB);
            free(corP);
            free(corB);
            break;
        }
        case Tl: {
            Linha l = getLinhaFromForma(f);
            char* cor = getCorLinha(l);
            sprintf(desc, "linha\nextremidade1: (%.3f, %.3f)\nextremidade2: (%.3f, %.3f)\ncor: %s",
                   getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), cor);
            free(cor);
            break;
        }
        case Tt: {
            Texto t = getTextoFromForma(f);
            char* texto = getTexto(t);
            char* corP = getCorPTexto(t);
            char* corB = getCorBTexto(t);
            sprintf(desc, "texto\nâncora em (%.3f, %.3f)\nconteúdo: %s\npreenchimento: %s\nborda: %s",
                   getXTexto(t), getYTexto(t), texto, corP, corB);
            free(texto);
            free(corP);
            free(corB);
            break;
        }
    }
    return desc;
}

void txtLc(int idCarregador, Forma formas[], int count) {
    if (!txtFile) return;
    fprintf(txtFile, "[*] lc %d %d\n", idCarregador, count);
    for (int i = 0; i < count; i++) {
        char* desc = getDescricaoDetalhada(formas[i]);
        fprintf(txtFile, "%s\n", desc);
        free(desc);
    }
}

void txtShift(Forma forma) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] shift\n");
    char* desc = getDescricaoDetalhada(forma);
    fprintf(txtFile, "%s\n", desc);
    free(desc);
}

void txtDsp(Forma forma, double xFinal, double yFinal) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] dsp\n");
    char* desc = getDescricaoDetalhada(forma);
    fprintf(txtFile, "%s\nposição final: (%.2f, %.2f)\n", desc, xFinal, yFinal);
    free(desc);
}

void txtRjd(int sequencia, Forma forma, double xFinal, double yFinal) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] rjd - disparo %d\n", sequencia);
    char* desc = getDescricaoDetalhada(forma);
    fprintf(txtFile, "%s\nposição: (%.2f, %.2f)\n", desc, xFinal, yFinal);
    free(desc);
}

void txtCalcResultado(const char* resultado) {
    if (!txtFile) return;
    fprintf(txtFile, "[*] calc\n%s\n", resultado);
}

void txtCalcAreaEsmagada(double area) {
    if (!txtFile) return;
    fprintf(txtFile, "Área total esmagada no round: %.2f\n", area);
}

void txtFinal(double pontuacao, int instrucoes, int disparos, int esmagadas, int clonadas) {
    if (!txtFile) return;
    fprintf(txtFile, "Pontuação final: %.2f\n", pontuacao);
    fprintf(txtFile, "Número total de instruções executadas: %d\n", instrucoes);
    fprintf(txtFile, "Número total de disparos: %d\n", disparos);
    fprintf(txtFile, "Número total de formas esmagadas: %d\n", esmagadas);
    fprintf(txtFile, "Número total de formas clonadas: %d\n", clonadas);
}
