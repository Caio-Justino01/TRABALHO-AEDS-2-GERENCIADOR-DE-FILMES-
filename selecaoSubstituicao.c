// Modulo PARTE 2 - QUESTAO 2: Selecao com Substituicao
#include "filme.h"
#include "selecaoSubstituicao.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int acharMenorNaoCongelado(TFilme **memoria, int *congelado, int M) {
    int posMenor = -1;
    for (int i = 0; i < M; i++) {
        if (memoria[i] != NULL && !congelado[i]) {
            if (posMenor == -1 || memoria[i]->id < memoria[posMenor]->id) {
                posMenor = i;
            }
        }
    }
    return posMenor;
}

int gerarParticoesSelecaoSubstituicao(FILE *arqEntrada, int tam, int M, FILE *logFile, int silencio) {
    TFilme **memoria = (TFilme **) malloc(sizeof(TFilme *) * M);
    int *congelado = (int *) calloc(M, sizeof(int));
    int particaoAtual = 1;
    long totalGravados = 0;
    long comparacoes = 0;
    clock_t inicio = clock();

    if (!silencio) {
        printf("\nGerando particoes (Selecao com Substituicao, M=%d)...\n", M);
    }

    rewind(arqEntrada);
    for (int i = 0; i < M; i++) {
        memoria[i] = leFilme(arqEntrada);
    }

    char nomeParticao[64];
    sprintf(nomeParticao, "particao_%d.dat", particaoAtual);
    FILE *particaoArq = fopen(nomeParticao, "wb");
    int ultimoGravado = -1;

    while (1) {
        int posMenor = acharMenorNaoCongelado(memoria, congelado, M);
        comparacoes += (M - 1);

        if (posMenor == -1) {
            fflush(particaoArq);
            fclose(particaoArq);
            for (int i = 0; i < M; i++) congelado[i] = 0;
            int temAlgo = 0;
            for (int i = 0; i < M; i++) {
                if (memoria[i] != NULL) { temAlgo = 1; break; }
            }
            if (!temAlgo) {
                particaoArq = NULL;
                break;
            }
            particaoAtual++;
            ultimoGravado = -1;
            sprintf(nomeParticao, "particao_%d.dat", particaoAtual);
            particaoArq = fopen(nomeParticao, "wb");
            continue;
        }

        salvaFilme(memoria[posMenor], particaoArq);
        ultimoGravado = memoria[posMenor]->id;
        totalGravados++;
        free(memoria[posMenor]);
        memoria[posMenor] = NULL;

        TFilme *novo = leFilme(arqEntrada);
        if (novo != NULL) {
            memoria[posMenor] = novo;
            if (novo->id < ultimoGravado) {
                congelado[posMenor] = 1;
            }
        }
    }

    if (particaoArq != NULL) {
        fflush(particaoArq);
        fclose(particaoArq);
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

    if (!silencio) {
        printf("%d particoes geradas em %.4fs (%ld registros)\n",
               particaoAtual, tempo, totalGravados);
    }

    if (logFile != NULL) {
        fprintf(logFile, "Selecao com Substituicao (Q2) | base=%d | M=%d | particoes=%d | gravados=%ld | comparacoes=%ld | tempo=%.4fs\n",
                tam, M, particaoAtual, totalGravados, comparacoes, tempo);
        fflush(logFile);
    }

    for (int i = 0; i < M; i++) {
        if (memoria[i] != NULL) free(memoria[i]);
    }
    free(memoria);
    free(congelado);

    return particaoAtual;
}
