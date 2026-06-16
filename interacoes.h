#ifndef INTERACOES_H_INCLUDED
#define INTERACOES_H_INCLUDED

#include <stdio.h>

// Operacoes que exemplificam as interacoes entre as entidades
// Filme e Usuario (atende a QUESTAO 6 do enunciado).
// Todas as operacoes usam as buscas do item 3 para validar os IDs
// e gravam um registro no log.txt para fins de auditoria.

// (1) Usuario favorita um filme
// - usa busca binaria no arquivo de usuarios para validar id_usuario
// - usa busca binaria no arquivo de filmes para validar id_filme
// - se os dois existirem, grava o par no arquivo de favoritos
// - registra a operacao no log.txt
void favoritarFilme(FILE *arqFav, FILE *arqUsuarios, FILE *arqFilmes,
                    int tamUsuarios, int tamFilmes, FILE *logFile);

// (2) Lista todos os filmes que um usuario favoritou
// - usa busca binaria para validar o usuario
// - percorre o arquivo de favoritos (sequencial) filtrando pelo id_usuario
// - para cada favorito, usa busca binaria no arquivo de filmes para
//   mostrar o titulo do filme favoritado
// - registra a operacao no log.txt
void listarFavoritosDoUsuario(FILE *arqFav, FILE *arqUsuarios, FILE *arqFilmes,
                              int tamUsuarios, int tamFilmes, FILE *logFile);

#endif
