/*
Funcoes basicas para manipulacao de matrizes
*/

#ifndef _MATRIZLIB_H_
#define _MATRIZLIB_H_

	typedef enum { INFERIOR, SUPERIOR, NAO } orientacaoTriang;

	typedef struct {
		double** valor;
		unsigned int linhas;
		unsigned int colunas;
		orientacaoTriang triangular;
	} Matriz;

	extern short int Matriz_debug;

	//aloca espaco para uma nova matriz
	extern Matriz Matriz_init (unsigned int linhas, unsigned int colunas);

	//aloca espaco para uma nova matriz triangular
	extern Matriz Matriz_initTriang (unsigned int ordem, orientacaoTriang orientacao);

	//libera espaco alocado por uma matriz
	extern void Matriz_free (Matriz matriz);

	//cria copia de uma matriz
	extern Matriz Matriz_copia (Matriz matriz);

	//transfere os valores de A para B
	extern void Matriz_transf (Matriz A, Matriz B);

	//transpoe uma matriz
	extern Matriz Matriz_transp(Matriz matriz, short int copyFlag);

	//cria vetor de uma linha de uma matriz
	extern Matriz Matriz_vetorLinha (Matriz matriz, int linha);

	//cria vetor de uma coluna de uma matriz
	extern Matriz Matriz_vetorColuna (Matriz matriz, int coluna);

	//recebe valores da matriz da entrada padrao
	extern void Matriz_fscanf (FILE *entrada, Matriz matriz);

	//cria string de um numero decimal sem 0s a direita
	extern char* stringLimpa(double valor);

	//imprime matriz na saida padrao
	extern void Matriz_fprintf (FILE *saida, Matriz matriz, char ultimo);

	//soma entre duas matrizes
	extern Matriz Matriz_soma (Matriz A, Matriz B, short int copyFlag);

	//efetua subtracao entre duas matrizes
	extern Matriz Matriz_sub (Matriz A, Matriz B, short int copyFlag);

	//multiplicacao entre duas matrizes
	extern Matriz Matriz_mult (Matriz A, Matriz B, short int copyFlag);

	//modulo de um numero double
	extern double mod (double numero);

	//multiplicacao de matriz por um escalar
	extern Matriz Matriz_multEscalar (double escalar, Matriz matriz, short int copyFlag);

	//substituicao para tras
	extern Matriz Matriz_substTras (Matriz A, Matriz b, short int copyFlag);

	//substituicao para frente
	extern Matriz Matriz_substFrente (Matriz A, Matriz b, short int copyFlag);

	//eliminacao gaussiana, gera uma matriz triangular superior
	extern Matriz Matriz_eliminacaoGauss (Matriz matriz, short int copyFlag);

	//eliminacao gaussiana com duas matrizes, onde B sofre toda as transformacoes de A
	extern void Matriz_eliminacaoGauss2 (Matriz A, Matriz B);

	//determinante
	extern double Matriz_det (Matriz matriz);

	//inversa
	extern Matriz Matriz_inversa (Matriz matriz, short int copyFlag);

	//fator cholesky
	extern Matriz Matriz_fatorCholesky (Matriz matriz);

	//verifica matriz de vandermonde
	extern short int Matriz_ehVandermonde(Matriz matriz);

	//norma de frobenius
	extern double Matriz_normaFrobenius (Matriz matriz);

	//norma linha
	extern double Matriz_normaLinha (Matriz matriz);

	//norma coluna
	extern double Matriz_normaColuna (Matriz matriz);

	//produto interno
	extern double Matriz_produtoInterno (Matriz a, Matriz b);

	//angulo entre dois vetores
	extern double Matriz_anguloVetores (Matriz a, Matriz b);

	//determinante de matriz de vandermonde
	extern double Matriz_detVandermonde (Matriz matriz);

	//resolve o sistema R*Rt*x = b, onde R eh o fator Cholesky (triangular inferior) de uma matriz e Rt sua transposta
	extern Matriz Matriz_solucaoCholesky (Matriz R, Matriz b, short int copyFlag);

	//verifica se a matriz satisfaz o criterio das linhas, 1 = satisfaz; 0 = nao satisfaz
	extern short int Matriz_criterioLinhas (Matriz matriz);

	//verifica se a matriz satisfaz o criterio das colunas, 1 = satisfaz; 0 = nao satisfaz
	extern short int Matriz_criterioColunas (Matriz matriz);

	//verifica se a matriz satisfaz o criterio de sassenfeld, 1 = satisfaz; 0 = nao satisfaz
	extern short int Matriz_criterioSassenfeld (Matriz matriz);

	//verifica se a matriz eh uma matriz banda, 1 = verdadeiro; 0 = falso
	extern short int Matriz_ehBanda (Matriz matriz);

	//igualdade entre duas matrizes 1 = verdadeiro; 0 = falso
	extern short int Matriz_iguais (Matriz A, Matriz B, double tol);

	// Forma uma matriz a partir de um intervalo [inicio, fim) de vetores nx1 
	extern Matriz Matriz_vetorParaMatriz(Matriz* vetores, int inicio, int fim);

#endif
