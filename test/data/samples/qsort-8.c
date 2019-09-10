// https://github.com/WoXinfeiyang/QuickSort01/blob/master/QuickSort01Main.c

#include<stdio.h>
/**
 * �ļ����ƣ���������QuickSort01(�����ڱ�����)
 * ʱ�䣺2016-3-7 21:32
 * ˵����1����������QuickSort���ͨ��һ�����򽫴������м�¼�ָ�ɶ����������֣�
 * ����һ���ּ�¼�Ĺؼ��־�������һ���ּ�¼�Ĺؼ���С������Զ��������ּ�¼������������
 * �Ѵﵽ�������������Ŀ�ġ�
 *2��ʱ�临�Ӷȣ���������ʱ�临�Ӷ�����������Ϊo(n^2),ƽ��ʱ�临�Ӷ�Ϊo(nlogn).
 *3��ʹ�õݹ�ʱһ��Ҫ�еݹ�����˳�������
 * */

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

/**����*/
int partition(int *a,int low,int high)
{
	int pivotkey=a[low];
	while(low<high)
	{
		while((low<high)&&(a[high]>pivotkey))
		{
			high--;
		}
		swap(&a[low],&a[high]);

		while((low<high)&&(a[low]<pivotkey))
		{
			low++;
		}
		swap(&a[low],&a[high]);
	}
	return low;
}


void quickSort(int *a,int low,int high)
{
	int mid;
	if(low<high)/*ע��ݹ�Ľ�������*/
	{	
		mid=partition(a,low,high);
		quickSort(a,low,mid-1);
		quickSort(a,mid+1,high);
	}
}




void arrayTraversal(int *a,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

void main()
{
	int a[7]={5,4,3,2,1,7,6};
	quickSort(a,0,6);
	arrayTraversal(a,7);

	int b[5]={5,3,4,6,2};
	quickSort(b,0,4);
	arrayTraversal(b,5);
}

