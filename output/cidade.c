#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"

const char *arquivo = "teste01.txt"
Estrada *getEstrada(const char *arquivo) {
    FILE *arquivo = fopen(arquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", &estrada->T);
    fscanf(arquivo, "%d", &estrada->N);

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d", &estrada->C[i].Posicao);
        fscanf(arquivo, "%s", estrada->C[i].Nome);
    }

    fclose(arquivo);
    return estrada;
}


double calcularMenorVizinhanca(const char *arquivo) {
    Estrada *estrada = getEstrada(arquivo);
    if (estrada == NULL) {
        return -1.0;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double inicio, fim, vizinhanca;

        if (i == 0) {

            inicio = 0;
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        } else if (i == estrada->N - 1) {

            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            fim = estrada->T;

        } else {

            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        }

        vizinhanca = fim - inicio;

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}


char *cidadeMenorVizinhanca(const char *arquivo) {
    Estrada *estrada = getEstrada(arquivo);
    if (estrada == NULL) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    int cidadeMenor = 0;

    for (int i = 0; i < estrada->N; i++) {
        double inicio, fim, vizinhanca;

        if (i == 0) {

            inicio = 0;
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        } else if (i == estrada->N - 1) {

            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            fim = estrada->T;

        } else {

            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        }

        vizinhanca = fim - inicio;

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeMenor = i;
        }
    }

    char *nomeCidade = (char *)malloc((strlen(estrada->C[cidadeMenor].Nome) + 1) * sizeof(char));
    if (nomeCidade == NULL) {
        free(estrada->C);
        free(estrada);
        return NULL;
    }

    strcpy(nomeCidade, estrada->C[cidadeMenor].Nome);

    free(estrada->C);
    free(estrada);
    return nomeCidade;
}
