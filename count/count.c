#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void countSort(int *v, int n, long long int *comparacoes, long long int *movimentacoes) {
    int X[n], B[n], i, j;

    // inicializando arranjo auxiliar
    for (i=0; i<n; i++)
        X[i]=0;

    // contando menores
    for (i=1; i<n; i++) {
        for (j=i-1; j>=0; j--) {
            (*comparacoes)++;
            if (v[i]<v[j]) X[j]++;
            else X[i]++;
        }
    }

    // montando arranjo final
    for (i=0; i<n; i++) {
        B[X[i]]=v[i];
        (*movimentacoes)++;
    }

    // copiando arranjo final para original
    for (i=0; i<n; i++) {
        v[i]=B[i];
        (*movimentacoes)++;
    }
}

int main() {
    char nome[50];
    scanf("%s",nome);
    FILE *file = fopen(nome, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int tam;
    fscanf(file, "%d", &tam);
    int *v = (int*)malloc(tam * sizeof(int));

    for (int i = 0; i < tam; i++) {
        fscanf(file, "%d", &v[i]);
    }
    fclose(file);

    long long int comparacoes = 0, movimentacoes = 0;

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    countSort(v, tam, &comparacoes, &movimentacoes);

    QueryPerformanceCounter(&end);
    double tempo = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    FILE *comparacoesFile = fopen("comparacoes.txt", "a");
    if (comparacoesFile == NULL) {
        printf("Erro ao abrir o arquivo comparacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(comparacoesFile,"%lld\n", comparacoes);
    fclose(comparacoesFile);

    FILE *movimentacoesFile = fopen("movimentacoes.txt", "a");
    if (movimentacoesFile == NULL) {
        printf("Erro ao abrir o arquivo movimentacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(movimentacoesFile,"%lld\n", movimentacoes);
    fclose(movimentacoesFile);

    FILE *tempoFile = fopen("tempo.txt", "a");
    if (tempoFile == NULL) {
        printf("Erro ao abrir o arquivo tempo.txt.\n");
        free(v);
        return 1;
    }
    fprintf(tempoFile, "%f\n", tempo);
    fclose(tempoFile);

    // printf("Array ordenado: ");
    // for (int i = 0; i < tam; i++) {
    //     printf("%d ", v[i]);
    // }
    printf("\ncomparacoes: %lld\nmovimentacoes: %lld", comparacoes, movimentacoes);
    printf("\ntempo gasto: %f segundos\n", tempo);
    free(v);

    return 0;
}