#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>


/*
   Um círculo é uma forma geométrica descrita num plano, onde é composta por infinitos pontos equidistantes de um único e mesmo ponto, dado como centro do círculo, e onde tal distância é denominada raio do círculo.
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/


typedef void *Circulo;

Circulo criaCirculo(i: Int;  x: Int;  y:Int;  r: Double; corb: String;  corp:String;);
/*
   Cria um círculo cujo ID é o ‘i’, com o centro (âncora) dados pelos 2° e 3° parâmetros e com um raio dado pelo quarto parâmetro. A cor de borda e preenchimento são dadas pelos dois últimos parâmetros.
*/


Circulo areaCirculo(i: Int;  r: Double;);
/*
   Calcula a área de um círculo com o ID repassado pelo primeiro parâmetro, baseando-se na fórmula geral dada por A = πr², sendo ‘r’ o raio do círculo, ‘A’ a área final e  pi(π) uma constante universal equivalente a, aproximadamente, 3,14. 
*/


Circulo idCirculo(Circulo r);
/*
   Coleta o ID de um círculo específico para possíveis manipulações no mesmo, retornando tal identificador.
*/



#endif
