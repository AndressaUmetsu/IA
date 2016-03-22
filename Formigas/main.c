#include <stdio.h>
#include <stdlib.h>
#include "Formigas.h"


int main( int argc, char const *argv[] ){
	int i = 0;
	if ( argc < 5 ){
		printf ( "Erro! Falta de argumentos\n" );
		exit ( 1 );
	}

	Raio = atoi ( argv[1] );
	FormigasVivas = atoi ( argv[2] );
	FormigasMortas = atoi ( argv[3] );
	Tam = atoi ( argv[4] );

	AbrirArquivo();

	CalcularNumeroDeCelulas();

	InicializarMatriz();
	
	while( i < 10000 ){
		//ImprimirMatrizArq( MatrizMortas, "Matriz Mortas");
		ImprimirMatriz( MatrizMortas, "Matriz Mortas");
		//ImprimirMatriz( MatrizVivas, "Matriz Vivas" );
		DecidirPegarLargar();
		printf("%d\n",i);
		i++;
	}
	Liberar();
	return 0;
}


