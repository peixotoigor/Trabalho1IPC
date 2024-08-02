#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    FILE *arq;

    arq=fopen("matriz.txt","r");
    if(!(arq)){
        printf("Erro, não foi possivel abrir o arquivo.");
    }
    
    return 0;
}