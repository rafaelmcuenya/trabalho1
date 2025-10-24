#ifndef SOBREPOR_H
#define SOBREPOR_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*
   O módulo sobrepor é responsável por verificar sobreposições entre diferentes formas na arena com algoritmos de detecção de colisão baseados em bounding boxes e geometria analítica.
*/

int sobrepoeCirculoCirculo(Circulo c1, Circulo c2);
/*
   Verifica se dois círculos se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeCirculoRetangulo(Circulo c, Retangulo r);
/*
   Verifica se um círculo e um retângulo se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeCirculoLinha(Circulo c, Linha l);
/*
   Verifica se um círculo e uma linha se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeCirculoTexto(Circulo c, Texto t);
/*
   Verifica se um círculo e um texto se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeRetanguloRetangulo(Retangulo r1, Retangulo r2);
/*
   Verifica se dois retângulos se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeRetanguloLinha(Retangulo r, Linha l);
/*
   Verifica se um retângulo e uma linha se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeRetanguloTexto(Retangulo r, Texto t);
/*
   Verifica se um retângulo e um texto se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeLinhaLinha(Linha l1, Linha l2);
/*
   Verifica se duas linhas se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeLinhaTexto(Linha l, Texto t);
/*
   Verifica se uma linha e um texto se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

int sobrepoeTextoTexto(Texto t1, Texto t2);
/*
   Verifica se dois textos se sobrepõem no plano.
   Retorna 1 se há sobreposição, 0 caso contrário.
*/

#endif
