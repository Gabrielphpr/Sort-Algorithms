#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void salvar(int *vetor, int tamanho, const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "w");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        fprintf(file, "%d\n", vetor[i]);
    }
    fclose(file);
}

int main() {
    int tamanho;
    char ordem[20];
    srand(time(NULL));

    printf("Tamanho do vetor: ");
    scanf("%d", &tamanho);

    int *vetor = (int *)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória");
        return 1;
    }

    while (!((strcmp(ordem, "ordenado") == 0) || (strcmp(ordem, "inverso") == 0) || (strcmp(ordem, "aleatorio") == 0)))
    {
        printf("Ordem (ordenado, inverso, aleatorio): ");
        scanf("%s", ordem);
    }
    
    if (strcmp(ordem, "ordenado") == 0) {
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = i + 1;
        }
        char nome_arquivo[30];
        sprintf(nome_arquivo, "%d-vetor_ordenado.txt", tamanho);
        salvar(vetor, tamanho, nome_arquivo);
    }
    
    else if (strcmp(ordem, "inverso") == 0) {
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = tamanho - i;
        }
        char nome_arquivo[30];
            sprintf(nome_arquivo, "%d-vetor_inverso.txt", tamanho);
            salvar(vetor, tamanho, nome_arquivo);
    }
    
    else if (strcmp(ordem, "aleatorio") == 0) {
        for (int i = 0; i < 5; i++) {
            for (int i = 0; i < tamanho; i++) {
                vetor[i] = rand() % 1000000;
            }
            char nome_arquivo[30];
            sprintf(nome_arquivo, "%d-vetor_aleatorio_%d.txt", tamanho, i + 1);
            salvar(vetor, tamanho, nome_arquivo);
        }
    }

    free(vetor);
    return 0;
}
