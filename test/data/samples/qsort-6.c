// https://github.com/jzfjay/-/blob/master/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/main.c

//
//  main.c
//  快速排序算法
//
//  Created by admin on 15/12/10.
//  Copyright © 2015年 admin. All rights reserved.
//

#include <stdio.h>

void Q_sort(int a[],int num);
static int m=0,n=0;
int main()
{

    int k=0;
    int a[9]={3,6,5,9,7,1,8,2,4};
    Q_sort(a, 9);
    for (k=0; k<9; k++) {
        
        printf("%d,",a[k]);
    }
    printf("\n比较次数为:%d\n交换次数为:%d\n",m,n);
    return 0;
}

 //快速排序是不稳定的算法  以为每次排完该元素不一定就确定位置
void Q_sort(int a[],int num){

    int i = 0;
    int j= num -1;
    int key = a[0];
    
    if (num>1) {//重要的判断条件，如果长度小于2，则不需要进行拍排序
        while (i!=j) {
            
            for (; i<j; j--) {
                m++;
                if (a[j]<key) {
                    
                    a[i]=a[j];
                    n++;
                    break;
                }
            }
            
            for (; i<j; i++) {
                m++;
                if (a[i]>key) {
                    a[j] = a[i];
                    n++;
                    break;
                }
                
            }
            a[i]=key;
        }
        
        Q_sort(a, i);//分治思想，递归调用 每次快排结束 把 左侧快排下
        Q_sort(a+i+1, num-i-1);//把 右侧快排下
        
    }
}
