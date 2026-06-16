#include "filme.h"

// Cria um filme na memoria RAM.
TFilme *criarFilme(int id, char *titulo, char *diretor, int ano, char *genero, float nota) {
    TFilme *filme = (TFilme *) malloc(sizeof(TFilme));
    if (filme) {
        memset(filme, 0, sizeof(TFilme));
        filme->id = id;
        strcpy(filme->titulo, titulo);
        strcpy(filme->diretor, diretor);
        filme->ano = ano;
        strcpy(filme->genero, genero);
        filme->nota = nota;
    }
    return filme;
}

// Salva o filme no arquivo, na posicao atual do cursor.
void salvaFilme(TFilme *filme, FILE *out) {
    fwrite(&filme->id, sizeof(int), 1, out);
    fwrite(filme->titulo, sizeof(char), sizeof(filme->titulo), out);
    fwrite(filme->diretor, sizeof(char), sizeof(filme->diretor), out);
    fwrite(&filme->ano, sizeof(int), 1, out);
    fwrite(filme->genero, sizeof(char), sizeof(filme->genero), out);
    fwrite(&filme->nota, sizeof(float), 1, out);
}

// Le os bytes do arquivo e remonta a struct na memoria RAM.
TFilme *leFilme(FILE *in) {
    TFilme *filme = (TFilme *) malloc(sizeof(TFilme));
    if (filme == NULL) {
        return NULL;
    }
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

// Tamanho fixo usado nos fseek, sem depender de padding da struct.
int tamanhoRegistroFilme() {
    return sizeof(int)
           + sizeof(char) * 100
           + sizeof(char) * 50
           + sizeof(int)
           + sizeof(char) * 30
           + sizeof(float);
}

static void gravarFilmeGerado(FILE *out, int id) {
    char *titulos[] = {"O Poderoso Chefao", "Interestelar", "Clube da Luta", "Matrix",
                       "Forrest Gump", "O Senhor dos Aneis", "Batman", "Gladiador",
                       "Titanic", "Jurassic Park"};
    char *diretores[] = {"Francis Coppola", "Christopher Nolan", "David Fincher", "Wachowski",
                         "Robert Zemeckis", "Peter Jackson", "Christopher Nolan", "Ridley Scott",
                         "James Cameron", "Steven Spielberg"};
    char *generos[] = {"Drama", "Ficcao", "Drama", "Ficcao", "Drama",
                       "Fantasia", "Acao", "Acao", "Romance", "Aventura"};
    int anos[] = {1972, 2014, 1999, 1999, 1994, 2001, 2008, 2000, 1997, 1993};

    int idx = id % 10;
    float nota = (float)((id % 50) + 50) / 10.0;
    TFilme *f = criarFilme(id, titulos[idx], diretores[idx],
                           anos[idx] + (id % 30), generos[idx], nota);
    salvaFilme(f, out);
    free(f);
}

// Cria a base de filmes usada na Parte 1.
void criarBaseFilmes(FILE *out, int tam) {
    int vet[tam];

    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;
    }

    embaralhaFilmes(vet, tam);

    printf("\nGerando a base de dados de filmes...\n");
    for (int i = 0; i < tam; i++) {
        gravarFilmeGerado(out, vet[i]);
    }
}

// Cria base desordenada de filmes para a Parte 2 (ordenacao externa).
void criarBaseFilmesDesordenada(FILE *out, int tam, int silencio) {
    int *ids = (int *) malloc(sizeof(int) * tam);
    if (ids == NULL) {
        printf("Erro: memoria insuficiente para %d registros\n", tam);
        return;
    }

    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    srand(time(NULL));
    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = ids[i];
        ids[i] = ids[j];
        ids[j] = tmp;
    }

    if (!silencio) {
        printf("Gerando base de %d filmes desordenada...\n", tam);
    }

    rewind(out);
    for (int i = 0; i < tam; i++) {
        gravarFilmeGerado(out, ids[i]);
    }
    fflush(out);
    free(ids);
}

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

void imprimirBaseFilmes(FILE *out) {
    printf("\nImprimindo a base de dados de filmes...\n");
    rewind(out);
    TFilme *f;
    while ((f = leFilme(out)) != NULL) {
        imprimeFilme(f);
        free(f);
    }
}

int tamanhoArquivoFilmes(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    return (int)(ftell(arq) / tamanhoRegistroFilme());
}
