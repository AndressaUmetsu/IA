#ifndef FORMIGAS_H_INCLUDE
#define FORMIGAS_H_INCLUDE

#define VAZIO 0
#define MORTO 1 
#define VIVO 1

typedef struct ponto{
	int x, y;
	int item;	
} Ponto;


// Variáveis Globais
int Raio; 

int FormigasVivas;

int FormigasMortas;

int Tam; 			

int Ncelulas;

int **MatrizMortas;

int **MatrizVivas;

Ponto *PosViva;

// Funções 
void CalcularNumeroDeCelulas (); 

void InicializarMatriz();

void DecidirPegarLargar();

void MovimentarFormiga(int n);

int VerificarMovimento(int i, int j, int n);

int **AlocarMatriz ();

void AbrirArquivo();

void ImprimirMatriz( int **matriz, char str[15]);

void ImprimirVetor ();

void Liberar();

#endif 