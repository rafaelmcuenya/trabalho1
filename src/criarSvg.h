#ifndef CRIARSVG_H
#define CRIARSVG_H

#include "forma.h"
#include "chao.h"
#include "arena.h"
#include <stdio.h>

/*
   Módulo responsável pela geração de arquivos SVG para visualização dos resultados, criando os desenhos nos formatos .svg.
*/

void svgGeo(const char* caminhoCompleto, Chao chao);
/*
   Gera um arquivo SVG com o estado atual do chão após processar um arquivo .geo.
*/

void svgQry(const char* caminhoCompleto, Chao chao);
/*
   Gera um arquivo SVG com o estado do sistema após processar um arquivo .qry.
*/

void svgArena(const char* caminhoCompleto, Arena arena);
/*
   Gera um arquivo SVG com o estado atual da arena.
*/

void svgAnotarDimensoesDisparo(FILE* svgFile, double xOrigem, double yOrigem, double dx, double dy);
/*
   Adiciona anotações visuais no SVG atual representando o vetor de disparo.
*/

void svgAsteriscoEsmagada(FILE* svgFile, double x, double y);
/*
   Marca uma posição no SVG com um asterisco vermelho, indicando onde uma forma foi esmagada, após a arena.
*/

void adicionarFormaSvg(FILE* svgFile, Forma f);
/*
   Adiciona uma forma ao arquivo SVG aberto.
*/

#endif
