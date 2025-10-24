#include <math.h>
#include <string.h>
#include "sobrepor.h"

static double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

static double max(double a, double b){
    return (a > b) ? a : b;
}

static double min(double a, double b){
    return (a < b) ? a : b;
}

static void calcularBoundingBoxTexto(Texto t, double *x1, double *y1, double *x2, double *y2){
    double tx = getXTexto(t);
    double ty = getYTexto(t);
    char ancora = getAncoraTexto(t);
    char* conteudo = getTexto(t);
    int len = strlen(conteudo);
    double comprimento = 10.0 * len;  

    switch(ancora){
        case 'i': 
            *x1 = tx;
            *y1 = ty;
            *x2 = tx + comprimento;
            *y2 = ty;
            break;
        case 'm':
            *x1 = tx - comprimento/2;
            *y1 = ty;
            *x2 = tx + comprimento/2;
            *y2 = ty;
            break;
        case 'f': 
            *x1 = tx - comprimento;
            *y1 = ty;
            *x2 = tx;
            *y2 = ty;
            break;
        default: 
            *x1 = tx;
            *y1 = ty;
            *x2 = tx + comprimento;
            *y2 = ty;
    }
    
    free(conteudo);
}

static int segmentosSeIntersectam(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4){
    double orient1 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    double orient2 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
    double orient3 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    double orient4 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
    
    if (orient1 * orient2 < 0 && orient3 * orient4 < 0) return 1;
    if (orient1 == 0 && x3 >= min(x1, x2) && x3 <= max(x1, x2) && y3 >= min(y1, y2) && y3 <= max(y1, y2)) return 1;
    if (orient2 == 0 && x4 >= min(x1, x2) && x4 <= max(x1, x2) && y4 >= min(y1, y2) && y4 <= max(y1, y2)) return 1;
    if (orient3 == 0 && x1 >= min(x3, x4) && x1 <= max(x3, x4) && y1 >= min(y3, y4) && y1 <= max(y3, y4)) return 1;
    if (orient4 == 0 && x2 >= min(x3, x4) && x2 <= max(x3, x4) && y2 >= min(y3, y4) && y2 <= max(y3, y4)) return 1;
    
    return 0;
}

static double distanciaPontoSegmento(double px, double py, double x1, double y1, double x2, double y2){
    double A = px - x1;
    double B = py - y1;
    double C = x2 - x1;
    double D = y2 - y1;
    double dot = A * C + B * D;
    double len_sq = C * C + D * D;
    
    if (len_sq == 0) return distancia(px, py, x1, y1);
    
    double param = dot / len_sq;
    double xx, yy;
    
    if (param < 0){
        xx = x1; yy = y1;
    } else if (param > 1){
        xx = x2; yy = y2;
    } else{
        xx = x1 + param * C;
        yy = y1 + param * D;
    }
    return distancia(px, py, xx, yy);
}

int sobrepoeCirculoCirculo(Circulo c1, Circulo c2){
    double x1 = getXCircle(c1);
    double y1 = getYCircle(c1);
    double r1 = getRaioCirculo(c1);
    double x2 = getXCircle(c2);
    double y2 = getYCircle(c2);
    double r2 = getRaioCirculo(c2);

    return (distancia(x1, y1, x2, y2) <= (r1 + r2));
}

