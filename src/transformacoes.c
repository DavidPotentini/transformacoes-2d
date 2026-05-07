#include "transformacoes.h"
#include <math.h>

#define PI 3.14159265358979323846

void transladar(Objeto *o, float dx, float dy) {
    for (int i = 0; i < o->n; i++) {
        o->x[i] += dx;
        o->y[i] += dy;
    }
}

void escalar(Objeto *o, float sx, float sy) {
    float cx, cy;
    objeto_centroide(o, &cx, &cy);
    
    for (int i = 0; i < o->n; i++) {
        o->x[i] = cx + (o->x[i] - cx) * sx;
        o->y[i] = cy + (o->y[i] - cy) * sy;
    }
}

void rotacionar(Objeto *o, float graus) {
    float cx, cy;
    objeto_centroide(o, &cx, &cy);
    float rad = graus * (float) PI / 180.0f;
    float cs = cosf(rad);
    float sn = sinf(rad);

    for (int i = 0; i < o->n; i++) {
        float dx = o->x[i] - cx;
        float dy = o->y[i] - cy;
        o->x[i] = cx + dx * cs - dy * sn;
        o->y[i] = cy + dx * sn + dy * cs;
    }
}
