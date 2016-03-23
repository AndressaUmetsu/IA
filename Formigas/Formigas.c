#include <stdio.h>
#include <stdlib.h>
#include "Formigas.h"

FILE *Arq;

void CalcularNumeroDeCelulas (){
	Ncelulas = 4 * Raio * Raio + 4 * Raio;
	printf( "Numero de celulas no campo de visão %d\n",Ncelulas );
}

void InicializarMatriz(){
 	int i, j, n = 0; 
 	srand( ( unsigned )time( NULL ) );

 	MatrizMortas = AlocarMatriz ();

 	while( n < FormigasMortas ){
 		i = rand() % Tam;  j = rand() % Tam;

 		if ( MatrizMortas[i][j] != MORTO ){
 			MatrizMortas[i][j] = MORTO;
 			n++;
 		}
 	}

 	n = 0;

 	MatrizVivas = AlocarMatriz ();
 	VetFormiga = ( Formiga *) malloc ( FormigasVivas * sizeof( Formiga ) );

 	while( n < FormigasVivas ){
 		i = rand() % Tam;  j = rand() % Tam;

 		if ( MatrizVivas[i][j] != VIVO ){
 			MatrizVivas[i][j] = VIVO;
 			VetFormiga[n].x = i;
 			VetFormiga[n].y = j; 
 			VetFormiga[n].item = VAZIO;
 			n++;
 		}
  	}
}

void DecidirPegarLargar(){
	int n, i, j, vontadeDaFormiga;
	double porcentagem;

	srand( ( unsigned )time( NULL ) );

	for ( n = 0; n < FormigasVivas; n++ ){
		printf("Formiga viva %d ", n);

		if (VetFormiga[n].item == VAZIO)
			printf(" VAZIO \n");
		else 	
			printf(" COM ITEM \n");		
		
		i = VetFormiga[n].x;
		j = VetFormiga[n].y;

		/* Formiga sem item */
		if ( VetFormiga[n].item  == VAZIO ){ 

			/* Posição com célula vazia */			
			if( MatrizMortas[ i ][ j ] == VAZIO ){
				printf("Formiga sem item e em celula vazia \n");
				MovimentarFormiga( n );
			}
			
			/* Posição com item morto */
			else{
				printf("Tem item\n");
				porcentagem = ( double ) ContarVizinhasMortas( n ) * 100 / Ncelulas;
				vontadeDaFormiga = rand() % 101;
				printf("vontade Da Formiga %d porcentagem %lf %%\n", vontadeDaFormiga, porcentagem );
				 // Decisão para pegar
				if ( vontadeDaFormiga >= porcentagem ){ 
					printf("Pegar item\n");
					VetFormiga[n].item = MORTO;
					MatrizMortas[i][j] = VAZIO; 
				}

				MovimentarFormiga( n );
			}

		/* Formiga com item */	
		} else {

			/* Posição com item morto */
			if ( MatrizMortas[ i ][ j ] == MORTO ){
				printf("Formiga com item e em celula com item \n");
				MovimentarFormiga( n );
			}
			/* Posição com celular vazia*/	
			else{ 
				printf("celula vazia\n");
				porcentagem = ( double ) ContarVizinhasMortas( n ) *100 / Ncelulas;
				
				vontadeDaFormiga = rand() % 101;
				printf("vontade Da Formiga %d porcentagem %lf %%\n", vontadeDaFormiga, porcentagem );
				//Decisão de largar 
				if ( vontadeDaFormiga <= porcentagem ){ // Larga
					printf("Largando item\n");
					VetFormiga[n].item = VAZIO;
					MatrizMortas[i][j] = MORTO; 
				}
				
				MovimentarFormiga( n );
			}
		}
	}
 }

int ContarVizinhasMortas ( int n ){
	int i, j, xi, yi, xf, yf, cont = -1;

	xi = VetFormiga[n].x - Raio; 
	if ( xi < 0 )	
		xi = 0;

	yi = VetFormiga[n].y - Raio;
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

	printf("número de vizinhas %d\n",cont );

	return cont; 
}

void MovimentarFormiga( int n ){
	int i, j;
	srand( ( unsigned )time( NULL ) );

	printf("formiga andando\n");

	do {
		i = ( rand() % 3 ) - 1;
		j = ( rand() % 3 ) - 1;
		printf("movimento %d %d \n", i, j );
	} while ( VerificarMovimento( i, j, n ) );

	MatrizVivas[VetFormiga[n].x][VetFormiga[n].y] = VAZIO;

	VetFormiga[n].x += i;
	VetFormiga[n].y += j;

	MatrizVivas[VetFormiga[n].x][VetFormiga[n].y] = VIVO;
}

int VerificarMovimento(int i, int j, int n){
	int x, y;

	x = VetFormiga[n].x + i;
	y = VetFormiga[n].y + j;

	if ( ( x >= 0 ) && ( y >= 0 ) && ( x < Tam ) && ( y < Tam ) && MatrizVivas[x][y] != VIVO )
		return 0; // Movimento válido
	else {
		printf("Movimento invalido\n");
		return 1;
	}
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
		printf( "Erro ao abrir o arquivo texto\n" );

}

void ImprimirMatrizArq( int **matriz, char str[15] ){
    int i, j;
    fprintf( Arq, "%s\n", str );
    for( i = 0; i < Tam; i++ ){
        for( j = 0; j < Tam; j++ ){
        	if ( matriz[i][j] == 1 )
	            fprintf( Arq, "X\t" );
            else 
	            fprintf( Arq, "-\t" );
        }
        fprintf( Arq, "\n" );
    }
    fprintf( Arq,"\n" );

}

void ImprimirMatriz( int **matriz, char str[15] ){
    int i, j;
    printf( "%s\n", str );
    for( i = 0; i < Tam; i++ ){
        for( j = 0; j < Tam; j++ ){
        	if ( matriz[i][j] == 1 )
	            printf( " X " );
            else 
	            printf( " - " );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

void ImprimirVetor (){
	int i;
	for ( i = 0; i < FormigasVivas; i++ ){
		printf( "(%d, %d)\n",VetFormiga[i].x, VetFormiga[i].y );
	}
}

void Liberar(){
	int i;
	for (i = 0; i < Tam; i++){
		free ( MatrizMortas[i] );
		free ( MatrizVivas[i] );
	}
	free ( MatrizMortas );
	free ( MatrizVivas );
	free ( VetFormiga );
	}