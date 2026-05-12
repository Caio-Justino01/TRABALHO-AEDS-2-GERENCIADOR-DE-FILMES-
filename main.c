#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filme.c"
#include "usuario.c"
#include "buscaSequencial.c"
#include "buscaBinaria.c"
#include "insertionSort.c"
#include "log.c"
#include "operacoes.c"

// Funcao para executar testes automaticos de busca com diferentes tamanhos de base
void executarTestes(FILE *logFile) {
    int tamanhos[] = {100, 500, 1000};
    int numTamanhos = 3;

    fprintf(logFile, "==============================================\n");
    fprintf(logFile, "       TESTES AUTOMATICOS DE BUSCA\n");
    fprintf(logFile, "==============================================\n\n");

    for (int t = 0; t < numTamanhos; t++) {
        int tam = tamanhos[t];
        int comparacoes;
        clock_t inicio, fim;
        double tempo;

        printf("\n--- Testando com base de %d registros ---\n", tam);
        fprintf(logFile, "\n=== BASE DE %d REGISTROS ===\n\n", tam);

        // Cria base de filmes
        FILE *arqFilmes = fopen("filmes_teste.dat", "w+b");
        if (arqFilmes == NULL) {
            printf("Erro ao criar arquivo de filmes para teste\n");
            continue;
        }
        criarBaseFilmes(arqFilmes, tam);

        // Cria base de usuarios
        FILE *arqUsuarios = fopen("usuarios_teste.dat", "w+b");
        if (arqUsuarios == NULL) {
            printf("Erro ao criar arquivo de usuarios para teste\n");
            fclose(arqFilmes);
            continue;
        }
        criarBaseUsuarios(arqUsuarios, tam);

        // --- BUSCA SEQUENCIAL EM FILMES ---
        int chaveBusca = tam / 2;  // busca um id que existe

        inicio = clock();
        TFilme *f = buscaSequencialFilme(chaveBusca, arqFilmes, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Sequencial", "Filme", chaveBusca, tam, comparacoes, tempo, f != NULL);
        if (f) free(f);

        // --- BUSCA SEQUENCIAL EM USUARIOS ---
        inicio = clock();
        TUsuario *u = buscaSequencialUsuario(chaveBusca, arqUsuarios, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Sequencial", "Usuario", chaveBusca, tam, comparacoes, tempo, u != NULL);
        if (u) free(u);

        // --- ORDENA PARA BUSCA BINARIA ---
        printf("Ordenando base de filmes (%d registros)...\n", tam);
        insertionSortFilmes(arqFilmes, tam);
        printf("Ordenando base de usuarios (%d registros)...\n", tam);
        insertionSortUsuarios(arqUsuarios, tam);

        // --- BUSCA BINARIA EM FILMES ---
        inicio = clock();
        f = buscaBinariaFilme(chaveBusca, arqFilmes, 1, tam, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Binaria", "Filme", chaveBusca, tam, comparacoes, tempo, f != NULL);
        if (f) free(f);

        // --- BUSCA BINARIA EM USUARIOS ---
        inicio = clock();
        u = buscaBinariaUsuario(chaveBusca, arqUsuarios, 1, tam, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Binaria", "Usuario", chaveBusca, tam, comparacoes, tempo, u != NULL);
        if (u) free(u);

        // --- BUSCA POR CHAVE INEXISTENTE ---
        int chaveInexistente = tam + 100;

        inicio = clock();
        f = buscaSequencialFilme(chaveInexistente, arqFilmes, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Sequencial", "Filme (chave inexistente)", chaveInexistente, tam, comparacoes, tempo, f != NULL);
        if (f) free(f);

        inicio = clock();
        f = buscaBinariaFilme(chaveInexistente, arqFilmes, 1, tam, &comparacoes);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        salvaLog(logFile, "Binaria", "Filme (chave inexistente)", chaveInexistente, tam, comparacoes, tempo, f != NULL);
        if (f) free(f);

        fclose(arqFilmes);
        fclose(arqUsuarios);

        printf("Testes com %d registros concluidos.\n", tam);
    }

    printf("\nTodos os testes foram concluidos. Resultados salvos em log.txt\n");
}

int main() {
    FILE *arqFilmes, *arqUsuarios, *logFile;
    int opcao, tamBaseFilmes, tamBaseUsuarios;

    // Abre arquivo de log
    logFile = fopen("log.txt", "w");
    if (logFile == NULL) {
        printf("Erro ao criar arquivo de log\n");
        exit(1);
    }

    // Abre arquivos das bases
    arqFilmes = fopen("filmes.dat", "w+b");
    if (arqFilmes == NULL) {
        printf("Erro ao abrir arquivo de filmes\n");
        exit(1);
    }

    arqUsuarios = fopen("usuarios.dat", "w+b");
    if (arqUsuarios == NULL) {
        printf("Erro ao abrir arquivo de usuarios\n");
        exit(1);
    }

    // Cria bases iniciais
    int tamInicial = 100;
    criarBaseFilmes(arqFilmes, tamInicial);
    criarBaseUsuarios(arqUsuarios, tamInicial);

    // Ordena as bases para busca binaria
    printf("Ordenando bases de dados...\n");
    insertionSortFilmes(arqFilmes, tamInicial);
    insertionSortUsuarios(arqUsuarios, tamInicial);
    printf("Bases ordenadas com sucesso!\n");

    do {
        tamBaseFilmes = tamanhoArquivoFilmes(arqFilmes);
        tamBaseUsuarios = tamanhoArquivoUsuarios(arqUsuarios);

        printf("\n==============================================\n");
        printf("   SISTEMA DE GERENCIAMENTO DE CATALOGO DE FILMES\n");
        printf("==============================================\n");
        printf("1.  Cadastrar Filme\n");
        printf("2.  Cadastrar Usuario\n");
        printf("3.  Buscar Filme por ID\n");
        printf("4.  Buscar Usuario por ID\n");
        printf("5.  Buscar Filmes por Diretor\n");
        printf("6.  Atualizar Filme\n");
        printf("7.  Atualizar Usuario\n");
        printf("8.  Remover Filme\n");
        printf("9.  Remover Usuario\n");
        printf("10. Imprimir Base de Filmes\n");
        printf("11. Imprimir Base de Usuarios\n");
        printf("12. Executar Testes (diferentes tamanhos de base)\n");
        printf("0.  Sair\n");
        printf("==============================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFilme(arqFilmes);
                break;
            case 2:
                cadastrarUsuario(arqUsuarios);
                break;
            case 3:
                exibirFilme(arqFilmes, logFile, tamBaseFilmes);
                break;
            case 4:
                exibirUsuario(arqUsuarios, logFile, tamBaseUsuarios);
                break;
            case 5:
                buscarFilmesPorDiretor(arqFilmes);
                break;
            case 6:
                atualizarFilme(arqFilmes, tamBaseFilmes);
                break;
            case 7:
                atualizarUsuario(arqUsuarios, tamBaseUsuarios);
                break;
            case 8:
                removerFilme(arqFilmes, tamBaseFilmes);
                break;
            case 9:
                removerUsuario(arqUsuarios, tamBaseUsuarios);
                break;
            case 10:
                imprimirBaseFilmes(arqFilmes);
                break;
            case 11:
                imprimirBaseUsuarios(arqUsuarios);
                break;
            case 12:
                executarTestes(logFile);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    fclose(arqFilmes);
    fclose(arqUsuarios);
    fclose(logFile);

    return 0;
}
