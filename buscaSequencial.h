#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

// Busca sequencial por um filme na base de dados
// Retorna ponteiro para o filme encontrado ou NULL
TFilme *buscaSequencialFilme(int chave, FILE *in, int *comparacoes);

// Busca sequencial por um usuario na base de dados
// Retorna ponteiro para o usuario encontrado ou NULL
TUsuario *buscaSequencialUsuario(int chave, FILE *in, int *comparacoes);

#endif // BUSCASEQUENCIAL_H_INCLUDED
