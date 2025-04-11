#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void insertionSort(int *v, int n, long long int *comparacoes, long long int *movimentacoes) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = v[i];
        
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
            (*movimentacoes)++;
        }
        (*comparacoes)++;

        if (v[j + 1] != chave) {
            v[j + 1] = chave;
            (*movimentacoes)++;
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

    insertionSort(v, tam, &comparacoes, &movimentacoes);

    QueryPerformanceCounter(&end);
    double tempo = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    FILE *comparacoesFile = fopen("comparacoes.txt", "a");
    if (comparacoesFile == NULL) {
        printf("Erro ao abrir o arquivo comparacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(comparacoesFile,"%lld, ", comparacoes);
    fclose(comparacoesFile);

    FILE *movimentacoesFile = fopen("movimentacoes.txt", "a");
    if (movimentacoesFile == NULL) {
        printf("Erro ao abrir o arquivo movimentacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(movimentacoesFile,"%lld, ", movimentacoes);
    fclose(movimentacoesFile);

    FILE *tempoFile = fopen("tempo.txt", "a");
    if (tempoFile == NULL) {
        printf("Erro ao abrir o arquivo tempo.txt.\n");
        free(v);
        return 1;
    }
    fprintf(tempoFile, "%f, ", tempo);
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