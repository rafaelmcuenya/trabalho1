#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregador.h"
#include "forma.h"

/*
    Um disparador é um objeto que dispara, na arena, as formas repassadas pelos carregadores.
    Ele só pode comportar uma forma de cada vez, repassadas pelos carregadores conectados, na qual podem ter somente, no máximo, dois conectados (direita e esquerda).
*/

typedef void* Disparador;

Disparador criaDisparador(int id, double x, double y);
/*
   Cria e retorna um novo disparador
*/

void liberaDisparador(Disparador d);
/* 
   Libera a memória do disparador
*/

void inicializaDisparador(Disparador d, int id, double x, double y);
/* 
   Inicializa um disparador
*/

void encaixaCarregadores(Disparador d, Carregador cesq, Carregador cdir);
/* 
   Encaixa os carregadores esquerdo e direito ao disparador
*/

void setPosDisparador(Disparador d, double x, double y);
/* 
   Move a posição (x,y) do disparador 
*/

void shftDisparador(Disparador d, char lado, int n);
/*
    Move a forma engatilhada e as formas dos carregadores do disparador repassado pelo primeiro parâmetro.
    A direção do movimento depende do segundo parâmetro: 'd' para direita, e 'e' para a esquerda.
    A quantidade de movimentos é repassada pelo terceiro parâmetro.
    Tal função só funciona caso tenha dois carregadores acoplados no disparador, com pelo menos um deles possuindo, no mínimo, duas formas carregadas.
*/

Forma disparaForma(Disparador d, double dx, double dy);
/*
  Dispara a forma que está engatilhada, deslocando-a na distância repassada pelos parâmetros 2 (eixo x) e 3 (eixo y). 
  e retornando a Forma para o chamador (ex.: para inserir na arena). Retorna NULL se não há forma engatilhada.
  
  ATENÇÃO: A forma retornada torna-se responsabilidade do chamador, que deve liberá-la quando apropriado. O disparador não mantém referência após o disparo.
*/

int possuiCarregadorEsq(Disparador d);
/* 
   Retorna 1 se possui carregador esquerdo acoplado
*/

int possuiCarregadorDir(Disparador d);
/*
   Retorna 1 se possui carregador direito acoplado
*/

int getIdDisparador(Disparador d);
/*
   Retorna o ID do disparador
*/

double getXDisparador(Disparador d);
/*
   Retorna a coordenada X do disparador
*/

double getYDisparador(Disparador d);
/*
   Retorna a coordenada Y do disparador
*/

Forma getPosDisparo(Disparador d);
/*
   Retorna a forma atualmente engatilhada
*/

void freeDisparador(Disparador d);
/*
  Limpa o disparador: libera a forma em posDisparo (se houver) e zera os campos.
  
  ATENÇÃO: Esta função assume que o disparador é o proprietário exclusivo da forma
  em posDisparo.
*/

#endif
