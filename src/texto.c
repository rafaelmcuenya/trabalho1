#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "texto.h"

typedef struct{
    int id;
    double x, y;
    char* corBorda;
    char* corPreenchimento;
    char ancora; 
    char* texto;
    char* fontFamily;    
    char* fontWeight;    
    double fontSize;     
}TextoStruct;

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
    txt->corBorda = strdup(corBorda);
    txt->corPreenchimento = strdup(corPreenchimento);
    txt->texto = strdup(texto);
    
    if (!txt->corBorda || !txt->corPreenchimento || !txt->texto){
        fprintf(stderr, "Erro: falha na alocação de strings\n");
        if (txt->corBorda) free(txt->corBorda);
        if (txt->corPreenchimento) free(txt->corPreenchimento);
        if (txt->texto) free(txt->texto);
        free(txt);
        return NULL;
    }

    txt->fontFamily = strdup("sans");
    txt->fontWeight = strdup("n");
    txt->fontSize = 12.0; 
    
    if (!txt->fontFamily || !txt->fontWeight){
        fprintf(stderr, "Erro: falha na alocação de estilo\n");
        liberaTexto(txt);
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
    
    char* copia = strdup(txt->texto);
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

TipoForma getTipo(Texto t){
    (void)t;
    return Tt;
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
    
    char* copia = strdup(txt->corBorda);
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
    
    char* copia = strdup(txt->corPreenchimento);
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
    
    txt->fontFamily = strdup(fontFamily);
    txt->fontWeight = strdup(fontWeight);
    txt->fontSize = fontSize;
    
    if (!txt->fontFamily || !txt->fontWeight){
        fprintf(stderr, "Erro: falha na alocação de estilo\n");
        txt->fontFamily = strdup("sans");
        txt->fontWeight = strdup("n");
        txt->fontSize = 12.0;
    }
}

char* getFontFamilyTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getFontFamilyTexto\n");
        return NULL;
    }
    TextoStruct* txt = (TextoStruct*)t;
    
    char* copia = strdup(txt->fontFamily);
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
    
    char* copia = strdup(txt->fontWeight);
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
           (txt->corBorda != NULL) && (txt->corPreenchimento != NULL) &&  (txt->texto != NULL) && 
           (txt->ancora == 'i' || txt->ancora == 'm' || txt->ancora == 'f') &&
           (txt->fontFamily != NULL) && (txt->fontWeight != NULL) && (txt->fontSize > 0);
}

void setCorBTexto(Texto t, char* novaCor){
    if (!t || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorBTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    free(txt->corBorda);
    txt->corBorda = strdup(novaCor);
}

void setCorPTexto(Texto t, char* novaCor){
    if (!t || !novaCor){
        fprintf(stderr, "Erro: parâmetros inválidos em setCorPTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    free(txt->corPreenchimento);
    txt->corPreenchimento = strdup(novaCor);
}

void liberaTexto(Texto t){
    if (!t) return;
    TextoStruct* txt = (TextoStruct*)t;
    
    if (txt->corBorda) free(txt->corBorda);
    if (txt->corPreenchimento) free(txt->corPreenchimento);
    if (txt->texto) free(txt->texto);
    if (txt->fontFamily) free(txt->fontFamily);
    if (txt->fontWeight) free(txt->fontWeight);
    
    free(txt);
}
