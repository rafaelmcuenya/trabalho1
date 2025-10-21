#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>
#include "forma.h"

/*
   Um retângulo é uma forma geométrica composta por quatro pontos distintos entre si, interligados por segmentos de reta, e postos em um plano. 
   Tal forma possui uma âncora, uma cor de preenchimento e uma cor de borda.
   A âncora é dada pelo ponto criado mais próximo do ponto de origem (0,0).
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/

typedef void* Retangulo;

Retangulo criaRet(int i, double x, double y, double w, double h, char* corb, char* corp);
/*
   Cria um retângulo com a âncora posicionada nos dados repassados pelos parâmetros 3 e 4, com tal forma possuindo um ID dado pelo primeiro parâmetro. 
   O mesmo terá comprimento e altura das informações enviadas pelos 4° e 5° parâmetros, respectivamente.
   As cores de borda e preenchimento são enviadas por meio dos parâmetros 6 e 7, e retorna um ponteiro para a forma recém criada.
*/

double areaRet(Retangulo r);
/*
   Calcula a área de um retângulo, baseando-se na fórmula geral dada por A = l*c, sendo 'c' o comprimento do retângulo, 'A' a área final e 'l' a largura do mesmo.
*/

int idRet(Retangulo r);
/*
   Coleta o ID de um retângulo específico para possíveis manipulações no mesmo, retornando tal identificador.
*/

void moveRet(Retangulo r, double x, double y);
/*
   Por meio do ID repassado pelo primeiro parâmetro, move a âncora de tal forma em tantas coordenadas no eixo x e eixo y, valores repassados respectivamente pelos segundo e terceiro parâmetros.   
*/

Retangulo clonaRet(Retangulo r);
/*
   Cria uma cópia idêntica do retângulo, retornando um ponteiro para o novo retângulo com os mesmos atributos.
*/

double getXRet(Retangulo r);
/*
   Retorna a coordenada X da âncora do retangulo.
*/

double getYRet(Retangulo r);
/*
   Retorna a coordenada Y da âncora do retangulo.
*/

char* getCorBRet(Retangulo r);  // CORREÇÃO 1: mudado 'c' para 'r'
/*
   Retorna a cor de borda do retangulo, descrita no padrão sRGB de 6 dígitos.
*/

char* getCorPRet(Retangulo r);
/*
   Retorna a cor de preenchimento do retangulo, descrita no padrão sRGB de 6 dígitos.
*/

void liberaRet(Retangulo r);
/*
   Libera toda a memória associada ao retangulo passado como parâmetro.Essa função deve ser utilizada sempre que o retangulo não for mais necessário.
*/

#endif
