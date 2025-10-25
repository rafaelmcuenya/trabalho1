#ifndef CRIARSVG_H
#define CRIARSVG_H

#include "forma.h"
#include "chao.h"

/*
   Módulo responsável pela geração de arquivos SVG para visualização dos resultados, criando os desenhos nos formatos .svg.
*/

void svgGeo(const char* baseNome, Chao chao);
/*
   Gera um arquivo SVG com o estado atual do chão após processar um arquivo .geo.
*/

void svgQry(const char* baseNome, Chao chao);
/*
   Gera um arquivo SVG com o estado do sistema após processar um arquivo .qry.
*/

void svgAnotarDimensoesDisparo(double xOrigem, double yOrigem, double dx, double dy);
/*
   Adiciona anotações visuais no SVG atual representando o vetor de disparo.
*/

void svgAsteriscoEsmagada(double x, double y);
/*
   Marca uma posição no SVG com um asterisco vermelho, indicando onde uma forma foi esmagada, após a arena.
*/

#endif
