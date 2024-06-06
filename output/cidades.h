#ifndef CIDADES_H
#define CIDADES_H

typedef struct {
    char Nome[256]; // Nome da cidade
    int Posicao; // Posição da cidade
} Cidade;

typedef struct {
    int N; // Número de cidades
    int T; // Comprimento da estrada
    Cidade *C; // Vetor de cidades
} Estrada;

Estrada *getEstrada(const char *teste01); // Inicializa cidades no TAD indicado acima.
double calcularMenorVizinhanca(const char *teste01); // Retorna a menor vizinhança.
char *cidadeMenorVizinhanca(const char *teste01); // Retorna a cidade que tem menor vizinhança.

#endif
