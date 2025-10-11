#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>

/*
   Um texto é um conjunto de caracteres exibidos sobre um plano de forma linear. Tal estrutura possui uma âncora, que pode ser posicionada no começo do texto (i), no meio dele (m), ou em seu final (f). As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/


typedef void *Texto;

Texto criaTexto(i: Int;  x: Double;  y: double;  corb: String;  corp: String;  a: Char;  txto: String);
/*
   Cria um texto contendo os caracteres do último parâmetro, com a âncora posicionada baseada no caracter recebido pelo quarto parâmetro. Os 2° e 3° parâmetros são a posição da âncora do texto sobre o plano. A cor padrão de preenchimento e borda são dadas pelos quarto e quinto parâmetros.
*/


Texto areaTexto(i: Int;  x: Double;  y:Double;  r: Double;);
/*
  Calcula a área de um círculo, baseando-se na fórmula geral dada por A = πr², sendo ‘r’ o raio do círculo, ‘A’ a área final e  pi(π) uma constante universal equivalente a, aproximadamente, 3,14.
*/


Texto idTexto(Texto r);
/*
   Coleta o ID de um texto específico para possíveis manipulações no mesmo, retornando tal identificador.
*/

#endif
