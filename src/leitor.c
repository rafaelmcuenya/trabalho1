#include "leitor.h"
#include <string.h>
#include <ctype.h>

void abrirArquivo(FILE **f, char *caminho) {
    *f = fopen(caminho, "r");
    if (!(*f)) {
        fprintf(stderr, "Erro: Não foi possível abrir %s\n", caminho);
        exit(1);
    }
}

void processarComando(const char* linha, int ehQry, const char* nomeBase) {
    if (linha[0] == '\n' || linha[0] == '#' || linha[0] == '\0') return;
    
    char comando[10];
    sscanf(linha, "%s", comando);
    
    if (!ehQry) {
        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; char corb[32], corp[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &id, &x, &y, &r, corb, corp) == 6) {
                cmdCriaCircle(id, x, y, r, corb, corp);
            }
        }
        else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[32], corp[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &id, &x, &y, &w, &h, corb, corp) == 7) {
                cmdCriaRet(id, x, y, w, h, corb, corp);
            }
        }
        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &id, &x1, &y1, &x2, &y2, cor) == 6) {
                cmdCriaLinha(id, x1, y1, x2, y2, cor);
            }
        }
        else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char corb[32], corp[32], anchor, texto[256];
            if (sscanf(linha, "%*s %d %lf %lf %31s %31s %c %255[^\n]", &id, &x, &y, corb, corp, &anchor, texto) == 7) {
                cmdCriaTexto(id, x, y, corb, corp, anchor, texto);
            }
        }
        else if (strcmp(comando, "ts") == 0) {
            char family[32], weight[8]; double size;
            if (sscanf(linha, "%*s %31s %7s %lf", family, weight, &size) == 3) {
                cmdTextoStyle(family, weight, size);
            }
        }
    } else {
        if (strcmp(comando, "pd") == 0) {
            int id; double x, y;
            if (sscanf(linha, "%*s %d %lf %lf", &id, &x, &y) == 3) {
                cmdPD(id, x, y);
            }
        }
        else if (strcmp(comando, "lc") == 0) {
            int id, n;
            if (sscanf(linha, "%*s %d %d", &id, &n) == 2) {
                cmdLC(id, n);
            }
        }
        else if (strcmp(comando, "atch") == 0) {
            int disp, esq, dir;
            if (sscanf(linha, "%*s %d %d %d", &disp, &esq, &dir) == 3) {
                cmdATCH(disp, esq, dir);
            }
        }
        else if (strcmp(comando, "shft") == 0) {
            int disp, n; char lado;
            if (sscanf(linha, "%*s %d %c %d", &disp, &lado, &n) == 3) {
                cmdSHFT(disp, lado, n);
            }
        }
        else if (strcmp(comando, "dsp") == 0) {
            int disp; double dx, dy; char flag[2];
            int res = sscanf(linha, "%*s %d %lf %lf %1s", &disp, &dx, &dy, flag);
            cmdDSP(disp, dx, dy, (res == 4 && strcmp(flag, "v") == 0));
        }
        else if (strcmp(comando, "rjd") == 0) {
            int disp; double dx, dy, ix, iy;
            if (sscanf(linha, "%*s %d %lf %lf %lf %lf", &disp, &dx, &dy, &ix, &iy) == 5) {
                cmdRJD(disp, dx, dy, ix, iy);
            }
        }
        else if (strcmp(comando, "calc") == 0) {
            cmdCALC();
        }
    }
}

void processarArquivo(const char* caminho, int ehQry, const char* nomeBase) {
    FILE *f;
    abrirArquivo(&f, caminho);
    
    if (ehQry) {
        iniciarTxt(nomeBase);
    }
    
    char linha[1024];
    while (fgets(linha, sizeof(linha), f)) {
        processarComando(linha, ehQry, nomeBase);
    }
    
    if (ehQry) {
        txtFinal(getPontuacaoFinal(), getTotalInstrucoes(), getTotalDisparos(), getTotalEsmagadas(), getTotalClonadas());
        fecharTxt();
    }
    fclose(f);
}


