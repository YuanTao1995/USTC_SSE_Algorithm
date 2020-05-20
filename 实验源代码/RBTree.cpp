#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef struct node{
	struct node *left,*right,*p;
	int key;
	string color;
}RBNode,*pRBNode;

typedef struct nodeTree{
	pRBNode root,NIL;
}RBTree,*pRBTree;

void left_rotate(pRBTree T,pRBNode t)
{//change not only itself but also its parent node, this's a double direction.
	pRBNode y= t->right;//step1 find the right child node as y
	t->right=y->left;//2 give y's left child node to t's right child
	if(y->left!=T->NIL)
	{
		y->left->p=t; 
	}
	y->p=t->p;//3 let y as the key
	if(t->p==T->NIL)//if x is root
	{
		T->root=y;
	}
	else if(t==t->p->left)//t is t's parent's left child
	{
		t->p->left=y;
	}
	else t->p->right=y;//right child 
	y->left=t;//4 let x as y's left child
	t->p=y;
}
void right_rotate(pRBTree T,pRBNode t)
{
	pRBNode y=t->left;
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
void RB_Insert_Fixup(pRBTree T,pRBNode z)
{
	while(z->p->color=="RED")
	{
		if(z->p==z->p->p->left)
		{
			pRBNode y=z->p->p->right;
			if(y->color=="RED")
			{
				z->p->color="BLACK";
				y->color="BLACK";
				z->p->p->color="RED";
				z=z->p->p;
				//cout<<z->key<<"!"<<endl;
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
			pRBNode y=z->p->p->left;
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
	//cout<<z->key<<"???"<<endl;
	T->root->color="BLACK";
	//cout<<T->root->key<<"!"<<endl;
}
void RB_Insert(pRBTree T,pRBNode z)
{
	pRBNode y=T->NIL;
	pRBNode x=T->root;
	while(x!=T->NIL)
	{
		//cout<<"???"<<endl;
		y=x;
		//cout<<x->key<<"?"<<endl;
		if(z->key<x->key)
			x=x->left;
		else x=x->right;
	}
	z->p=y;
	if(y==T->NIL)
	{
		T->root=z;
	}	
	else if(z->key<y->key)
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
	//cout<<T->root->key<<"?"<<endl;
	RB_Insert_Fixup(T,z);
}




int inOrderWalk (pRBTree T, pRBNode t)
{//
    if (t == T->NIL){
		cout<<"nil"; 
        return 0;
    }
    cout<<'(';
    inOrderWalk (T, t->left);
    cout<<')';
	cout<<" "<<t->key;
    if (t->color == "BLACK")
        cout<<"B ";
    else
        cout<<"R ";

	cout<<'(';
    inOrderWalk (T, t->right);
    cout<<')';
    return 0;
}





int initRB (pRBTree T)
{//初始化红黑树
    if (T == NULL)
        return 0;
    T->NIL = new RBNode;
    T->NIL->color = "BLACK";
    T->root = T->NIL;
    return 0;
}//initRB




int main()
{
	pRBTree T=new RBTree;
	int n;
	cout<<"请输入红黑树的规模：";
	cin>>n;
	initRB(T); 
	srand(time(0));
	for(int i=0;i<n;++i)
	{
		int tmp=rand()%100;
		cout<<i<<") 将"<<tmp<<"插入红黑树："<<endl;
		pRBNode t=new RBNode;
		t->key=tmp;
		//cin>>t->key;
		RB_Insert(T,t);	
		inOrderWalk(T,T->root);
		cout<<endl<<endl;
		//cout<<endl;
	}	
	cout<<"插入完毕！"<<endl;
	return 0;
}


