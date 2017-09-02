/*
 * POJ 1007（最近点对+分治）
 * 题目大意：给定若干点，最小两点距离。
 */
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;

class point{
public:
    double x,y;
    bool operator<(const point &t)const{
        if(x==t.x) return y<t.y;
        return x<t.x;
    }
    double dist(point t){
        return sqrt((x-t.x)*(x-t.x)+(y-t.y)*(y-t.y));
    }
}a[maxn],tt[maxn];

bool cmp(point a,point b){

    return a.y<b.y;
}
double work(int left,int right){

    double res=INT_MAX;
    if(left==right) return res;
    if(left+1==right) return a[left].dist(a[right]);

    int mid=(left+right)>>1;    //分治，递归实现
    res=min(work(left,mid),work(mid+1,right));

    int ct=0;
    for(int i=left;i<=right;i++)
        if(fabs(a[mid].x-a[i].x)<res) tt[ct++]=a[i];
    sort(tt,tt+ct,cmp);     //筛选优化，缩小枚举范围

    for(int i=0;i<ct;i++)
        for(int j=i+1;j<ct&&tt[j].y-tt[i].y<res;j++)
            res=min(res,tt[i].dist(tt[j]));

    return res;
}
int main() {

    int n;
    while(scanf("%d",&n)!=EOF&&n){
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        sort(a,a+n);
        printf("%.2lf\n",work(0,n-1)/2);
    }

    return 0;
}

