#ifndef FORMIGAS_H_INCLUDE
#define FORMIGAS_H_INCLUDE

#define VAZIO 0
#define MORTO 1 
#define VIVO 1

typedef struct formiga{
	int x, y;
	int item;	 
} Formiga;

typedef struct ponto{
	int x, y;
} Ponto;

// Variáveis Globais
int Raio; 

int FormigasVivas;

int FormigasMortas;

int Tam; 			

int **MatrizMortas;

int **MatrizVivas;

Formiga *VetFormiga;

void AbrirArquivo(); //OK

void DecidirPegarLargar();

void MovimentarFormiga(int n); //OK

double Porcentagem ( int n ); // OK

// Funções Verificações

int MovimentoInvalido(int i, int j, int n); //OK

int VerificarParedes ( int ponto ); //OK

// Funções Geradoras rand

Ponto GerarMovimento(); //OK

// Funções Manipulação de matriz

int **AlocarMatriz (); //OK

void InicializarMatriz(); //OK

void ImprimirMatrizArq( int **matriz, char str[15]); //OK

void ImprimirMatriz( int **matriz, char str[15] ); //OK

void ImprimirVetor (); //OK

void Liberar(); //OK

#endif 