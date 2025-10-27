#include "trataNomeArquivo.h"
#include <sys/stat.h>

void extrairNomeBase(const char* caminhoCompleto, char* nomeBase){
    if (!caminhoCompleto || !nomeBase) return;
    
    const char* ultimaBarra = strrchr(caminhoCompleto, '/');
    const char* inicioNome = (ultimaBarra != NULL) ? ultimaBarra + 1 : caminhoCompleto;
    
    strcpy(nomeBase, inicioNome);
    
    char* ponto = strrchr(nomeBase, '.');
    if (ponto != NULL){
        *ponto = '\0';
    }
}

void gerarNomeGeoSvg(const char* nomeBase, const char* outputDir, char* caminhoCompleto){
    if (!nomeBase || !outputDir || !caminhoCompleto) return;
    
    if (strlen(outputDir) > 0){
        snprintf(caminhoCompleto, PATH_LEN, "%s/%s.svg", outputDir, nomeBase);
    } else{
        snprintf(caminhoCompleto, PATH_LEN, "%s.svg", nomeBase);
    }
}

void gerarNomeQrySvg(const char* nomeBase, const char* outputDir, char* caminhoCompleto){
    if (!nomeBase || !outputDir || !caminhoCompleto) return;
    
    if (strlen(outputDir) > 0){
        snprintf(caminhoCompleto, PATH_LEN, "%s/%s-consulta.svg", outputDir, nomeBase);
    } else{
        snprintf(caminhoCompleto, PATH_LEN, "%s-consulta.svg", nomeBase);
    }
}

void gerarNomeTxt(const char* nomeBase, const char* outputDir, char* caminhoCompleto){
    if (!nomeBase || !outputDir || !caminhoCompleto) return;
    
    if (strlen(outputDir) > 0){
        snprintf(caminhoCompleto, PATH_LEN, "%s/%s.txt", outputDir, nomeBase);
    } else{
        snprintf(caminhoCompleto, PATH_LEN, "%s.txt", nomeBase);
    }
}

void gerarNomeArenaSVG(const char* nomeBase, const char* sufixo, const char* outputDir, char* caminhoCompleto){
    if (!nomeBase || !sufixo || !outputDir || !caminhoCompleto) return;
    
    if (strlen(outputDir) > 0){
        snprintf(caminhoCompleto, PATH_LEN, "%s/%s-arena-%s.svg", outputDir, nomeBase, sufixo);
    } else{
        snprintf(caminhoCompleto, PATH_LEN, "%s-arena-%s.svg", nomeBase, sufixo);
    }
}

int criarDiretorioSeNecessario(const char* caminho){
    if (!caminho) return 0;
    
    char dir[PATH_LEN];
    strcpy(dir, caminho);
    
    char* ultimaBarra = strrchr(dir, '/');
    if (ultimaBarra != NULL){
        *ultimaBarra = '\0';
    }
    
    if (strlen(dir) == 0){
        return 1;
    }
    
    struct stat st ={0};
    if (stat(dir, &st) == -1){
        #ifdef _WIN32
            return mkdir(dir);
        #else
            return mkdir(dir, 0700);
        #endif
    }
    
    return 1;
}
