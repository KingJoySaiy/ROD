/*
 * @模板题
 * POJ 1127 （计算几何+并查集）
 * 题目大意：给定若干线段的两端点坐标，判断两线段是否相交或间接相交。
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#define x first
#define y second
using namespace std;

const double eps=1e-10;
const int maxn=15;
int n,par[maxn],ran[maxn];//记录并查集的祖先和深度

struct line{

    pair<int,int> l;
    pair<int,int> r;

};
int find(int xx){//找出xx的祖先

    return par[xx]==xx?xx:par[xx]=find(par[xx]);
}
void unite(int a,int b){//若a和b高度相同，则b接到a下

    a=find(a);
    b=find(b);
    if(a==b) return;
    if(ran[a]<ran[b]) par[a]=b;
    else{
        par[b]=a;
        if(ran[a]==ran[b]) ran[a]++;
    }
}
bool check(line xx,line yy){    //判断两线段是否相交

    pair<int,int> a=xx.l,b=xx.r,c=yy.l,d=yy.r;
    int e,f,g,h;

    //快速排斥实验
    if(min(a.x,b.x)>max(c.x,d.x)||min(a.y,b.y)>max(c.y,d.y)||
       min(c.x,d.x)>max(a.x,b.x)||min(c.y,d.y)>max(a.y,b.y)) return false;

    //跨立实验
    e=(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
    f=(b.x-a.x)*(d.y-a.y)-(b.y-a.y)*(d.x-a.x);
    g=(d.x-c.x)*(a.y-c.y)-(d.y-c.y)*(a.x-c.x);
    h=(d.x-c.x)*(b.y-c.y)-(d.y-c.y)*(b.x-c.x);
    return e*f<=eps&&g*h<=eps;
}
int main(){

    while(cin>>n,n){
        for(int i=1;i<=n;i++){  //初始化并查集
            par[i]=i;
            ran[i]=1;
        }
        line a[n+1];        //读入每条线段的两端点坐标
        for(int i=1;i<=n;i++)
            cin>>a[i].l.x>>a[i].l.y>>a[i].r.x>>a[i].r.y;

        for(int i=1;i<n;i++)//根据关系生成树
            for(int j=i+1;j<=n;j++)
                if(check(a[i],a[j])) unite(i,j);

        int p,q;    //查询线段间的关系
        while(cin>>p>>q,p||q){
            puts((find(p)==find(q))?"CONNECTED":"NOT CONNECTED");
        }
    }
    return 0;
}

