#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include "forma.h"

/*
   Uma linha é um segmento de reta delimitado por dois pontos, colineares e não sobrepostos, dispostos em um plano. 
   A linha possui uma cor, dada por um código de cor existente no padrão sRGB de 6 dígitos.
*/

typedef void* Linha;

Linha criaLinha(int i, double x1, double y1, double x2, double y2, char* cor);
/*
   Cria uma linha delimitada pelos pontos dados nos parâmetros. 
   Dentre os parâmetros x1, y1, x2 e y2, somente no máximo três podem possuir o mesmo valor, sendo obrigatório, no mínimo, um deles possuir um valor diferente de, pelo menos, um dos outros parâmetros. 
   A cor da linha será dada pelo último parâmetro.
*/

double areaLinha(Linha l);
/*
   Calcula a área teórica de uma linha, utilizando uma fórmula auxiliar dada por 
A = 2c, onde ‘A’ é a área final e ‘c’ o comprimento total da linha. 
   Essa área não é geométrica, servindo apenas como valor teórico para o programa.
*/

int idLinha(Linha l);
/*
   Coleta o ID de uma linha específica para possíveis manipulações no mesmo, retornando tal identificador.
*/


void moveLinha(Linha l, double dx, double dy);
/*
   Move ambas as extremidades da linha em tantas coordenadas no eixo x e no eixo y, valores repassados respectivamente pelos segundo e terceiro parâmetros.
*/

Linha clonaLinha(Linha l);
/*
   Cria uma cópia idêntica da linha, retornando um ponteiro para a nova linha com os mesmos atributos.
*/

TipoForma getTipo(Linha l);
/*
   Retorna o tipo da forma como enum TipoForma linha.
*/

double getXLinha(Linha l);
/*
   Retorna a coordenada X da âncora da linha.
*/

double getYLinha(Linha l);
/*
   Retorna a coordenada Y da âncora da linha.
*/

char* getCorBLinha(Linha l);
/*
   Retorna a cor de borda da linha, descrita no padrão sRGB de 6 dígitos.
*/

char* getCorPLinha(Linha l);
/*
   Retorna a cor de preenchimento da linha, descrita no padrão sRGB de 6 dígitos.
*/

void liberaLinha(Linha l);
/*
   Libera toda a memória associada a linha passada como parâmetro.Essa função deve ser utilizada sempre que a linha não for mais necessária.
*/

#endif
