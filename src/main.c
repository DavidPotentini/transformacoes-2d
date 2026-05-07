#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objeto.h"
#include "transformacoes.h"
#include "viewport.h"
#include "render.h"

/*
 * Programa principal.
 * Le um arquivo de objeto, mantem um loop de comandos pelo teclado
 * para aplicar transformacoes 2D e redesenhar o objeto no terminal.
 */

static void mostrar_ajuda(void) {
    printf("\n=== Comandos ===\n");
    printf("  t <dx> <dy>                    Translacao por (dx, dy)\n");
    printf("  r <graus>                      Rotacao (anti-horario)\n");
    printf("  s <s>                          Escala (uniforme em x e y)\n");
    printf("  d                              Redesenhar\n");
    printf("  l <arquivo>                    Carregar outro objeto\n");
    printf("  h                              Esta ajuda\n");
    printf("  q                              Sair\n\n");
}

static void ajustar_janela(const Objeto *o, Janela *j) {
    if (!o || o->n == 0) return;
    float xmin = o->x[0], xmax = o->x[0];
    float ymin = o->y[0], ymax = o->y[0];
    for (int i = 1; i < o->n; i++) {
        if (o->x[i] < xmin) xmin = o->x[i];
        if (o->x[i] > xmax) xmax = o->x[i];
        if (o->y[i] < ymin) ymin = o->y[i];
        if (o->y[i] > ymax) ymax = o->y[i];
    }
    float padx = (xmax - xmin) * 0.2f + 1.0f;
    float pady = (ymax - ymin) * 0.2f + 1.0f;
    j->xmin = xmin - padx;
    j->xmax = xmax + padx;
    j->ymin = ymin - pady;
    j->ymax = ymax + pady;
}

static void redesenhar_tela(const Objeto *o, Janela j) {
    render_limpar();
    render_borda();
    render_objeto(o, j);
    render_flush();
    float cx, cy;
    objeto_centroide(o, &cx, &cy);
    printf("Janela: x=[%.2f, %.2f], y=[%.2f, %.2f] | Centroide: (%.2f, %.2f)\n",
           j.xmin, j.xmax, j.ymin, j.ymax, cx, cy);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Erro: arquivo do objeto nao informado.\n");
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }
    const char *arquivo = argv[1];

    Objeto *obj = objeto_carregar(arquivo);
    if (!obj) return 1;

    Janela j;
    ajustar_janela(obj, &j);

    printf("Objeto carregado de: %s\n", arquivo);
    objeto_imprimir(obj);
    mostrar_ajuda();
    printf("Pressione ENTER para desenhar...");
    getchar();

    char linha_cmd[256];
    char cmd;
    int redesenhar = 1;

    while (1) {
        if (redesenhar) {
            redesenhar_tela(obj, j);
            redesenhar = 0;
        }
        printf("> ");
        fflush(stdout);
        if (!fgets(linha_cmd, sizeof(linha_cmd), stdin)) break;
        if (sscanf(linha_cmd, " %c", &cmd) != 1) continue;

        switch (cmd) {
            case 't': case 'T': {
                float dx, dy;
                if (sscanf(linha_cmd, " %*c %f %f", &dx, &dy) == 2) {
                    transladar(obj, dx, dy);
                    redesenhar = 1;
                } else printf("Uso: t <dx> <dy>\n");
                break;
            }
            case 'r': case 'R': {
                float ang;
                if (sscanf(linha_cmd, " %*c %f", &ang) == 1) {
                    rotacionar(obj, ang);
                    redesenhar = 1;
                } else printf("Uso: r <graus>\n");
                break;
            }
            case 's': case 'S': {
                float s;
                if (sscanf(linha_cmd, " %*c %f", &s) == 1) {
                    escalar(obj, s, s);
                    redesenhar = 1;
                } else printf("Uso: s <s>\n");
                break;
            }
            case 'd': case 'D':
                redesenhar = 1;
                break;
            case 'l': case 'L': {
                char arq[200];
                if (sscanf(linha_cmd, " %*c %199s", arq) == 1) {
                    Objeto *novo = objeto_carregar(arq);
                    if (novo) {
                        objeto_desalocar(obj);
                        obj = novo;
                        objeto_imprimir(obj);
                        ajustar_janela(obj, &j);
                        redesenhar = 1;
                    }
                } else printf("Uso: l <arquivo>\n");
                break;
            }
            case 'h': case 'H':
                mostrar_ajuda();
                break;
            case 'q': case 'Q':
                objeto_desalocar(obj);
                printf("Encerrando.\n");
                return 0;
            default:
                printf("Comando desconhecido. Use 'h' para ajuda.\n");
        }
    }

    objeto_desalocar(obj);
    return 0;
}
