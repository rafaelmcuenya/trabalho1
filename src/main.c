#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdupi.h"

int main(int argc, char *argv[]) {
    char *geoFile = NULL;
    char *qryFile = NULL;
    char *outputDir = NULL;
    char *inputDir = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i+1 < argc) {
            geoFile = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i+1 < argc) {
            qryFile = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
            outputDir = argv[++i];
        } else if (strcmp(argv[i], "-e") == 0 && i+1 < argc) {
            inputDir = argv[++i];
        }
    }

    if (!geoFile) {
        fprintf(stderr, "Uso: %s -f <arquivo.geo> [-q <arquivo.qry>] -o <diretorio> [-e <diretorio>]\n", argv[0]);
        return 1;
    }

    inicializarSistema();

    processarArquivo(geoFile, 0, "saida");

    if (qryFile) {
        processarArquivo(qryFile, 1, "saida");
    }

    finalizarSistema();

    return 0;
}
