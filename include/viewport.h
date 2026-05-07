#ifndef VIEWPORT_H
#define VIEWPORT_H

#define DISP_W 80
#define DISP_H 40

typedef struct {
    float xmin, xmax, ymin, ymax;
} Janela;

void worldToNdc(float wx, float wy, Janela j, float *nx, float *ny);

void ndcToViewport(float nx, float ny, int *px, int *py);

#endif
