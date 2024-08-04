#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int busca_fibonacci(int vetor_fibo[],int tamanho, int busca){
    int inicio = 0;
    int fim =tamanho - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio)/2;
        if(vetor_fibo[meio] == busca){
            return meio;
        }
        if(vetor_fibo[meio] < busca){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }

    return -1;
}


int main(){
    int *vetor_fibo;
    int n, busca;
    printf("Digite o número de elementos da sequência de Fibonacci: ");
    scanf("%d", &n);
    printf("Digite o número que deseja buscar: ");
    scanf("%d", &busca);
    
    vetor_fibo = (int *)malloc(n*sizeof(int));
    if (vetor_fibo == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    for(int i = 0; i < n; i++){
        vetor_fibo[i] = fibonacci(i);
    }

    printf("Sequência de Fibonacci: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor_fibo[i]);
    }
    printf("\n");

    int resultado = busca_fibonacci(vetor_fibo, n, busca);
    if (resultado != -1) {
        printf("Valor encontrado no indice: %d\n", resultado);
    } else {
        printf("Indice -1.\n");
    }

    free(vetor_fibo);
    return 0;
}