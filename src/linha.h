#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>

/*
   Uma linha é um segmento de reta delimitado por dois pontos, colineares e não sobrepostos, dispostos em um plano. A linha possui uma cor, dada por um código de cor existente no padrão sRGB de 6 dígitos.
*/

typedef void *Linha;

Linha criaLinha(i: Int;  x1: Double;  y1:Double;  x2: Double;  y2: Double;  String cor);
/*
   Cria uma linha delimitada pelos pontos dados nos parâmetros. Dentre os parâmetros x1, y1, x2 e y2, somente no máximo três podem possuir o mesmo valor, sendo obrigatório, no mínimo, um deles possuir um valor diferente de, pelo menos, um dos outros parâmetros. A cor da linha será dada pelo último parâmetro.
*/

Linha areaLinha(i: Int;  x1: Double;  y1:Double;  x2: Double;  y2: Double;);
/*
  Calcula a área de uma linha, utilizando uma fórmula teórica utilizada para a execução do programa, apesar de não ser possível calcular de forma prática a área de uma linha. A equação é dada por A = 2c, onde ‘A’ é a área final e ‘c’ o comprimento total da linha.
*/


Linha idLinha(Linha r);
/*
   Coleta o ID de uma linha específica para possíveis manipulações no mesmo, retornando tal identificador.
*/



#endif
