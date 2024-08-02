#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    FILE *arq;
    int **matriz;
    int i, j, linhas=0, colunas=0;
    
    // Abrindo o arquivo
    arq=fopen("matriz.txt","r");
    if(!(arq)){
        printf("Erro, não foi possivel abrir o arquivo.");
        exit(1);
    }

    //Fazendo a leitura da quantidade de linhas e colunas
    fscanf(arq,"%d %d", &linhas, &colunas);
    printf("A quantidade de linhas: %d e colunas: %d \n", linhas, colunas);

    //Alocacação da matriz
    matriz=(int **)malloc(linhas*sizeof(int *));
    for(i=0; i<linhas;i++){
        matriz[i]=(int *)malloc(colunas*sizeof(int));
    }

    // Fazendo a leitura dos dados
    for(i=0;i<linhas; i++){
        for(j=0;j<colunas;j++){
            fscanf(arq,"%d", &matriz[i][j]);
        }
    }

    for(i=0;i<linhas; i++){
        for(j=0;j<colunas;j++){
        printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }

    fclose(arq);


    
    return 0;
}