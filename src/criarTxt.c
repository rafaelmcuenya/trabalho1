#include "criarTxt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE* txtFile = NULL;

void iniciarTxt(const char* baseNome) {
    char filename[256];
    sprintf(filename, "%s.txt", baseNome);
    txtFile = fopen(filename, "w");
}

void fecharTxt() {
    if (txtFile) fclose(txtFile);
}

void txtLc(int idCarregador, int n) {
    if (!txtFile) return;
    fprintf(txtFile, "[*] lc %d %d\n", idCarregador, n);
}

void txtShift(Forma forma) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] shift\n");
    fprintf(txtFile, "Forma %d em posição de disparo\n", getIdForma(forma));
}

void txtDsp(Forma forma, double x, double y) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] dsp\n");
    fprintf(txtFile, "Forma %d disparada para (%.2f, %.2f)\n", getIdForma(forma), x, y);
}

void txtRjd(int sequencia, Forma forma, double x, double y) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "[*] rjd - Disparo %d\n", sequencia);
    fprintf(txtFile, "Forma %d para (%.2f, %.2f)\n", getIdForma(forma), x, y);
}

void txtCalcSobreposicao(Forma f1, Forma f2, int sobreposicao, const char* resultado) {
    if (!txtFile) return;
    fprintf(txtFile, "[*] calc\n");
    fprintf(txtFile, "Formas %d e %d - Sobreposição: %s\n%s\n", 
            getIdForma(f1), getIdForma(f2), sobreposicao ? "SIM" : "NÃO", resultado);
}

void txtCalcEsmagada(Forma forma) {
    if (!txtFile || !forma) return;
    fprintf(txtFile, "Forma %d esmagada\n", getIdForma(forma));
}

void txtCalcClonada(Forma original, Forma clone) {
    if (!txtFile) return;
    fprintf(txtFile, "Forma %d clonada -> %d\n", getIdForma(original), getIdForma(clone));
}

void txtFinal(double pontuacao, int instrucoes, int disparos, int esmagadas, int clonadas) {
    if (!txtFile) return;
    fprintf(txtFile, "Pontuação final: %.2f\n", pontuacao);
    fprintf(txtFile, "Total de instruções: %d\n", instrucoes);
    fprintf(txtFile, "Total de disparos: %d\n", disparos);
    fprintf(txtFile, "Formas esmagadas: %d\n", esmagadas);
    fprintf(txtFile, "Formas clonadas: %d\n", clonadas);
}
