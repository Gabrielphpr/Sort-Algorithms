#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void Merge(int *v, int i, int m, int f, long long int *comparacoes, long long int *movimentacoes){
    int n1 = m - i + 1;
    int n2 = f - m;
    
    int *Esquerda = (int *)malloc(n1 * sizeof(int));
    int *Direita = (int *)malloc(n2 * sizeof(int));
    
    int e, d;
    for(e = 0; e < n1; e++) {
        Esquerda[e] = v[i + e];
        (*movimentacoes)++;
    }
    for(int d = 0; d < n2; d++) {
        Direita[d] = v[m + 1 + d];
        (*movimentacoes)++;
    }

    e=d=0;
    int k = i;
    while (e < n1 && d < n2) {
        if (Esquerda[e] <= Direita[d]) {
            v[k] = Esquerda[e];
            e++;
        } 
        else {
            v[k] = Direita[d];
            d++;
        }
        (*comparacoes)++;
        (*movimentacoes)++;
        k++;
    }
    
    while (e < n1) {
        v[k] = Esquerda[e];
        (*movimentacoes)++;
        e++;
        k++;
    }
    
    while (d < n2) {
        v[k] = Direita[d];
        (*movimentacoes)++;
        d++;
        k++;
    }

    free(Esquerda);
    free(Direita);
}

void MergeSort(int *v, int i, int f, long long int *comparacoes, long long int *movimentacoes){
    if(i<f){
		int m = i+(f-i)/2;
		MergeSort(v, i, m, comparacoes, movimentacoes);
		MergeSort(v, m+1, f, comparacoes, movimentacoes);
		Merge(v, i, m, f, comparacoes, movimentacoes);
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

    MergeSort(v, 0, tam-1, &comparacoes, &movimentacoes);

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