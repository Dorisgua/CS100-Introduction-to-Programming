#include<stdio.h>
#include<iostream>
using namespace std;

bool op(double *a, int row, int col, int temp)
{
	double NUM1, NUM2;//��Ԫ�ء�����Ԫ��
	//�ж϶Խ����Ƿ�Ϊ��
	if (a[temp*col + temp] == 0)//���Խ���Ԫ��Ϊ0
		for (int i = temp+1; i < row; i++)//������ǰ���µ���
		{
			double t;
			if (a[i*col+ temp] != 0)//�ҳ���Ԫ�ط�0����
			{
				for (int j = 0; j < col; j++)//����
				{
					t = -a[temp*col +j];
					a[temp*col + j] = a[i*col + j];
					a[i*col + j] = t;
				}
				break;
			}
			if (i == row - 1)//���޷�0�У�ֵΪ0������
			{
				return false;
			}
		}
	NUM1 = a[temp*col + temp];//��Ԫ��
	for (int i = temp + 1; i<row; i++)//��������ȥ���з���Ԫ��
	{
		NUM2 = a[i*col + temp];//����Ԫ��
		for (int j = temp; j<col; j++)
		{
			//ͨ�֡������������Ԫ����Ϊ0
			a[i*col + j] = a[i*col + j] - NUM2*a[temp*col + j] / NUM1;
		}
	}
	return true;
}

int main() {

	int row, col;
	double value = 1;
	cout << "����������ʽ����";
	cin >> row;
	col = row;

	double  *a = (double*)malloc(row*col*sizeof(double));
	cout << "����������Ԫ��" << endl;

	for (int i = 0; i<col*row; i++)
	{
		cin >> a[i];
	}
	cout << "����������ɹ�������" << endl;
	
	int k = row;
    if (k>col) k = col;

	for (int i = 0; i<k - 1; i++)//�����i��Ϊ��Ԫ�ص��м����
	{
		if (op(a, row, col, i) == false)//��ֵΪ0�����������
		{
			cout << "����ʽ��ֵΪ" << 0 << endl;
			system("pause");
			return 0;
		}
		cout << "������������̡�����" << endl;
		for (int i = 0; i<col*row; i++)//����м����
		{
			cout << a[i] << " ";
			if ((i + 1) % col == 0)
				cout << endl;
		}
	}
	cout << "������������¡�����" << endl;
	for (int i = 0; i<col*row; i++)//����������
	{
		cout << a[i] << " ";
		if ((i + 1) % col == 0)
			cout << endl;
	}
	//�������ʽ��ֵ
	for (int i = 0; i<k; i++)
		value *= a[i*col + i];
	cout << "����ʽ��ֵΪ" << value << endl;
	system("pause");
	return 0;
}