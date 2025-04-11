#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap(int *v, int n, int i, long long int *comparacoes, long long int *movimentacoes) {
    int maior = i;
    int e = 2 * i + 1;
    int d = 2 * i + 2;

    if (e < n && v[e] > v[maior]) {maior = e;}
    (*comparacoes)++;
    
    if (d < n && v[d] > v[maior]) {maior = d;}
    (*comparacoes)++;

    if (maior != i) {
        swap(&v[i], &v[maior]);
        (*movimentacoes)++;
        heap(v, n, maior, comparacoes, movimentacoes);
    }
}

void heapSort(int *v, int n, long long int *comparacoes, long long int *movimentacoes) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(v, n, i, comparacoes, movimentacoes);

    for (int i = n - 1; i >= 0; i--) {
        swap(&v[0], &v[i]);
        (*movimentacoes)++;
        heap(v, i, 0, comparacoes, movimentacoes);
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

    heapSort(v, tam, &comparacoes, &movimentacoes);

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