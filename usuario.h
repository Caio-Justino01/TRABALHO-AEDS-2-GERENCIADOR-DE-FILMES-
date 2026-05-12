#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Usuario {
    int id;
    char nome[50];
    char email[50];
} TUsuario;

// cria usuario
TUsuario *criarUsuario(int id, char *nome, char *email);

// calva usuario no arquivo out, na posicao atual do cursor
void salvaUsuario(TUsuario *usuario, FILE *out);

// le um usuario do arquivo in na posicao atual do cursor
TUsuario *leUsuario(FILE *in);

// imprime usuario
void imprimeUsuario(TUsuario *usuario);

// Retorna tamanho do registro de usuario em bytes
int tamanhoRegistroUsuario();

// Cria a base de dados de usuarios
void criarBaseUsuarios(FILE *out, int tam);

// Embaralha vetor de ids
void embaralhaUsuarios(int *vet, int tam);

// Imprime a base de dados de usuarios
void imprimirBaseUsuarios(FILE *out);

// Retorna quantidade de registros no arquivo
int tamanhoArquivoUsuarios(FILE *arq);

#endif 
