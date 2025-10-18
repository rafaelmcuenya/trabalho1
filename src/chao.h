#ifndef CHAO_H
#define CHAO_H

#include <stdio.h>
#include "forma.h"

/*
   O chão se trata de um local onde as formas lidas a partir do .geo serC#o criadas e armazenadas.
    Será do chC#o que os carregadores retirarC#o as formas, e também para onde as formas restantes após a arena retornarão, além do local onde as formas recém criadas, sejam elas pelo .geo ou clonadas, irão ser colocadas.
*/

typedef void* Chao;

Chao criaChao();
/*
Cria um novo chC#o vazio.
*/

void insereFormaChao(Chao c, Forma f);
/*
Adiciona uma forma no final do chC#o.
*/

Forma retiraFormaChao(Chao c);
/*
Remove e retorna a primeira forma do chC#o.
*/

Forma consultaPrimeiraFormaChao(Chao c);
/*
Retorna, sem remover, a primeira forma do chC#o.
*/

int estaVazioChao(Chao c);
/*
Verifica se o chC#o estC! vazio.
*/

void liberaChao(Chao c);
/*
Libera toda a memC3ria do chC#o.
*/

#endif
