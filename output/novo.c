#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função para inicializar a estrutura Estrada com os dados do arquivo
Estrada *getEstrada(const char *teste01) {
    FILE *arquivo = fopen(teste01, "r");
    if (arquivo == NULL) {
        printf("Este arquivo nao pode ser aberto!!"\n);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", &estrada->T);
    fscanf(arquivo, "%d", &estrada->N);

    if (estrada->T < 3 || estrada->T > 106 || estrada->N < 2 || estrada->N > 104) {
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

// Função para calcular a menor vizinhança
double calcularMenorVizinhanca(const char *teste01) {
    Estrada *estrada = getEstrada(teste01);
    if (estrada == NULL) {
        return -1.0;
    }

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) {
            vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        } else {
            double esquerda = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
            double direita = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
            vizinhanca = esquerda < direita ? esquerda : direita;
        }

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Função para retornar o nome da cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *teste01) {
    Estrada *estrada = getEstrada(teste01);
    if (estrada == NULL) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    int cidadeMenor = 0;

    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) {
            vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        } else {
            double esquerda = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
            double direita = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
            vizinhanca = esquerda < direita ? esquerda : direita;
        }

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
