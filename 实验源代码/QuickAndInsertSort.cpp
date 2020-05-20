#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
//插入排序
void InsertSort(vector<int> &v){
	for(auto i=1;i<v.size();i++){
		int key=v[i];
		int j =  i-1;
		while(j>=0&&v[j]>key){
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=key;
	}
}
//以枢轴为中心划分
unsigned int partion(vector<int> &v, unsigned int p,unsigned int r){
	
	int pivot = v[p];
	while(p<r){
		while((p<r) && (pivot <= v[r]) )//从后往前寻找
			r--;
		v[p]=v[r];
		while( (p<r) && (v[p]<=pivot ) )//从前往后寻找
			p++;
		v[r]=v[p];
	}
	v[p]=pivot;
	return p;	
}
void QuickSort(vector<int> &v,unsigned int p, unsigned int r , unsigned int k){
	if((p<r)&&(r-p+1>k)){      //子数组小于k时则直接返回
		auto q = partion(v,p,r);
		QuickSort(v,p,q-1,k);
		QuickSort(v,q+1,r,k);
	}

}

int main()
{
	srand(time(0));//设置种子
	int n;
	cout<<"请输入n值："<<endl;
	cin>>n;
	int k;
	cout<<"请输入k值："<<endl;
	cin>>k;

	vector<int> v;
	for(auto i=0;i<n;i++){
		v.push_back(rand()%1000);//插入随机值
	}

	for(int t=1;t<1000;t++){
		vector<int > v1=v;
		// cout<<"之前数组：";
		// for(auto j: v)
		// 	cout<<j<<" ";
		// cout<<endl;

		int start_time=clock();
		//cout<<"开始时间："<<start_time<<endl;

		QuickSort(v1,0,v1.size()-1,t);
		// for(auto j: v)
		// 	cout<<j<<" ";
		// cout<<endl;

		InsertSort(v1);
		// cout<<"排序之后数组";
		// for(auto j: v)
		// 	cout<<j<<" ";
		// cout<<endl;
		
		int end_time=clock();
		//cout<<"结束时间："<<start_time<<endl;

		//运行时间
		cout<<t<<"时运行时间："<<end_time-start_time<<endl;
	}
	return 0;
}


//n取1000
//k 
//1 2 3 4 5 6 7 8 9 10 11 12 13 14
//1510 1286 1821 1217 1806 