#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <stdio.h>
#include "forma.h"

/* 
  Carregadores são locais cuja função é armazenar formas do chão e repassá-las para um disparador na qual eles estejam conectados.
*/

typedef void* Carregador;

Carregador criaCarregador(int id);
/*
   Cria um novo carregador vazio com o ID especificado. Retorna um ponteiro para o carregador criado ou NULL em caso de falha.
*/

void inicializaCarregador(Carregador car, int id);
/*
   Inicializa um carregador com o ID especificado.
*/

void empilhaCarregador(Carregador car, Forma f);
/*
   Adiciona uma forma no topo do carregador.
*/

Forma desempilhaCarregador(Carregador car);
/*
   Remove e retorna a forma do topo do carregador. Retorna NULL se o carregador estiver vazio.
*/

int voidCarregador(Carregador car);
/*
   Verifica se o carregador está vazio. Retorna 1 se vazio, 0 caso contrário.
*/

int tamCarregador(Carregador car);
/*
   Retorna o número de formas atualmente no carregador.
*/

int getIdCarregador(Carregador car);
/*
   Retorna o ID do carregador.
*/

Forma topoCarregador(Carregador car);
/*
   Retorna a forma do topo do carregador sem removê-la. Retorna NULL se o carregador estiver vazio.
*/

void limpaCarregador(Carregador car);
/*
   Remove todas as formas do carregador, liberando a estrutura interna.
   ATENÇÃO: Esta função NÃO libera as formas - apenas a estrutura do carregador.
*/

void freeCarregador(Carregador car);
/*
   Libera toda a memória associada ao carregador passado como parâmetro.
   ATENÇÃO: Esta função NÃO libera as formas armazenadas.
*/

#endif
