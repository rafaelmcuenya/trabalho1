#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>
#include "forma.h" 

/*
   Um círculo é uma forma geométrica descrita num plano, onde é composta por infinitos pontos equidistantes de um único e mesmo ponto, dado como centro do círculo, e onde tal distância é denominada raio do círculo.
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/

typedef void* Circulo;

Circulo criaCirculo(int i, double x, double y, double r, char* corb, char* corp);
/*
   Cria um círculo cujo ID é o ‘i’, com o centro (âncora) dado pelos 2° e 3° parâmetros e com um raio dado pelo quarto parâmetro.
   A cor de borda e preenchimento são dadas pelos dois últimos parâmetros.
*/

double areaCirculo(Circulo c);
/*
   Calcula a área de um círculo com o ID repassado pelo primeiro parâmetro, baseando-se na fórmula geral dada por A = πr², sendo ‘r’ o raio do círculo, ‘A’ a área final e pi(π) uma constante universal equivalente a aproximadamente 3,14.
*/

int idCirculo(Circulo c);
/*
   Coleta o ID de um círculo específico para possíveis manipulações no mesmo, retornando tal identificador.
*/

void moveCirculo(Circulo c, double x, double y);
/*
   Por meio do ID repassado pelo primeiro parâmetro, move a âncora de tal círculo em tantas coordenadas no eixo x e eixo y, valores repassados respectivamente pelos segundo e terceiro parâmetros.
*/

Circulo clonaCirculo(Circulo c);
/*
   Cria uma cópia do círculo, retornando um ponteiro para o novo círculo com os mesmos atributos.
*/

TipoForma getTipo(Circulo c);
/*
   Retorna o tipo da forma como enum TipoForma círculo.
*/

double getXCirculo(Circulo c);
/*
   Retorna a coordenada X da âncora do círculo.
*/

double getYCirculo(Circulo c);
/*
   Retorna a coordenada Y da âncora do círculo.
*/

char* getCorBordaCirculo(Circulo c);
/*
   Retorna a cor de borda do círculo, descrita no padrão sRGB de 6 dígitos.
*/

char* getCorPreenchimentoCirculo(Circulo c);
/*
   Retorna a cor de preenchimento do círculo, descrita no padrão sRGB de 6 dígitos.
*/

void liberaCirculo(Circulo c);
/*
   Libera toda a memória associada ao círculo passado como parâmetro.Essa função deve ser utilizada sempre que o círculo não for mais necessário.
*/

#endif



