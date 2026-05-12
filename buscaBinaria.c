#include "filme.h"
#include "usuario.h"
#include "buscaBinaria.h"
#include <math.h>

// Busca binaria por um filme na base de dados ordenada (O(LOG N))
TFilme *buscaBinariaFilme(int chave, FILE *in, int inicio, int fim, int *comparacoes) {
    TFilme *f = NULL;
    int cod = -1; // guardar o ID do filme que esta sendo lido na iteraçao atual
    *comparacoes = 0;

    while (inicio <= fim && cod != chave) {
        int meio = (inicio + fim) / 2;
        fseek(in, (meio - 1) * tamanhoRegistroFilme(), SEEK_SET); //se for 1000 :(500 - 1) * 192 bytes

        if (f != NULL) free(f);
        f = leFilme(in); /// le nop disco aquele unico registro localizado pelo fseek
        cod = f->id; // extraiu o id para aram para aprox etap
        (*comparacoes)++;

        if (f) {
            if (cod > chave) {
                fim = meio - 1; // chave ta na metade esquerda 
            } else {
                inicio = meio + 1; // se nao ajusta o inicio para descartar metade esquerda 
            }
        }
    }

    if (cod == chave) {
        return f;
    } else {
        if (f != NULL) free(f);///se nao encontrou limpa o ultimo bloco da ram
        return NULL;
    }
}

// Busca binaria por um usuario na base de dados ordenada (mesma logica do de cima)
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
