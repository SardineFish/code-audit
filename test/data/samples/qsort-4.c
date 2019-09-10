// https://github.com/WYQ3333/QuickSort/blob/master/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95%E5%85%AD%EF%BC%88%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%EF%BC%89/QuickSort.c

#include<Windows.h>
#include<stdio.h>

void swap(int *p, int *q)
{
	int *tmp = *p;
	*p = *q;
	*q = tmp;
}

//////////////////////////////////////////////////////////////////////////////
int Parition1(int array[], int left, int right)//�������Ϊ�����֣������±�
{
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while ((begin < end) && (array[begin] <= array[right]))
		{
			begin++;
		}
		while ((begin < end) && (array[end] > array[right]))
		{
			end--;
		}
		swap(&array[begin], &array[end]);
	}
	swap(&array[begin], &array[right]);
	return begin;
}

void _QuickSort1(int array[], int left, int right)//���ұ���Ϊ��׼ֵ,hoare�汾
{
	if (left == right)
		return;//����ֻʣһ����
	if (left > right)
		return;//����û����
	int div = Parition1(array, left, right);
	_QuickSort1(array, left, div-1);
	_QuickSort1(array, div + 1, right);
}

void QuickSort1(int array[], int size)
{
	_QuickSort1(array, 0, size - 1);
}

/////////////////////////////////////////////////////////////////////////////////////
int Parition2(int array[], int left, int right)
{
	int begin = left;
	int end = right;
	int tmp = array[right];
	while (begin < end)
	{
		while (begin<end&&array[begin] <= tmp)
		{
			begin++;
		}
		array[right] = array[begin];
		while (begin<end&&array[end] >= tmp)
		{
			end--;
		}
		array[begin] = array[end];
	}
	array[begin] = tmp;
	return begin;
}

void _QuickSort2(int array[], int left, int right)//���ұߵ�����Ϊ��׼ֵ
{
	if (left == right)//ֻ��һ����
		return; 
	if (left > right)//û����
		return;
	int div = Parition2(array, left, right);
	_QuickSort2(array, left, div - 1);
	_QuickSort2(array, div + 1, right);
}

void QuickSort2(int array[], int size)
{
	_QuickSort2(array, 0, size - 1);
}

/////////////////////////////////////////////////////////////////////////////////////

int Parition3(int array[], int left, int right)
{
	int div = left;
	int cur = left;
	for (; cur < right; cur++)
	{
		if (array[cur] <= array[right])
		{
			swap(&array[cur], &array[div]);
			div++;
		}
	}
	swap(&array[div], &array[right]);
	return div;
}

void _QuickSort3(int array[], int left, int right)
{
	if (left == right)//ֻ��һ����
		return;
	if (left > right)//û����
		return;
	int div = Parition3(array, left, right);
	_QuickSort3(array, left, div - 1);
	_QuickSort3(array, div + 1, right);
}

void QuickSort3(int array[], int size)
{
	_QuickSort3(array, 0, size - 1);
}

void test()
{
	int array[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int size = sizeof(array) / sizeof(array[0]);
	//QuickSort1(array, size);//hoare�����
	//QuickSort2(array, size);//�ڿӷ�����
	QuickSort3(array, size);//ǰ��ָ��
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}