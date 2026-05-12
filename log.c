#include "log.h"

// Salva informacoes de busca no arquivo de log
void salvaLog(FILE *logFile, char *tipoBusca, char *entidade, int chave, int tamanhoBase, int comparacoes, double tempo, int encontrado) {
    fprintf(logFile, "Tipo de Busca: %s\n", tipoBusca);
    fprintf(logFile, "Entidade: %s\n", entidade);
    fprintf(logFile, "Chave buscada: %d\n", chave);
    fprintf(logFile, "Tamanho da base: %d registros\n", tamanhoBase);
    fprintf(logFile, "Comparacoes realizadas: %d\n", comparacoes);
    fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
    fprintf(logFile, "Resultado: %s\n", encontrado ? "Encontrado" : "Nao encontrado");
    fprintf(logFile, "----------------------------------------------\n");
    fflush(logFile);
}
