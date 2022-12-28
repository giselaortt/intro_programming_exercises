//Gisela Moreira Ortt, 8937761
#include <stdlib.h>
#include <stdio.h>

int main (){
    int N, O, P, Q, R, S;
    int i, j;
    int matriz[50][51];
    O=0;
    P=0;

    scanf("%d", &N);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d", &matriz[i][j]);
        }
    }
    // este for vai checar as diagonais
    for(i=0;i<N;i++){
        O += matriz[N-i-1][i];
        P += matriz[i][i];
    }
    if(O != P){
        printf("Nao");
        return 0;
    }
    //este for vai checar as linhas e colunas
    for(i=0;i<N;i++){
        P = 0;//esta variavel sera reciclada
        Q = 0;
        for(j=0;j<N;j++){
            P += matriz[j][i];
            Q += matriz[i][j];
        }
        if(P != Q || P != O){//O esta armazenando o valor de referencia
            printf("Nao");
            return 0;
        }
    }
    printf("Sim");

return 0;
}
