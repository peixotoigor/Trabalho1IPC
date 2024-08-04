#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int verificar_palindromo(char frase [], int tam){
    int i, j=0;
    char frase2[tam];
    for(i=0; i<tam; i++){
        if(frase[i]!=' '&& frase[i]!=','&& frase[i]!='.'&& frase[i]!='!'&& frase[i]!='?'){
            frase2[j]=tolower(frase[i]);
            j++;
        }
    }
    frase2[j]='\0';
    for(i=0; i<strlen(frase2)/2; i++){
        if(frase2[i]==frase2[strlen(frase2)-1-i]){
            return 1;
        }
        else{
            return 0;
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    char frase[200], frase2[200];
    printf("Digite uma frase: \n ");
    fgets(frase,sizeof(frase),stdin);
    frase[strcspn(frase, "\n")]='\0';
    int tam=strlen(frase);

    if(verificar_palindromo(frase, tam)==1){
        printf("A frase é um palíndromo\n");
    }
    else{
        printf("A frase não é um palíndromo\n");
    }



    return 0;
}