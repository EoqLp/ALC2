#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "matrizlib.h"

// Gera uma matriz aleatória com elementos variando de -max a +max
Matriz Matriz_initAleatoria(unsigned int linhas, unsigned int colunas, int max)
{
	Matriz matriz;

	matriz.linhas = linhas;
	matriz.colunas = colunas;
	matriz.triangular = NAO;

	int i, j;

	if ( !( matriz.valor = (double**)malloc(linhas*sizeof(double*)) ) ) {
		if (Matriz_debug == 1) printf ("Nao foi possivel criar matriz\n");
	}
	for ( i = 0; i < linhas; i++) {
		if ( !( matriz.valor[i] = (double*)malloc(colunas*sizeof(double) ) ) ) {
			if (Matriz_debug == 1) printf ("Nao foi possivel criar matriz\n");
		}
		else
			for( j = 0; j < colunas; j++ )
				matriz.valor[i][j] = rand() % ( ( max + 1 ) * 2 ) - max;
	}

	return matriz;
}

Matriz Matriz_residuo( Matriz A, Matriz x, Matriz b )
{
	Matriz Ax = Matriz_mult( A, x, 0 );
	Matriz b_Ax = Matriz_sub( b, Ax, 0 );
	Matriz_free( Ax );

	return b_Ax;
}

Matriz PSO( Matriz A, Matriz b, double max_aleatorio )
{
	int qnt = A.colunas * 0.3;
	int i, j, count = 0, sem_solucao = 0;
	double melhor_residuo = 2e31, criterio_parada, soma_nulo = 0;
	double A1, A2, A3, C1, C2;

	if( qnt < 3 )
		qnt = 3;	

	C1 = 1;
	C2 = 1;

	puts( "\tPARTICLE SWARM OPTIMIZATION ");
	printf( "%d partícula(s) criada(s)\n", qnt );
	puts( "Critério de parada:" );
	scanf( "%lf", &criterio_parada );

	// Melhor posição do bando, resíduo_melhor_posição_bando, melhor posição da partícula, posição da partícula, velocidade da partícula
	Matriz 	mb, rMB, mp[qnt], s[qnt], v[qnt], rMP, rSi;
	
	mb = Matriz_init( 1, 1 ); // só iniciando
	// iniciando as partículas com posições e velocidades aleatórias
	for( i = 0; i < qnt; i++ )
	{
		s[i] = Matriz_initAleatoria( A.colunas, 1, max_aleatorio );
		v[i] = Matriz_initAleatoria( A.colunas, 1, max_aleatorio );
		mp[i] = Matriz_copia( s[i] );

		rMP = Matriz_residuo( A, mp[i], b ); // resíduo da melhor posição da partícula

		if( Matriz_normaFrobenius( rMP ) < melhor_residuo )
		{
			Matriz_free( mb );
			melhor_residuo = Matriz_normaFrobenius( rMP );
			mb = Matriz_copia( mp[i] );
			Matriz_free( rMP );
		}

	}

	// Enquanto não alcançar o critério de parada
	while( melhor_residuo > criterio_parada /*&& count < A.colunas * 10000 */)
	{
		// para cada partícula, geraremos escalares aleatórios variando entre 0 e 1 para controlar melhor a velocidade
		for( i = 0; i < qnt; i++ )
		{
			A1 = fmod( rand(), 10e6 ) / 10e6 ;
			A2 = fmod( rand(), 10e6 ) / 10e6 ;
			A3 = fmod( rand(), 10e6 ) / 10e6 ;
			
			// Aqui garantimos que a velocidade nunca zere
			if( criterio_parada/10 > Matriz_normaFrobenius( v[i] ) )
			{	
				Matriz_free( v[i] );
				v[i] = Matriz_initAleatoria( s[i].linhas, 1, max_aleatorio );
			}

			// Ajustamos a velocidade
			for( j = 0; j < v[i].linhas; j++ )
				v[i].valor[j][0] = ( A1* v[i].valor[j][0] ) + ( A2 * C1 * ( mp[i].valor[j][0] - s[i].valor[j][0] ) ) + ( A3 * C2 * ( mb.valor[j][0] - s[i].valor[j][0] ) );
			// Ajustamos a posição
			for( j = 0; j < s[i].linhas; j++ )
				s[i].valor[j][0] += v[i].valor[j][0];

			// Verificamos a posição da partícula, para saber se é a melhor posição desta partícula
			rSi = Matriz_residuo( A, s[i], b ); // residuo da posição da partícula
			rMP = Matriz_residuo( A, mp[i], b ); // resíduo da melhor posição da partícula

			if( Matriz_normaFrobenius( rSi ) < Matriz_normaFrobenius( rMP ) )
			{
				Matriz_free( mp[i] );
				mp[i] = Matriz_copia( s[i] );
			}

			// Verificamos se a melhor posição da partícula é a melhor posição do bando
			rMB = Matriz_residuo( A, mb, b ); // resíduo da melhor posição do bando

			if( Matriz_normaFrobenius( rMP ) < Matriz_normaFrobenius( rMB ) )
			{
				Matriz_free( mb );
				mb = Matriz_copia( mp[i] );

				/*Matriz_free( rMB );
				rMB = Matriz_residuo( A, mb, b );
				melhor_residuo = Matriz_normaFrobenius( rMB );

				Matriz_free( rMP );*/

				sem_solucao = 0;
			}
			count++;
		}

		sem_solucao++;

		// Se após 300 * qnt iterações não houver melhora na posição do bando de partículas, assumiremos que o sistema não tem solução
		if( sem_solucao >= 300 )
		{
			printf( "O sistema não tem solução. Exibindo a solução para a melhor norma do resíduo\n" );
			break;
		}

		
	}

	printf( "%d iterações feitas\n", count );
	printf( "Norma residual da solução = %.20lf\n", melhor_residuo );
	puts( "Vetor solução encontrado" );
	for( i = 0; i < mb.linhas; i++ )
	{
		printf("%.3lf\n", mb.valor[i][0] );
	}

	//Liberar espaço alocado
	for( i = 0; i < qnt; i++ )
	{
		Matriz_free( s[i] );
		Matriz_free( v[i] );//exemplo 
		Matriz_free( mp[i] );
	}

	Matriz_free( rMB );

	return mb;
}

int main( void )
{
	srand( time( NULL ) );

	FILE  *entrada, *saida;

	entrada = fopen( "entrada.txt", "r" );
	saida = fopen( "saida.txt", "w" );

	puts( "\tEXERCÍCIO 3" );
	int linhas, colunas, i, j;
	fscanf( entrada, "%d %d", &linhas, &colunas );

	puts( "Limite superior aleatório para criação dos vetores:" );
	double max_aleatorio;
	scanf( "%lf", &max_aleatorio );

	Matriz A = Matriz_init( linhas, colunas);
	Matriz b = Matriz_init( linhas, 1 );

	Matriz_fscanf( entrada, A );
	Matriz_fscanf( entrada, b );

	puts( "Matriz A (lida no arquivo)" );
	Matriz_fprintf( stdout, A, '\n' );

	puts("\nVetor b (lido no arquivo)" );
	Matriz_fprintf( stdout, b, '\n' );

	A = Matriz_transp( A, 0 );

	// xPSO guardará a solução x pelo PSO
	Matriz xPSO = PSO( A, b, max_aleatorio );

	Matriz_fprintf( saida, A, '\n' );
	Matriz_fprintf( saida, b, '\n' );
	Matriz_fprintf( saida, xPSO, '\n' );

	Matriz_free( A );
	Matriz_free( b );
	Matriz_free( xPSO );
}
