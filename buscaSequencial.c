#include "filme.h"
#include "usuario.h"
#include "buscaSequencial.h"

// Busca sequencial por um filme na base de dados
TFilme *buscaSequencialFilme(int chave, FILE *in, int *comparacoes) {
    TFilme *f = NULL;
    *comparacoes = 0;

    rewind(in);

    while ((f = leFilme(in)) != NULL) {
        (*comparacoes)++;
        if (f->id == chave) {
            return f;
        }
        free(f);
    }

    return NULL;
}

// Busca sequencial por um usuario na base de dados
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
