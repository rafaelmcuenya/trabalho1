#include <stdio.h>
#include <stdlib.h>
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct {
	TipoForma tipo;
	void* elemento;
} FormStruct;

Forma criaForma(TipoForma tipo, void* elemento) {
	FormStruct* f = (FormStruct*)malloc(sizeof(FormStruct));
	if (!f) return NULL;
	f->tipo = tipo;
	f->elemento = elemento;
	return (Forma)f;
}

TipoForma getTipoForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	return form->tipo;
}

int getIdForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		return idCirculo(form->elemento);
	case Tr:
		return idRetangulo(form->elemento);
	case Tl:
		return idLinha(form->elemento);
	case Tt:
		return idTexto(form->elemento);
	default:
		return -1;
	}
}

double areaForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		return areaCirculo(form->elemento);
	case Tr:
		return areaRetangulo(form->elemento);
	case Tl:
		return areaLinha(form->elemento);
	case Tt:
		return areaTexto(form->elemento);
	default:
		return 0.0;
	}
}

void moveForma(Forma f, double dx, double dy) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		moveCirculo(form->elemento, dx, dy);
		break;
	case Tr:
		moveRetangulo(form->elemento, dx, dy);
		break;
	case Tl:
		moveLinha(form->elemento, dx, dy);
		break;
	case Tt:
		moveTexto(form->elemento, dx, dy);
		break;
	default:
		break;
	}
}

double getXForma(Forma f) {
    FormStruct* form = (FormStruct*)f;
    switch (form->tipo) {
        case Tc:
            return getXCirculo(form->elemento);
        case Tr:
            return getXRetangulo(form->elemento);
        case Tl: {
            double x1 = getX1Linha(form->elemento);
            double y1 = getY1Linha(form->elemento);
            double x2 = getX2Linha(form->elemento);
            double y2 = getY2Linha(form->elemento);
            if (x1 < x2) return x1;
            if (x2 < x1) return x2;
            return (y1 < y2) ? x1 : x2;
        }
        case Tt:
            return getXTexto(form->elemento);
        default:
            return 0.0;
    }
}

double getYForma(Forma f) {
    FormStruct* form = (FormStruct*)f;
    switch (form->tipo) {
        case Tc:
            return getYCirculo(form->elemento);
        case Tr:
            return getYRetangulo(form->elemento);
        case Tl: {
            double x1 = getX1Linha(form->elemento);
            double y1 = getY1Linha(form->elemento);
            double x2 = getX2Linha(form->elemento);
            double y2 = getY2Linha(form->elemento);
            if (x1 < x2) return y1;
            if (x2 < x1) return y2;
            return (y1 < y2) ? y1 : y2;
        }
        case Tt:
            return getYTexto(form->elemento);
        default:
            return 0.0;
    }
}

char* getCorBForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		return getCorBCirculo(form->elemento);
	case Tr:
		return getCorBordaRetangulo(form->elemento);
	case Tl:
		return getCorLinha(form->elemento);
	case Tt:
		return getCorBTexto(form->elemento);
	default:
		return NULL;
	}
}

char* getCorPForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		return getCorPCirculo(form->elemento);
	case Tr:
		return getCorPreenchimentoRetangulo(form->elemento);
	case Tl:
		return getCorLinha(form->elemento);
	case Tt:
		return getCorPTexto(form->elemento);
	default:
		return NULL;
	}
}

void liberaForma(Forma f) {
	FormStruct* form = (FormStruct*)f;
	switch (form->tipo) {
	case Tc:
		liberaCirculo(form->elemento);
		break;
	case Tr:
		liberaRetangulo(form->elemento);
		break;
	case Tl:
		liberaLinha(form->elemento);
		break;
	case Tt:
		liberaTexto(form->elemento);
		break;
	default:
		break;
	}
	free(form);
}
