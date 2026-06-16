#include "favorito.h"

// Cria favorito na RAM
TFavorito *criarFavorito(int id_usuario, int id_filme) {
    TFavorito *f = (TFavorito *) malloc(sizeof(TFavorito));
    if (f) memset(f, 0, sizeof(TFavorito)); // tira o lixo do malloc
    f->id_usuario = id_usuario;
    f->id_filme = id_filme;
    return f;
}

// Salva favorito no HD, na posicao atual do cursor
void salvaFavorito(TFavorito *fav, FILE *out) {
    fwrite(&fav->id_usuario, sizeof(int), 1, out);
    fwrite(&fav->id_filme, sizeof(int), 1, out);
}

// Le os bytes do HD e remonta a struct na RAM
TFavorito *leFavorito(FILE *in) {
    TFavorito *f = (TFavorito *) malloc(sizeof(TFavorito));
    if (fread(&f->id_usuario, sizeof(int), 1, in) <= 0) {
        free(f); // chegou no fim do arquivo
        return NULL;
    }
    fread(&f->id_filme, sizeof(int), 1, in);
    return f;
}

// Imprime favorito na tela
void imprimeFavorito(TFavorito *fav) {
    printf("Usuario %d  ->  Filme %d\n", fav->id_usuario, fav->id_filme);
}

// Retorna tamanho do registro em bytes
int tamanhoRegistroFavorito() {
    return sizeof(int)   // id_usuario
         + sizeof(int);  // id_filme
}

// Retorna quantos favoritos tem no arquivo
int tamanhoArquivoFavoritos(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = (int)(ftell(arq) / tamanhoRegistroFavorito());
    return tam;
}
