#ifndef FORMIGAS_H_INCLUDE
#define FORMIGAS_H_INCLUDE

#define VAZIO 0
#define MORTO 1 
#define VIVO 1

typedef struct formiga{
	int x, y;
	int item;	
} Formiga;

// Variáveis Globais
int Raio; 

int FormigasVivas;

int FormigasMortas;

int Tam; 			

int Ncelulas;

int **MatrizMortas;

int **MatrizVivas;

Formiga *VetFormiga;

void CalcularNumeroDeCelulas (int n); //ok

void InicializarMatriz();  // ok

void DecidirPegarLargar();

int ContarVizinhasMortas ( int n );  // ok

void MovimentarFormiga(int n);

int VerificarMovimento(int i, int j, int n);

int **AlocarMatriz ();

void AbrirArquivo();

void ImprimirMatrizArq( int **matriz, char str[15]);

void ImprimirMatriz( int **matriz, char str[15] );

void ImprimirVetor ();

void Liberar();

#endif 