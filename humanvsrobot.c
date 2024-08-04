#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


int fuga_humana(char **matriz, int linhas, int colunas){
    // Encontrando as coordenadas de H e Z
    int coordH1 = -1, coordH2 = -1; // Coordenadas de 10
    int coordZ1 = -1, coordZ2 = -1; // Coordenadas de 20
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] =='H') {
                coordH1 = i;
                coordH2 = j;
            }
            if (matriz[i][j] == 'Z') {
                coordZ1 = i;
                coordZ2 = j;
            }
        }
    }

// Verificando se as coordenadas foram encontradas
    if (coordH1 == -1 || coordH2 == -1 || coordZ1 == -1 || coordZ2 == -1) {
        printf("Coordenadas de H ou Z não encontradas.\n");
        return -1;
    }

    // Imprimindo as coordenadas encontradas
    printf("Coordenadas de H: (%d, %d)\n", coordH1, coordH2);
    printf("Coordenadas de Z: (%d, %d)\n", coordZ1, coordZ2);

    return 0; // Retorno de sucesso
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    FILE *arq;
    char **matriz;
    char linha[100];
    int i, j, k, linhas=0, colunas=0;
        
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
    matriz=(char **)malloc(linhas*sizeof(char *));
    for(i=0; i<linhas;i++){
        matriz[i]=(char *)malloc(colunas*sizeof(char));
    }
// Leitura da matriz
    fgetc(arq); // Consumir o newline após os números
    for (i = 0; i < linhas; i++) {
        if (fgets(linha, sizeof(linha), arq) != NULL) {
           linha[strcspn(linha, "\n")] = 0;
            k = 0;
            for (j = 0; j < strlen(linha) && k < colunas; j++) {
                if (j % 2 == 0) { // Pula os espaços
                    matriz[i][k] = linha[j];
                    k++;
                }
            }
        } else {
            // Tratar erro de leitura ou fim inesperado do arquivo
            printf("Erro ao ler a linha %d do arquivo.\n", i);
            break;
        }
    }

    // Impressão da matriz lida
    printf("Matriz lida:\n");
    for(i=0;i<linhas; i++){
        for(j=0;j<colunas;j++){
        printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }

    // Chamando a função fuga_humana
    int resultado = fuga_humana(matriz, linhas, colunas);
    printf("Resultado da fuga_humana: %d\n", resultado);

    // Liberando a memória alocada
    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    fclose(arq);

    return 0;
}