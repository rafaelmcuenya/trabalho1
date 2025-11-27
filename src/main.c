#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdupi.h"
#include "trataNomeArquivo.h"

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

    if (outputDir) {
        criarDiretorioSeNecessario(outputDir);
    }

    char nomeBase[FILE_NAME_LEN];
    extrairNomeBase(geoFile, nomeBase);

    inicializarSistema();

    processarArquivo(geoFile, inputDir, 0, nomeBase, outputDir);

    if (qryFile) {
        processarArquivo(qryFile, inputDir, 1, nomeBase, outputDir);
    }

    finalizarSistema();

    return 0;
}
