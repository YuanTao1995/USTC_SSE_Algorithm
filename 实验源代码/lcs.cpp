#include<iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


//计算最长公共子序列长度，算出b数组和c数组
void LCSLength(string &x, string &y, vector<vector<char> >  &b, vector<vector<int> >  &c) {
    for(int i = 1; i< c.size(); i++) {
        for(int j = 1; j <= c[i].size(); j++) {
            if(x[i-1] == y[j-1]){                         
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j]='*';//left upper
            }
            else {
                if(c[i-1][j] >= c[i][j-1]){
                    c[i][j] = c[i-1][j];
                    b[i][j]='\136';//upper
                }
                else{
                    c[i][j] = c[i][j-1];
                    b[i][j]='\74';//left
                }
            }
        }
    }

}
//问题1：只有一条通路，如果有多个LCS，则无法解决 ->动态规划只能求出一个最优值，并不能求出所有最优值
//问题2：如果去掉b数组，当斜上角比上方小1且当前取斜上角时，会走到上方去. 反例：BCBC和BC
void PrintLCS(vector<vector<char> >  &b, vector<vector<int> >  &c, string &x, int i, int j) {
    if(i == 0 || j == 0)
        return;
    // if(c[i][j] == c[i-1][j])
    //     PrintLCS(b, c, x, i-1, j);
    // else {
    //     if(c[i][j] == c[i][j-1])
    //         PrintLCS(b, c, x, i, j-1);
    //     else {
    //         PrintLCS(b, c, x, i-1, j-1);
    //         cout<<x[i-1];
    //     }
    // }
    //所以加回b数组
    if(b[i][j]=='*'){//left upper
        PrintLCS(b, c, x, i-1, j-1);
        cout<<x[i-1];
    }
    else {
        if(b[i][j]=='\136')//upper
            PrintLCS(b, c, x, i-1, j);
        else//left
            PrintLCS(b, c, x, i, j-1);
    }
}
int main() {
    //无LCS
    // string x="hello";
    // string y="t";

    //有一个LCS
    string x = "ABCBDAB";
    string y = "BDCABA";
    // string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"; 
    // string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

    //有多个LCS，动态规划算法只能算出一个最优解
    // string x = "BCBD";
    // string y = "BDBC";
    cout<<"x字符串为："<<x<<endl<<"y字符串为："<<y<<endl<<endl;
    vector<vector<char> >  b(x.length()+1, vector<char>(y.length()+1, 'T'));     //使用一个b数组
    vector<vector<int> >  c(x.length()+1, vector<int>(y.length()+1, 0) );     //使用一个c数组

    LCSLength(x, y, b, c);

    //打印b数组
    cout<<"b数组如下："<<endl<<"    y ";
    for(int i=0;i<y.length();i++)
        cout<<setw(2)<<y[i]<<" ";
    cout<<endl;
    for(int i=0;i<b.size();i++){
        if(i!=0)
            cout<<setw(2)<<x[i-1]<<" ";
        else
            cout<<" x ";

        for(int j=0;j<b[i].size();j++){
            cout<<setw(2)<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    // 打印c数组
    cout<<"c数组如下："<<endl<<"    y ";
    for(int i=0;i<y.length();i++)
        cout<<setw(2)<<y[i]<<" ";
    cout<<endl;
    for(int i=0;i<c.size();i++){
        if(i!=0)
            cout<<setw(2)<<x[i-1]<<" ";
        else
            cout<<" x ";

        for(int j=0;j<c[i].size();j++){
            cout<<setw(2)<<c[i][j]<<" ";
        }
        cout<<endl;
    }

    //打印最后结果
    cout<<endl<<"最长公共子序列长度为: "<<c[c.size()-1][c[0].size()-1]<<endl<<"对应的序列为:";
    PrintLCS(b, c, x, c.size()-1, c[0].size()-1);
    cout<<endl;

    return 0;
}