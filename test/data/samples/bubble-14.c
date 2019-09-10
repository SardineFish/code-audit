// https://github.com/aneeshamanocha/bubblesort.c/blob/master/bubbleSort.c

/*bubble sort is a simple algorithm that swaps neighboring elemnts
of an array if they are in the wrong order until the elements
are in a sequential order*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main () {
	//making array of random numbers
  int size = 10;
	int array[size];
	int range = 100;
	int temp;
	srand(time(NULL)); //seed number generator with correct time

	for(int i =0;  i < size; i++) {
    array[i] = rand() % range;
  }

  //algorithm
  for(int i = 0; i < size - 1; i++) {
	   bool ordered = true;
	   for(int j = 0; j < size - i - 1; j++) {
		     if (array[j] > array[j+1]) {
			        ordered = false;
              temp = array[j];
			        array[j] = array[j +1];
			        array[j + 1] = temp;
        }
	    }
	   if(ordered) {
		    break;
      }
    }


    for(int i = 0; i < size; i++) {
	     printf("%d, ", array[i]);
     }
     printf("\n");
}
