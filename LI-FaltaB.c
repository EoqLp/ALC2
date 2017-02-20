#include <stdio.h>
#include <math.h>

void check_Linear_Dependency(int n, int dim, double *matrix);
void ordering_Matrix(int n, int dim, double *matrix);
void calculate_Unitary_Vector(int n, int dim, double *matrix);
double CalculoDeterminante(int ordem , double *matriz);
double cofactor(int ordem, double *matriz, int linha, int coluna);

int main(void)
{

	printf("-----------VETORES LINEARMENTE INDEPENDENTES-----------\n\n");

	int n = 0;
	int dim = 0;
	int forcar_entrada_correta = 0;

	while (n < 1 || dim < 1)
	{
		if (forcar_entrada_correta > 0)
		{
			printf("\nEntre com valores iguais a 1 ou maiores!\n");
		}

		printf("Entre com o número de vetores a serem analizados\n");
		scanf("%d", &n);

		printf("Entre com a dimensão dos vetores a serem analizados\n");
		scanf("%d", &dim);

		forcar_entrada_correta ++;
	}

	double matriz[n][dim];


	printf("Entre com %d vetores de %d dimensões, não nulos\n", n, dim);

	for (int i = 0; i < n; i ++)
	{

		for (int j = 0; j < dim; j ++)
		{
			scanf("%lf", &matriz[i][j]);
		}

		
	}




	if (n == dim && CalculoDeterminante(n, &matriz[0][0]) == 0)
	{
		printf("\n\nLinearmente Dependente! (Det = 0)\n");
		calculate_Unitary_Vector(n, dim, &matriz[0][0]);
		return 0;
	}

	calculate_Unitary_Vector(n, dim, &matriz[0][0]);

	check_Linear_Dependency(n, dim, &matriz[0][0]);
	
	return 0;

}

void calculate_Unitary_Vector(int n, int dim, double *matrix)
{

	long double norm[n];


	for (int i = 0; i < n; i ++)
	{

		norm[i] = 0;

		for (int j = 0; j < dim; j ++)
		{
			norm[i] = norm[i] + *(matrix + (i*dim) + j) * *(matrix + (i*dim) + j);
		}

		norm[i] = sqrt(norm[i]);
		
		printf("\n\nVetor Unitário %d = {", i + 1);

		for (int l = 0; l < dim; l ++)
		{
			if (l + 1 < dim)
			{
				printf("%Lf , ", *(matrix + (i * dim) + l) /norm[i] );

			}

			else
			{
				printf("%Lf}", *(matrix + (i * dim) + l) /norm[i] );

			}
		}

		printf("\n\n");
	}

	return;

}

void check_Linear_Dependency(int n, int dim, double *matrix)
{
	int same_horizontal = 0;
	int same_vertical = 0;
	int zeros = 0;
	long double norm[n];

	//Checa zeros
	for (int i = 0; i < n; i ++)
	{
		zeros = 0;

		for (int j = 0; j < dim; j ++)
		{
			if (*(matrix + (i*n) + j) == 0)
			{
				zeros ++;
			}
		}

		if (zeros == dim)
		{
			printf("Linearmente Dependente! (Vetor Nulo)\n");
			return ;
		}
	}

	//CHeca Posto
	if (n > dim)
	{
		printf("Linearmente Dependente! (Mais Vetores que a Dimensão)\n" );
		return;
	}
	
	for (int i = 0; i < n; i ++)
	{
		norm[i] = 0;

		for (int j = 0; j < dim; j ++)
		{
			norm[i] = norm[i] + *(matrix + (i*dim) + j) * *(matrix + (i*dim) + j);
		}

		norm[i] = sqrt(norm[i]);

	}

	//Checka igualdade por linhas
	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < n; j ++)
		{
			same_horizontal = 0;

			for (int k = 0; k < dim; k ++)
			{
				if(i == j)
				{
					break;
				}
				
				//OBSSSS -> FLOAT SÃO APROXIMAÇÔES... diferencas de (-0.001 a 0.001) são consideradas iguais 
				if ((*(matrix + (i*dim) + k)/norm[i]) - (*(matrix + (j*dim) + k)/norm[j]) < 0.001 && (*(matrix + (i*dim) + k)/norm[i]) - (*(matrix + (j*dim) + k)/norm[j]) > - 0.001)
				{
					same_horizontal ++;

				}
				
				if (same_horizontal == dim)
				{
					printf("Linearmente Dependente!\n");
					return;
				}
			}
		}
	}

	
	printf("Linearmente Independente!\n");
	return;
}

double CalculoDeterminante(int ordem , double *matriz)
{
	double determinante = 0; 
	int i, j;
	if(ordem == 1)
		determinante = *matriz;
	else{
		for(j = 0; j < ordem; j++){
			determinante = determinante + (*(matriz + j) * cofactor(ordem, &(*matriz), 0, j));
		} 
	}

	return determinante;
}

double cofactor(int ordem, double *matriz, int linha, int coluna)
{
	int i, j, aux1 = 0, aux2 = 0, ordem2 = ordem - 1;
	double matrizCofactor[ordem2][ordem2];
	
	for(i = 0; i<ordem; i++)
	{
		for(j = 0; j<ordem; j++)
		{
			if(i != linha && j != coluna)
			{
				matrizCofactor[aux1][aux2] = *(matriz + (i*ordem) + j);
				aux2++;
				if(aux2 >= ordem2)
				{
					aux1++;
					aux2 = 0;
				}
			}
		}
	}
	return pow(-1, linha+coluna) * CalculoDeterminante(ordem2, &matrizCofactor[0][0]);
}

