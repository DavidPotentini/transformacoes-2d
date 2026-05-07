#ifndef RENDER_H
#define RENDER_H

#include "objeto.h"
#include "viewport.h"

void render_limpar(void);
void render_borda(void);
void render_objeto(const Objeto *o, Janela j);

void render_flush(void);

#endif
