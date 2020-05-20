#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Huffman树的节点类
typedef struct node
{
    char value;               //节点的字符值   
    double weight;               //节点字符出现的频度
    vector<int> code;          //节点字符对应的编码
    struct node *lchild, *rchild;     //节点的左右孩子
}HFMNode,*pHFMNode;

//自定义排序规则，即以vector中node结点weight值升序排序
bool Compare(pHFMNode p,pHFMNode q)
{
    return p->weight<q->weight;
}


//构造Huffman树
void BuildHuffmanTree(vector<pHFMNode> &vctNode)//传入引用
{
    while(vctNode.size()>1)                            //vctNode森林中树个数大于1时循环进行合并
    {
        sort(vctNode.begin(),vctNode.end(),Compare);   //每次依频度对森林中的树进行升序排序

        // for(int i=0;i<vctNode.size();i++){
        //     cout<<"节点"<<vctNode[i]->value<<"频度为"<<vctNode[i]->weight<<endl;
        // }
        // cout<<endl;

        pHFMNode first=vctNode[0];    //取排完序后vctNode森林中频度最小的树根
        pHFMNode second=vctNode[1];   //取排完序后vctNode森林中频度第二小的树根
        pHFMNode merge=new HFMNode;      //合并上面两个树
        merge->weight=first->weight+second->weight;
        merge->lchild=first; //小的放左子树
        merge->rchild=second;//大的放右子树

        vector<pHFMNode>::iterator iter;
        iter=vctNode.erase(vctNode.begin(),vctNode.begin()+2);    //从vctNode森林中删除上诉频度最小的两个节点first和second
        vctNode.push_back(merge);                                 //向vctNode森林中添加合并后的merge树
    }
    //最后只剩下一个节点，即Huffman树的root节点
}



//用回溯法来便利打印编码
void PrintHuffman(pHFMNode node, vector<int> &vctchar)
{
    if(node->lchild==NULL && node->rchild==NULL)
    {//若走到叶子节点，则将当前编码复制到code中，并打印code
        cout<<node->value<<": ";
        node->code.assign(vctchar.begin(),vctchar.end());//复制vctchar到code
        for(vector<int>::iterator iter=node->code.begin();iter!=node->code.end();iter++)
            cout<<*iter;
        cout<<endl;
        return;
    }
    else
    {
        vctchar.push_back(0);     //遇到左子树时给vctchar中加一个1
        PrintHuffman(node->lchild,vctchar);
        vctchar.pop_back();       //回溯，删除刚刚加进去的1
        vctchar.push_back(1);     //遇到左子树时给vctchar中加一个0
        PrintHuffman(node->rchild,vctchar);
        vctchar.pop_back();       //回溯，删除刚刚加进去的0

    }
}

int main()
{
    cout<<"请输入要编码的字符："<<endl;   //字符数量无限制
    vector<pHFMNode> vctNode;        //存放Node结点的vector容器vctNode

    //输入字符
    char ch;                      //临时存放输入的字符
    while((ch=getchar())!='\n')
    {
        if(ch==' ')continue;      //遇到空格时跳过，即每次输入一个字符空一格空格
        pHFMNode temp = new HFMNode;
        temp->value=ch;
        temp->lchild = temp->rchild = NULL;
        vctNode.push_back(temp);  //将新的节点插入到容器vctNode中
    }

    //输入频度
    cout<<endl<<"请输入每个字符对应的频度："<<endl;
    for(int i=0;i<vctNode.size();i++)
        cin>>vctNode[i]->weight;


    BuildHuffmanTree(vctNode);   //构造Huffman树
    vector<int> vctchar; //记录遍历顺序

    cout<<endl<<"对应的Huffman编码如下："<<endl;
    PrintHuffman(vctNode[0],vctchar);

}