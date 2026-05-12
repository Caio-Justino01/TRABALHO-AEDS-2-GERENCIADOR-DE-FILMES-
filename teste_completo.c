#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filme.c"
#include "usuario.c"
#include "buscaSequencial.c"
#include "buscaBinaria.c"
#include "insertionSort.c"
#include "log.c"

void testarTamanho(int tam, FILE *logFile) {
    int comparacoes;
    clock_t inicio, fim;
    double tempo;
    int chave = tam / 2;
    int chaveInexistente = tam + 100;

    printf("\n========== BASE DE %d REGISTROS ==========\n", tam);

    FILE *arqF = fopen("filmes_teste.dat", "w+b");
    FILE *arqU = fopen("usuarios_teste.dat", "w+b");

    criarBaseFilmes(arqF, tam);
    criarBaseUsuarios(arqU, tam);

    // Busca sequencial filme - chave existente
    inicio = clock();
    TFilme *f = buscaSequencialFilme(chave, arqF, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Filme (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, f?"OK":"NAO");
    salvaLog(logFile, "Sequencial", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if(f) free(f);

    // Busca sequencial usuario - chave existente
    inicio = clock();
    TUsuario *u = buscaSequencialUsuario(chave, arqU, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Usuario (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, u?"OK":"NAO");
    salvaLog(logFile, "Sequencial", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if(u) free(u);

    // Busca sequencial filme - chave inexistente
    inicio = clock();
    f = buscaSequencialFilme(chaveInexistente, arqF, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Filme inexistente (chave=%d): comp=%d, t=%.6f\n", chaveInexistente, comparacoes, tempo);
    salvaLog(logFile, "Sequencial", "Filme (inexistente)", chaveInexistente, tam, comparacoes, tempo, 0);
    if(f) free(f);

    // Ordenacao
    printf("Ordenando...\n");
    insertionSortFilmes(arqF, tam);
    insertionSortUsuarios(arqU, tam);
    printf("Ordenado!\n");

    // Busca binaria filme - chave existente
    inicio = clock();
    f = buscaBinariaFilme(chave, arqF, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Filme (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, f?"OK":"NAO");
    salvaLog(logFile, "Binaria", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if(f) free(f);

    // Busca binaria usuario - chave existente
    inicio = clock();
    u = buscaBinariaUsuario(chave, arqU, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Usuario (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, u?"OK":"NAO");
    salvaLog(logFile, "Binaria", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if(u) free(u);

    // Busca binaria filme - chave inexistente
    inicio = clock();
    f = buscaBinariaFilme(chaveInexistente, arqF, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Filme inexistente (chave=%d): comp=%d, t=%.6f\n", chaveInexistente, comparacoes, tempo);
    salvaLog(logFile, "Binaria", "Filme (inexistente)", chaveInexistente, tam, comparacoes, tempo, 0);
    if(f) free(f);

    fclose(arqF);
    fclose(arqU);
}

int main() {
    FILE *logFile = fopen("log.txt", "w");
    fprintf(logFile, "==============================================\n");
    fprintf(logFile, "   LOG DE BUSCAS - CATALOGO DE FILMES\n");
    fprintf(logFile, "   Aluno: Caio Justino - 24.2.8068\n");
    fprintf(logFile, "==============================================\n\n");

    testarTamanho(100, logFile);
    testarTamanho(1000, logFile);
    testarTamanho(5000, logFile);

    fclose(logFile);

    printf("\n\n--- LOG COMPLETO ---\n");
    logFile = fopen("log.txt", "r");
    char buf[256];
    while(fgets(buf, 256, logFile)) printf("%s", buf);
    fclose(logFile);

    return 0;
}
