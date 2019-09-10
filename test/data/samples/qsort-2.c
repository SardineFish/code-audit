// https://github.com/MingYanWoo/QuickSort/blob/master/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F/QuickSort.c

//
//  QuickSort.c
//  快速排序
//
//  Created by 吴铭彦 on 16/5/21.
//  Copyright © 2016年 MingYan. All rights reserved.
//

#include "QuickSort.h"

void Qsort(int A[],int Left,int Right);
int Median3(int A[],int Left,int Right);
void Swap(int *a,int *b);

void QuickSort(int A[],int N)
{
    Qsort(A, 0, N - 1);
}

//int a[] = {3,5,7,1,35,9};

void Qsort(int A[],int Left,int Right)
{
    if (Left >= Right) return ;                         //Left >= Right时要返回，不然一直循环
    int i,j;
    int Pivot;
    
    Pivot = Median3(A, Left, Right);
    i = Left;j = Right - 1;
    if (Left+1 != Right)                                 //Left和Right相邻时，数组两个数已经排好序，不进入，否则越界 （数组三个数时也已排好序，但可以进入，因为不改变）
        for (; ; ) {
            while(A[++i] < Pivot);                      //i自加到大于Pivot停止
            while(A[--j] > Pivot);                      //j自减到小于Pivot停止
            if (i < j)
                Swap(&A[i], &A[j]);
            else
                break;
        }
    Swap(&A[i], &A[Right-1]);
    Qsort(A, Left, i-1);
    Qsort(A, i+1, Right);
}

//选取枢纽元并排序前中后三个元素
int Median3(int A[],int Left,int Right)
{
    int Center = (Left + Right) / 2;
    
    if (A[Left] > A[Center])
        Swap(&A[Left],&A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left],&A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center],&A[Right]);
    /** 使A[Left] <= A[Center] <= A[Right] */
    Swap(&A[Center],&A[Right-1]);            //将枢纽元放到倒数第二，（最后一个数肯定比枢纽元大）
    return A[Right-1];                      //返回枢纽元
}

void Swap(int *a,int *b)                    //交换元素
{
    int Temp;
    Temp = *a;
    *a = *b;
    *b = Temp;
}