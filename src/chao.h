#ifndef CHAO_H
#define CHAO_H

#include <stdio.h>
#include "forma.h"

/*
   O chão se trata de um local onde as formas lidas a partir do .geo serão criadas e armazenadas. Será do chão que os carregadores retirarão as formas, e também para onde as formas restantes após a arena retornarão, além do local onde as formas recém criadas, sejam elas pelo .geo ou clonadas, irão ser colocadas.
*/

typedef void* Chao;

Chao criaChao();
/*
Cria um novo chão vazio.
*/

void insereFormaChao(Chao c, Forma f);
/*
Adiciona uma forma no final do chão.
*/

Forma retiraFormaChao(Chao c);
/*
Remove e retorna a primeira forma do chão.
*/

Forma consultaPrimeiraFormaChao(Chao c);
/*
Retorna, sem remover, a primeira forma do chão.
*/

int estaVazioChao(Chao c);
/*
Verifica se o chão está vazio.
*/

void liberaChao(Chao c);
/*
Libera toda a memória do chão.
*/

#endif
