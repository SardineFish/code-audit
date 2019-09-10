// https://github.com/nerd010/BubbleSort/blob/master/BubbleSort/main.c

//
//  main.c
//  BubbleSort
//
//  Created by chw on 16/1/17.
//  Copyright © 2016年 CHW. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
   /*
    冒泡排序的基本思想：每次比较两个相邻的元素，如果它们的顺序错误就把它们交换过来
    5个数冒泡 ：12，35，99，18，76
    从大到小
    */
    /*
    int a[100],i,j,t,n;
    printf("请输入您要排序的数字个数(<100)：");
    scanf("%d",&n);
    for (i = 1; i <= n; i++)
    {
        printf("请输入你要排序的数字：");
        scanf("%d",&a[i]);
    }
    for (i = 1; i <= n - 1; i++)
    {
        for (j = 1; j <= n - i; j++)
        {
            if (a[j] < a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
                printf("bubble sort");
                for (int m = 0; m < 5; m++)
                {
                    printf(" %d",a[m]);
                }
                printf("\n=============\n");
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        printf(" %d",a[i]);
    }
    
    getchar();getchar();
    
    */
    
    
    
    /*
    int bubble[5] = {12, 35, 99, 18, 76};
    int j = 0;
    int m = 0;
    
    for (int i = 0; i < 5 - 1; i++)
    {
        for (int j = 0; j < 5 - (i+1); j++)
        {
            if (bubble[i] < bubble[i+1])
            {
                j = bubble[i+1];
                bubble[i+1] = bubble[i];
                bubble[i] = j;
                printf("bubble sort");
                for (m = 0; m < 5; m++)
                {
                    printf(" %d",bubble[m]);
                }
                printf("\n=============\n");
            }
        }
       
    }
    
    for (int k = 0; k < 5; k++)
    {
         printf(" %d",bubble[k]);
    }
*/
    /*
    int bubble[5] = {12, 35, 99, 18, 76};
    int j;
    int n = 0;
    for (int i = 0; i < 5 - 1; i++)
    {
        for (int k = 0; k < 5 - (i + 1); k++)
        {
            n++;
            printf("n:%d\n",n);
            printf("bubble[k]:%d\nbubble[k+1]:%d\n",bubble[k],bubble[k+1]);
            if (bubble[k] < bubble[k+1])
            {
                j = bubble[k];
                bubble[k] = bubble[k+1];
                bubble[k+1] = j;
                printf("bubble sort");
                for (int m = 0; m < 5; m++)
                {
                    printf(" %d",bubble[m]);
                }
                printf("\n=============\n");
            }
        }
    }
    
    printf("\n------------------------\nbubble sort:");
    
    for (int l = 0; l < 5; l++)
    {
        printf(" %d",bubble[l]);
    }
    */
    
    
    /*=====================================冒泡排序=================================================*/
    int bubbleSort[100];
    int n;
    int k;
    int l = 0;
    
    printf("请输入您要输入的数字的个数(<100)：");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        printf("请输入数字：");
        scanf("%d",&bubbleSort[i]);
    }
    
    /*--------------------------------------从小到大----------------------------------------------------*/
    //循环次数为 n-1 次（清楚这一点）
    for (int i = 0; i < n - 1; i++ )
    {
        //因为每次比较后都会有一个数“归位”，所以每次在“一趟”的比较过程中都会减少一次的比较
        
        for (int j = 0; j < n - (i + 1); j++)
        {
            l++;
            printf("l:%d\n",l);
            printf("bubbleSort[j]:%d\n bubbleSort[j+1]:%d\n",bubbleSort[j],bubbleSort[j+1]);
            if (bubbleSort[j] > bubbleSort[j+1])
            {
                k = bubbleSort[j];
                bubbleSort[j] = bubbleSort[j+1];
                bubbleSort[j+1] = k;
                
                printf("subbleSort:");
                for (int h = 0; h < n; h++)
                {
                    printf(" %d",bubbleSort[h]);
                }
                printf("\n===================================================\n");
            }
        }
    }
    
    printf("\n-------------------------------------------------\n");
    //从小到大 排好顺序的数组
    for (int m = 0; m < n; m++)
    {
        printf(" %d",bubbleSort[m]);
    }
    
/*----------------------------------------------------从大到小-------------------------------------------
    //循环次数为 n-1 次（清楚这一点）
    for (int i = 0; i < n - 1; i++ )
    {
        //因为每次比较后都会有一个数“归位”，所以每次在“一趟”的比较过程中都会减少一次的比较
        
        for (int j = 0; j < n - (i + 1); j++)
        {
            l++;
            printf("l:%d\n",l);
            printf("bubbleSort[j]:%d\n bubbleSort[j+1]:%d\n",bubbleSort[j],bubbleSort[j+1]);
            if (bubbleSort[j] < bubbleSort[j+1])
            {
                k = bubbleSort[j];
                bubbleSort[j] = bubbleSort[j+1];
                bubbleSort[j+1] = k;
                
                printf("subbleSort:");
                for (int h = 0; h < n; h++)
                {
                    printf(" %d",bubbleSort[h]);
                }
                printf("\n===================================================\n");
            }
        }
    }
    
    printf("\n-------------------------------------------------\n");
    //从大到小 排好顺序的数组
    for (int m = 0; m < n; m++)
    {
        printf(" %d",bubbleSort[m]);
    }
    */
    getchar();getchar();
    return 0;
}
