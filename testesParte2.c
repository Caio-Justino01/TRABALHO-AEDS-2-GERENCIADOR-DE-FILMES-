// Modulo PARTE 2 - Demos e Testes Q4.
// Controla as demonstracoes das questoes 1, 2, 3 e os testes
// comparativos da questao 4. Os algoritmos ficam em seus proprios TADs.
#include "filme.h"
#include "selectionSortDisco.h"
#include "selecaoSubstituicao.h"
#include "intercalacaoOtima.h"
#include "testesParte2.h"
#include <stdio.h>
#include <time.h>

static void copiar(const char *o, const char *d) {
    FILE *s = fopen(o, "rb");
    FILE *t = fopen(d, "wb");
    if (!s || !t) return;
    char buf[4096]; size_t n;
    while ((n = fread(buf, 1, sizeof(buf), s)) > 0) fwrite(buf, 1, n, t);
    fclose(s); fflush(t); fclose(t);
}

static int prepararBaseDesordenada(const char *nomeArquivo, int N) {
    FILE *arq = fopen(nomeArquivo, "w+b");
    if (arq == NULL) {
        printf("Erro ao criar base de filmes.\n");
        return 0;
    }
    criarBaseFilmesDesordenada(arq, N, 1);
    fclose(arq);
    return 1;
}

// ============================================================
// OPCAO 1 - Demonstracao Q1 (Selection Sort em Disco)
// ============================================================
void demonstrarQ1(const char *arqFilmes, int N, FILE *logFile) {
    printf("\n--- Demonstracao Q1 (Selection Sort em Disco) ---\n");
    if (N >= 100000) {
        printf("ATENCAO: Selection Sort em base de %d eh INVIAVEL (varias horas).\n", N);
        printf("Use a opcao 3 (Testes Q4) que mostra a extrapolacao matematica.\n");
        return;
    }
    printf("Preparando base desordenada com %d registros...\n", N);
    if (!prepararBaseDesordenada(arqFilmes, N)) return;

    printf("Ordenando com Selection Sort em Disco...\n");
    FILE *arq = fopen(arqFilmes, "r+b");
    clock_t ini = clock();
    selectionSortFilmesDisco(arq, N, logFile, 1);
    double tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
    fclose(arq);
    printf("Tempo: %.4fs | Concluido com sucesso.\n", tempo);
}

// ============================================================
// OPCAO 2 - Demonstracao Q2+Q3 (Selecao com Substituicao + Intercalacao Otima)
// ============================================================
void demonstrarQ2Q3(const char *arqFilmes, int N, FILE *logFile) {
    printf("\n--- Demonstracao Q2+Q3 (Selecao com Substituicao + Intercalacao Otima) ---\n");
    printf("Preparando base desordenada com %d registros...\n", N);
    if (!prepararBaseDesordenada(arqFilmes, N)) return;

    clock_t ini = clock();
    FILE *arq = fopen(arqFilmes, "rb");
    int nP = gerarParticoesSelecaoSubstituicao(arq, N, 1000, logFile, 1);
    fclose(arq);
    printf("Q2 - Selecao com Substituicao: %d particoes geradas\n", nP);

    intercalarParticoesOtima(nP, 4, logFile, 1);
    double tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
    printf("Q3 - Intercalacao Otima: arquivo final gravado em ordenado_final.dat\n");
    printf("Tempo total: %.4fs | Concluido com sucesso.\n", tempo);

    // Copia o ordenado_final.dat por cima do filmes.dat
    copiar("ordenado_final.dat", arqFilmes);
    remove("ordenado_final.dat");
    for (int p = 1; p <= nP * 2 + 10; p++) {
        char np[64]; sprintf(np, "particao_%d.dat", p); remove(np);
    }
}

// ============================================================
// OPCAO 3 - Testes Q4 com extrapolacao matematica
// ============================================================
void executarTestesParte2(void) {
    int tamanhos[] = {1000, 10000, 100000, 500000};
    double temposA[4] = {0,0,0,0};
    double temposB[4] = {0,0,0,0};

    FILE *log = fopen("log_q4.txt", "w");
    if (!log) { printf("Erro ao criar log_q4.txt\n"); return; }

    fprintf(log, "Log dos testes da Questao 4 - Parte 2\n\n");

    printf("\n=== Testes da Questao 4 ===\n");
    printf("Selection Sort: rodando em 1k e 10k. Para 100k e 500k, extrapolacao matematica\n");
    printf("(porque O(N^2) seria varias horas / dias - INVIAVEL na pratica).\n");

    for (int i = 0; i < 4; i++) {
        int N = tamanhos[i];
        printf("\nBase de %d registros:\n", N);

        // Gera base
        FILE *base = fopen("base_q4.dat", "w+b");
        criarBaseFilmesDesordenada(base, N, 1);
        fclose(base);
        copiar("base_q4.dat", "base_q4_a.dat");
        copiar("base_q4.dat", "base_q4_b.dat");

        // Selection Sort: roda real apenas em 1k e 10k
        if (N <= 10000) {
            FILE *fa = fopen("base_q4_a.dat", "r+b");
            clock_t ti = clock();
            selectionSortFilmesDisco(fa, N, log, 1);
            temposA[i] = (double)(clock() - ti) / CLOCKS_PER_SEC;
            fclose(fa);
            printf("  Selection Sort em Disco:           %.4fs (medido)\n", temposA[i]);
        } else {
            // Extrapola usando O(N^2): tempo_estimado = tempo_1k * (N/1000)^2
            // Pega o tempo de 1k (primeira medicao) para extrapolar
            double tempo1k = temposA[0];
            temposA[i] = tempo1k * ((double)N / 1000.0) * ((double)N / 1000.0);
            printf("  Selection Sort em Disco:           %.1fs (extrapolado, O(N^2))\n", temposA[i]);
            fprintf(log, "Selection Sort em base=%d: EXTRAPOLADO (~%.1fs) - O(N^2) inviavel\n", N, temposA[i]);
        }

        // Selecao+Intercalacao: roda em todos
        FILE *fb = fopen("base_q4_b.dat", "rb");
        clock_t ti = clock();
        int nP = gerarParticoesSelecaoSubstituicao(fb, N, 1000, log, 1);
        fclose(fb);
        intercalarParticoesOtima(nP, 4, log, 1);
        temposB[i] = (double)(clock() - ti) / CLOCKS_PER_SEC;
        printf("  Selecao + Intercalacao Otima:      %.4fs\n", temposB[i]);

        if (N <= 10000) {
            fprintf(log, "Resumo base=%d | Selection Sort=%.4fs (medido) | Selecao+Intercalacao=%.4fs\n",
                    N, temposA[i], temposB[i]);
        } else {
            fprintf(log, "Resumo base=%d | Selection Sort=%.1fs (extrapolado, O(N^2)) | Selecao+Intercalacao=%.4fs\n",
                    N, temposA[i], temposB[i]);
        }
        fflush(log);

        // Limpa
        remove("base_q4.dat"); remove("base_q4_a.dat"); remove("base_q4_b.dat");
        for (int p = 1; p <= nP * 2 + 10; p++) {
            char np[64]; sprintf(np, "particao_%d.dat", p); remove(np);
        }
        remove("ordenado_final.dat");
    }

    fclose(log);
    printf("\nLog dos testes salvo em log_q4.txt\n");
}
