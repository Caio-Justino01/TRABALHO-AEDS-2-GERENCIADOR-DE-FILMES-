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
#include "usuario"

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

    // Usuario escolhe o tamanho da base de dados
    int tamInicial, escolha;
    printf("\n==============================================\n");
    printf("   ESCOLHA O TAMANHO DA BASE DE DADOS\n");
    printf("==============================================\n");
    printf("1. 100 registros\n");
    printf("2. 500 registros\n");
    printf("3. 1000 registros\n");
    printf("4. 5000 registros\n");
    printf("==============================================\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1: tamInicial = 100; break;
        case 2: tamInicial = 500; break;
        case 3: tamInicial = 1000; break;
        case 4: tamInicial = 5000; break;
        default:
            printf("Opcao invalida! Usando base de 100 registros.\n");
            tamInicial = 100;
    }

    printf("\nCriando base de %d registros...\n", tamInicial);
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
