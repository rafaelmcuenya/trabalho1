#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "texto.h"
#include "strdupi.h"

typedef struct{
    int id;
    double x, y;
    char corBorda[8];
    char corPreenchimento[8];
    char ancora; 
    char* texto;
    char* fontFamily;    
    char* fontWeight;    
    double fontSize;     
}TextoStruct;

static void preencherCor(char* dest, const char* fonte, const char* corPadrao){
    if (fonte && strlen(fonte) > 0){
        const char* cor = (fonte[0] == '#') ? fonte + 1 : fonte;
        int len = strlen(cor);
        
        if (len == 6){
            strncpy(dest, cor, 6);
        } else if (len < 6){
            int zeros = 6 - len;
            for (int i = 0; i < zeros; i++){
                dest[i] = '0';
            }
            strncpy(dest + zeros, cor, len);
        } else{
            strncpy(dest, cor, 6);
        }
        dest[6] = '\0';
    } else{
        strcpy(dest, corPadrao);
    }
}

Texto criaTexto(int id, double x, double y, char* corBorda, char* corPreenchimento, char ancora, char* texto){
    if (id <= 0){
        fprintf(stderr, "Erro: ID do texto inválido\n");
        return NULL;
    }
    
    if (!corBorda || !corPreenchimento || !texto){
        fprintf(stderr, "Erro: parâmetro(s) inválido(s)\n");
        return NULL;
    }
    
    if (strlen(texto) == 0){
        fprintf(stderr, "Erro: texto não pode ser vazio\n");
        return NULL;
    }
  
    if (ancora != 'i' && ancora != 'm' && ancora != 'f'){
        fprintf(stderr, "Erro: âncora inválida.\n");
        return NULL;
    }
  
    if (x != x || y != y){ 
        fprintf(stderr, "Erro: coordenada(s) inválida(s)\n");
        return NULL;
    }
    
    TextoStruct* txt = (TextoStruct*)malloc(sizeof(TextoStruct));
    if (!txt){
        fprintf(stderr, "Erro: falha na alocação de texto\n");
        return NULL;
    }
    
    txt->id = id;
    txt->x = x;
    txt->y = y;
    txt->ancora = ancora;
    
    preencherCor(txt->corBorda, corBorda, "000000");
    preencherCor(txt->corPreenchimento, corPreenchimento, "FFFFFF");
    txt->texto = strdupi(texto);
    
    if (!txt->texto){
        fprintf(stderr, "Erro: falha na alocação do texto\n");
        free(txt);
        return NULL;
    }

    txt->fontFamily = strdupi("sans");
    txt->fontWeight = strdupi("n");
    txt->fontSize = 12.0; 
    
    if (!txt->fontFamily || !txt->fontWeight){
        fprintf(stderr, "Erro: falha na alocação de estilo\n");
        if (txt->fontFamily) free(txt->fontFamily);
        if (txt->fontWeight) free(txt->fontWeight);
        if (txt->texto) free(txt->texto);
        free(txt);
        return NULL;
    }
    return txt;
}

double areaTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em areaTexto\n");
        return -1.0;
    }
    
    TextoStruct* txt = (TextoStruct*)t;
    if (!txt->texto){
        fprintf(stderr, "Erro: string de texto NULL em areaTexto\n");
        return -1.0;
    }
    return 20.0 * strlen(txt->texto);
}

int idTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em idTexto\n");
        return -1;
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->id;
}

void moveTexto(Texto t, double dx, double dy){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em moveTexto\n");
        return;
    }

    if (dx != dx || dy != dy || isinf(dx) || isinf(dy)){
        fprintf(stderr, "Erro: parâmetro(s) inválido(s) em moveTexto\n");
        return;
    }
    
    TextoStruct* txt = (TextoStruct*)t;
    txt->x += dx;
    txt->y += dy;
    
    if (txt->x != txt->x || txt->y != txt->y || isinf(txt->x) || isinf(txt->y)){
        fprintf(stderr, "Erro: coordenada(s) corrompida(s) após movimento\n");
        txt->x -= dx;
        txt->y -= dy;
    }
}

char* getTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdupi(txt->texto);
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da cópia do texto\n");
    }
    return copia;
}

char getAncoraTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getAncoraTexto\n");
        return '\0';
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->ancora;
}

double getXTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getXTexto\n");
        return -1.0;
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->x;
}

double getYTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getYTexto\n");
        return -1.0;
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->y;
}

char* getCorBTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getCorBTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdupi(txt->corBorda);
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da cor de borda\n");
    }
    return copia;
}

char* getCorPTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getCorPTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdupi(txt->corPreenchimento);
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da cor de preenchimento\n");
    }
    return copia;
}

void setAncoraTexto(Texto t, char ancora){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em setAncoraTexto\n");
        return;
    }

    if (ancora != 'i' && ancora != 'm' && ancora != 'f'){
        fprintf(stderr, "Erro: âncora inválida.\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    txt->ancora = ancora;
}

void aplicaStyleTexto(Texto t, char* fontFamily, char* fontWeight, double fontSize){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em aplicaStyleTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;

    if (!fontFamily || (strcmp(fontFamily, "sans") != 0 && strcmp(fontFamily, "serif") != 0 && strcmp(fontFamily, "cursive") != 0)){
        fprintf(stderr, "Erro: fontFamily inválida.\n");
        return;
    }
    
    if (!fontWeight || (strcmp(fontWeight, "n") != 0 &&  strcmp(fontWeight, "b") != 0 && strcmp(fontWeight, "b+") != 0 && strcmp(fontWeight, "l") != 0)){
        fprintf(stderr, "Erro: fontWeight inválido.\n");
        return;
    }
    
    if (fontSize <= 0 || fontSize != fontSize || isinf(fontSize)){
        fprintf(stderr, "Erro: fontSize inválido\n");
        return;
    }
    
    free(txt->fontFamily);
    free(txt->fontWeight);
    
    txt->fontFamily = strdupi(fontFamily);
    txt->fontWeight = strdupi(fontWeight);
    txt->fontSize = fontSize;
    
    if (!txt->fontFamily || !txt->fontWeight){
        fprintf(stderr, "Erro: falha na alocação de estilo\n");
        txt->fontFamily = strdupi("sans");
        txt->fontWeight = strdupi("n");
        txt->fontSize = 12.0;
    }
}

char* getFontFamilyTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getFontFamilyTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdupi(txt->fontFamily);
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da font family\n");
    }
    return copia;
}

char* getFontWeightTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getFontWeightTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdupi(txt->fontWeight);
    if (!copia){
        fprintf(stderr, "Erro: falha na alocação da font weight\n");
    }
    return copia;
}

double getFontSizeTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getFontSizeTexto\n");
        return -1.0;
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->fontSize;
}

int validaTexto(void* t){
    if (!t) return 0;
    TextoStruct* txt = (TextoStruct*)t;
    
    return (txt->id > 0) && 
           (txt->corBorda[0] != '\0') && (txt->corPreenchimento[0] != '\0') &&  (txt->texto != NULL) && 
           (txt->ancora == 'i' || txt->ancora == 'm' || txt->ancora == 'f') &&
           (txt->fontFamily != NULL) && (txt->fontWeight != NULL) && (txt->fontSize > 0);
}

void setCorBTexto(Texto t, char* novaCor){
    if (!t || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorBTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    preencherCor(txt->corBorda, novaCor, "000000");
}

void setCorPTexto(Texto t, char* novaCor){
    if (!t || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorPTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    preencherCor(txt->corPreenchimento, novaCor, "FFFFFF");
}

void liberaTexto(Texto t){
    if (!t) return;
    TextoStruct* txt = (TextoStruct*)t;
    
    if (txt->texto) free(txt->texto);
    if (txt->fontFamily) free(txt->fontFamily);
    if (txt->fontWeight) free(txt->fontWeight);
    
    free(txt);
}
