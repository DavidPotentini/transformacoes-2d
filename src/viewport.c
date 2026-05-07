#include "viewport.h"

void worldToNdc(float wx, float wy, Janela j, float *nx, float *ny) {
    *nx = 2.0f * (wx - j.xmin) / (j.xmax - j.xmin) - 1.0f;
    *ny = 2.0f * (wy - j.ymin) / (j.ymax - j.ymin) - 1.0f;
}

void ndcToViewport(float nx, float ny, int *px, int *py) {
    *px = (int) (DISP_W * (nx + 1) / 2);
    *py = (int) (DISP_H * (-ny + 1) / 2);
}
