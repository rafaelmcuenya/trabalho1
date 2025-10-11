#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>
#include “ponto.h”

/*
   Um retângulo é uma forma geométrica composta por quatro pontos distintos entre si, interligados por um segmento de reta, e postos em um plano. Tal forma possui uma âncora, uma cor de preenchimento e uma cor de borda.
   A âncora é dada pelo ponto criado mais próximo do ponto de origem (0,0).
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/

typedef void *Retangulo;

Retangulo criaRetangulo(Int i; Double x; Double y; Double w; Double h; 
String corb; String corp);
/*
   Cria um retângulo com a âncora posicionada nos dados repassados pelos parâmetros 3 e 4, com tal forma possuindo um ID dado pelo primeiro parâmetro. O mesmo terá comprimento e altura das informações enviadas pelos 4° e 5° parâmetros, respectivamente.
   As cores de borda e preenchimento são enviadas por meio dos parâmetros 6 e 7, e retorna um ponteiro para a forma recém criada.
*/


Retangulo idRetangulo(Retangulo r);
/*
   Coleta o ID de um retângulo específico para possíveis manipulações no mesmo, retornando tal identificador.
*/






Retangulo areaRetangulo(Ponto x; Ponto y; String corb; String corp);
/*
  Calcula a área de um retângulo, baseando-se na fórmula geral dada por A = l*c, sendo ‘c’ o comprimento do retângulo, ‘A’ a área final e  ‘l’ a largura do mesmo.
*/


#endif