int sobrepoeCirculoRetangulo(Circulo c, Retangulo r){
    double cx = getXCircle(c);
    double cy = getYCircle(c);
    double raio = getRaioCirculo(c);
    double rx = getXRet(r);
    double ry = getYRet(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    double px = max(rx, min(cx, rx + w));
    double py = max(ry, min(cy, ry + h));
    double dist = distancia(cx, cy, px, py);
  
    return (dist <= raio);
}

int sobrepoeCirculoLinha(Circulo c, Linha l){
    double cx = getXCircle(c);
    double cy = getYCircle(c);
    double raio = getRaioCirculo(c);
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    double dist = distanciaPontoSegmento(cx, cy, x1, y1, x2, y2);
  
    return (dist <= raio);
}

int sobrepoeCirculoTexto(Circulo c, Texto t){
    double cx = getXCircle(c);
    double cy = getYCircle(c);
    double raio = getRaioCirculo(c);
    double x1, y1, x2, y2;
    calcularBoundingBoxTexto(t, &x1, &y1, &x2, &y2);
    double px = max(x1, min(cx, x2));
    double py = max(y1, min(cy, y2));
    double dist = distancia(cx, cy, px, py);
  
    return (dist <= raio);
}

int sobrepoeRetanguloRetangulo(Retangulo r1, Retangulo r2){
    double x1 = getXRet(r1);
    double y1 = getYRet(r1);
    double w1 = getLarguraRetangulo(r1);
    double h1 = getAlturaRetangulo(r1);

    double x2 = getXRet(r2);
    double y2 = getYRet(r2);
    double w2 = getLarguraRetangulo(r2);
    double h2 = getAlturaRetangulo(r2);

    return !(x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
}

int sobrepoeRetanguloLinha(Retangulo r, Linha l){
    double rx = getXRet(r);
    double ry = getYRet(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);

    if ((x1 >= rx && x1 <= rx + w && y1 >= ry && y1 <= ry + h) || (x2 >= rx && x2 <= rx + w && y2 >= ry && y2 <= ry + h)){
        return 1;
    }
      
    double bordas[4][4] ={
       {rx, ry, rx + w, ry},        
       {rx + w, ry, rx + w, ry + h}, 
       {rx, ry + h, rx + w, ry + h}, 
       {rx, ry, rx, ry + h}          
    };

    for (int i = 0; i < 4; i++){
        if (segmentosSeIntersectam(x1, y1, x2, y2, bordas[i][0], bordas[i][1], bordas[i][2], bordas[i][3])){
            return 1;
        }
    }
    return 0;
}

int sobrepoeRetanguloTexto(Retangulo r, Texto t){
    double rx = getXRet(r);
    double ry = getYRet(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    double tx1, ty1, tx2, ty2;
    calcularBoundingBoxTexto(t, &tx1, &ty1, &tx2, &ty2);

    return !(rx + w < tx1 || tx2 < rx || ry + h < ty1 || ty2 < ry);
}

int sobrepoeLinhaLinha(Linha l1, Linha l2){
    double x1 = getX1Linha(l1), y1 = getY1Linha(l1);
    double x2 = getX2Linha(l1), y2 = getY2Linha(l1);
    double x3 = getX1Linha(l2), y3 = getY1Linha(l2);
    double x4 = getX2Linha(l2), y4 = getY2Linha(l2);

    return segmentosSeIntersectam(x1, y1, x2, y2, x3, y3, x4, y4);
}

int sobrepoeLinhaTexto(Linha l, Texto t){
    double x1 = getX1Linha(l), y1 = getY1Linha(l);
    double x2 = getX2Linha(l), y2 = getY2Linha(l);
    double tx1, ty1, tx2, ty2;
    calcularBoundingBoxTexto(t, &tx1, &ty1, &tx2, &ty2);

    double bordas[4][4] ={
       {tx1, ty1, tx2, ty1}, 
       {tx2, ty1, tx2, ty2}, 
       {tx1, ty2, tx2, ty2}, 
       {tx1, ty1, tx1, ty2}  
    };

    for (int i = 0; i < 4; i++){
        if (segmentosSeIntersectam(x1, y1, x2, y2, bordas[i][0], bordas[i][1], bordas[i][2], bordas[i][3])){
            return 1;
        }
    }
    return 0;
}

int sobrepoeTextoTexto(Texto t1, Texto t2){
    double x11, y11, x12, y12;
    calcularBoundingBoxTexto(t1, &x11, &y11, &x12, &y12);
    double x21, y21, x22, y22;
    calcularBoundingBoxTexto(t2, &x21, &y21, &x22, &y22);

    return !(x12 < x21 || x22 < x11 || y12 < y21 || y22 < y11);
}

int formasSobrepoem(Forma f1, Forma f2) {
    if (!f1 || !f2) return 0;
    TipoForma tipo1 = getTipoForma(f1);
    TipoForma tipo2 = getTipoForma(f2);
    
    if (tipo1 == Tc && tipo2 == Tc) {
        return sobrepoeCirculoCirculo(getCirculoFromForma(f1), getCirculoFromForma(f2));
    }
    else if (tipo1 == Tc && tipo2 == Tr) {
        return sobrepoeCirculoRetangulo(getCirculoFromForma(f1), getRetanguloFromForma(f2));
    }
    else if (tipo1 == Tc && tipo2 == Tl) {
        return sobrepoeCirculoLinha(getCirculoFromForma(f1), getLinhaFromForma(f2));
    }
    else if (tipo1 == Tc && tipo2 == Tt) {
        return sobrepoeCirculoTexto(getCirculoFromForma(f1), getTextoFromForma(f2));
    }
    else if (tipo1 == Tr && tipo2 == Tc) {
        return sobrepoeCirculoRetangulo(getCirculoFromForma(f2), getRetanguloFromForma(f1));
    }
    else if (tipo1 == Tr && tipo2 == Tr) {
        return sobrepoeRetanguloRetangulo(getRetanguloFromForma(f1), getRetanguloFromForma(f2));
    }
    else if (tipo1 == Tr && tipo2 == Tl) {
        return sobrepoeRetanguloLinha(getRetanguloFromForma(f1), getLinhaFromForma(f2));
    }
    else if (tipo1 == Tr && tipo2 == Tt) {
        return sobrepoeRetanguloTexto(getRetanguloFromForma(f1), getTextoFromForma(f2));
    }
    else if (tipo1 == Tl && tipo2 == Tc) {
        return sobrepoeCirculoLinha(getCirculoFromForma(f2), getLinhaFromForma(f1));
    }
    else if (tipo1 == Tl && tipo2 == Tr) {
        return sobrepoeRetanguloLinha(getRetanguloFromForma(f2), getLinhaFromForma(f1));
    }
    else if (tipo1 == Tl && tipo2 == Tl) {
        return sobrepoeLinhaLinha(getLinhaFromForma(f1), getLinhaFromForma(f2));
    }
    else if (tipo1 == Tl && tipo2 == Tt) {
        return sobrepoeLinhaTexto(getLinhaFromForma(f1), getTextoFromForma(f2));
    }
    else if (tipo1 == Tt && tipo2 == Tc) {
        return sobrepoeCirculoTexto(getCirculoFromForma(f2), getTextoFromForma(f1));
    }
    else if (tipo1 == Tt && tipo2 == Tr) {
        return sobrepoeRetanguloTexto(getRetanguloFromForma(f2), getTextoFromForma(f1));
    }
    else if (tipo1 == Tt && tipo2 == Tl) {
        return sobrepoeLinhaTexto(getLinhaFromForma(f2), getTextoFromForma(f1));
    }
    else if (tipo1 == Tt && tipo2 == Tt) {
        return sobrepoeTextoTexto(getTextoFromForma(f1), getTextoFromForma(f2));
    }
    return 0;
}
