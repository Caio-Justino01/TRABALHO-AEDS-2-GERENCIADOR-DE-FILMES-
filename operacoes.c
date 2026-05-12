#include "filme.h"
#include "usuario.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "log.h"
#include "operacoes.h"

// Cadastrar um novo filme na base
void cadastrarFilme(FILE *arqFilmes) {
    int id, ano, comparacoes;
    char titulo[100], diretor[50], genero[30];
    float nota;
// coletar os ddados de filme na ram
    printf("\n--- Cadastrar Filme ---\n");
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    // Verifica se o ID ja existe na base antes de cadastrar
    TFilme *existente = buscaSequencialFilme(id, arqFilmes, &comparacoes);
    if (existente != NULL) {
        printf("Erro: Ja existe um filme com ID %d na base!\n", id);
        free(existente);
        // Encontra o maior ID na base para sugerir o proximo disponivel
        rewind(arqFilmes);
        int maiorId = 0;
        TFilme *tmp;
        while ((tmp = leFilme(arqFilmes)) != NULL) {
            if (tmp->id > maiorId) maiorId = tmp->id;
            free(tmp);
        }
        printf("Sugestao: o proximo ID disponivel e %d\n", maiorId + 1);
        return;
    }

    printf("Titulo: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    printf("Diretor: ");
    fgets(diretor, 50, stdin);
    diretor[strcspn(diretor, "\n")] = '\0';
    printf("Ano: ");
    scanf("%d", &ano);
    getchar();
    printf("Genero: ");
    fgets(genero, 30, stdin);
    genero[strcspn(genero, "\n")] = '\0';
    printf("Nota: ");
    scanf("%f", &nota);

    TFilme *f = criarFilme(id, titulo, diretor, ano, genero, nota);// na ram

    // Posiciona no final do arquivo e salva
    fseek(arqFilmes, 0, SEEK_END);
    salvaFilme(f, arqFilmes); //grava no disco
    fflush(arqFilmes); //forca gravacao
    free(f); // limpa a RAM

    printf("Filme cadastrado com sucesso!\n");
}

// Cadastrar um novo usuario na base (mesma logica de filmes)
void cadastrarUsuario(FILE *arqUsuarios) {
    int id, comparacoes;
    char nome[50], email[50];
// captar os dados na ram
    printf("\n--- Cadastrar Usuario ---\n");
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    // Verifica se o ID ja existe na base antes de cadastrar
    TUsuario *existente = buscaSequencialUsuario(id, arqUsuarios, &comparacoes);
    if (existente != NULL) {
        printf("Erro: Ja existe um usuario com ID %d na base!\n", id);
        free(existente);
        return;
    }

    printf("Nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Email: ");
    fgets(email, 50, stdin);
    email[strcspn(email, "\n")] = '\0';

    TUsuario *u = criarUsuario(id, nome, email);

    fseek(arqUsuarios, 0, SEEK_END); // posiciona no final
    salvaUsuario(u, arqUsuarios);// salva no disco
    fflush(arqUsuarios); // forca gravacao
    free(u);// libera espaco

    printf("Usuario cadastrado com sucesso!\n");
}

// Atualizar um filme existente na base
void atualizarFilme(FILE *arqFilmes, int tamBase) {
    int chave, comparacoes;

    printf("\n--- Atualizar Filme ---\n");
    printf("Digite o ID do filme a atualizar: ");
    scanf("%d", &chave);
    getchar();

    // Usa busca sequencial para encontrar o filme
    TFilme *f = buscaSequencialFilme(chave, arqFilmes, &comparacoes);

    if (f != NULL) {
        printf("Filme encontrado:\n");
        imprimeFilme(f);

        printf("\nDigite os novos dados:\n");
        printf("Titulo: ");
        fgets(f->titulo, 100, stdin);
        f->titulo[strcspn(f->titulo, "\n")] = '\0';
        printf("Diretor: ");
        fgets(f->diretor, 50, stdin);
        f->diretor[strcspn(f->diretor, "\n")] = '\0';
        printf("Ano: ");
        scanf("%d", &f->ano);
        getchar();
        printf("Genero: ");
        fgets(f->genero, 30, stdin);
        f->genero[strcspn(f->genero, "\n")] = '\0';
        printf("Nota: ");
        scanf("%f", &f->nota);

        // Volta uma posicao para sobrescrever o registro
        fseek(arqFilmes, -tamanhoRegistroFilme(), SEEK_CUR);
        salvaFilme(f, arqFilmes);
        fflush(arqFilmes);
        free(f);

        printf("Filme atualizado com sucesso!\n");
    } else {
        printf("Filme com ID %d nao encontrado.\n", chave);
    }
}

// Atualizar um usuario existente na base
void atualizarUsuario(FILE *arqUsuarios, int tamBase) {
    int chave, comparacoes;

    printf("\n--- Atualizar Usuario ---\n");
    printf("Digite o ID do usuario a atualizar: ");
    scanf("%d", &chave);
    getchar();

    TUsuario *u = buscaSequencialUsuario(chave, arqUsuarios, &comparacoes);

    if (u != NULL) {
        printf("Usuario encontrado:\n");
        imprimeUsuario(u);

        printf("\nDigite os novos dados:\n");
        printf("Nome: ");
        fgets(u->nome, 50, stdin);
        u->nome[strcspn(u->nome, "\n")] = '\0';
        printf("Email: ");
        fgets(u->email, 50, stdin);
        u->email[strcspn(u->email, "\n")] = '\0';

        fseek(arqUsuarios, -tamanhoRegistroUsuario(), SEEK_CUR);
        salvaUsuario(u, arqUsuarios);
        fflush(arqUsuarios);
        free(u);

        printf("Usuario atualizado com sucesso!\n");
    } else {
        printf("Usuario com ID %d nao encontrado.\n", chave);
    }
}

// Remover um filme (marca como removido com id = -1)
void removerFilme(FILE *arqFilmes, int tamBase) {
    int chave, comparacoes;

    printf("\n--- Remover Filme ---\n");
    printf("Digite o ID do filme a remover: ");
    scanf("%d", &chave);

    TFilme *f = buscaSequencialFilme(chave, arqFilmes, &comparacoes);

    if (f != NULL) {
        printf("Filme encontrado:\n");
        imprimeFilme(f);

        f->id = -1;  // marca como removido

        fseek(arqFilmes, -tamanhoRegistroFilme(), SEEK_CUR);
        salvaFilme(f, arqFilmes);
        fflush(arqFilmes);
        free(f);

        printf("Filme removido com sucesso!\n");
    } else {
        printf("Filme com ID %d nao encontrado.\n", chave);
    }
}

// Remover um usuario (marca como removido com id = -1)
void removerUsuario(FILE *arqUsuarios, int tamBase) {
    int chave, comparacoes;

    printf("\n--- Remover Usuario ---\n");
    printf("Digite o ID do usuario a remover: ");
    scanf("%d", &chave);

    TUsuario *u = buscaSequencialUsuario(chave, arqUsuarios, &comparacoes);

    if (u != NULL) {
        printf("Usuario encontrado:\n");
        imprimeUsuario(u);

        u->id = -1;  // marca como removido

        fseek(arqUsuarios, -tamanhoRegistroUsuario(), SEEK_CUR);
        salvaUsuario(u, arqUsuarios);
        fflush(arqUsuarios);
        free(u);

        printf("Usuario removido com sucesso!\n");
    } else {
        printf("Usuario com ID %d nao encontrado.\n", chave);
    }
}

// Buscar filmes por diretor (usando busca sequencial)
void buscarFilmesPorDiretor(FILE *arqFilmes) {
    char diretor[50];
    int encontrados = 0;

    printf("\n--- Buscar Filmes por Diretor ---\n");
    printf("Digite o nome do diretor: ");
    getchar();
    fgets(diretor, 50, stdin);
    diretor[strcspn(diretor, "\n")] = '\0';

    rewind(arqFilmes); // leitura do byte zero
    TFilme *f;

    while ((f = leFilme(arqFilmes)) != NULL) {
        if (f->id != -1 && strcmp(f->diretor, diretor) == 0) { // o(n)
            imprimeFilme(f);
            encontrados++;
        }
        free(f);
    }

    if (encontrados == 0) {
        printf("Nenhum filme encontrado para o diretor '%s'.\n", diretor);
    } else {
        printf("\nTotal de filmes encontrados: %d\n", encontrados);
    }
}

// Exibir informacoes de um filme buscando pelo id
void exibirFilme(FILE *arqFilmes, FILE *logFile, int tamBase) {
    int chave, comparacoes, tipoBusca;
    clock_t inicio, fim;
    double tempo;

    printf("\nDigite o ID do filme: ");
    scanf("%d", &chave);
    printf("Tipo de busca (1-Sequencial, 2-Binaria): ");
    scanf("%d", &tipoBusca);

    if (tipoBusca == 1) {
        inicio = clock();
        TFilme *f = buscaSequencialFilme(chave, arqFilmes, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (f != NULL) {
            imprimeFilme(f);
            salvaLog(logFile, "Sequencial", "Filme", chave, tamBase, comparacoes, tempo, 1);
            free(f);
        } else {
            printf("Filme com ID %d nao encontrado.\n", chave);
            salvaLog(logFile, "Sequencial", "Filme", chave, tamBase, comparacoes, tempo, 0);
        }
    } else {
        inicio = clock();
        TFilme *f = buscaBinariaFilme(chave, arqFilmes, 1, tamBase, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (f != NULL) {
            imprimeFilme(f);
            salvaLog(logFile, "Binaria", "Filme", chave, tamBase, comparacoes, tempo, 1);
            free(f);
        } else {
            printf("Filme com ID %d nao encontrado.\n", chave);
            salvaLog(logFile, "Binaria", "Filme", chave, tamBase, comparacoes, tempo, 0);
        }
    }
}

// Exibir informacoes de um usuario buscando pelo id
void exibirUsuario(FILE *arqUsuarios, FILE *logFile, int tamBase) {
    int chave, comparacoes, tipoBusca;
    clock_t inicio, fim;
    double tempo;

    printf("\nDigite o ID do usuario: ");
    scanf("%d", &chave);
    printf("Tipo de busca (1-Sequencial, 2-Binaria): ");
    scanf("%d", &tipoBusca);

    if (tipoBusca == 1) {
        inicio = clock();
        TUsuario *u = buscaSequencialUsuario(chave, arqUsuarios, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (u != NULL) {
            imprimeUsuario(u);
            salvaLog(logFile, "Sequencial", "Usuario", chave, tamBase, comparacoes, tempo, 1);
            free(u);
        } else {
            printf("Usuario com ID %d nao encontrado.\n", chave);
            salvaLog(logFile, "Sequencial", "Usuario", chave, tamBase, comparacoes, tempo, 0);
        }
    } else {
        inicio = clock();
        TUsuario *u = buscaBinariaUsuario(chave, arqUsuarios, 1, tamBase, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        if (u != NULL) {
            imprimeUsuario(u);
            salvaLog(logFile, "Binaria", "Usuario", chave, tamBase, comparacoes, tempo, 1);
            free(u);
        } else {
            printf("Usuario com ID %d nao encontrado.\n", chave);
            salvaLog(logFile, "Binaria", "Usuario", chave, tamBase, comparacoes, tempo, 0);
        }
    }
}
