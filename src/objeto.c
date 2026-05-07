#include "objeto.h"
#include <stdio.h>
#include <stdlib.h>

Objeto* objeto_carregar(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'\n", arquivo);
        return NULL;
    }

    Objeto *o = (Objeto*) malloc(sizeof(Objeto));
    if (!o) { fclose(f); return NULL; }

    if (fscanf(f, "%d", &o->n) != 1 || o->n <= 0) {
        fprintf(stderr, "Erro: arquivo invalido (numero de vertices)\n");
        free(o);
        fclose(f);
        return NULL;
    }

    o->x = (float*) malloc(sizeof(float) * o->n);
    o->y = (float*) malloc(sizeof(float) * o->n);
    if (!o->x || !o->y) {
        free(o->x); free(o->y); free(o);
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < o->n; i++) {
        if (fscanf(f, "%f %f", &o->x[i], &o->y[i]) != 2) {
            fprintf(stderr, "Erro: vertice %d invalido\n", i);
            free(o->x); free(o->y); free(o);
            fclose(f);
            return NULL;
        }
    }

    fclose(f);
    return o;
}

void objeto_desalocar(Objeto *o) {
    if (!o) return;
    free(o->x);
    free(o->y);
    free(o);
}

void objeto_imprimir(const Objeto *o) {
    if (!o) { printf("(objeto nulo)\n"); return; }
    printf("Objeto com %d vertices:\n", o->n);
    for (int i = 0; i < o->n; i++) {
        printf("  v[%d] = (%.3f, %.3f)\n", i, o->x[i], o->y[i]);
    }
}

void objeto_centroide(const Objeto *o, float *cx, float *cy) {
    float sx = 0, sy = 0;
    for (int i = 0; i < o->n; i++) {
        sx += o->x[i];
        sy += o->y[i];
    }
    *cx = sx / o->n;
    *cy = sy / o->n;
}
