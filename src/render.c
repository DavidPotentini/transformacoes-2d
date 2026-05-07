#include "render.h"
#include <stdio.h>
#include <stdlib.h>

static char buffer[DISP_H][DISP_W + 1];

void render_limpar(void) {
    for (int r = 0; r < DISP_H; r++) {
        for (int c = 0; c < DISP_W; c++) buffer[r][c] = ' ';
        buffer[r][DISP_W] = '\0';
    }
}

void render_borda(void) {
    for (int c = 0; c < DISP_W; c++) {
        buffer[0][c]          = '-';
        buffer[DISP_H - 1][c] = '-';
    }
    for (int r = 0; r < DISP_H; r++) {
        buffer[r][0]          = '|';
        buffer[r][DISP_W - 1] = '|';
    }
    buffer[0][0]                  = '+';
    buffer[0][DISP_W - 1]         = '+';
    buffer[DISP_H - 1][0]         = '+';
    buffer[DISP_H - 1][DISP_W - 1] = '+';
}

static void plot(int x, int y, char c) {
    if (x > 0 && x < DISP_W - 1 && y > 0 && y < DISP_H - 1) {
        buffer[y][x] = c;
    }
}

static void linha(int x0, int y0, int x1, int y1, char c) {
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        plot(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void render_objeto(const Objeto *o, Janela j) {
    if (!o || o->n < 2) return;

    int *px = (int*) malloc(sizeof(int) * o->n);
    int *py = (int*) malloc(sizeof(int) * o->n);
    if (!px || !py) { free(px); free(py); return; }

    for (int i = 0; i < o->n; i++) {
        float nx, ny;
        worldToNdc(o->x[i], o->y[i], j, &nx, &ny);
        ndcToViewport(nx, ny, &px[i], &py[i]);
    }

    for (int i = 0; i < o->n; i++) {
        int k = (i + 1) % o->n;
        linha(px[i], py[i], px[k], py[k], '*');
    }

    for (int i = 0; i < o->n; i++) plot(px[i], py[i], '#');

    free(px);
    free(py);
}

void render_flush(void) {

    printf("\033[2J\033[H");
    for (int r = 0; r < DISP_H; r++) {
        printf("%s\n", buffer[r]);
    }
}
