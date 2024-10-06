#include<stdio.h>
#include<iostream>
using namespace std;

bool op(double *a, int row, int col, int temp)
{
	double NUM1, NUM2;//主元素、非主元素
	//判断对角线是否为零
	if (a[temp*col + temp] == 0)//若对角线元素为0
		for (int i = temp+1; i < row; i++)//遍历当前以下的行
		{
			double t;
			if (a[i*col+ temp] != 0)//找出主元素非0的行
			{
				for (int j = 0; j < col; j++)//换行
				{
					t = -a[temp*col +j];
					a[temp*col + j] = a[i*col + j];
					a[i*col + j] = t;
				}
				break;
			}
			if (i == row - 1)//若无非0行，值为0，结束
			{
				return false;
			}
		}
	NUM1 = a[temp*col + temp];//主元素
	for (int i = temp + 1; i<row; i++)//遍历，消去所有非主元素
	{
		NUM2 = a[i*col + temp];//非主元素
		for (int j = temp; j<col; j++)
		{
			//通分、相减、将非主元素消为0
			a[i*col + j] = a[i*col + j] - NUM2*a[temp*col + j] / NUM1;
		}
	}
	return true;
}

int main() {

	int row, col;
	double value = 1;
	cout << "请输入行列式阶数";
	cin >> row;
	col = row;

	double  *a = (double*)malloc(row*col*sizeof(double));
	cout << "请输入所有元素" << endl;

	for (int i = 0; i<col*row; i++)
	{
		cin >> a[i];
	}
	cout << "———输入成功———" << endl;
	
	int k = row;
    if (k>col) k = col;

	for (int i = 0; i<k - 1; i++)//计算第i行为主元素的中间矩阵
	{
		if (op(a, row, col, i) == false)//若值为0，输出，结束
		{
			cout << "行列式的值为" << 0 << endl;
			system("pause");
			return 0;
		}
		cout << "———计算过程———" << endl;
		for (int i = 0; i<col*row; i++)//输出中间矩阵
		{
			cout << a[i] << " ";
			if ((i + 1) % col == 0)
				cout << endl;
		}
	}
	cout << "———结果如下———" << endl;
	for (int i = 0; i<col*row; i++)//输出结果矩阵
	{
		cout << a[i] << " ";
		if ((i + 1) % col == 0)
			cout << endl;
	}
	//输出行列式的值
	for (int i = 0; i<k; i++)
		value *= a[i*col + i];
	cout << "行列式的值为" << value << endl;
	system("pause");
	return 0;
}