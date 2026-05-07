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

Pressione ENTER após cada comando.

| Comando        | Efeito                                          |
|----------------|-------------------------------------------------|
| `w`            | Transladar +y (passo 1.0)                       |
| `s`            | Transladar -y (passo 1.0)                       |
| `a`            | Transladar -x (passo 1.0)                       |
| `d`            | Transladar +x (passo 1.0)                       |
| `/`            | Rotacionar +15° (anti-horário)                  |
| `+`            | Escalar uniformemente por 1.10                  |
| `-`            | Escalar uniformemente por 1/1.10                |
| `l <arquivo>`  | Carrega outro objeto                            |
| `h`            | Exibe a ajuda                                   |
| `q`            | Sai                                             |