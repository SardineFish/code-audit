// https://github.com/DarkPocket/Quicksort/blob/master/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95.c

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int Partition (int r[], int low , int high )
{
        //交换顺序表L中子表r high的记录 枢轴记录到位，并返回其所在的位置，
        //此时在它之前 （后）的记录均不大（小）于它
        int cache;
        int pivotkey;

        cache = r[low];
        pivotkey = r[low];   //用子表的第一个记录作枢轴记录

        while (low < high) //从表的两段交替向中间扫描
        {
                while ((low < high) && (r[high] >= pivotkey))
                {
                        high--; //比枢轴记录小的移到低端
                }
                r[low] = r[high];
                while ((low < high) && (r[low] <= pivotkey))
                {
                        low++;//比枢轴记录大的移到高端
                }
                r[high] = r[low];

        }


        r[low] = cache;
        r[low] = pivotkey;
        return low ; //返回枢轴位置

}

void QSort (int L, int low, int high)
{
        int pivotloc = 0;
        //对顺序表L中 子序列 low high 做快速排序

        if (low < high) //长度大于一
        {
                pivotloc = Partition(L, low, high);  //将L一分为二
                QSort(L, low, pivotloc - 1);      //对低子表递归排序
                QSort(L, pivotloc + 1, high);    //对高子表递归排序

        }

}


void QuickSort(int L[], int len)
{

        //对顺序表L   做快速排序
       // printf ("  len=%d ", len);
        QSort(L, 0, len);


}



int main()
{

        int a[50] = {0};
        int i;
        int len;


        for (i = 0; i < 30; i++)
        {
                //  a[i] = i * i * i - 20 * i * i + 10 * i + 20;
                a[i] = 60 - i * 2;
        }





        for (i = 0; i < 30; i++)
        {
                if (i % 5 == 0)
                {
                        printf("\n");
                }
                printf (" %d ", a[i]);
        }
        printf("\n");

        len = 29;
        QuickSort (a, len);

        printf (" \n");
        for (i = 0; i < 30; i++)
        {

                if (i % 5 == 0)
                {

                        printf("\n");
                }
                printf (" %d ", a[i]);
        }

        printf("\n\n");
        return 0;
}
