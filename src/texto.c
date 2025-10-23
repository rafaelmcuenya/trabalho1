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
        fprintf(stderr, "Erro: ID do texto deve ser positivo\n");
        return NULL;
    }
    
    if (!corBorda || !corPreenchimento || !texto){
        fprintf(stderr, "Erro: parâmetros string não podem ser NULL\n");
        return NULL;
    }
    
    if (strlen(texto) == 0){
        fprintf(stderr, "Erro: texto não pode ser vazio\n");
        return NULL;
    }
  
    if (ancora != 'i' && ancora != 'm' && ancora != 'f'){
        fprintf(stderr, "Erro: âncora inválida. Use 'i', 'm' ou 'f'\n");
        return NULL;
    }
  
    if (x != x || y != y){ 
        fprintf(stderr, "Erro: coordenadas inválidas\n");
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

char getAncoraTexto(Texto t){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em getAncoraTexto\n");
        return '\0';
    }
    TextoStruct* txt = (TextoStruct*)t;
    return txt->ancora;
}

void setAncoraTexto(Texto t, char ancora){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em setAncoraTexto\n");
        return;
    }

    if (ancora != 'i' && ancora != 'm' && ancora != 'f'){
        fprintf(stderr, "Erro: âncora inválida. Use 'i', 'm' ou 'f'\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;
    txt->ancora = ancora;
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

void moveTexto(Texto t, double dx, double dy){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em moveTexto\n");
        return;
    }

    if (dx != dx || dy != dy || isinf(dx) || isinf(dy)){
        fprintf(stderr, "Erro: deltas inválidos em moveTexto\n");
        return;
    }
    
    TextoStruct* txt = (TextoStruct*)t;
    txt->x += dx;
    txt->y += dy;
    
    if (txt->x != txt->x || txt->y != txt->y || isinf(txt->x) || isinf(txt->y)){
        fprintf(stderr, "Erro: coordenadas corrompidas após movimento\n");
        txt->x -= dx;
        txt->y -= dy;
    }
}

int colideTexto(Texto t, double x1, double y1, double x2, double y2){
    if (!t) return 0;
    
    TextoStruct* txt = (TextoStruct*)t;
    if (!txt->texto) return 0;
    
    double comprimento = 10.0 * strlen(txt->texto);
    double seg_x1, seg_y1, seg_x2, seg_y2;

    switch (txt->ancora){
        case 'i': 
            seg_x1 = txt->x;
            seg_y1 = txt->y;
            seg_x2 = txt->x + comprimento;
            seg_y2 = txt->y;
            break;
        case 'f': 
            seg_x1 = txt->x - comprimento;
            seg_y1 = txt->y;
            seg_x2 = txt->x;
            seg_y2 = txt->y;
            break;
        case 'm': 
            seg_x1 = txt->x - comprimento / 2.0;
            seg_y1 = txt->y;
            seg_x2 = txt->x + comprimento / 2.0;
            seg_y2 = txt->y;
            break;
        default:
            fprintf(stderr, "Erro: âncora desconhecida em colideTexto\n");
            return 0;
    }
    return detectaColisaoSegmentos(seg_x1, seg_y1, seg_x2, seg_y2, x1, y1, x2, y2);
}

void aplicaStyleTexto(Texto t, char* fontFamily, char* fontWeight, double fontSize){
    if (!t){
        fprintf(stderr, "Erro: texto NULL em aplicaStyleTexto\n");
        return;
    }
    TextoStruct* txt = (TextoStruct*)t;

    if (!fontFamily || (strcmp(fontFamily, "sans") != 0 && strcmp(fontFamily, "serif") != 0 && strcmp(fontFamily, "cursive") != 0)){
        fprintf(stderr, "Erro: fontFamily inválida. Use 'sans', 'serif' ou 'cursive'\n");
        return;
    }
    
    if (!fontWeight || (strcmp(fontWeight, "n") != 0 &&  strcmp(fontWeight, "b") != 0 && strcmp(fontWeight, "b+") != 0 && strcmp(fontWeight, "l") != 0)){
        fprintf(stderr, "Erro: fontWeight inválido. Use 'n', 'b', 'b+' ou 'l'\n");
        return;
    }
    
    if (fontSize <= 0 || fontSize != fontSize || isinf(fontSize)){
        fprintf(stderr, "Erro: fontSize deve ser positivo\n");
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

int validaTexto(void* t){
    if (!t) return 0;
    TextoStruct* txt = (TextoStruct*)t;
    
    return (txt->id > 0) && 
           (txt->corBorda != NULL) && (txt->corPreenchimento != NULL) &&  (txt->texto != NULL) && 
           (txt->ancora == 'i' || txt->ancora == 'm' || txt->ancora == 'f') &&(txt->fontFamily != NULL) && (txt->fontWeight != NULL) && (txt->fontSize > 0);
}
