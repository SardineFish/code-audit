// https://github.com/Qaczka/Bubble/blob/master/Bubble/%C5%B9r%C3%B3d%C5%82o.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


int main()
{
	int i, n, m, l, c, il_oper;

	long long int il_oper2;

	il_oper = 0;
	il_oper2 = 0;


	printf("Ile liczb chcesz uporzadkowac?\n");
	scanf("%i", &l);
	scanf("%i", &c);

	printf("\n");

	int liczby[l], tym;

	FILE *sort = fopen("sort.txt", "w");
	FILE *sortr = fopen("sortr.txt", "w");

	srand(time(NULL));
	for (i = 0; i<l; i++)
	{
		liczby[i] = rand() % 32001;
	}

	for (i = 0; i<l; i++)
	{
		fprintf(sort, "%i ", liczby[i]);

	}

	printf("\n");



	/*
	printf("Prosze wprowadzic liczby: \n");

	for(m=0;m<l;m++)
	{
	scanf("%i",&liczby[m]);
	}

	printf("\n");
	*/

	//---------------------------------------------------------------------------------------------------------------------------//

	if (c == 1)
	{
		clock_t poczatek = clock();

		for (n = 0; n<l; n++)
		{
			for (m = 0; m<l - 1 - n; m++)
			{
				if (liczby[m]>liczby[m + 1])
				{
					tym = liczby[m];
					liczby[m] = liczby[m + 1];
					liczby[m + 1] = tym;
					il_oper2 = il_oper2 + 3;
				}
			}
		}
		clock_t koniec = clock();
		double czas = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
		printf("Czas wykonywania to: %f", czas);
		printf("\n");

		printf("Ilosc przestawien to: %lli", il_oper2);




	}



	//---------------------------------------------------------------------------------------------------------------------------//

	if (c == 2)
	{
		clock_t poczatek = clock();

		int najwieksza, pozycja;

		najwieksza = liczby[0];
		i = 0;

		for (n = 0; n<l - 1; n++)
		{
			for (m = 0; m<l - n; m++)
			{
				if (najwieksza<liczby[m])
				{
					najwieksza = liczby[m];
					pozycja = m;
				}
			}

			tym = liczby[l - 1 - n];
			liczby[l - 1 - n] = najwieksza;
			liczby[pozycja] = tym;
			il_oper2 = il_oper2 + 3;
			najwieksza = 0;
		}

		clock_t koniec = clock();
		double czas = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
		printf("Czas wykonywania to: %f", czas);
		printf("\n");

		printf("Ilosc przestawien to: %lli", il_oper2);


	}

	for (i = 0; i<l; i++)
	{
		fprintf(sort, "%i ", liczby[i]);
	}

	printf("\n");

	//---------------------------------------------------------------------------------------------------------------------------//


	if (c == 3)
	{


		//przypadek bazowy
		clock_t poczatek = clock();





		for (m = 1; m<l; m++)
		{


			i = m;

			while (liczby[i]<liczby[i - 1] && (i>0))
			{
				tym = liczby[i - 1];
				liczby[i - 1] = liczby[i];
				liczby[i] = tym;
				i--;
				il_oper2 = il_oper2 + 3;
			}

		}
		clock_t koniec = clock();
		double czas = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
		printf("Czas wykonywania to: %f", czas);
		printf("\n");


		printf("Ilosc przestawien i przesuniec to: %lli", il_oper2);
		printf("\n");




	}




	for (i = 0; i<l; i++)
	{
		//  printf("%i ",liczby[i]);
	}
	printf("Ilosc operacji to: %i", il_oper);





	return 0;
}
