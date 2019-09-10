// https://github.com/sugerchestnut/DataSort/blob/master/atrtokcode.c

/*======================================================
    > File Name: atrtokcode.c
    > Author: panlu
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月22日 星期日 10时05分23秒
 =======================================================*/

#include<stdio.h>
#include<string.h>

//从小到大排列
int judge(int data[],int low,int high){
    int flag = 0;
    int a1 = 0;
    flag = data[low];  // flag的应用就是将传过来的数组分成两部分，一边比flag小，一边比flag大
    printf("flag = %d\n",flag);

    while(low < high){
        while((data[high] > flag) && (low < high)) high--;    //如果high处的值比flag小
        data[low] = data[high];                               //将high处的值放入low中
        while((data[low] < flag) && (low < high))  low++;     //遇到比flag小的数  将low++
        data[high] = data[low]; //否则将low里面的值变换到high中，此时while((data[high]>flag) && (low < high)) high--语句执行，将high--
    }

    data[low] = flag;
    for(a1 = 0; a1 < high; a1++){
        printf("%d ",data[a1]);
    }
    return low;
}

void quicksort(int data[],int low,int high){
    int preventlow = 0;
    int t1 = 0;

    if(low < high){
        printf("\nquicksort start\n");
        preventlow = judge(data,low,high);   //第一次调用
        quicksort(data,low,preventlow-1);   // 递归调用   分治的思想
        quicksort(data,preventlow+1,high);
    }
}

int main(){
    char s[] ="5,7,2,8,6,1,9,3";
    int num[100];
    char *spilt = ",";      //不能写成char[] 也不知道为什么
    char *p;
    int i = 0;
    int j = 0;
    int len;
    p = strtok(s,spilt);        //第一次分割  取出了第一个数
    num[i++] = *p - '0';
    while((p = strtok(NULL,spilt))){         //接下来循环分割   但是注意第一个原本是原始字符串的参数得改为NULL了
        num[i++] = *p - '0';            //也可以用atoi()函数
    }
    len = i;
    printf("原始数据: \n%d\n ",len);
    quicksort(num,0,i-1);
    printf("\nresult: \n");
    for(j = 0; j < len; j++){
        printf("%d ",num[j]);
    }
    printf("\n");
}
