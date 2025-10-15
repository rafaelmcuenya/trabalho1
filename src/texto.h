#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include "forma.h"

/*
   Um texto é um conjunto de caracteres exibidos sobre um plano de forma linear. 
   Tal estrutura possui uma âncora, que pode ser posicionada no começo do texto (i), 
   no meio dele (m) ou em seu final (f). 
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/

typedef void* Texto;

Texto criaTexto(int i, double x, double y, char* corb, char* corp, char a, char* txto);
/*
   Cria um texto contendo os caracteres do último parâmetro, com a âncora posicionada baseada 
   no caractere recebido pelo sexto parâmetro. 
   Os 2° e 3° parâmetros são a posição da âncora do texto sobre o plano. 
   As cores padrão de preenchimento e borda são dadas pelos quarto e quinto parâmetros.
*/

double areaTexto(Texto t);
/*
   Calcula uma área teórica associada ao texto, apenas para fins de padronização do sistema. 
   A área é estimada de forma simbólica, não geométrica, podendo representar o espaço ocupado pelo texto no plano.
*/

int idTexto(Texto t);
/*
   Coleta o ID de um texto específico para possíveis manipulações no mesmo, retornando tal identificador.
*/

void moveTexto(Texto t, double dx, double dy);
/*
   Por meio do ID repassado pelo primeiro parâmetro, move a âncora do texto selecionado 
   em tantas coordenadas no eixo x e no eixo y, valores repassados respectivamente pelos segundo e terceiro parâmetros.   
*/

char* getTexto(Texto t);
/*
   Retorna a sequência de caracteres contida no texto selecionado.
*/

char getAncoraTexto(Texto t);
/*
   Retorna o tipo de âncora (i, m ou f) associada ao texto.
*/

TipoForma getTipo(Texto t);
/*
   Retorna o tipo da forma como enum TipoForma texto.
*/

double getXTexto(Texto t);
/*
   Retorna a coordenada X da âncora do texto.
*/

double getYTexto(Texto t);
/*
   Retorna a coordenada Y da âncora do texto.
*/

char* getCorBordaTexto(Texto t);
/*
   Retorna a cor de borda do texto, descrita no padrão sRGB de 6 dígitos.
*/

char* getCorPreenchimentoTexto(Texto t);
/*
   Retorna a cor de preenchimento do texto, descrita no padrão sRGB de 6 dígitos.
*/

void liberaTexto(Texto t);
/*
   Libera toda a memória associada ao texto passado como parâmetro.Essa função deve ser utilizada sempre que o texto não for mais necessário.
*/

#endif
