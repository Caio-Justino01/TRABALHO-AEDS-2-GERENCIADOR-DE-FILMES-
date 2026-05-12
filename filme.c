#include "filme.h"

// Cria filme
TFilme *criarFilme(int id, char *titulo, char *diretor, int ano, char *genero, float nota) {
    TFilme *filme = (TFilme *) malloc(sizeof(TFilme));
    if (filme) memset(filme, 0, sizeof(TFilme));
    filme->id = id;
    strcpy(filme->titulo, titulo);
    strcpy(filme->diretor, diretor);
    filme->ano = ano;
    strcpy(filme->genero, genero);
    filme->nota = nota;
    return filme;
}

// Salva filme no arquivo out, na posicao atual do cursor
void salvaFilme(TFilme *filme, FILE *out) {
    fwrite(&filme->id, sizeof(int), 1, out);
    fwrite(filme->titulo, sizeof(char), sizeof(filme->titulo), out);
    fwrite(filme->diretor, sizeof(char), sizeof(filme->diretor), out);
    fwrite(&filme->ano, sizeof(int), 1, out);
    fwrite(filme->genero, sizeof(char), sizeof(filme->genero), out);
    fwrite(&filme->nota, sizeof(float), 1, out);
}

// Le um filme do arquivo in na posicao atual do cursor
TFilme *leFilme(FILE *in) {
    TFilme *filme = (TFilme *) malloc(sizeof(TFilme));
    if (0 >= fread(&filme->id, sizeof(int), 1, in)) {
        free(filme);
        return NULL;
    }
    fread(filme->titulo, sizeof(char), sizeof(filme->titulo), in);
    fread(filme->diretor, sizeof(char), sizeof(filme->diretor), in);
    fread(&filme->ano, sizeof(int), 1, in);
    fread(filme->genero, sizeof(char), sizeof(filme->genero), in);
    fread(&filme->nota, sizeof(float), 1, in);
    return filme;
}

// Imprime filme
void imprimeFilme(TFilme *filme) {
    printf("**********************************************\n");
    printf("Filme de ID: %d\n", filme->id);
    printf("Titulo: %s\n", filme->titulo);
    printf("Diretor: %s\n", filme->diretor);
    printf("Ano: %d\n", filme->ano);
    printf("Genero: %s\n", filme->genero);
    printf("Nota: %.1f\n", filme->nota);
    printf("**********************************************\n");
}

// Retorna tamanho do registro de filme em bytes
int tamanhoRegistroFilme() {
    return sizeof(int)       // id
           + sizeof(char) * 100  // titulo
           + sizeof(char) * 50   // diretor
           + sizeof(int)        // ano
           + sizeof(char) * 30   // genero
           + sizeof(float);     // nota
}

// Cria a base de dados de filmes
void criarBaseFilmes(FILE *out, int tam) {
    int vet[tam];
    TFilme *f;

    char *titulos[] = {"O Poderoso Chefao", "Interestelar", "Clube da Luta", "Matrix",
                       "Forrest Gump", "O Senhor dos Aneis", "Batman", "Gladiador",
                       "Titanic", "Jurassic Park"};
    char *diretores[] = {"Francis Coppola", "Christopher Nolan", "David Fincher", "Wachowski",
                         "Robert Zemeckis", "Peter Jackson", "Christopher Nolan", "Ridley Scott",
                         "James Cameron", "Steven Spielberg"};
    char *generos[] = {"Drama", "Ficcao", "Drama", "Ficcao", "Drama",
                       "Fantasia", "Acao", "Acao", "Romance", "Aventura"};
    int anos[] = {1972, 2014, 1999, 1999, 1994, 2001, 2008, 2000, 1997, 1993};

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    embaralhaFilmes(vet, tam);

    printf("\nGerando a base de dados de filmes...\n");

    for (int i = 0; i < tam; i++) {
        int idx = vet[i] % 10;
        float nota = (float)((vet[i] % 50) + 50) / 10.0;
        f = criarFilme(vet[i], titulos[idx], diretores[idx], anos[idx] + (vet[i] % 30), generos[idx], nota);
        salvaFilme(f, out);
        free(f);
    }
}

// Embaralha vetor de ids
void embaralhaFilmes(int *vet, int tam) {
    int tmp;
    srand(time(NULL));
    int trocas = (tam * 60) / 100;

    for (int t = 1; t < trocas; t++) {
        int i = rand() % tam;
        int j = rand() % tam;
        tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

// Imprime a base de dados de filmes
void imprimirBaseFilmes(FILE *out) {
    printf("\nImprimindo a base de dados de filmes...\n");
    rewind(out);
    TFilme *f;
    while ((f = leFilme(out)) != NULL) {
        imprimeFilme(f);
        free(f);
    }
}

// Retorna quantidade de registros no arquivo
int tamanhoArquivoFilmes(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = (int)(ftell(arq) / tamanhoRegistroFilme());
    return tam;
}
