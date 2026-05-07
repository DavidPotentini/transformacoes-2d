# Transformações 2D — Computação Gráfica T1

Implementação em C das transformações
geométricas 2D — translação, rotação e escala — sobre objetos definidos
por vértices.

## Integrantes

- David Sebastião Zardo Potentini

## Como compilar

Pré-requisito: `gcc`.

```sh
gcc -Iinclude src/*.c -o transformacoes2d -lm
```

## Como executar

```sh
./transformacoes2d data/casaNDC.dcg    # arquivo do objeto (obrigatório)
./transformacoes2d outro.txt        # qualquer arquivo válido
```

Sem argumento o programa imprime erro de uso e encerra.

---

## Comandos disponíveis

| Comando        | Efeito                                  |
|----------------|-----------------------------------------|
| `t <dx> <dy>`  | Translação por (dx, dy)                 |
| `r <graus>`    | Rotação (anti-horário)                  |
| `s <s>`        | Escala uniforme (mesmo fator em x e y)  |
| `d`            | Redesenha a tela                        |
| `l <arquivo>`  | Carrega outro objeto                    |
| `h`            | Exibe a ajuda                           |
| `q`            | Sai                                     |