#include <ctime>
#include <cmath>
#include <iostream>  
#include <algorithm>

using namespace std;

#define INFINITE_DISTANCE 65535    // 无限大作为比较距离
#define COORDINATE_RANGE 100    // 横纵坐标范围为[-100,100]



typedef struct Point
{// 二维坐标上的点Point
    double x;
    double y;
}Point;

double Distance(Point a, Point b)
{//平面上任意两点对之间的距离公式计算
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool compareX(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.x < b.x;
}

bool compareY(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.y < b.y;
}

double ClosestPair(Point pointsByX[], Point pointsByY[],int length, Point &a, Point &b)
{// 求出最近点对记录，并将两点记录再a、b中
    double distance;                   //记录集合points中最近两点距离 
    double d1, d2;                     //记录分割后两个子集中各自最小点对距离
    int i = 0, j = 0, k = 0, x = 0;    //用于控制for循环的循环变量
    Point a1, b1, a2, b2;              //保存分割后两个子集中最小点对

    if (length < 2)
        return INFINITE_DISTANCE;    //若子集长度小于2，定义为最大距离，表示不可达
    else if (length == 2)
    {//若子集长度等于2，直接返回该两点的距离
        a = pointsByX[0];
        b = pointsByX[1];
        distance = Distance(pointsByX[0], pointsByX[1]);
    }
    else
    {//子集长度大于3，进行分治求解
        Point *pts1 = new Point[length];     //开辟两个子集
        Point *pts2 = new Point[length];

        
        double mid = pointsByX[(length - 1) / 2].x;    //排完序后的中间下标值，即中位数

        for (i = 0; i < length / 2; i++)
            pts1[i] = pointsByX[i];
        for (int j = 0, i = length / 2; i < length; i++)
            pts2[j++] = pointsByX[i];

        d1 = ClosestPair(pts1, pointsByY, length / 2, a1, b1);             //分治求解左半部分子集的最近点  
        d2 = ClosestPair(pts2, pointsByY, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点  

        if (d1 < d2) { distance = d1; a = a1; b = b1; }            //记录最近点，最近距离
        else { distance = d2; a = a2; b = b2; }

        // cout<<d1<<" "<<d2<<" "<<distance;
        //merge - 进行子集合解合并
        //求解跨分割线并在δ×2δ区间内的最近点对
        Point *pts3 = new Point[length];

        for (i = 0, k = 0; i < length; i++)                        //从按Y排序的数组中取得中线2δ宽度的所有点对共k个    
            if (abs(pointsByY[i].x - mid) <= distance)
                pts3[k++] = pointsByY[i];

        

        for(int t=0;t<k;t++){
            if((pts3[t].x-mid)>=0){//当前点为右侧点
                x=0;
                for(j=t+1;j<= t+7+x && j<k;j++){
                    if((pts3[j].x-mid)<0){//对应点为左侧
                        if (Distance(pts3[t], pts3[j]) < distance){//如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                                distance = Distance(pts3[t], pts3[j]);
                                a = pts3[t];
                                b = pts3[j];
                        }
                    }
                    else{//同侧则后沿
                        x++;
                    }
                }
            }
            else{//当前点为左侧点
                x=0;
                for(j=t+1;j<= t+7+x && j<k;j++){
                    if((pts3[j].x-mid)>=0){//对应点为右侧
                        if (Distance(pts3[t], pts3[j]) < distance){//如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                                distance = Distance(pts3[t], pts3[j]);
                                a = pts3[t];
                                b = pts3[j];
                        }
                    }
                    else{//同侧
                        x++;
                    }
                }
            }
        }

    }
    return distance;
}

void SetPoints(Point *points, int length)
{//随机函数对点数组points中的二维点进行初始化
    srand(unsigned(time(NULL)));
    for (int i = 0; i < length; i++)
    {
        //生成小数
        // points[i].x = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        // points[i].y = (rand() % int(COORDINATE_RANGE * 200)) / COORDINATE_RANGE - COORDINATE_RANGE;
        
        //生成整数
        points[i].x = rand() % COORDINATE_RANGE;
        points[i].y = rand() % COORDINATE_RANGE;
        // cin>>points[i].x>>points[i].y;
    }
}

int main()
{
    int num;            //随机生成的点对个数
    Point a, b;            //最近点对
    double diatance;    //点对距离

    cout << "请输入二维点对个数:";
    cin >> num;
    if (num < 2)
        cout << "请输入大于等于2的点个数！！" << endl;
    else
    {
        cout << endl << "随机生成的" << num << "个二维点对如下：" << endl;
        Point *points = new Point[num];
        Point *pointsByX = new Point[num];//按X排好
        Point *pointsByY = new Point[num];//按Y排好

        SetPoints(points, num);
        for (int i = 0; i < num; i++)
            cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
        
        sort(points, points + num, compareX);    //调用algorithm库中的sort函数对points进行以X排序
        
        for(int i=0;i<num;i++){
            pointsByX[i]=points[i];
        }

        sort(points, points + num, compareY);             // 以Y排序
        for(int i=0;i<num;i++){
            pointsByY[i]=points[i];
        }

        diatance = ClosestPair(pointsByX, pointsByY, num, a, b);
        cout << endl << endl << "按横坐标排序后的点对:" << endl;
        for (int i = 0; i < num; i++)
            cout << "(" << pointsByX[i].x << "," << pointsByX[i].y << ")" << endl;

        cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
    }
}