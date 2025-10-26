#ifndef ARENA_H
#define ARENA_H

#include "forma.h"
#include "chao.h"

/*
   A arena é o local onde as formas disparadas pelos disparadores são depositadas e onde ocorre o processo de sobreposição, caso houver um. 
   Qualquer forma restante após o término das sobreposições e disparos retorna para o chão, na ordem que foram disparadas.
*/

typedef void* Arena;

Arena criaArena();
/*
   Cria uma nova arena vazia.
   Retorna um ponteiro para a arena criada ou NULL em caso de falha.
*/

void insereFormaArena(Arena a, Forma f);
/*
   Insere uma forma na arena para processamento posterior. As formas são armazenadas na ordem de inserção para processamento em pares.
*/

void processaArena(Arena a, Chao chao, double* pontuacaoTotal, int* formasEsmagadas, int* formasClonadas, const char* nomeBase, const char* outputDir);
/*
   Processa todas as formas na arena em pares sequenciais, aplicando as regras do jogo.
*/

void desenharArenaSVG(Arena a, const char* filename);
/*
   Gera um arquivo SVG com o estado atual da arena
*/

int getNumFormasArena(Arena a);
/*
   Retorna o número de formas atualmente na arena.
*/

void percorreArena(Arena arena, FILE* svgFile, void (*callback)(FILE*, Forma));
/*
  Percorre a arena forma por forma.
*/

void liberaArena(Arena a);
/*
   Libera toda a memória associada à arena.
   ATENÇÃO: Esta função NÃO libera as formas contidas na arena.
*/

#endif
