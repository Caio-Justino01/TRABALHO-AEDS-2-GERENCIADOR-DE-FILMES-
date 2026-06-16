#ifndef INTERCALACAOOTIMA_H_INCLUDED
#define INTERCALACAOOTIMA_H_INCLUDED

// Modulo PARTE 2 - QUESTAO 3
// Intercalacao Otima com F arquivos (F-1 entrada + 1 saida).

#include <stdio.h>

// Parametro silencio = 1 suprime os printf na tela.
// Apos execucao, arquivo final fica em "ordenado_final.dat".
void intercalarParticoesOtima(int numParticoes, int F, FILE *logFile, int silencio);

#endif
