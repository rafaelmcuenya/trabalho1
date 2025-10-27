#ifndef CRIARTXT_H
#define CRIARTXT_H

#include "forma.h"

/*
   Esse módulo é responsável por criar o arquivo Txt das operações provindas pelos outros módulos.
*/

void iniciarTxt(const char* baseNome);
/*
   Inicia o arquivo Txt
*/

void fecharTxt(void);
/*
   Fecha o arquivo Txt
*/

//Funções que cuidam das operações provindas do .qry
void txtLc(int idCarregador, Forma formas[], int count);  
void txtShift(Forma forma);    
void txtDsp(Forma forma, double xFinal, double yFinal);  
void txtRjd(int sequencia, Forma forma, double xFinal, double yFinal); 

void txtCalcResultado(const char* resultado); 
/*
   Calcula o resultado final e repassa pro Txt
*/

void txtCalcAreaEsmagada(double area); 
/*
   Calcula o total de áreas esmagadas final e repassa pro Txt
*/

void txtFinal(double pontuacao, int instrucoes, int disparos, int esmagadas, int clonadas);
/*
   Cria o TxT final.
*/

#endif
