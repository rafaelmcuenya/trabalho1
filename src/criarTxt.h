#ifndef CRIARTXT_H
#define CRIARTXT_H

#include "forma.h"

void iniciarTxt(const char* baseNome);
void fecharTxt();

void txtLc(int idCarregador, Forma formas[], int count);  
void txtShift(Forma forma);                              
void txtDsp(Forma forma, double xFinal, double yFinal);  
void txtRjd(int sequencia, Forma forma, double xFinal, double yFinal); 
void txtCalcResultado(const char* resultado);           
void txtCalcAreaEsmagada(double area);                  

void txtFinal(double pontuacao, int instrucoes, int disparos, int esmagadas, int clonadas);

#endif
