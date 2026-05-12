#include "filme.h"
#include "usuario.h"
#include "insertionSort.h"

// Ordena arquivo de filmes por id usando insertion sort
void insertionSortFilmes(FILE *arq, int tam) {
    int i;
    int t = tamanhoRegistroFilme();

    for (int j = 2; j <= tam; j++) {
        fseek(arq, (j - 1) * t, SEEK_SET);
        TFilme *fj = leFilme(arq);
        i = j - 1;

        fseek(arq, (i - 1) * t, SEEK_SET);
        TFilme *fi = leFilme(arq);

        while ((i > 0) && (fi->id > fj->id)) {
            fseek(arq, i * t, SEEK_SET);
            salvaFilme(fi, arq);
            i = i - 1;
            if (i > 0) {
                fseek(arq, (i - 1) * t, SEEK_SET);
                free(fi);
                fi = leFilme(arq);
            }
        }

        fseek(arq, i * t, SEEK_SET);
        salvaFilme(fj, arq);

        free(fj);
        free(fi);
    }

    fflush(arq);
}

// Ordena arquivo de usuarios por id usando insertion sort
void insertionSortUsuarios(FILE *arq, int tam) {
    int i;
    int t = tamanhoRegistroUsuario();

    for (int j = 2; j <= tam; j++) {
        fseek(arq, (j - 1) * t, SEEK_SET);
        TUsuario *uj = leUsuario(arq);
        i = j - 1;

        fseek(arq, (i - 1) * t, SEEK_SET);
        TUsuario *ui = leUsuario(arq);

        while ((i > 0) && (ui->id > uj->id)) {
            fseek(arq, i * t, SEEK_SET);
            salvaUsuario(ui, arq);
            i = i - 1;
            if (i > 0) {
                fseek(arq, (i - 1) * t, SEEK_SET);
                free(ui);
                ui = leUsuario(arq);
            }
        }

        fseek(arq, i * t, SEEK_SET);
        salvaUsuario(uj, arq);

        free(uj);
        free(ui);
    }

    fflush(arq);
}
