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

    // Busca sequencial filme
    inicio = clock();
    TFilme *f = buscaSequencialFilme(chave, arqF, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Filme (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, f?"OK":"X");
    salvaLog(logFile, "Sequencial", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if(f) free(f);

    // Busca sequencial usuario
    inicio = clock();
    TUsuario *u = buscaSequencialUsuario(chave, arqU, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Usuario (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, u?"OK":"X");
    salvaLog(logFile, "Sequencial", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if(u) free(u);

    // Busca seq chave inexistente
    inicio = clock();
    f = buscaSequencialFilme(chaveInexistente, arqF, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Seq Filme inexist: comp=%d, t=%.6f\n", comparacoes, tempo);
    salvaLog(logFile, "Sequencial", "Filme (chave inexistente)", chaveInexistente, tam, comparacoes, tempo, 0);
    if(f) free(f);

    // Ordena
    printf("Ordenando...\n");
    insertionSortFilmes(arqF, tam);
    insertionSortUsuarios(arqU, tam);
    printf("OK!\n");

    // Busca binaria filme
    inicio = clock();
    f = buscaBinariaFilme(chave, arqF, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Filme (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, f?"OK":"X");
    salvaLog(logFile, "Binaria", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if(f) free(f);

    // Busca binaria usuario
    inicio = clock();
    u = buscaBinariaUsuario(chave, arqU, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Usuario (chave=%d): comp=%d, t=%.6f, %s\n", chave, comparacoes, tempo, u?"OK":"X");
    salvaLog(logFile, "Binaria", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if(u) free(u);

    // Busca binaria chave inexistente
    inicio = clock();
    f = buscaBinariaFilme(chaveInexistente, arqF, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Bin Filme inexist: comp=%d, t=%.6f\n", comparacoes, tempo);
    salvaLog(logFile, "Binaria", "Filme (chave inexistente)", chaveInexistente, tam, comparacoes, tempo, 0);
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
    testarTamanho(200, logFile);

    fclose(logFile);

    printf("\n--- LOG ---\n");
    logFile = fopen("log.txt", "r");
    char buf[256];
    while(fgets(buf, 256, logFile)) printf("%s", buf);
    fclose(logFile);
    return 0;
}
