//Gisela Moreira Ortt, 8937761
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int matriz[100][101];//Matriz dos numeros aleatorios
int matriz2[100][101];//Matriz do resultado da operacao
//declarei esta matriz global para nao ter de preenche-la com zeros;

int main (){
    int A;
    int i, j, l;
    srand(time(NULL));

    do{
        printf("digite um numero entre 2 e 100:  ");
        scanf("%d", &A);
    }while(A<2||A>100);

    for(i=0;i<A;i++){
        for(j=0;j<A;j++){
            matriz[i][j] = rand() % 10;
        }
    }

    printf("Esta eh a matriz:\n");
    for(i=0;i<A;i++){
        for(j=0;j<A;j++){
            printf("%d  ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\nEsta eh a matriz transposta:\n");
    for(i=0;i<A;i++){
        for(j=0;j<A;j++){
            printf("%d  ", matriz[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");

    for(l=0;l<A;l++){
        for(i=0;i<A;i++){
            for(j=0;j<A;j++){
                matriz2[l][i] += matriz[l][j]*matriz[i][j];
            }
        }
    }
    printf("Este eh o resultado da operacao:\n");
    printf("{");
    for(i=0;i<A;i++){
        printf("{");
        for(j=0;j<A-1;j++){
            if(j == i){
                matriz2[i][j] += A;
            }
            printf("%d,", matriz2[i][j]);
        }
        printf("%d", matriz2[i][A]);
        if(i!=A-1)
            printf("},");
        else
            printf("}");
    }
    printf("}");
return 0;
}
