#include <time.h>
#include "filme.h"
#include "usuario.h"
#include "favorito.h"
#include "buscaBinaria.h"
#include "interacoes.h"

// (1) Usuario favorita um filme.
// Antes de gravar, valida os dois IDs usando BUSCA BINARIA (item 3).
// Tudo que acontece e registrado no log.txt.
void favoritarFilme(FILE *arqFav, FILE *arqUsuarios, FILE *arqFilmes,
                    int tamUsuarios, int tamFilmes, FILE *logFile) {
    int id_usuario, id_filme, compU, compF;
    clock_t inicio, fim;
    double tempo;

    printf("\n--- Favoritar Filme ---\n");
    printf("ID do usuario: ");
    scanf("%d", &id_usuario);
    printf("ID do filme: ");
    scanf("%d", &id_filme);

    inicio = clock();

    // Verifica se o usuario existe (busca binaria na base ordenada)
    TUsuario *u = buscaBinariaUsuario(id_usuario, arqUsuarios, 1, tamUsuarios, &compU);
    if (u == NULL) {
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Erro: usuario com ID %d nao existe na base!\n", id_usuario);

        // Registra falha no log
        fprintf(logFile, "Operacao: Favoritar Filme\n");
        fprintf(logFile, "Usuario: %d (busca binaria - %d comparacoes) -> NAO encontrado\n", id_usuario, compU);
        fprintf(logFile, "Filme: %d (nao verificado)\n", id_filme);
        fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
        fprintf(logFile, "Resultado: FALHA - usuario inexistente\n");
        fprintf(logFile, "----------------------------------------------\n");
        fflush(logFile);
        return;
    }
    free(u);

    // Verifica se o filme existe (busca binaria na base ordenada)
    TFilme *f = buscaBinariaFilme(id_filme, arqFilmes, 1, tamFilmes, &compF);
    if (f == NULL) {
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Erro: filme com ID %d nao existe na base!\n", id_filme);

        // Registra falha no log
        fprintf(logFile, "Operacao: Favoritar Filme\n");
        fprintf(logFile, "Usuario: %d (busca binaria - %d comparacoes) -> OK\n", id_usuario, compU);
        fprintf(logFile, "Filme: %d (busca binaria - %d comparacoes) -> NAO encontrado\n", id_filme, compF);
        fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
        fprintf(logFile, "Resultado: FALHA - filme inexistente\n");
        fprintf(logFile, "----------------------------------------------\n");
        fflush(logFile);
        return;
    }
    free(f);

    // IDs validos - cria o favorito e grava no arquivo
    TFavorito *fav = criarFavorito(id_usuario, id_filme);
    fseek(arqFav, 0, SEEK_END);
    salvaFavorito(fav, arqFav);
    fflush(arqFav);
    free(fav);

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Filme %d favoritado com sucesso pelo usuario %d!\n", id_filme, id_usuario);

    // Registra sucesso no log
    fprintf(logFile, "Operacao: Favoritar Filme\n");
    fprintf(logFile, "Usuario: %d (busca binaria - %d comparacoes) -> OK\n", id_usuario, compU);
    fprintf(logFile, "Filme: %d (busca binaria - %d comparacoes) -> OK\n", id_filme, compF);
    fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
    fprintf(logFile, "Resultado: SUCESSO - par gravado em favoritos.dat\n");
    fprintf(logFile, "----------------------------------------------\n");
    fflush(logFile);
}

// (2) Lista todos os filmes que um usuario favoritou.
void listarFavoritosDoUsuario(FILE *arqFav, FILE *arqUsuarios, FILE *arqFilmes,
                              int tamUsuarios, int tamFilmes, FILE *logFile) {
    int id_usuario, compU, compF;
    clock_t inicio, fim;
    double tempo;

    printf("\n--- Favoritos do Usuario ---\n");
    printf("ID do usuario: ");
    scanf("%d", &id_usuario);

    inicio = clock();

    // Valida o usuario com busca binaria
    TUsuario *u = buscaBinariaUsuario(id_usuario, arqUsuarios, 1, tamUsuarios, &compU);
    if (u == NULL) {
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Erro: usuario com ID %d nao existe na base!\n", id_usuario);

        // Registra falha no log
        fprintf(logFile, "Operacao: Listar Favoritos do Usuario\n");
        fprintf(logFile, "Usuario: %d (busca binaria - %d comparacoes) -> NAO encontrado\n", id_usuario, compU);
        fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
        fprintf(logFile, "Resultado: FALHA - usuario inexistente\n");
        fprintf(logFile, "----------------------------------------------\n");
        fflush(logFile);
        return;
    }

    printf("\nUsuario:\n");
    imprimeUsuario(u);
    free(u);

    // Percorre o arquivo de favoritos (sequencial) e filtra pelo id_usuario
    rewind(arqFav);
    TFavorito *fav;
    int encontrados = 0;
    int totalComparacoesBinaria = 0;

    printf("\nFilmes favoritados:\n");
    while ((fav = leFavorito(arqFav)) != NULL) {
        if (fav->id_usuario == id_usuario) {
            TFilme *f = buscaBinariaFilme(fav->id_filme, arqFilmes, 1, tamFilmes, &compF);
            totalComparacoesBinaria += compF;
            if (f != NULL) {
                imprimeFilme(f);
                free(f);
                encontrados++;
            }
        }
        free(fav);
    }

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (encontrados == 0) {
        printf("Este usuario ainda nao favoritou nenhum filme.\n");
    } else {
        printf("\nTotal de filmes favoritados: %d\n", encontrados);
    }

    // Registra no log
    fprintf(logFile, "Operacao: Listar Favoritos do Usuario\n");
    fprintf(logFile, "Usuario: %d (busca binaria - %d comparacoes) -> OK\n", id_usuario, compU);
    fprintf(logFile, "Filmes encontrados: %d\n", encontrados);
    fprintf(logFile, "Total de comparacoes nas buscas binarias de filme: %d\n", totalComparacoesBinaria);
    fprintf(logFile, "Tempo gasto: %.6f segundos\n", tempo);
    fprintf(logFile, "Resultado: SUCESSO\n");
    fprintf(logFile, "----------------------------------------------\n");
    fflush(logFile);
}
