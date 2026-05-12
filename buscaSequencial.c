#include "filme.h"
#include "usuario.h"
#include "buscaSequencial.h"

// Busca sequencial por um filme na base de dados (executa N vezes)
TFilme *buscaSequencialFilme(int chave, FILE *in, int *comparacoes) { ///o(n)
    TFilme *f = NULL;
    *comparacoes = 0;

    rewind(in); //obriga a agulha de leitura do hd a voltar pro byte 0

    while ((f = leFilme(in)) != NULL) {
        (*comparacoes)++;
        if (f->id == chave) {// se encontrou , aborta a execução  e o ponteiro (filme) é devolvido para a RAM
            return f;
        }
        free(f);
    }

    return NULL;
}

// Busca sequencial por um usuario na base de dados (mesma logica do de cima)
TUsuario *buscaSequencialUsuario(int chave, FILE *in, int *comparacoes) {
    TUsuario *u = NULL;
    *comparacoes = 0;

    rewind(in);

    while ((u = leUsuario(in)) != NULL) {
        (*comparacoes)++;
        if (u->id == chave) {
            return u;
        }
        free(u);
    }

    return NULL;
}
