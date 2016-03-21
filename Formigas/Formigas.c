#include <stdio.h>
#include <stdlib.h>
#include "Formigas.h"

FILE *Arq;

void CalcularNumeroDeCelulas (){
	Ncelulas = 4 * Raio * Raio + 4 * Raio;
}

void InicializarMatriz(){
 	int i, j, n = 0; 
 	srand( ( unsigned )time( NULL ) );

 	MatrizMortas = AlocarMatriz ();

 	while( n < FormigasMortas ){
 		i = rand() % Tam;  j = rand() % Tam;

 		if ( MatrizMortas[i][j] != MORTO){
 			MatrizMortas[i][j] = MORTO;
 			n++;
 		}
 	}

 	n = 0;

 	MatrizVivas = AlocarMatriz ();
 	PosViva = ( Ponto *) malloc ( FormigasVivas * sizeof( Ponto ) );

 	while( n < FormigasVivas ){
 		i = rand() % Tam;  j = rand() % Tam;

 		if ( MatrizVivas[i][j] != VIVO){
 			MatrizVivas[i][j] = VIVO;
 			PosViva[n].x = i;
 			PosViva[n].y = j; 
 			PosViva[n].item = VAZIO;
 			n++;
 		}
  	}

  	ImprimirVetor();
}

void DecidirPegarLargar(){
	int n, i, j, vontadeDaFormiga;
	double porcentagem;

	srand( ( unsigned )time( NULL ) );

	for ( n = 0; n < FormigasVivas; n++ ){
		i = PosViva[n].x;
		j = PosViva[n].y;

		/* Formiga sem item */
		if ( PosViva[n].item  == VAZIO ){ 

			/* Posição com célula vazia */			
			if( MatrizMortas[ i ][ j ] == VAZIO )
				MovimentarFormiga( n );
			
			/* Posição com item morto */
			else{ // Decisão para pegar
				porcentagem = ( double ) ContarVizinhasMortas( n ) * 100 / Ncelulas;
				printf( "%.3lf %%\n", porcentagem);
				vontadeDaFormiga = rand() % 101;

				if (vontadeDaFormiga <= porcentagem){ // Pega
					PosViva[n].item = MORTO;
					MatrizMortas[i][j] = VAZIO; 
				}

				MovimentarFormiga( n );
			}

		/* Formiga com item */	
		} else {

			/* Posição com item morto */
			if ( MatrizMortas[ i ][ j ] == MORTO )
				MovimentarFormiga( n );
			
			/* Posição com celular vazia*/	
			else{ //Decisão de largar 
				porcentagem = ( double ) ContarVizinhasMortas( n ) *100 / Ncelulas;
				printf( "%.3lf %%\n", porcentagem );
				vontadeDaFormiga = rand() % 101;

				if (vontadeDaFormiga <= porcentagem){ // Larga
					PosViva[n].item = VAZIO;
					MatrizMortas[i][j] = MORTO; 
				}
				
				MovimentarFormiga( n );
			}
		}
	}
 }

int ContarVizinhasMortas ( int n ){
	int i, j, xi, yi, xf, yf, cont = -1;

	xi = PosViva[n].x - Raio; 
	if ( xi < 0 )	
		xi = 0;

	yi = PosViva[n].y - Raio;
	if ( yi < 0 )	
		yi = 0;
	
	xf = xi + ( 2 * Raio );
	if ( xf >= Tam )	
		xf = Tam - 1 ;

	yf = yi + ( 2 * Raio );
	if ( yf >= Tam )	
		yf = Tam - 1 ;

	for ( i = xi; i <= xf; i++ ){
		for ( j = yi; j <= yf; j++ ){
			if ( MatrizMortas[i][j] == MORTO )
				cont++;			
		}
	}

	printf("%d\n",cont );

	return cont; 
}

void MovimentarFormiga( int n ){
	int i, j;
	srand( ( unsigned )time( NULL ) );


	do {
		i = ( rand() % 3 ) - 1;
		j = ( rand() % 3 ) - 1;
	} while ( VerificarMovimento( i, j, n) );

	MatrizVivas[PosViva[n].x][PosViva[n].y] = VAZIO;

	PosViva[n].x += i;
	PosViva[n].y += j;

	MatrizVivas[PosViva[n].x][PosViva[n].y] = VIVO;
}

int VerificarMovimento(int i, int j, int n){
	int x, y;

	x = PosViva[n].x + i;
	y = PosViva[n].y + j;

	if ( ( x >= 0 ) && ( y >= 0 ) && ( x < Tam ) && ( y < Tam ) && MatrizVivas[x][y] != VIVO )
		return 0; // Movimento válido
	else 
		return 1;
}

int **AlocarMatriz (){
	int i, j;
    int **matriz = NULL;

    matriz = ( int ** ) malloc( Tam * sizeof( int * ) );
    if( !matriz ){
        printf( "Erro: problemas na Alocação!\n" );
        exit( 1 );
    }

    for( i = 0; i < Tam; i++ ){
        matriz[i] = ( int * ) malloc( Tam * sizeof( int ) );
        if ( !matriz[i] ){
            printf( "Erro: problemas na Alocação!\n" );
            exit( 1 );
        }
        for( j = 0; j < Tam; j++ )
            matriz[i][j] = VAZIO;
    }
    
    return matriz;
}

void AbrirArquivo(){
	Arq = fopen ( "out.txt", "wt" );
	if ( !Arq )
		printf("Erro ao abrir o arquivo texto\n");

}

void ImprimirMatriz( int **matriz, char str[15]){
    int i, j;
    fprintf( Arq, "%s\n", str );
    for( i = 0; i < Tam; i++ ){
        for( j = 0; j < Tam; j++ ){
        	if ( matriz[i][j] == 1 )
	            fprintf( Arq, "X\t" );
            else 
	            fprintf( Arq, "-\t" );
        }
        fprintf( Arq, "\n");
    }
    fprintf( Arq,"\n");

}

void ImprimirVetor (){
	int i;
	for ( i = 0; i < FormigasVivas; i++ ){
		printf("(%d, %d)\n",PosViva[i].x, PosViva[i].y );
	}

}

void Liberar(){
	//free(MatrizMortas);
}