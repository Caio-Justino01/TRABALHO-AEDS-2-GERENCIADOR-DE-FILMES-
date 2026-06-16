#ifndef FAVORITO_H_INCLUDED
#define FAVORITO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Entidade "Favorito" - liga um usuario a um filme
// (relacao muitos-para-muitos entre Usuario e Filme)
typedef struct Favorito {
    int id_usuario;   // qual usuario favoritou
    int id_filme;     // qual filme foi favoritado
} TFavorito;

// Cria favorito na RAM
TFavorito *criarFavorito(int id_usuario, int id_filme);

// Salva favorito no arquivo, na posicao atual do cursor
void salvaFavorito(TFavorito *fav, FILE *out);

// Le um favorito do arquivo na posicao atual do cursor
TFavorito *leFavorito(FILE *in);

// Imprime favorito
void imprimeFavorito(TFavorito *fav);

// Retorna tamanho do registro de favorito em bytes (sem espaco fantasma)
int tamanhoRegistroFavorito();

// Retorna quantidade de registros no arquivo
int tamanhoArquivoFavoritos(FILE *arq);

#endif
