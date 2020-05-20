#include<iostream>
#include<queue>
using namespace std;
#define INFINITY 2147483647

typedef struct node {//邻接结点
	int key;
	struct node *next;
}vertexNode,*pvertexNode;

typedef struct Gnode {//图结点
	string color;
	int d;
	int key;
	pvertexNode next; 
}GNode,*pGNode;

void bfs(pGNode G, int s, int n)
{
	for (int i = 0;i < n;++i)
	{
		if (i == s) continue;
		G[i].color = "white";
		G[i].d = INFINITY;
	}
	G[s].color = "gray";
	G[s].d = 0;
	queue<GNode>Q;
	Q.push(G[s]);
	int flag = 0;
	while (!Q.empty())
	{
		flag++;
		GNode u = Q.front();
		Q.pop();
		pvertexNode v = u.next;
		while (v != NULL)
		{
			if (G[v->key].color == "white")
			{
				G[v->key].color = "gray";
				G[v->key].d = u.d + 1;
				Q.push(G[v->key]);
			}

			v = v->next;
		}
		u.color = "black";
		cout <<"第"<<flag<<"个遍历的结点为："<< u.key << " 源结点s到结点v距离：" << u.d << endl;
	}
}
int main()
{
	int n, m, s;//n个结点 m条路径 s为源结点
	cout << "请输入结点个数：";
	cin >> n;
	cout << "请输入边数：";
	cin >> m;
	pGNode G = new GNode[n];
	int p, q;
	for (int i = 0;i < n;++i)
	{//初始化n个结点
		G[i].key = i;
		G[i].next = NULL;
	}
	for (int i = 0;i < m;++i)
	{//处理m条路径
		cout << "第" << i + 1 << "条边：";
		cin >> p >> q;//q与q间有路径
		pvertexNode u = new vertexNode;//p
		pvertexNode v = new vertexNode;//q
		u->key = p;
		u->next = NULL;
		v->key = q;
		v->next = NULL;
		u->next = G[q].next;
		G[q].next = u;
		v->next = G[p].next;
		G[p].next = v;
	}
	cout << "请输入源结点：";
	cin >> s;
	cout << endl;
	bfs(G, s, n);
	delete[]G;
	return 0;
}
