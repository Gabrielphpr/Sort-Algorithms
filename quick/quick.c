#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort (int *v, int l, int r, long long int *comparacoes, long long int *movimentacoes){

    //se o array tiver 2 ou menos elementos, a escolha do pivo é desconsiderada e tem-se um caso exclusivo
    if (r - l < 2)
    {
        if (r - l == 1 && v[r] < v[l])
        {
            swap(&v[r], &v[l]);
            (*movimentacoes)++;
        }
    }
    //para arrays maiores que 2 elementos, tem-se a escolha do pivo
    else
    {
        int meio = l + (r-l)/2, index = meio;

        if (v[l] > v[meio])
        {
            index = l;
        }
        if (v[r] > v[l])
        {
            index = r;
        }
        if (v[meio] > v[r])
        {
            index = meio;
        }

        swap(&v[index], &v[meio]);
        (*movimentacoes)++;

        (*comparacoes) = (*comparacoes) + 3;
        int pivo = v[index];

        int i = l, j = r;

        while (1)
        {
            while (v[++i] < pivo)
                (*comparacoes)++;
            while (v[--j] > pivo)
                (*comparacoes)++;

            if (i >= j) break;

            swap(&v[i], &v[j]);
            (*movimentacoes)++;
        }
        
        swap(&v[i], &v[r]);
        (*movimentacoes)++;

        quickSort(v, l, i-1, comparacoes, movimentacoes);
        quickSort(v, i+1, r, comparacoes, movimentacoes);
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

    quickSort(v, 0, tam-1, &comparacoes, &movimentacoes);

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