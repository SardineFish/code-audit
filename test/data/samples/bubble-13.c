// https://github.com/baranseldinc/bubbleSortAndSelectionSort/blob/master/bubbleSort.c

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int randomNumberGenerator(int a, int b) { 
  if(b <= a) { 
    printf("Ikinci parametre mutlaka ilkinden buyuk olmalidir!\n"); 
    return(0); 
  } else { 
    int randomize = rand(); 
    srand(time(0) * randomize); 
    return rand() % ((b - a) + 1) + a; 
  } 
}
int main()
{
  int array[10000], n, c, d, swap,r;
  int numOfComp = 0,numOfSwap = 0;
  
  printf("Enter number of elements\n");
  scanf("%d", &n);
 
  printf("Enter %d integers\n", n);
 
  for (c = 0; c < n; c++){
  

	array[c] = randomNumberGenerator(0,n+1);
  }
 
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
        numOfComp ++;
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
         numOfSwap++;
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
  }
 
  printf("Sorted list in ascending order:\n");
 
  for ( c = 0 ; c < n ; c++ )
     printf("%d\n", array[c]);
     printf("\n\n\n");
     printf("Num Of Comparation: %d\n",numOfComp);
     printf("Num Of Swap: %d\n",numOfSwap);
     system("pause");
  return 0;
}


// Bubble Sort i�in
