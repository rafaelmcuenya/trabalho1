#ifndef CHAO_H
#define CHAO_H

#include <stdio.h>
#include "forma.h"

/*
   O chão se trata de um local onde as formas lidas a partir do .geo serão criadas e armazenadas. 
    Será do chão que os carregadores retirarão as formas, e também para onde as formas restantes após a arena retornarão, além do local onde as formas recém criadas, sejam elas pelo .geo ou clonadas, irão ser colocadas.
*/

typedef void* Chao;

Chao criaChao();
/*
Cria um novo chão vazio.
*/

void inFormaChao(Chao c, Forma f);
/*
Adiciona uma forma no final do chão.
*/

Forma outFormaChao(Chao c);
/*
Remove e retorna a primeira forma do chão.
*/

Forma seePFChao(Chao c);
/*
Retorna, sem remover, a primeira forma do chão.
*/

int voidChao(Chao c);
/*
Verifica se o chão está vazio.
*/

int tamChao(Chao c);
/*
Retorna o número de formas atualmente no chão.
*/

void freeChao(Chao c);
/*
Libera toda a memória do chão.
*/

#endif
