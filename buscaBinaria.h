#ifndef BUSCABINARIA_H_INCLUDED
#define BUSCABINARIA_H_INCLUDED

// Busca binaria por um filme na base de dados ordenada
TFilme *buscaBinariaFilme(int chave, FILE *in, int inicio, int fim, int *comparacoes);

// Busca binaria por um usuario na base de dados ordenada
TUsuario *buscaBinariaUsuario(int chave, FILE *in, int inicio, int fim, int *comparacoes);

#endif 
