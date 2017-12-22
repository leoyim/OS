/*********************************
*   程序：页面调度算法模拟         *
*   作者：闫文博                  *
*********************************/
#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;

//先入先出FIFO
void FIFO(int *pages, int num, int block) {
	int *mem = (int *)malloc(block * sizeof(int));
	for (int i = 0; i < block; i++)
	{
		mem[i] = 0;
	}
	char *f = (char *)malloc(num * sizeof(char));
	int q, sum = 0;
	char flag;
	int ** List = new int *[block];
	for (int i = 0; i < block; i++)
	{
		List[i] = new int[num];
	}
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < num; j++)
		{
			List[i][j] = 0;
		}
	}
	for (int i = 0; i<num; i++)               //查页表，看是否缺页
	{
		q = 0;
		while ((pages[i] != mem[q]) && (q != block))
			q++;
		if (q == block)
			flag = '*';                       //缺页，则置标志flag为'*'
		else
			flag = ' ';
		if (flag == '*')
		{
			for (int j = block - 1; j > 0; j--) //淘汰最先调入的页面调入当前访问的
			{
				mem[j] = mem[j - 1];
			}
			mem[0] = pages[i];
		}
		for (int j = 0; j<block; j++)
			List[j][i] = mem[j];
		f[i] = flag;
	}
	cout << "\n----------------FIFO----------------" << endl;
	for (int i = 0; i<block; i++)
	{
		for (int j = 0; j<num; j++)
			cout << List[i][j] << "  ";
		cout << endl;
	}
	for (int i = 0; i<num; i++)
	{
		if (f[i] == '*')
			sum++;
		cout << f[i] << "  ";
	}
	cout << "\n-----------------------------------" << endl;
	cout << "缺页次数:" << sum << '\t' << "缺页率:" << (float)sum / num * 100.0 << "%" << endl;
	for (int i = 0; i<block; ++i)
		delete[] List[i];
	delete[] List;
}

//最近最久未使用LRU
void LRU(int *pages, int num, int block) {
	int *mem = (int *)malloc(block * sizeof(int));
	for (int i = 0; i < block; i++)
	{
		mem[i] = 0;
	}
	char *f = (char *)malloc(num * sizeof(char));
	int q, sum = 0;
	char flag;
	int ** List = new int *[block];
	for (int i = 0; i < block; i++)
	{
		List[i] = new int[num];
	}
	for (int i = 0; i < block; i++)
	{
		for (int j = 0; j < num; j++)
		{
			List[i][j] = 0;
		}
	}
	for (int i = 0; i<num; i++)         //查页表，看是否缺页
	{
		q = 0;
		while ((pages[i] != mem[q]) && (q != block))
			q++;
		if (q == block)
			flag = '*';                 //缺页，则置标志flag为'*'
		else
			flag = ' ';
		for (int j = q; j>0; j--)
			mem[j] = mem[j - 1];
		mem[0] = pages[i];
		for (int j = 0; j<block; j++)
		{
			List[j][i] = mem[j];
		}
		f[i] = flag;
	}
	cout << "\n----------------LRU-----------------" << endl;
	for (int i = 0; i<block; i++)
	{
		for (int j = 0; j<num; j++)
			cout << List[i][j] << "  ";
		cout << endl;
	}
	for (int i = 0; i<num; i++)
	{
		if (f[i] == '*')
			sum++;
		cout << f[i] << "  ";
	}
	cout << "\n-----------------------------------" << endl;
	cout << "缺页次数:" << sum << '\t' << "缺页率:" << (float)sum / num * 100 << "%" << endl;
	for (int i = 0; i<block; ++i)
		delete[] List[i];
	delete[] List;
}

int main(int argc, char const *argv[]) {
	int num, block;
	cout << "请输入页面数量：";
	cin >> num;
	int *pages = (int *)malloc(num * sizeof(int));
	for (int i = 0; i < num; i++) {
		cin >> pages[i];     
	}
	cout << "请输入空闲内存块数：";
	cin >> block;
	//两种页面调度算法
	FIFO(pages, num, block);  //先入先出 FIFO
	LRU(pages, num, block);   //最近最久未使用 LRU
	delete[] pages;
	pages = NULL;
	cout << endl;
	system("pause");
	return 0;
}