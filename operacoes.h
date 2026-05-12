#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED

// Cadastrar um novo filme na base
void cadastrarFilme(FILE *arqFilmes);

// Cadastrar um novo usuario na base
void cadastrarUsuario(FILE *arqUsuarios);

// Atualizar um filme existente na base
void atualizarFilme(FILE *arqFilmes, int tamBase);

// Atualizar um usuario existente na base
void atualizarUsuario(FILE *arqUsuarios, int tamBase);

// Remover um filme (marca como removido com id = -1)
void removerFilme(FILE *arqFilmes, int tamBase);

// Remover um usuario (marca como removido com id = -1)
void removerUsuario(FILE *arqUsuarios, int tamBase);

// Buscar filmes por diretor (usando busca sequencial)
void buscarFilmesPorDiretor(FILE *arqFilmes);

// Exibir informacoes de um filme buscando pelo id
void exibirFilme(FILE *arqFilmes, FILE *logFile, int tamBase);

// Exibir informacoes de um usuario buscando pelo id
void exibirUsuario(FILE *arqUsuarios, FILE *logFile, int tamBase);

#endif // OPERACOES_H_INCLUDED
