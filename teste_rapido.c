#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filme.c"
#include "usuario.c"
#include "buscaSequencial.c"
#include "buscaBinaria.c"
#include "insertionSort.c"
#include "log.c"

int main() {
    FILE *arqFilmes, *arqUsuarios, *logFile;
    int comparacoes;
    clock_t inicio, fim;
    double tempo;

    logFile = fopen("log.txt", "w");
    arqFilmes = fopen("filmes.dat", "w+b");
    arqUsuarios = fopen("usuarios.dat", "w+b");

    if (!logFile || !arqFilmes || !arqUsuarios) {
        printf("Erro ao abrir arquivos\n");
        return 1;
    }

    // Teste com 100 registros
    int tam = 100;
    printf("Criando base de %d filmes...\n", tam);
    criarBaseFilmes(arqFilmes, tam);
    printf("Criando base de %d usuarios...\n", tam);
    criarBaseUsuarios(arqUsuarios, tam);

    // Busca sequencial
    int chave = 50;
    inicio = clock();
    TFilme *f = buscaSequencialFilme(chave, arqFilmes, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nBusca Sequencial Filme (chave=%d): comparacoes=%d, tempo=%.6f\n", chave, comparacoes, tempo);
    salvaLog(logFile, "Sequencial", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if (f) { imprimeFilme(f); free(f); }

    // Ordena filmes
    printf("\nOrdenando filmes...\n");
    insertionSortFilmes(arqFilmes, tam);
    printf("Filmes ordenados!\n");

    // Busca binaria
    inicio = clock();
    f = buscaBinariaFilme(chave, arqFilmes, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nBusca Binaria Filme (chave=%d): comparacoes=%d, tempo=%.6f\n", chave, comparacoes, tempo);
    salvaLog(logFile, "Binaria", "Filme", chave, tam, comparacoes, tempo, f != NULL);
    if (f) { imprimeFilme(f); free(f); }

    // Busca sequencial usuario
    inicio = clock();
    TUsuario *u = buscaSequencialUsuario(chave, arqUsuarios, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nBusca Sequencial Usuario (chave=%d): comparacoes=%d, tempo=%.6f\n", chave, comparacoes, tempo);
    salvaLog(logFile, "Sequencial", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if (u) { imprimeUsuario(u); free(u); }

    // Ordena usuarios
    printf("\nOrdenando usuarios...\n");
    insertionSortUsuarios(arqUsuarios, tam);
    printf("Usuarios ordenados!\n");

    // Busca binaria usuario
    inicio = clock();
    u = buscaBinariaUsuario(chave, arqUsuarios, 1, tam, &comparacoes);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nBusca Binaria Usuario (chave=%d): comparacoes=%d, tempo=%.6f\n", chave, comparacoes, tempo);
    salvaLog(logFile, "Binaria", "Usuario", chave, tam, comparacoes, tempo, u != NULL);
    if (u) { imprimeUsuario(u); free(u); }

    fclose(arqFilmes);
    fclose(arqUsuarios);
    fclose(logFile);

    printf("\n--- Conteudo do log.txt ---\n");
    logFile = fopen("log.txt", "r");
    char buf[256];
    while (fgets(buf, 256, logFile)) printf("%s", buf);
    fclose(logFile);

    return 0;
}
