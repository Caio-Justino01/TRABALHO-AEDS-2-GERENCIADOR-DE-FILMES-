// Modulo PARTE 2 - QUESTAO 1: Selection Sort em Disco
#include "filme.h"
#include "selectionSortDisco.h"
#include <time.h>

void selectionSortFilmesDisco(FILE *arq, int tam, FILE *logFile, int silencio) {
    int t = tamanhoRegistroFilme();
    long comparacoes = 0;
    long trocas = 0;
    clock_t inicio = clock();

    if (!silencio) printf("\nOrdenando %d filmes com Selection Sort em Disco...\n", tam);

    for (int i = 0; i < tam - 1; i++) {
        fseek(arq, i * t, SEEK_SET);
        TFilme *menor = leFilme(arq);
        int posicaoMenor = i;

        for (int j = i + 1; j < tam; j++) {
            fseek(arq, j * t, SEEK_SET);
            TFilme *atual = leFilme(arq);
            comparacoes++;
            if (atual->id < menor->id) {
                free(menor);
                menor = atual;
                posicaoMenor = j;
            } else {
                free(atual);
            }
        }

        if (posicaoMenor != i) {
            fseek(arq, i * t, SEEK_SET);
            TFilme *deslocado = leFilme(arq);
            fseek(arq, i * t, SEEK_SET);
            salvaFilme(menor, arq);
            fseek(arq, posicaoMenor * t, SEEK_SET);
            salvaFilme(deslocado, arq);
            free(deslocado);
            trocas++;
        }
        free(menor);
    }
    fflush(arq);

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    if (!silencio) {
        printf("Ordenado em %.4fs (%ld comparacoes, %ld trocas)\n", tempo, comparacoes, trocas);
    }

    if (logFile != NULL) {
        fprintf(logFile, "Selection Sort em Disco (Q1) | base=%d | tempo=%.4fs | comparacoes=%ld | trocas=%ld\n",
                tam, tempo, comparacoes, trocas);
        fflush(logFile);
    }
}
