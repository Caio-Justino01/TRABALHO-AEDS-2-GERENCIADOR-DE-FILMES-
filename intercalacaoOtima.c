// Modulo PARTE 2 - QUESTAO 3: Intercalacao Otima
#include "filme.h"
#include "intercalacaoOtima.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static long intercalarKParticoes(char **nomesEntrada, int k, char *nomeSaida) {
    FILE **entradas = (FILE **) malloc(sizeof(FILE *) * k);
    TFilme **bocas = (TFilme **) malloc(sizeof(TFilme *) * k);
    long gravados = 0;

    for (int i = 0; i < k; i++) {
        entradas[i] = fopen(nomesEntrada[i], "rb");
        bocas[i] = (entradas[i] != NULL) ? leFilme(entradas[i]) : NULL;
    }

    FILE *saida = fopen(nomeSaida, "wb");

    while (1) {
        int posMenor = -1;
        for (int i = 0; i < k; i++) {
            if (bocas[i] != NULL) {
                if (posMenor == -1 || bocas[i]->id < bocas[posMenor]->id) {
                    posMenor = i;
                }
            }
        }
        if (posMenor == -1) break;

        salvaFilme(bocas[posMenor], saida);
        gravados++;
        free(bocas[posMenor]);
        bocas[posMenor] = leFilme(entradas[posMenor]);
    }

    fflush(saida);
    fclose(saida);
    for (int i = 0; i < k; i++) {
        if (entradas[i] != NULL) fclose(entradas[i]);
    }
    free(entradas);
    free(bocas);
    return gravados;
}

void intercalarParticoesOtima(int numParticoes, int F, FILE *logFile, int silencio) {
    if (numParticoes <= 0 || F < 3) return;

    int kPorFase = F - 1;
    if (!silencio) {
        printf("\nIntercalando %d particoes (Intercalacao Otima, F=%d)...\n", numParticoes, F);
    }

    clock_t inicio = clock();
    int fase = 0;

    int maxNomes = numParticoes * 2 + 10;
    char **ativas = (char **) malloc(sizeof(char *) * maxNomes);
    for (int i = 0; i < numParticoes; i++) {
        ativas[i] = (char *) malloc(64);
        sprintf(ativas[i], "particao_%d.dat", i + 1);
    }
    int qtdAtivas = numParticoes;
    int proximoId = numParticoes + 1;

    while (qtdAtivas > 1) {
        fase++;
        int k = qtdAtivas < kPorFase ? qtdAtivas : kPorFase;

        char *nomesEntrada[k];
        for (int i = 0; i < k; i++) nomesEntrada[i] = ativas[i];

        char *nomeSaida = (char *) malloc(64);
        sprintf(nomeSaida, "particao_%d.dat", proximoId);
        proximoId++;

        intercalarKParticoes(nomesEntrada, k, nomeSaida);

        for (int i = 0; i < k; i++) free(ativas[i]);
        for (int i = k; i < qtdAtivas; i++) ativas[i - k] = ativas[i];
        qtdAtivas -= k;
        ativas[qtdAtivas++] = nomeSaida;
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    long copiados = 0;

    if (qtdAtivas == 1) {
        FILE *src = fopen(ativas[0], "rb");
        FILE *dst = fopen("ordenado_final.dat", "wb");
        TFilme *f;
        while ((f = leFilme(src)) != NULL) {
            salvaFilme(f, dst);
            free(f);
            copiados++;
        }
        fclose(src);
        fflush(dst);
        fclose(dst);
        free(ativas[0]);
    }
    free(ativas);

    if (!silencio) {
        printf("Intercalado em %.4fs (%d fases, %ld registros no arquivo final)\n",
               tempo, fase, copiados);
    }

    if (logFile != NULL) {
        fprintf(logFile, "Intercalacao Otima (Q3) | particoes=%d | F=%d | fases=%d | gravados=%ld | tempo=%.4fs\n",
                numParticoes, F, fase, copiados, tempo);
        fflush(logFile);
    }
}
