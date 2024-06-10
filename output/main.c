#include <stdio.h>
#include <stdlib.h>
#include "cidade.h"

int main() {
    const char *arquivo = "teste01.txt";

    Estrada *estrada = getEstrada(arquivo);
    if (estrada == NULL) {
        printf("Erro ao ler o arquivo!\n");
        return 1;
    }
    
    double menorVizinhanca = calcularMenorVizinhanca(arquivo);
    
    printf("Menor vizinhanca: %.2f\n", menorVizinhanca);
  
    free(estrada -> C);
    free (estrada);

    return 0;
}
