// https://github.com/BenedictOwler/BubbleSort/blob/master/BubbleSort.c

#include <stdio.h>

void bubblesort (int *, int);
void erzeugeArray (int *, int);
void zeigeArrayInConsole (int *, int);
void dreiEcksTausch (int *, int);



int
main ()
{
  int anz = 10;
  int z[anz];

  erzeugeArray (z, anz);
  printf ("\nArray mit %d zufaellige Zahlen \n", anz);
  zeigeArrayInConsole (z, anz);
  bubblesort (z, anz);
  printf ("\nArray mit %d zufaellige Zahlen sortiert:\n", anz);
  zeigeArrayInConsole (z, anz);

  printf ("\n Die maximalen Zahl von Sortieren wären (%d-1)*(%d-1) = %d\n", anz,anz,(anz-1)*(anz-1));
  printf ("Verbesserte Version (Pro Durchlauf 1 Vergleich weniger) wäre:(%d+%d+%d+ ... + 2 +1 =%d\n", anz-1,anz-2,anz-3,(anz/2)*(1+anz));
}

int zeigeArrayInConsole (int *array, int anz)
{

  for (int i = 0; i < anz; i++)
    {
        printf ("%d ", array[i]);
    }

//array = [1,2,3,4,5]

  return 0;
}

void
erzeugeArray (int *array, int anz)
{
  srand (5);
  for (int i = 0; i < anz; i++)
    array[i] = rand()%100;
  return 0;
}


void dreiEcksTausch (int *array, int position)
{
    //printf("vorher: %d , %d  ",array[position], array[position+1]);
    int temp = array[position];
    array[position] = array[position+1];
    array[position+1] = temp;
    //printf("nacher: %d , %d\n",array[position], array[position+1]);
  return 0;
}
void bubblesort (int *z, int anz)
{ int getauscht;
    for (int d=0; d < anz-1; d++) {
        
        getauscht = 0;
        
        for (int v=0; v < anz-1-d; v++) {
            
            if (z[v] > z[v+1]) {
                
                dreiEcksTausch (z,v);
                getauscht = 1;
            }
        }
        if ( getauscht == 0) {
            break;
        }
        
    }
    
    
      return 0;

}
