// ============================================================
// PROGRAMA PRINCIPAL - Sistema de Catalogo de Filmes
// Trabalho Pratico AEDS II - Caio Justino - UFOP
// ============================================================
// Estrutura:
//   1. Tela de boas-vindas: escolhe PARTE 1 ou PARTE 2
//   2. PARTE 1: CRUD com Insertion Sort
//   3. PARTE 2: Demos das Q1, Q2+Q3 e testes Q4
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filme.h"
#include "usuario.h"
#include "favorito.h"
#include "buscaSequencial.h"
#include "buscaBinaria.h"
#include "insertionSort.h"
#include "log.h"
#include "operacoes.h"
#include "interacoes.h"
// ----- PARTE 2 -----
#include "selectionSortDisco.h"
#include "selecaoSubstituicao.h"
#include "intercalacaoOtima.h"
#include "testesParte2.h"
// -------------------

// ============================================================
// PARTE 1 - Sistema CRUD
// ============================================================
void executarParte1(FILE *logFile) {
    FILE *arqFilmes = fopen("filmes.dat", "w+b");
    FILE *arqUsuarios = fopen("usuarios.dat", "w+b");
    FILE *arqFavoritos = fopen("favoritos.dat", "w+b");
    if (!arqFilmes || !arqUsuarios || !arqFavoritos) {
        printf("Erro ao abrir arquivos\n");
        return;
    }

    int tam, escolha;
    printf("\n--- PARTE 1 - Tamanho da base ---\n");
    printf("1. 100 registros\n");
    printf("2. 500 registros\n");
    printf("3. 1.000 registros\n");
    printf("4. 5.000 registros\n");
    printf("Opcao: ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1: tam = 100; break;
        case 2: tam = 500; break;
        case 3: tam = 1000; break;
        case 4: tam = 5000; break;
        default: tam = 100; break;
    }

    printf("\nGerando base de %d registros...\n", tam);
    criarBaseFilmes(arqFilmes, tam);
    criarBaseUsuarios(arqUsuarios, tam);

    printf("Ordenando com Insertion Sort...\n");
    insertionSortFilmes(arqFilmes, tam);
    insertionSortUsuarios(arqUsuarios, tam);
    printf("Pronto!\n");

    int opcao, tF, tU;
    do {
        tF = tamanhoArquivoFilmes(arqFilmes);
        tU = tamanhoArquivoUsuarios(arqUsuarios);
        printf("\n--- MENU PARTE 1 ---\n");
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
        printf("--- Questao 6 (Interacoes) ---\n");
        printf("12. Favoritar Filme\n");
        printf("13. Listar Favoritos de um Usuario\n");
        printf("0.  Voltar ao menu inicial\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:  cadastrarFilme(arqFilmes); break;
            case 2:  cadastrarUsuario(arqUsuarios); break;
            case 3:  exibirFilme(arqFilmes, logFile, tF); break;
            case 4:  exibirUsuario(arqUsuarios, logFile, tU); break;
            case 5:  buscarFilmesPorDiretor(arqFilmes); break;
            case 6:  atualizarFilme(arqFilmes); break;
            case 7:  atualizarUsuario(arqUsuarios); break;
            case 8:  removerFilme(arqFilmes); break;
            case 9:  removerUsuario(arqUsuarios); break;
            case 10: imprimirBaseFilmes(arqFilmes); break;
            case 11: imprimirBaseUsuarios(arqUsuarios); break;
            case 12: favoritarFilme(arqFavoritos, arqUsuarios, arqFilmes, tU, tF, logFile); break;
            case 13: listarFavoritosDoUsuario(arqFavoritos, arqUsuarios, arqFilmes, tU, tF, logFile); break;
            case 0:  printf("Voltando ao menu inicial...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    fclose(arqFilmes);
    fclose(arqUsuarios);
    fclose(arqFavoritos);
}

// ============================================================
// PARTE 2 - Ordenacao Externa
// ============================================================
void executarParte2(FILE *logFile) {
    int tam, escolha;
    printf("\n--- PARTE 2 - Tamanho da base ---\n");
    printf("1. 100 registros\n");
    printf("2. 500 registros\n");
    printf("3. 1.000 registros\n");
    printf("4. 5.000 registros\n");
    printf("5. 10.000 registros\n");
    printf("6. 100.000 registros\n");
    printf("7. 500.000 registros\n");
    printf("Opcao: ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1: tam = 100; break;
        case 2: tam = 500; break;
        case 3: tam = 1000; break;
        case 4: tam = 5000; break;
        case 5: tam = 10000; break;
        case 6: tam = 100000; break;
        case 7: tam = 500000; break;
        default: tam = 1000; break;
    }

    int opcao;
    do {
        printf("\n--- MENU PARTE 2 ---\n");
        printf("1. Demonstrar Selection Sort em Disco (Questao 1)\n");
        printf("2. Demonstrar Selecao com Substituicao + Intercalacao Otima (Q2+Q3)\n");
        printf("3. Executar testes da Questao 4 (1k, 10k, 100k, 500k)\n");
        printf("0. Voltar ao menu inicial\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: demonstrarQ1("filmes.dat", tam, logFile); break;
            case 2: demonstrarQ2Q3("filmes.dat", tam, logFile); break;
            case 3: executarTestesParte2(); break;
            case 0: printf("Voltando ao menu inicial...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// ============================================================
// MAIN - Menu inicial
// ============================================================
int main() {
    FILE *logFile = fopen("log.txt", "w");
    if (!logFile) { printf("Erro ao criar log\n"); return 1; }

    int opcao;
    do {
        printf("\n==============================================\n");
        printf("  TRABALHO PRATICO AEDS II - Caio Justino\n");
        printf("==============================================\n");
        printf("1. PARTE 1 do trabalho (Sistema CRUD)\n");
        printf("2. PARTE 2 do trabalho (Ordenacao Externa)\n");
        printf("0. Sair\n");
        printf("==============================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: executarParte1(logFile); break;
            case 2: executarParte2(logFile); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    fclose(logFile);
    return 0;
}
