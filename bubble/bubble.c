#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *v, int tam, long long int *comparacoes, long long int *movimentacoes) {
    int i, j, temp;
    int sentinela;

    for (i = 0; i < tam-1; i++) {
        sentinela = 0;
        for (j = 0; j < tam-1-i; j++) {
            (*comparacoes)++; // comparação pelo if adiante
            if (v[j] > v[j+1]) {
                swap(&v[j], &v[j+1]);
                (*movimentacoes)++; // movimentação pelo swap
                sentinela = 1;
            }
        }

        if (sentinela == 0) {
            break;
        }
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

    bubbleSort(v, tam, &comparacoes, &movimentacoes);

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
    printf("\nComparacoes: %lld\nMovimentacoes: %lld\n", comparacoes, movimentacoes);
    printf("Tempo de execucao: %f segundos\n", tempo);

    free(v);
    return 0;
}