//深度为N的K叉树，回溯剪枝
#include <iostream>
#include <vector>
#include<cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//计算当前最长时间,para为-1默认则输出最长时间，为下标索引则返回machineTime[para]
int calMax(const int &n, const int &k, vector<int> &taskTime, vector<int> &schedule, int para=-1)
{
	vector<int> machineTime(k);//机器i需要运行的时间
	for(int i=0;i<n;i++){
		if(schedule[i]!=-1)//已分配
			machineTime[schedule[i]]+=taskTime[i];
	}
	// cout<<endl;
	// for(auto i:machineTime){
	// 	cout<<i<<" ";
	// }
	// cout<<endl;
	int max = machineTime[0];
	for(int i=1;i<k;i++){
		if(machineTime[i]>max)max=machineTime[i];
	}

	if(para==-1)
		return max;
	else
		return machineTime[para];
}


//递归回溯+剪枝解决最佳调度
void BestSchedule(int deep,const int &n,const int &k, vector<int> &taskTime, vector<int> &schedule, vector<int> &best, int &bestTime,vector<vector<int> > &machine,vector<vector<int> > &bestMachine, vector<int> &index)
{
	
	if(deep==n){//递归出口
		int tmp=calMax(n,k,taskTime,schedule);//本趟最优解
		if(tmp<bestTime){//如果是更优化的解，则
			//更新bestTime
			bestTime=tmp;
			//更新best数组
			for(int i=0;i<n;i++){
				best[i]=schedule[i];
			}
			//更新bestMachine队列数组
			for(int i=0;i<k;i++){
				for(int j=0;j<n;j++){
					bestMachine[i][j]=machine[i][j];
					//cout<<bestMachine[i][j]<<" ";
				}
				//cout<<endl;
			}


			cout<<"----更新bestTime和best:"<<bestTime<<"------"<<endl;
		}
	}
	else{
		for(int i = 0; i < k; i++ ){//当前i指代机器
				schedule[deep]=i; //当前任务deep分配给机器i
				//想建一个机器队列，bug有点多
				machine[i][++index[i]]=deep;

				//输出schedule数组
				cout<<setw(2)<<deep<<" "<<setw(2)<<i<<"|";
				for(auto t:schedule){
					cout<<setw(2)<<t<<" ";
				}
				cout<<"|";
				// for(auto t:index){
				// 		cout<<setw(2)<<t<<" ";
				// }
				// cout<<"|";
				// for(int p=0;p<k;p++){
				// 	for(int q=0;q<n;q++)
				// 		cout<<machine[p][q]<<" ";
				// 	cout<<endl;
				// }
				cout<<endl;

				if(calMax(n,k,taskTime,schedule)<bestTime)//剪枝
					BestSchedule(deep+1,n,k,taskTime,schedule,best,bestTime,machine,bestMachine,index);//递归节点
				else{
					cout<<"       被剪枝！"<<endl;
				}
				
				machine[i][index[i]--]=-1;
				schedule[deep]=-1;//回溯

				//输出schedule数组
				cout<<"     |";
				for(auto t:schedule){
					cout<<setw(2)<<t<<" ";
				}
				cout<<"|";
				// for(auto t:index){
				// 		cout<<setw(2)<<t<<" ";
				// }
				// cout<<"|";
				// for(int p=0;p<k;p++){
				// 	for(int q=0;q<n;q++)
				// 		cout<<machine[p][q]<<" ";
				// 	cout<<endl;
				// }
				cout<<endl;
		}
		
	}

}


int main(int argc, char const *argv[])
{
	//输入任务规模和机器规模
	int n,k;
	cout<<"请输入任务数目N= ";
	cin>>n;
	cout<<"请输入并行机器数目K= ";
	cin>>k;

	//相关数据结构
	vector<int> taskTime(n);//任务时间
	vector<int> schedule(n,-1);//当前调度方案数组
	vector<int> best(n,-1);//最佳调度方案数据
	int bestTime=0;//最佳时间
	vector<vector<int> > machine(k,vector<int>(n,-1));//当前机器的任务队列数组
	vector<vector<int> > bestMachine(k,vector<int>(n,-1));//最佳调度时的机器的任务队列数组
	vector<int> index(k,-1); //用于记录当前各个机器的任务队列的下标

	
	//随机产生任务时间并打印
	srand(time(0));
	cout<<endl<<"初始任务时间表："<<endl;
	for(int i=0;i<n;i++){
		int tmp=rand()%10;
		while(tmp==0){
			tmp=rand()%10;
		}
		//时间不能等于0
		taskTime[i]=tmp;
		bestTime+=taskTime[i];//所有任务时间之和用于初始比较
		cout<<"Task"<<i<<": "<<taskTime[i]<<endl;
	}
	cout<<endl;


	//调度算法
	cout<<"初始bestTime上界: "<<bestTime<<endl;
	cout<<endl<<"递归回溯过程如下"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<" d  i| schedule|"<<endl;
	cout<<"------------------------------"<<endl;

	
	BestSchedule(0,n,k,taskTime,schedule,best,bestTime,machine,bestMachine,index);

	
	//输出任务最佳调度序列、机器的完成任务情况和最佳时间
	cout<<endl<<endl<<"------最佳调度序列为----"<<endl;
	for(int i=0; i<n; i++){
		cout<<"Task "<<i<<" -> "<<"Machine "<<best[i]/*<<" TaskTime: "<<taskTime[i]*/<<endl;
	}

	cout<<endl<<endl<<"------最佳调度时各机器的任务队列-------"<<endl;
	for(auto i=0; i<k;i++){
		cout<<"机器 "<<i<<": ";
		for(auto j=0;j<n;j++)
			if(bestMachine[i][j]!=-1)
				cout<<"Task "<<bestMachine[i][j]<<" ";
		cout<<"      ---需要执行时间："<<calMax(n,k,taskTime,best,i)<<endl;
	}

	cout<<endl<<"综上得bestTime: "<<bestTime<<endl<<endl;
	
	return 0;
}