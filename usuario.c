#include "usuario.h"

// Cria usuario
TUsuario *criarUsuario(int id, char *nome, char *email) {
    TUsuario *usuario = (TUsuario *) malloc(sizeof(TUsuario));
    if (usuario) memset(usuario, 0, sizeof(TUsuario));
    usuario->id = id;
    strcpy(usuario->nome, nome);
    strcpy(usuario->email, email);
    return usuario;
}

// Salva usuario no arquivo out, na posicao atual do cursor
void salvaUsuario(TUsuario *usuario, FILE *out) {
    fwrite(&usuario->id, sizeof(int), 1, out);
    fwrite(usuario->nome, sizeof(char), sizeof(usuario->nome), out);
    fwrite(usuario->email, sizeof(char), sizeof(usuario->email), out);
}

// Le um usuario do arquivo in na posicao atual do cursor
TUsuario *leUsuario(FILE *in) {
    TUsuario *usuario = (TUsuario *) malloc(sizeof(TUsuario));
    if (0 >= fread(&usuario->id, sizeof(int), 1, in)) {
        free(usuario);
        return NULL;
    }
    fread(usuario->nome, sizeof(char), sizeof(usuario->nome), in);
    fread(usuario->email, sizeof(char), sizeof(usuario->email), in);
    return usuario;
}

// Imprime usuario
void imprimeUsuario(TUsuario *usuario) {
    printf("**********************************************\n");
    printf("Usuario de ID: %d\n", usuario->id);
    printf("Nome: %s\n", usuario->nome);
    printf("Email: %s\n", usuario->email);
    printf("**********************************************\n");
}

// Retorna tamanho do registro de usuario em bytes
int tamanhoRegistroUsuario() {
    return sizeof(int)       // id
           + sizeof(char) * 50   // nome
           + sizeof(char) * 50;  // email
}

// Cria a base de dados de usuarios
void criarBaseUsuarios(FILE *out, int tam) {
    int vet[tam];
    TUsuario *u;

    char *nomes[] = {"Ana Silva", "Bruno Costa", "Carlos Lima", "Diana Souza",
                     "Eduardo Santos", "Fernanda Reis", "Gabriel Alves", "Helena Rocha",
                     "Igor Mendes", "Julia Ferreira"};
    char *dominios[] = {"gmail.com", "hotmail.com", "yahoo.com", "outlook.com", "ufop.edu.br", "gmail.com", "hotmail.com", "yahoo.com", "outlook.com", "ufop.edu.br"};

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    embaralhaUsuarios(vet, tam);

    printf("\nGerando a base de dados de usuarios...\n");

    for (int i = 0; i < tam; i++) {
        int idx = vet[i] % 10;
        char email[50];
        sprintf(email, "usuario%d@%s", vet[i], dominios[vet[i] % 5]);
        u = criarUsuario(vet[i], nomes[idx], email);
        salvaUsuario(u, out);
        free(u);
    }
}

// Embaralha vetor de ids
void embaralhaUsuarios(int *vet, int tam) {
    int tmp;
    srand(time(NULL) + 1);
    int trocas = (tam * 60) / 100;

    for (int t = 1; t < trocas; t++) {
        int i = rand() % tam;
        int j = rand() % tam;
        tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
}

// Imprime a base de dados de usuarios
void imprimirBaseUsuarios(FILE *out) {
    printf("\nImprimindo a base de dados de usuarios...\n");
    rewind(out);
    TUsuario *u;
    while ((u = leUsuario(out)) != NULL) {
        imprimeUsuario(u);
        free(u);
    }
}

// Retorna quantidade de registros no arquivo
int tamanhoArquivoUsuarios(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = (int)(ftell(arq) / tamanhoRegistroUsuario());
    return tam;
}
