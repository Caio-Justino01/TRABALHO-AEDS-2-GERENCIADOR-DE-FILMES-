#ifndef FILME_H_INCLUDED
#define FILME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Filme {
    int id;
    char titulo[100];
    char diretor[50];
    int ano;
    char genero[30];
    float nota;
} TFilme;

// Cria filme
TFilme *criarFilme(int id, char *titulo, char *diretor, int ano, char *genero, float nota);

// Salva filme no arquivo out, na posicao atual do cursor
void salvaFilme(TFilme *filme, FILE *out);

// Le um filme do arquivo in na posicao atual do cursor
TFilme *leFilme(FILE *in);

// Imprime filme
void imprimeFilme(TFilme *filme);

// Retorna tamanho do registro de filme em bytes
int tamanhoRegistroFilme();

// Cria a base de dados de filmes
void criarBaseFilmes(FILE *out, int tam);

// Embaralha vetor de ids
void embaralhaFilmes(int *vet, int tam);

// Imprime a base de dados de filmes
void imprimirBaseFilmes(FILE *out);

// Retorna quantidade de registros no arquivo
int tamanhoArquivoFilmes(FILE *arq);

#endif 
