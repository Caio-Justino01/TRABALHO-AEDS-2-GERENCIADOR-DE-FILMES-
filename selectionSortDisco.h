#ifndef SELECTIONSORTDISCO_H_INCLUDED
#define SELECTIONSORTDISCO_H_INCLUDED

// Modulo PARTE 2 - QUESTAO 1
// Selection Sort em Disco (metodo diferente do Insertion Sort).

#include <stdio.h>

// Parametro silencio = 1 suprime os printf na tela (mas continua
// gravando no log). Usado pela Q4 para nao poluir a saida.
void selectionSortFilmesDisco(FILE *arq, int tam, FILE *logFile, int silencio);

#endif
