#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
using namespace std;

//节点
typedef struct node{
	struct node *left,*right,*p;
	int max,high,low;
	string color;
}inNode,*pinNode;
//树
typedef struct nodeTree{
	pinNode root,NIL;
}inTree,*pinTree;

// 左旋
void left_rotate(pinTree T,pinNode t)
{
	pinNode y= t->right;
	t->right=y->left;
	if(y->left!=T->NIL)
	{
		y->left->p=t;
	}
	y->p=t->p;
	if(t->p==T->NIL)
	{
		T->root=y;
	}
	else if(t==t->p->left)
	{
		t->p->left=y;
	}
	else t->p->right=y;
	y->left=t;
	t->p=y;
}

//右旋
void right_rotate(pinTree T,pinNode t)
{
	pinNode y=t->left;
	t->left=y->right;
	if(y->right!=T->NIL)
	{
		y->right->p=t;
	}
	y->p=t->p;
	if(t->p==T->NIL)
	{
		T->root=y;
	}
	else if(t==t->p->left)
	{
		t->p->left=y;
	}
	else t->p->right=y;
	y->right=t;
	t->p=y;
}

//插入调整
void RB_Insert_Fixup(pinTree T,pinNode z)
{
	while(z->p->color=="RED")
	{
		if(z->p==z->p->p->left)
		{
			pinNode y=z->p->p->right;
			if(y->color=="RED")
			{
				z->p->color="BLACK";
				y->color="BLACK";
				z->p->p->color="RED";
				z=z->p->p;
			}
			else
			{
				if(z==z->p->right)
				{
					z=z->p;
					left_rotate(T,z);
				}
				z->p->color="BLACK";
				z->p->p->color="RED";
				right_rotate(T,z->p->p);
			} 
		}
		else
		{
			pinNode y=z->p->p->left;
			if(y->color=="RED")
			{
				z->p->color="BLACK";
				y->color="BLACK";
				z->p->p->color="RED";
				z=z->p->p;
			}
			else {
			if(z==z->p->left)
			{
				z=z->p;
				right_rotate(T,z);
			}
			z->p->color="BLACK";
			z->p->p->color="RED";
			left_rotate(T,z->p->p);
		}
		}
	}
	T->root->color="BLACK";
}

//插入算法
void RB_Insert(pinTree T,pinNode z)
{
	pinNode y=T->NIL;
	pinNode x=T->root;
	while(x!=T->NIL)
	{
		y=x;
		if(z->low<x->low)
			x=x->left;
		else x=x->right;
	}
	z->p=y;
	if(y==T->NIL)
	{
		T->root=z;
	}	
	else if(z->low<y->low)
	{
		y->left=z;
	}
		
	else 
	{
		y->right=z;	
	}
	z->left=T->NIL;
	z->right=T->NIL;
	z->color="RED";
	RB_Insert_Fixup(T,z);
}



//后序遍历更新max
int afterOrderWalk (pinTree T, pinNode t)
{
    if (t == T->NIL){
        return 0;
    }
    afterOrderWalk (T, t->left);//左子树递归

    afterOrderWalk (T, t->right);//右子树递归
	if(t->left==T->NIL&&t->right==T->NIL)//左右子树都为nil
	{
		t->max=t->high;
	}
	else if(t->left==T->NIL)//左子树为nil
	{
		t->max=(t->high>t->right->high)?t->high:t->right->high;
	}
	else if(t->right==T->NIL)//右子树为nil
	{
		t->max=(t->high>t->left->high)?t->high:t->left->high;
	}
	else//左右子树都不为nil
	{
		int tem=(t->right->high>t->left->high)?t->right->high:t->left->high;
		t->max=(t->high>tem)?t->high:tem;
	}
    return 0;
}


//中序遍历
int inOrderWalk (pinTree T, pinNode t)
{
    if (t == T->NIL){
		cout<<"nil"; 
        return 0;
    }
    cout<<'(';
    inOrderWalk (T, t->left);
    cout<<')';
	cout<<" ["<<t->low<<","<<t->high<<","<<t->max<<"] ";
    if (t->color == "BLACK")
        cout<<"B ";
    else
        cout<<"R ";

	cout<<'(';
    inOrderWalk (T, t->right);
    cout<<')';
    return 0;
}


//红黑树的初始化
int initRB (pinTree T)
{
    if (T == NULL)
        return 0;
    T->NIL = new inNode;
    T->NIL->color = "BLACK";
    T->root = T->NIL;
    return 0;
}

//区间树的查找
void interval_search(pinTree T,int low,int high)
{
	pinNode x=T->root;
	while(x!=T->NIL && (high<x->low || low>x->high))
	{
		if(x->left!=T->NIL && x->left->max >= low)
			x=x->left;
		else x=x->right;
	}
	if(x!=T->NIL)
		cout<<"查找成功：["<<x->low<<","<<x->high<<"]"<<endl;
	else cout<<"查找失败！"<<endl;
}


int main()
{
	pinTree T=new inTree;
	int n;
	cout<<"请输入红黑树的规模：";
	cin>>n;
	initRB(T); 
	srand(time(0));
	for(int i=0;i<n;++i)
	{
		//随机生成正确的区间并插入区间树
		pinNode t=new inNode;
		t->low=rand()%100;
		int tem=rand()%100;
		while(tem<t->low) tem=rand()%100;
		t->high=tem;
		cout<<i<<")将["<<t->low<<","<<t->high<<"]插入区间树："<<endl;
		RB_Insert(T,t);
		afterOrderWalk(T,T->root);
		inOrderWalk(T,T->root);
		cout<<endl<<endl;
	}
	cout<<"区间树插入完毕！"<<endl;
	//查找输入正确的区间
	int low,high;
	cout<<endl<<"请输入查找区间的low:";
	cin>>low;
	cout<<"请输入查找区间的high:";
	cin>>high;
	while(low>high)
	{
		cout<<"输入有误，请重新输入(保证low<=high)"<<endl;
		cout<<endl<<"请输入查找区间的low:";
		cin>>low;
		cout<<"请输入查找区间的high:";
		cin>>high;
	}
	interval_search(T,low,high);
	return 0;
}





