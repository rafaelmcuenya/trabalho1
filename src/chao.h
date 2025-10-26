#ifndef CHAO_H
#define CHAO_H

#include "forma.h"
#include <stdio.h>

typedef void* Chao;

/*
   Módulo responsável por gerenciar o chão, que é uma coleção de formas.
*/

Chao criaChao(void);
/*
   Cria e retorna uma instância de chão vazia.
*/

void freeChao(Chao chao);
/*
   Libera toda a memória associada ao chão.
*/

void inFormaChao(Chao chao, Forma forma);
/*
   Insere uma forma no chão.
*/

Forma outFormaChao(Chao chao);
/*
   Remove e retorna uma forma do chão.
*/

int voidChao(Chao chao);
/*
   Retorna 1 se o chão estiver vazio, 0 caso contrário.
*/

void percorreChao(Chao chao, void (*func)(Forma));
/*
   Percorre todas as formas do chão aplicando a função func.
*/

void percorreChaoComFile(Chao chao, FILE* svgFile, void (*func)(FILE*, Forma));
/*
   Percorre todas as formas do chão aplicando a função func que recebe um FILE*.
*/

#endif
