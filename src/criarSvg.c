#include "criarSvg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static FILE* svgFile = NULL;

static void iniciarSvg(const char* filename) {
    svgFile = fopen(filename, "w");
    if (!svgFile) return;
    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

static void finalizarSvg() {
    if (!svgFile) return;
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
}

static void adicionarFormaSvg(Forma f) {
    if (!svgFile || !f) return;
    //falta coisa ainda
}

void svgGeo(const char* baseNome, Chao chao) {
    char filename[256];
    sprintf(filename, "%s.svg", baseNome);
    iniciarSvg(filename);
    //falta coisa ainda
    finalizarSvg();
}

void svgQry(const char* baseNome, Chao chao) {
    char filename[256];
    sprintf(filename, "%s-consulta.svg", baseNome);
    iniciarSvg(filename);
    //falta coisa ainda
    finalizarSvg();
}

void svgAnotarDimensoesDisparo(double xOrigem, double yOrigem, double dx, double dy) {
    if (!svgFile) return;
    double xDestino = xOrigem + dx;
    double yDestino = yOrigem + dy;

    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
            "stroke=\"blue\" stroke-dasharray=\"5,5\" stroke-width=\"1\"/>\n",
            xOrigem, yOrigem, xDestino, yDestino);
    
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"3\" fill=\"blue\">"
            "dx=%.2f dy=%.2f</text>\n",
            (xOrigem + xDestino)/2, (yOrigem + yDestino)/2 - 5, dx, dy);
}

void svgAsteriscoEsmagada(double x, double y) {
    if (!svgFile) return;
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"8\" fill=\"red\">*</text>\n", 
            x, y);
}
