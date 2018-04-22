/*
 * UVAlive 4043 (极角+分治)
 * 题目大意：给定n个白点和n个黑点的坐标，求出每个白点对应黑点的编号，使所有配对的黑白点构成的线段不相交。
 */
#include<bits/stdc++.h>
#define ang(a,b) atan2(a.y-b.y,a.x-b.x) //方位角
#define x first
#define y second
using namespace std;
typedef pair<int,int> point;

const int maxn=105;
int res[maxn<<1],n;
struct node{
    point po;
    double ang;
    int id;
    bool operator<(const node &t){
        return ang<t.ang;
    }
    int check(){
        return id<n?1:-1;   //赋予权值，当黑白个数相等时，权值和为0
    }
}a[maxn<<1];

bool cmp(node a,node b){

    return a.po.y<b.po.y||a.po.y==b.po.y&&a.po.x<b.po.x;
}
void work(int l,int r){

    if(l+1>r) return;
    swap(a[l],a[min_element(a+l,a+r,cmp)-a]);   //找出基点，与l交换
    for(int i=l+1;i<r;i++)
        a[i].ang=ang(a[i].po,a[l].po);
    sort(a+l+1,a+r);    //按极角升序排序

    for(int i=l+1,ct=a[l].check();i<r;i++){
        ct+=a[i].check();
        if(!ct){
            res[a[l].id]=a[i].id;   //双向赋予id，因为不知道哪个是白点
            res[a[i].id]=a[l].id;
            work(l+1,i);    //分治
            work(i+1,r);
            return;
        }
    }
}
int main(){

    while(cin>>n){
        for(int i=0;i<2*n;i++){ //0~n-1白点，n~2n-1黑点
            scanf("%d%d",&a[i].po.x,&a[i].po.y);
            a[i].id=i;
        }
        work(0,n<<1);
        for(int i=0;i<n;i++) cout<<res[i]-n+1<<endl;
    }

//    system("pause");
    return 0;
}
/*
5
-42  58
44  86
7  28
99  34
-13  -59
-47  -44
86  74
68  -75
-68  60
99  -60
 */
