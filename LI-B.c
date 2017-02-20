#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void)
{
	int i, j, n, k, count = 0;
	printf("Insira a quantidade de elementos do vetor:\n");
	scanf ("%d", &n);
	float mat[n][n],vet[n][n], /*vetun [n],*/ neg = 0, temp, rest = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("Insira o elemento a %d\n do vetor %d", j+1, i+1);
			scanf("%f", &vet[i][j]);
		}
	}

      	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			mat[i][j]=vet[i][j];

		}
	}


	for(i = 0; i < n - 1; i++)
    {
        if(vet[i][i] == 0)
        {
            for(k = i; k < n; k++)
            {
                if(vet[k][i] != 0)
                {
                    for(j = 0; j < n; j++)
                    {
                        temp = vet[i][j];
                        vet[i][j] = vet[k][j];
                        vet[k][j] = temp;
                    }
                    k = n;
                }
            }
            count++;
        }

        if(vet[i][i] != 0)
        {
            for(k = i + 1; k < n; k++)
            {
                neg = -1.0 * vet[k][i] /  vet[i][i];
                for(j = i; j < n; j++)
                {
                    vet[k][j] = vet[k][j] + (neg * vet[i][j]);
                }
            }
        }
    }

    temp = 1.0;
    // Calcula o determinante
    rest = count%2;
    for(i = 0; i < n; i++)
        temp *= vet[i][i];

    printf("\nDeterminante:\n");
    if(rest == 0)
        printf("%f \n", temp);
    else
        printf("%f \n", -1.0 * temp);

    if (temp == 0)
    {
    	printf("Esse sistema é linearmente dependente\n");
    }
    else
    {
    	printf("Esse sistema é linearmente independente\n");

    }
    	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf(" %f\n",mat[i][j]);

		}
	}


	// Vendo se é ortogonal

	float ort=1,ort1=0;
    int p=0;
    while(p<n){
    for (i = 0; i < n; i++)
	{

            ort*=mat[i][p];
        if(i+1==n){
            ort1+=ort;
            ort=1;
            p++;
        }
	}
	 for (i = 0; i < n; i++)
	{

        ort*=mat[i][p];
        if(i+1==n){
            ort1+=ort;
            ort=1;
            p++;
        }
	}
	}
	printf("\n\n\n\prod escalar: \n%f",ort1);

	float uni[n];
    for (i = 0; i < n; i++)
	{
	       uni[i]=0;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
            uni[i]+=pow(mat[i][j],2);
            uni[i]=sqrt(uni[i]);

        }
    }
 int t=1;
    if(temp!=0)
    {
            if(ort1==0)
            {
                    for(i=0;i<n;i++)
                    {
                            if(uni[i]==1)
                            {
                                t++;
                                if(t==n)
                                {
                                    printf("\n\n\nOs vetores sao ortonormais\n");
                                }
                            }
                            else
                                printf("\n\n\n\n Os vetores nao sao unitarios");
                    }
            }
            else
                printf("\n\n\n\nOs vetores nao sao ortogonais\n\n\n");
    }
    else
        printf("\n\n\n\nOs vetores sao linearmente dependentes");



return 0;

}
