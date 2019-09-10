// https://github.com/Kingpin007/Bubble-Sort/blob/master/main.c

#include <stdio.h>

void bubbleSort(int a[],int n);

int main()
{
  int a[10] = {9,7,5,3,1,8,6,2,0,4};
  bubbleSort(a,10);
  int i=0;
  for(i=0;i<10;i++)
    printf("%d ",a[i]);
  return 0;
}

void bubbleSort(int a[], int n)
{
  int i=0,j=0,temp;
  for(i=0;i<n;i++)
  {
    for(j=0;j<n-i;j++)
    {
      if(a[j]>a[j+1])
      {
        temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }
}
