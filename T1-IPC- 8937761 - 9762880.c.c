#include <stdio.h>
#include <stdlib.h>
//esta funcao recebe uma matriz e a imprime na forma tabuleiro.
void imprimir_grade(char m[3][3]){
	int i,j;
	printf("\n\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(m[i][j] == '\0') {
				printf(" %d", 3*(i)+(j+1));
			}else{
				printf(" %c", m[i][j]);
			}
			if(j!=2) { printf("|"); }
			}
		if(i != 2) {
			printf("\n------------\n");
		}
	}
}
//essa funcao recebe uma matriz e compara os resultados retornando um caractere, determinando se ha um vencedor.
char funcao(char m[3][3]){
	int i;
	char p = '\0';
	if(m[1][1]!='\0'&& ((m[0][0] == m[1][1] && m[1][1] == m[2][2])||(m[0][2] == m[1][1]&& m[1][1] == m[2][0]))){
        p = m[1][1];
	}else{
        for(i=0;i<3;i++){
            if(m[i][0]!= '\0' && m[i][0] == m[i][1] && m[i][0] == m[i][2]){
                p = m[i][0];
                break;
            }
            else if(m[0][i] != '\0' && (m[0][i] == m[1][i])&&(m[0][i]== m[2][i])){
                p = m[0][i];
                break;
            }
        }
	}
    return p;
}
int main(){
    //o vetor de uma posicao sera usado para ler a linha inteira, acabando com a nescessidade de usar fflush para cada scanf.
    //Ele impede bugs quando a pessoa digitar caracteres sem querer.
    int A, S, i, j, jogador, l, nlins, ncols;
    char marcador, perdedor='\0', again, g[2];
	char tabuleiro[3][3];
    printf("Bem vindo ao Jogo da Velha!\n");
    //a mascara usada no scanf vai ler todos os caracteres ate uma quebra de linha, mas salva apenas o primeiro.
    //o -48 e responsavel pela conversao de char para numero.
	do{
        printf("Digite 1 se voce usa o linux, e 2 se usa o windows.");
        scanf(" %[^\n]", g);
        S = g[0] - 48;
	}while (S!=1 && S!= 2);

    /*Aqui colocamos um label para redirecionamento*/inicio:
    //este for reseta nosso tabuleiro.
	for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++){
            tabuleiro[i][j] = '\0';
        }
	}
	perdedor = '\0';
	//este loop vai ler A quantas vezes forem nescessarias. Aindica a versao do jogo escolhida.
	do{
        printf("Aperte:\n1 - para jogar a variacao 1.\n2 - para jogar a variacao 2.\n0 - para ver as instrucoes de como usar.\n9 - para encerrar o programa.\n\n");
        scanf(" %[^\n]", g);
        A = g[0] - 48;
    }while(A != 1 && A != 2 && A != 0 && A != 9);

	switch(A){
        case 9:
			printf("Obrigado por jogar!\n");
            return 0;
		case 0:
			printf("----------------------------------------------------------------------------------------------\nEsse programa consiste em duas variacoes do jogo da velha:\n 1-O modo de jogo eh igual ao original, porem o jogador que \n completar uma linha, coluna ou diagonal primeiro eh o perdedor.\n 2- Cada jogador seleciona o seu marcador e a posicao desejada\n no inicio de cada rodada. O vencedor eh quem completar uma linha, coluna ou diagonal primeiro\n----------------------------------------------------------------------------------------------\n");
			//aqui vamos usar o comando goto para redirecionar ao menu inicial.
			goto inicio;

        //Esta e o jogo. Optamos por deixar as duas versoes juntas, devido a semelhanca dos codigos.
		default:
			if(S==1)
                system("clear");
            else
                system("cls");
            printf("Voces escolheram a modalidade %d!\n", A);
            for( i=0; i<9 && perdedor=='\0'; i++){
                printf("Rodada %d!\n", i+1);
                imprimir_grade(tabuleiro);
                jogador = i%2 + 1;
                if(A == 1){
                    marcador = (jogador == 1) ? 'X' : 'O';
                } else{
                    do{
                    printf("\nDigite o marcador, X ou O:\n");
                        scanf(" %[^\n]", g);
                        marcador = g[0];
                        if(marcador == 'x')
                            marcador = 'X';
                        else if(marcador == 'o')
                            marcador = 'O';
                    }while(marcador != 'X' && marcador != 'O');
                }
                printf("\nJogador %d, digite o quadrado que deseja marcar:\n", jogador);
                scanf(" %[^\n]", g);
                l = g[0] - 48;
                l--;
                ncols = l%3;
                nlins = l/3;
                if(l<0 || l>8 || tabuleiro[nlins][ncols] != '\0') {
                    do{
                        printf("Este lugar e invalido, tente novamente.\n");
                        scanf(" %[^\n]", g);
                        l = g[0] - 48;
                        l--;
                        ncols = l%3;
                        nlins = l/3;
                    }while(l<0 || l>8 || tabuleiro[nlins][ncols] != '\0');
                }
                tabuleiro[nlins][ncols] = marcador;
                perdedor = funcao(tabuleiro);
                if(S==1)
                    system("clear");
                else
                    system("cls");
            }
            if(perdedor == '\0'){
                printf("Deu velha!\n");
            }else{
                if(A == 1){
                    //A funcao "funcao" determina quem ganhou o jogo para a versao 1.
                    if(perdedor == 'X'){
                        printf("O ganhador foi o jogador 2!\n");
                    } else {
                        printf("O ganhador foi o jogador 1!\n");
                    }
                } else {
                    //Nesta versao o ultimo a jogar e sempre o vencedor.
                    printf("O ganhador foi o jogador %d!\n", jogador);
                }
            }
            printf("Voces desejam jogar novamente?: S/N\n");
            //Caso o usuário não deseje jogar novamente, o programa é encerrado. Caso contrário, o programa volta ao menu inicial.
            do{
                scanf(" %[^\n]", g);
                again = g[0];
                if(again == 's')
                    again = 'S';
                else if(again == 'n')
                    again = 'N';
            }while(!(again == 'S' || again == 'N'));
            if(again == 'S'){
                goto inicio;
            } else{
                printf("\n\nObrigada!\n\n");
            }
			break;
	}
return 0;
}
