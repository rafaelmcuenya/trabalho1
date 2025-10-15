#ifndef FORMA_H
#define FORMA_H

#include <stdio.h>

typedef void* Forma;

/*
   Uma forma é uma estrutura genérica utilizada para representar qualquer figura geométrica gerada pelo .geo, podendo ser um círculo, retângulo, linha ou texto. Esse tipo genérico é usado para permitir que as operações do programa possam manipular diferentes figuras de forma independente do tipo específico de cada uma.
*/

Forma criaForma(TipoForma tipo, void* elemento);
/*
   Cria uma nova forma genérica a partir de um tipo específico e do ponteiro para a forma concreta. Essa função encapsula a forma dentro de uma estrutura unificada, permitindo o uso genérico.
*/

TipoForma getTipoForma(Forma f);
/*
   Retorna o tipo da forma passada como parâmetro, permitindo identificar se é um círculo, retângulo, linha ou texto.
*/

int getIdForma(Forma f);
/*
   Retorna o identificador (ID) associado à forma.
*/

double areaForma(Forma f);
/*
   Calcula e retorna a área da forma, independentemente do tipo. A função internamente identifica o tipo da forma e chama o cálculo correspondente.
*/


void moveForma(Forma f, double dx, double dy);
/*
   Move a forma no plano, deslocando sua posição em tantas unidades nos eixos X e Y quanto forem passadas pelos parâmetros. A operação afeta a âncora da figura, dependendo do tipo.
*/

double getXForma(Forma f);
/*
   Retorna a coordenada X da âncora da forma.
*/

double getYForma(Forma f);
/*
   Retorna a coordenada Y da âncora da forma.
*/

char* getCorBordaForma(Forma f);
/*
   Retorna a cor da borda da forma, descrita no padrão sRGB de 6 dígitos.
*/

char* getCorPreenchimentoForma(Forma f);
/*
   Retorna a cor de preenchimento da forma, descrita no padrão sRGB de 6 dígitos.
*/

void liberaForma(Forma f);
/*
   Libera toda a memória associada à forma passada como parâmetro, de acordo com o tipo. Essa função deve ser utilizada sempre que a forma não for mais necessária.
*/

#endif


