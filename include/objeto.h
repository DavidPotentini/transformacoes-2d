#ifndef OBJETO_H
#define OBJETO_H

typedef struct {
    int    n;
    float *x;
    float *y;
} Objeto;

Objeto* objeto_carregar(const char *arquivo);

void objeto_desalocar(Objeto *o);

void objeto_imprimir(const Objeto *o);

void objeto_centroide(const Objeto *o, float *cx, float *cy);

#endif
