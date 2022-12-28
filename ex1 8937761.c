#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct termo{
    float coef;
    int pot;
};
// esta funcao calcula potencia de maneira eficiente (logn);
double pot(float um, int dois){
    if(dois == 0) return 1;
    if(dois == 1) return um;
    if(dois%2) return um*pot(um, dois/2)*pot(um, dois/2);
    return pot(um, dois/2)*pot(um, dois/2);
}
//esta funcao acha o valor de y dados um x e um polinomio;
double findy( int x, struct termo* vetor, int siz ){
    double y = 0.0;
    int i;
    for( i=0; i<siz; i++ ){
        y += pot( x, vetor[i].pot )*vetor[i].coef;
    }
    return y;
}
//funcao para buble sort;
void ordenar( int siz, struct termo vetor[] ){
    int i, j;
    int temp1, temp2;
    for( i=0; i<siz; i++ )
        for( j=0; j<siz; j++ )
            if( vetor[j].pot < vetor[i].pot ){
                temp1 = vetor[i].pot;
                temp2 = vetor[i].coef;
                vetor[i].pot = vetor[j].pot;
                vetor[i].coef = vetor[j].coef;
                vetor[j].pot = temp1;
                vetor[j].coef = temp2;
            }
}
//calcula a intgral indefinida e num intervalo e imprime;
void integra( int x1, int x2, struct termo* poli, int siz ){
    int i; struct termo* primitiva = NULL;
    primitiva = (struct termo*)malloc( sizeof(struct termo)*siz );
    for( i=0; i<siz; i++ ){
        primitiva[i].coef = (( poli[i].coef)/((float)poli[i].pot +1.0)) ;
        primitiva[i].pot = poli[i].pot + 1;
    }
    printf("F(x) = ");
    for( i=0; i<siz; i++ ){
        if( primitiva[i].pot > 1 ){
            if( primitiva[i].coef < 0 ) printf("%.2fx^%d ",  primitiva[i].coef, primitiva[i].pot);
            else printf("+%.2fx^%d ",  primitiva[i].coef, primitiva[i].pot);
        }
        if( primitiva[i].pot == 0 ){
            if( primitiva[i].coef < 0 ) printf("%.2f ",  primitiva[i].coef);
            else printf("+%.2f ",  primitiva[i].coef);
        }
        if( primitiva[i].pot == 1 ){
            if( primitiva[i].coef < 0 ) printf("%.2fx ",  primitiva[i].coef);
            else printf("+%.2fx ",  primitiva[i].coef);
        }
    }
    printf("+C\n");

    float y = findy( x2, primitiva, siz ) - findy( x1, primitiva, siz );
    printf("F(%d) - F(%d) = %.2f\n\n", x2, x1, y);

    free( primitiva );
}
// funcao recursiva. calcula todas as derivadas e as imprime;
void derive( struct termo* poli, int siz, int ctd, int x, int grau ){
    if( grau == 0 ) return;
    struct termo* flinha = NULL;
    int i, ncoef, nsiz=0;
    for( i=0; i<siz; i++ ){
        ncoef = (poli[i].coef)*(poli[i].pot);
        if( ncoef != 0 ){
            flinha = (struct termo*)realloc( flinha, (sizeof(struct termo))*(nsiz+1) );
            flinha[nsiz].coef = ncoef;
            flinha[nsiz].pot = poli[i].pot - 1;
            nsiz++;
        }
    }

    if( ctd == 1 ) printf("d/dx f(x) = ");
    else printf("d^%d/dx^%d f(x) = ", ctd, ctd);
    for( i=0; i<nsiz; i++ ){
        if( flinha[i].pot > 1 ) printf("%+dX^%d ", (int)flinha[i].coef, flinha[i].pot);
        else if( !flinha[i].pot ) printf("%+d ", (int)flinha[i].coef);
        else printf("%+dX", (int)flinha[i].coef);
    }
    printf("\n");
    int y = findy( x, flinha, nsiz );
    if( ctd == 1 ) printf("d/dx f(%d) = %d\n\n", x, y);
    else printf("d^%d/dx^%d f(%d) = %d\n\n", ctd, ctd, x, y);

    derive( flinha, nsiz, ctd+1, x, grau - 1 );

    free( flinha );
}

int main(){
    int a, b, c, ctd=0, sign, x, i;
    char* d = NULL;
    char e;
    struct termo* poli = NULL;

    poli = (struct termo*)malloc( sizeof(struct termo)*16 );

    //este loop le a string ate o final da linha e aloca memoria suficiente para armazenala;
    while( e != '\n' ){
        scanf("%c", &e);
        d = (char*)realloc( d, sizeof(char)*(ctd+2) );
        d[ctd] = e;
        ctd++;
    }

    scanf("%d %d %d", &a, &b, &c);

    ctd = 0; i=0;

    //este loop transforma a string no polinomio;
    while( d[i] != '\n' ){
        if( d[i] == '+' ) sign = 1;
        else sign = -1;
        i++;
        poli[ctd].coef = (d[i] - 48)*sign;
        i++;
        while( 48 <= d[i] && d[i] <= 57 ){
            poli[ctd].coef *= 10;
            poli[ctd].coef += (d[i] - 48)*sign;
            i++;
        }
        i+=2;
        poli[ctd].pot = ( d[i] - 48 );
        i++;
        if( 48 <= d[i] && d[i] <= 57 ){
            poli[ctd].pot *= 10;
            poli[ctd].pot += d[i] - 48;
            i++;
        }
        ctd++;
    }

    ordenar( ctd, poli );
    int grau = 0;
    for( i=0; i<ctd; i++ )
        if( poli[i].pot > grau ) grau = poli[i].pot;

    int y = findy( a, poli, ctd );
    printf("f(x) = ");
    for(i=0; i<ctd; i++) printf("%+dX^%d ", (int)poli[i].coef, poli[i].pot);
    printf("\nf(%d) = %d\n\n", a, y);

    derive( poli, ctd, 1, a, grau );

    integra( b, c, poli, ctd );

    free(poli);

return 0;
}
