#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdio.h>
#include <time.h>

// Salva informacoes de busca no arquivo de log
void salvaLog(FILE *logFile, char *tipoBusca, char *entidade, int chave, int tamanhoBase, int comparacoes, double tempo, int encontrado);

#endif 
