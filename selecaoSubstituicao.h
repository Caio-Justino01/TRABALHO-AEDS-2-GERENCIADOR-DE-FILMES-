#ifndef SELECAOSUBSTITUICAO_H_INCLUDED
#define SELECAOSUBSTITUICAO_H_INCLUDED

// Modulo PARTE 2 - QUESTAO 2
// Selecao com Substituicao (geracao de particoes ordenadas).

#include <stdio.h>

// Parametro silencio = 1 suprime os printf na tela.
// Retorna o numero de particoes geradas.
int gerarParticoesSelecaoSubstituicao(FILE *arqEntrada, int tam, int M, FILE *logFile, int silencio);

#endif
