#ifndef TESTESPARTE2_H_INCLUDED
#define TESTESPARTE2_H_INCLUDED

// Modulo PARTE 2 - Demos das questoes Q1, Q2+Q3 e testes Q4
#include <stdio.h>

// Opcao 1 do menu da Parte 2: Demonstracao Q1 (Selection Sort em Disco)
// Gera uma base desordenada, ordena e mostra estatisticas resumidas.
void demonstrarQ1(const char *arqFilmes, int N, FILE *logFile);

// Opcao 2 do menu da Parte 2: Demonstracao Q2+Q3
// (Selecao com Substituicao + Intercalacao Otima)
void demonstrarQ2Q3(const char *arqFilmes, int N, FILE *logFile);

// Opcao 3 do menu da Parte 2: Testes Q4 em 1k, 10k, 100k, 500k
// Selection Sort REAL em 1k e 10k. Extrapolacao matematica para 100k e 500k.
void executarTestesParte2(void);

#endif
