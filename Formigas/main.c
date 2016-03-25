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

	

	InicializarMatriz();
	
	while( i <= 6 ){
		printf("\nIteração %d\n",i);
		//ImprimirMatrizArq( MatrizMortas, "Matriz Mortas");
		//if (i % 10 == 0){
			 ImprimirMatrizArq( MatrizMortas, "Matriz Mortas");
			 ImprimirMatrizArq( MatrizVivas, "Matriz Vivas" );
			 ImprimirVetor();
		//}
		DecidirPegarLargar();
		i++;
	}
	Liberar();
	return 0;
}


