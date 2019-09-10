// https://github.com/UGknight/Bubble-Sort/blob/master/Bubble_Sort.c

#include<stdio.h>

int main(int argc,char* argv[])
{
 printf("how many number do you want to sort?");
 int length;
 int sort[length];
 scanf("%d",&length);
 for(int i = 0 ; i < length ; i++)
     {
      scanf("%d",&sort[i]);
     }
 for(int i = 0 ; i < length-1 ; i++)
     {for(int j = 0 ; j < length - 1 - i ; j++)
          {
	   if(sort[j] > sort[j+1])
	      {
	       int solider = sort[j+1];
	       sort[j+1] = sort[j];
	       sort[j] = solider;
	      }
	  }
     }
 for(int i = 0 ; i < length ; i++)
 {
  printf("%d\t",sort[i]);
 }
 printf("\n");
}
