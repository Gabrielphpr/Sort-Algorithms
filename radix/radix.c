#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void countSort(int *v, int n, int exp, long long int *movimentacoes) {
    int* saida = (int*)malloc(n * sizeof(int));
    int contador[10] = {0};

    // Conta a frequencia do digito dos numeros dado o expoente
    for (int i = 0; i < n; i++) {
        contador[(v[i] / exp) % 10]++;
    }
    // Modifica contador[i] para conter a posição atual do dígito em saida
    for (int i = 1; i < 10; i++) {
        contador[i] += contador[i - 1];
    }
    
    // Constrói o array de saída
    for (int i = n - 1; i >= 0; i--) {
        saida[contador[(v[i] / exp) % 10] - 1] = v[i];
        contador[(v[i] / exp) % 10]--;
        (*movimentacoes)++; 
    }
    
    // Copia o array de saída para v, para que v contenha os números ordenados por dígito atual
    for (int i = 0; i < n; i++) {
        v[i] = saida[i];
        (*movimentacoes)++;
    }
    
    free(saida);
}

void radixSort(int *v, int n, long long int *movimentacoes, long long int *comparacoes) {
    int maior = v[0];
    for (int i = 1; i < n; i++) {
        (*comparacoes)++;
        if (maior < v[i]) 
            maior = v[i];
    }

    for (int exp = 1; maior / exp > 0; exp *= 10) {
        countSort(v, n, exp, movimentacoes);
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

    long long int movimentacoes = 0, comparacoes=0;

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    radixSort(v, tam, &movimentacoes, &comparacoes);

    QueryPerformanceCounter(&end);
    double tempo = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    FILE *movimentacoesFile = fopen("movimentacoes.txt", "a");
    if (movimentacoesFile == NULL) {
        printf("Erro ao abrir o arquivo movimentacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(movimentacoesFile,"%lld, ", movimentacoes);
    fclose(movimentacoesFile);

    FILE *comparacoesFile = fopen("comparacoes.txt", "a");
    if (comparacoesFile == NULL) {
        printf("Erro ao abrir o arquivo comparacoes.txt.\n");
        free(v);
        return 1;
    }
    fprintf(comparacoesFile, "%f, ", tempo);
    fclose(comparacoesFile);

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
    printf("\nComparacoes: %lld \nMovimentacoes: %lld\n", comparacoes, movimentacoes);
    printf("Tempo de execucao: %f segundos\n", tempo);

    free(v);
    return 0;
}