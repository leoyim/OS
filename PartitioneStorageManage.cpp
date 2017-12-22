/*********************************
*   程序：分区式存储管理模拟       *
*   作者：闫文博                  *
*********************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef struct {
	int no;         //分区序号
	int pos;        //分区位置
	int size;       //分区大小
	int req[50];    //记录该空闲分区的分区请求
}RAM;

typedef struct {
	int size;       //分区大小
	bool find;     //判断是否已找到空闲分区
}Request;

//输入内存空闲分区序列
void RAMSeq(RAM *ram, int m, RAM *copy)
{
	for (int i = 0; i < m; i++)
	{
		ram[i].no = i+1;
		cin >> ram[i].pos >> ram[i].size;
	}
	for (int i = 0; i < m; i++)
	{
		
		copy[i].pos = ram[i].pos;
		copy[i].size = ram[i].size;
	}
}

//输入请求序列
void ReqSeq(Request *request,int n)
{
	for (int i = 0; i < n; i++)
	{
		cin >> request[i].size;
		request[i].find = 0;
	}
}

//结构体快速排序,从大到小
bool cmp1(RAM a, RAM b) 
{
	return a.size < b.size;
}
bool cmp2(RAM a, RAM b)
{
	return a.size > b.size;
}
bool cmp3(RAM a, RAM b)
{
	return a.no < b.no;
}

//首先适应算法   num 空闲分区数量    n 请求序列数量
void FirstFit(int num, RAM *ram, int n, Request *request, RAM *copy1)
{
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request[j].size <= ram[i].size && !request[j].find)
			{
				ram[i].size -= request[j].size;
				request[j].find = 1;
				ram[i].req[flag] = request[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	cout << "-------------Answer--------------" << endl;
	cout <<"No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram[i].no << '\t' << (ram[i].pos + copy1[i].size - ram[i].size) << '\t' << ram[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram[i].req[j] > 0) 
			{
				cout << ram[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request[j].find)
		{
			cout << "Not satisfied：" << request[j].size << " ";
		}
	}
	cout << endl;
}

//最佳适应算法
void BestFit(int num, RAM *ram1, int n, Request *request1, RAM *copy2)
{
	sort(ram1, ram1 + num, cmp1);
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request1[j].size <= ram1[i].size && !request1[j].find)
			{
				ram1[i].size -= request1[j].size;
				request1[j].find = 1;
				ram1[i].req[flag] = request1[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	sort(ram1, ram1 + num, cmp3);
	cout << "-------------Answer--------------" << endl;
	cout << "No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram1[i].no << '\t' << (ram1[i].pos + copy2[i].size - ram1[i].size) << '\t' << ram1[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram1[i].req[j] > 0)
			{
				cout << ram1[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request1[j].find)
		{
			cout << "Not satisfied：" << request1[j].size << " ";
		}
	}
	cout << endl;
}

//最坏适应算法
void WorstFit(int num, RAM *ram2, int n, Request *request2, RAM *copy3)
{
	sort(ram2, ram2 + num, cmp2);
	int flag;
	for (int i = 0; i < num; i++)
	{
		flag = 0;
		for (int j = 0; j < n;)
		{
			if (request2[j].size <= ram2[i].size && !request2[j].find)
			{
				ram2[i].size -= request2[j].size;
				request2[j].find = 1;
				ram2[i].req[flag] = request2[j].size;
				flag++;
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	sort(ram2, ram2 + num, cmp3);
	cout << "-------------Answer--------------" << endl;
	cout << "No." << '\t' << "begin" << '\t' << "free" << '\t' << "result" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << ram2[i].no << '\t' << (ram2[i].pos + copy3[i].size-ram2[i].size) << '\t' << ram2[i].size << '\t';
		for (int j = 0; j < n; j++)
		{
			if (ram2[i].req[j] > 0)
			{
				cout << ram2[i].req[j] << ' ';
			}
		}
		cout << endl;
	}
	for (int j = 0; j < n; j++)
	{
		if (!request2[j].find)
		{
			cout << "Not satisfied：" << request2[j].size << " ";
		}
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	int num1, num2, num3, n1, n2, n3;    //num1 num2 num3空闲分区数量   n1 n2 n3分区请求序列数量
	//三种分区存储管理算法
	//------------------------------------------
	cout << "--------------首次适应算法--------------" << endl;
	cout << "输入内存空闲分区数量: ";
	cin >> num1;
	RAM *ram = (RAM *)malloc(num1 * sizeof(RAM));
	RAM *copy1 = (RAM *)malloc(num1 * sizeof(RAM));
	cout << "输入内存空闲分区序列：" << endl;
	//空闲分区位置 | 空闲分区大小
	RAMSeq(ram, num1,copy1);
	cout << "输入请求序列数量: ";
	cin >> n1;
	Request *request = (Request *)malloc(n1 * sizeof(Request));
	cout << "输入分区请求序列：" << endl;
	//输入请求序列 | 
	ReqSeq(request, n1);
	FirstFit(num1, ram, n1, request,copy1);   //首次适应算法
	//-----------------------------------------
	cout << endl << "--------------最佳适应算法--------------" << endl;
	cout << "输入内存空闲分区数量: ";
	cin >> num2;
	RAM *ram1 = (RAM *)malloc(num2 * sizeof(RAM));
	RAM *copy2 = (RAM *)malloc(num1 * sizeof(RAM));
	cout << "输入内存空闲分区序列：" << endl;
	//空闲分区位置 | 空闲分区大小
	RAMSeq(ram1, num2,copy2);
	cout << "输入请求序列数量: ";
	cin >> n2;
	Request *request2 = (Request *)malloc(n2 * sizeof(Request));
	cout << "输入分区请求序列：" << endl;
	//输入请求序列 | 
	ReqSeq(request2, n2);
	BestFit(num2, ram1, n2, request2,copy2);    //最佳适应算法
	//-----------------------------------------
	cout << endl << "--------------最坏适应算法--------------" << endl;
	cout << "输入内存空闲分区数量: ";
	cin >> num3;
	RAM *ram2 = (RAM *)malloc(num3 * sizeof(RAM));
	RAM *copy3 = (RAM *)malloc(num3 * sizeof(RAM));
	cout << "输入内存空闲分区序列：" << endl;
	//空闲分区位置 | 空闲分区大小
	RAMSeq(ram2, num3, copy3);
	cout << "输入请求序列数量: ";
	cin >> n3;
	Request *request3 = (Request *)malloc(n3 * sizeof(Request));
	cout << "输入分区请求序列：" << endl;
	//输入请求序列 | 
	ReqSeq(request3, n3);
	WorstFit(num3, ram2, n3, request3, copy3);   //最坏适应算法
	//-----------------------------------------
	delete[] ram;      //释放动态数组
	ram = NULL;
	delete[] request;  //释放动态数组
	request = NULL;
	system("pause");
	return 0;
}