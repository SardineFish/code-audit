// https://github.com/HhDdshuai/quickSort/blob/master/main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemType;
int Partition(elemType a[],int low,int high){
    int pivot = a[low];                         //����ǰ���е�һ��Ԫ����Ϊ����ֵ���Ա����л���
    while(low < high){                          //low > high����ѭ��
        while(low < high && a[high] > pivot)    //�˴�low < high ��Ϊ�˱�����ȫ����ʱ������������
            --high;                             //�Ӻ���ǰѰ�ұ�pivotС��Ԫ��
        a[low] = a[high];                       //��������С���ƶ������
        while(low < high && a[low] < pivot)
            ++low;                              //��ǰ����Ѱ�ұ�������Ԫ��
        a[high] = a[low];                       //�����������ƶ����Ҷ�
    }
    a[low] = pivot;                             //����Ԫ�ط�������λ��
    return low;                                 //���ش�����������λ��
}
void Q_Sort(elemType a[],int low,int high){
    if(low < high){                             //�ݹ����
        int pivot_pos = Partition(a,low,high);  //����
        Q_Sort(a,low,pivot_pos - 1);            //�ݹ����
        Q_Sort(a,pivot_pos + 1,high);
    }
}

int main()
{
    elemType a[] = {12,864,212,7,54,2,69,76,127,965,5451,761,215,25,85,49,42,14,256,29,
    55,87,66,23,01,861,91,31};
    int len = sizeof(a)/sizeof(elemType);
    Q_Sort(a,0,len - 1);
    for(int i = 0;i < len;i++){
        printf("%d ",a[i]);
    }
    return 0;
}
