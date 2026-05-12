#include "filme.h"
#include "usuario.h"
#include "buscaBinaria.h"
#include <math.h>

// Busca binaria por um filme na base de dados ordenada
TFilme *buscaBinariaFilme(int chave, FILE *in, int inicio, int fim, int *comparacoes) {
    TFilme *f = NULL;
    int cod = -1;
    *comparacoes = 0;

    while (inicio <= fim && cod != chave) {
        int meio = (inicio + fim) / 2;
        fseek(in, (meio - 1) * tamanhoRegistroFilme(), SEEK_SET);

        if (f != NULL) free(f);
        f = leFilme(in);
        cod = f->id;
        (*comparacoes)++;

        if (f) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        return f;
    } else {
        if (f != NULL) free(f);
        return NULL;
    }
}

// Busca binaria por um usuario na base de dados ordenada
TUsuario *buscaBinariaUsuario(int chave, FILE *in, int inicio, int fim, int *comparacoes) {
    TUsuario *u = NULL;
    int cod = -1;
    *comparacoes = 0;

    while (inicio <= fim && cod != chave) {
        int meio = (inicio + fim) / 2;
        fseek(in, (meio - 1) * tamanhoRegistroUsuario(), SEEK_SET);

        if (u != NULL) free(u);
        u = leUsuario(in);
        cod = u->id;
        (*comparacoes)++;

        if (u) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave) {
        return u;
    } else {
        if (u != NULL) free(u);
        return NULL;
    }
}
