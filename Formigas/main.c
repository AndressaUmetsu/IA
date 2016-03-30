#include <stdio.h>
#include <stdlib.h>
#include "Formigas.h"

void teste ();

int main( int argc, char const *argv[] ){
	srand(time(NULL));
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

	InicializarMatriz();

	ImprimirMatrizArq( MatrizMortas, "Matriz Inicial");

	while( i <= 1000000 ){
		//ImprimirMatriz( MatrizMortas, "Matriz Mortas");
		DecidirPegarLargar();	
		i++;
	}
	ImprimirMatrizArq( MatrizMortas, "Matriz Final");
	ImprimirVetor();
	Liberar();
	return 0;
}
