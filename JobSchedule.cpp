/*********************************
*   程序：作业调度算法模拟         *
*   作者：闫文博                  *
*********************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef struct {
	char no;                       //作业序号
	int arrive;                    //到达时间
	int run;                       //运行时间
	int start;                     //开始执行时间
	int end;                       //完成时间
	int turnover;                  //周转时间
	float withweightturnover;      //带权周转时间
	int wait;                      //等待时间
}JOBS;

//结构体快速排序
bool cmp(JOBS a, JOBS b)
{
	return a.arrive < b.arrive;
}

//输入作业序列
void JobSeq(JOBS *jobs, int n)
{
	cout << "输入作业序列："<<endl;
	for (int i = 0; i < n; i++)
	{
		cin >> jobs[i].no >> jobs[i].arrive >> jobs[i].run;
	}
}

//先来先服务调度算法
int FCFS(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs + n, cmp);
	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n--------先来先服务调度算法---------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout <<"No."<<(i+1)<<"  序号："<<jobs[i].no<< "  开始时间: " << jobs[i].start << "\t分" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "平均周转时间：" << avgturnover << endl;
	cout << "平均带权周转时间：" << avgwithweightturnover << endl;
	return 0;
}

//短作业优先调度算法
int SJF(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs+n, cmp);
	for (int i = 0; i<n - 1; i++)
	{
		int k = 0;
		if (i == 0)
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		else
			jobs[i].end = jobs[i].arrive + jobs[i - 1].end;
		for (int j = i + 1; j<n; j++)
		{
			if (jobs[j].arrive <= jobs[i].end)
				k++;
		}
		double minstime = jobs[i + 1].run;
		int flag = i + 1;
		for (int m = i + 1; m<i + k; m++)
		{
			if (jobs[m + 1].run <minstime)
			{
				minstime = jobs[m + 1].run;
				flag = m + 1;
			}
		}
		JOBS temp;
		temp = jobs[i + 1];
		jobs[i + 1] = jobs[flag];
		jobs[flag] = temp;
	}

	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n--------短作业优先调度算法--------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "No." << (i + 1) << "  序号：" << jobs[i].no << "  开始时间: " << jobs[i].start << "\t分" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "平均周转时间：" << avgturnover << endl;
	cout << "平均带权周转时间：" << avgwithweightturnover << endl;
	return 0;
}

//最高响应比优先调度算法
int HRN(JOBS *jobs, int n)
{
	double sumturnover, sumwithweightturnover, avgturnover, avgwithweightturnover;
	sort(jobs, jobs + n, cmp);
	for (int i = 0; i<n - 1; i++)
	{
		int k = 0;
		if (i == 0)
			jobs[i].end = jobs[i].arrive + jobs[i].run;

		else
			jobs[i].end = (jobs[i].run + jobs[i - 1].end);
		for (int j = i + 1; j<n; j++)
		{
			if (jobs[j].arrive <= jobs[i].end)
				k++;
		}
		double maxrratio = (jobs[i].end - jobs[i + 1].arrive) / (1.0*jobs[i + 1].run);
		int flag = i + 1;
		for (int m = i + 1; m<i + k; m++)
		{
			if ((jobs[i].end - jobs[m + 1].arrive) / jobs[m + 1].run >= maxrratio)
			{
				maxrratio = (jobs[i].end - jobs[m + 1].arrive) / (1.0*jobs[m + 1].run);
				flag = m + 1;
			}
		}
		JOBS temp;
		temp = jobs[i + 1];
		jobs[i + 1] = jobs[flag];
		jobs[flag] = temp;
	}
	sumturnover = sumwithweightturnover = 0;
	jobs[0].start = jobs[0].arrive;
	jobs[0].end = jobs[0].arrive + jobs[0].run;
	for (int i = 1; i<n; i++)
	{
		if (jobs[i - 1].end>jobs[i].arrive)
		{
			jobs[i].start = jobs[i - 1].end;
			jobs[i].end = jobs[i - 1].end + jobs[i].run;
		}
		else
		{
			jobs[i].start = jobs[i].arrive;
			jobs[i].end = jobs[i].arrive + jobs[i].run;
		}
	}
	for (int j = 0; j<n; j++)
	{
		jobs[j].turnover = jobs[j].end - jobs[j].arrive;
		jobs[j].withweightturnover = jobs[j].turnover*1.0 / jobs[j].run*1.0;
		sumturnover += jobs[j].turnover;
		sumwithweightturnover += jobs[j].withweightturnover;
	}
	avgturnover = sumturnover / n;
	avgwithweightturnover = sumwithweightturnover / n;
	cout << "\n------最高响应比优先调度算法------\n" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "No." << (i + 1) << "  序号：" << jobs[i].no << "  开始时间: " << jobs[i].start << "\t分" << endl;
	}
	cout << "----------------------------------" << endl;
	cout << "平均周转时间：" << avgturnover << endl;
	cout << "平均带权周转时间：" << avgwithweightturnover << endl;
	return 0;
}


int main(int argc, char const *argv[])
{
	int num; 
	cout << "输入待执行作业数: ";
	cin >> num;
	JOBS *jobs = (JOBS *)malloc(num * sizeof(JOBS));
	//作业号 | 作业进入系统的时间 | 估计执行时间
	JobSeq(jobs, num);
	//三种作业调度算法
	FCFS(jobs, num);   //执行FCFS作业调度算法
	SJF(jobs, num);    //执行短作业优先作业调度算法
	HRN(jobs, num);    //执行最高响应比优先作业调度算法
	delete[] jobs;     //释放动态数组
	jobs = NULL;
	system("pause");
	return 0;
}
