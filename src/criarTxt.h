#ifndef CRIARTXT_H
#define CRIARTXT_H

#include "forma.h"

void iniciarTxt(const char* baseNome);
void fecharTxt();

void txtLc(int idCarregador, int n);
void txtShift(Forma forma);
void txtDsp(Forma forma, double x, double y);
void txtRjd(int sequencia, Forma forma, double x, double y);
void txtCalcSobreposicao(Forma f1, Forma f2, int sobreposicao, const char* resultado);
void txtCalcEsmagada(Forma forma);
void txtCalcClonada(Forma original, Forma clone);

void txtFinal(double pontuacao, int instrucoes, int disparos, int esmagadas, int clonadas);

#endif
