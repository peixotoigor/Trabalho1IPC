#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
// Função para imprimir o matriz
void imprimir_matriz(char **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Função recursiva para encontrar o caminho no labirinto
int encontrar_caminho(char **matriz, int linhas, int colunas, int x, int y) {
    // Verifica se a posição atual é a zona de evacuação
    if (matriz[x][y] == 'Z') {
        return 1;  // Caminho encontrado
    }

    // Marca a posição atual como parte do caminho
    matriz[x][y] = '*';

    // Tentativas de movimento: cima, baixo, esquerda, direita
    if (x > 0 && (matriz[x - 1][y] == ' ' || matriz[x - 1][y] == 'Z')) { // cima
        if (encontrar_caminho(matriz, linhas, colunas, x - 1, y)) {
            return 1;
        }
    }

    if (x < linhas - 1 && (matriz[x + 1][y] == ' ' || matriz[x + 1][y] == 'Z')) { // baixo
        if (encontrar_caminho(matriz, linhas, colunas, x + 1, y)) {
            return 1;
        }
    }

    if (y > 0 && (matriz[x][y - 1] == ' ' || matriz[x][y - 1] == 'Z')) { // esquerda
        if (encontrar_caminho(matriz, linhas, colunas, x, y - 1)) {
            return 1;
        }
    }

    if (y < colunas - 1 && (matriz[x][y + 1] == ' ' || matriz[x][y + 1] == 'Z')) { // direita
        if (encontrar_caminho(matriz, linhas, colunas, x, y + 1)) {
            return 1;
        }
    }

    // Desmarca a posição atual se nenhum caminho for encontrado
    matriz[x][y] = ' ';
    return 0;
}

int fuga_humana(char **matriz, int linhas, int colunas){
    // Encontrando as coordenadas de H e Z
    int coordxH = -1, coordyH = -1; // Coordenadas de 10
    int coordxZ = -1, coordyZ = -1; // Coordenadas de 20
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] =='H') {
                coordxH = i;
                coordyH = j;
            }
            if (matriz[i][j] == 'Z') {
                coordxZ = i;
                coordyZ = j;
            }
        }
    }

// Verificando se as coordenadas foram encontradas
    if (coordxH == -1 || coordyH == -1 || coordxZ == -1 || coordyZ == -1) {
        printf("Coordenadas de H ou Z não encontradas.\n");
        return -1;
    }

    // Imprimindo as coordenadas encontradas
    printf("Coordenadas de H: (%d, %d)\n", coordxH, coordyH);
    printf("Coordenadas de Z: (%d, %d)\n", coordxZ, coordyZ);

    // Inicia a busca a partir da posição inicial do humano
    if (encontrar_caminho(matriz, linhas, colunas, coordxH, coordyH)) {
        printf("Caminho encontrado:\n");
        imprimir_matriz(matriz, linhas, colunas);
        return 1;
    } else {
        printf("Caminho não encontrado\n");
        return 0;
    }
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
    
    // Tenta encontrar o caminho de fuga
    if (fuga_humana(matriz, linhas, colunas)==1) {
        printf("Caminho não encontrado\n");
    }

    // Liberando a memória alocada
    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    fclose(arq);

    return 0;
}