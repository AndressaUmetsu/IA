#include <stdio.h>
#include <stdlib.h>
#include "Formigas.h"

FILE *Arq;

void AbrirArquivo(){
	Arq = fopen ( "out.txt", "wt" );
	if ( !Arq )
		printf( "Erro ao abrir o arquivo texto\n" );
}

void DecidirPegarLargar(){
	int n, i, j;
	double evento;

	for ( n = 0; n < FormigasVivas; n++ ){

		i = VetFormiga[n].x;
		j = VetFormiga[n].y;

		switch (VetFormiga[n].item) {
			case VAZIO:

				/* Posição com célula vazia */			
				if( MatrizMortas[ i ][ j ] == VAZIO ){
					MovimentarFormiga( n );
				}
			
				/* Posição com item morto */
				else{
					evento = ( rand() % 100 );

					/* Decisão para pegar */					
					if ( evento >= Porcentagem( n ) ){ 
						VetFormiga[n].item = MORTO;
						MatrizMortas[i][j] = VAZIO; 
					}

					MovimentarFormiga( n );
				}

			break;
			
			case MORTO:
			
				/* Posição com item morto */
				if ( MatrizMortas[ i ][ j ] == MORTO ){
					MovimentarFormiga( n );
				}

				/* Posição com celular vazia*/	
				else{ 
					evento = ( rand() % 101 );

					/*Decisão de largar*/ 
					if ( evento <= Porcentagem( n ) ){ 
						VetFormiga[n].item = VAZIO;
						MatrizMortas[i][j] = MORTO; 
					}
				
					MovimentarFormiga( n );
				}

			break;
		}
	}
}

void MovimentarFormiga( int n ){
	Ponto p;
	int semente, max = 0;
	
	do {
		semente = ( rand() % 100 ) + 1;
		semente = ( semente * 7 ) % 11;
		p = GerarMovimento( semente % 8 );	
		max++;
	} while ( MovimentoInvalido( p.x, p.y, n ) && max < 30); 

	if (max < 30)
	{
		MatrizVivas[VetFormiga[n].x][VetFormiga[n].y] = VAZIO;
		VetFormiga[n].x += p.x;
		VetFormiga[n].y += p.y;
		MatrizVivas[VetFormiga[n].x][VetFormiga[n].y] = VIVO;
	}

}

double Porcentagem ( int n ){
	int i, j, xi, yi, xf, yf;
	double cont = 0, contCel = 0;

	xi = VerificarParedes ( VetFormiga[n].x - Raio );
	
	yi = VerificarParedes ( VetFormiga[n].y - Raio );
		
	xf = VerificarParedes ( VetFormiga[n].x + Raio );

	yf = VerificarParedes ( VetFormiga[n].y + Raio );

	for ( i = xi; i <= xf; i++ ){
		for ( j = yi; j <= yf; j++ ){
				
			if ( MatrizMortas[i][j] == MORTO )
				cont++;		
			contCel++;
		}
	}

	// numero de celulas vazias por numero de
	//contCel = (2*Raio+1)*(2*Raio+1);
	return ( ( cont ) / contCel ) * 100;   
}

int MovimentoInvalido(int i, int j, int n){
	int x, y;

	x = VetFormiga[n].x + i;
	y = VetFormiga[n].y + j;

	/*Movimento invalido*/
	if ( ( x < 0 ) || ( y < 0 ) || ( x >= Tam ) || ( y >= Tam ) || MatrizVivas[x][y] == VIVO ){
		return 1;

	return 0;
	}
}

int VerificarParedes ( int ponto ){
	if ( ponto < 0 ) 
		return 0;

	if ( ponto >= Tam )
		return Tam-1;

	return ponto;
}

Ponto GerarMovimento(int semente){
	Ponto movimento;
		switch ( semente ){
			case 0:
				movimento.x = -1;
				movimento.y = -1;
				break;
			case 1:
				movimento.x = -1;
				movimento.y = 0;
				break;
			case 2:
				movimento.x = -1;
				movimento.y = 1;
				break;
			case 3:
				movimento.x = 0;
				movimento.y = -1;
				break;
			case 4:
				movimento.x = 0;
				movimento.y = 1;
				break;
			case 5:
				movimento.x = 1;
				movimento.y = -1;
				break;
			case 6:
				movimento.x = 1;
				movimento.y = 0;
				break;
			case 7:
				movimento.x = 1;
				movimento.y = 1;
				break;
		}
	return movimento;
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

void ImprimirMatrizArq( int **matriz, char str[15] ){
    int i, j;
    fprintf( Arq, "%s\n", str );
    for( i = 0; i < Tam; i++ ){
        for( j = 0; j < Tam; j++ ){
        	if ( matriz[i][j] == 1 )
	            fprintf( Arq, "X" );
            else 
	            fprintf( Arq, "-" );
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

void ImprimirVetor(){
	int i;
	for ( i = 0; i < FormigasVivas; i++ ){
		printf( "(%d, %d) = %d\n",VetFormiga[i].x, VetFormiga[i].y, VetFormiga[i].item );
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
	fclose(Arq);
}

