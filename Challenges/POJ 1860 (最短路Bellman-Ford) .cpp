/*
 * POJ 1860 (最短路Bellman-Ford)
 */
#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
#include<climits>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

const double inf=(INT_MAX>>1)-10;
const int maxn=105;
double d[maxn],v;
int n,m,s,ct;

struct data{

    int s,e;
    double r,c;
    data(int s,int e,double r,double c):s(s),e(e),r(r),c(c){}
    data(){}
}a[maxn],t;

bool ford(){

    memset(d,0,sizeof(d));
    d[s]=v;
    while(1){
        bool flag=false;
        for(int i=0;i<ct;i++){
            t=a[i];
            if(d[t.e]<(d[t.s]-t.c)*t.r){
                d[t.e]=(d[t.s]-t.c)*t.r;
                flag=true;
            }
        }
        if(d[s]>v) return true;     //回路大于V则YES
        if(!flag) return false;     //无法继续松弛则NO
    }
}
void solve(){

    int x,y;
    double rr,cc;
    while(m--){
        scanf("%d%d%lf%lf",&x,&y,&rr,&cc);
        a[ct++]=data(x,y,rr,cc);
        scanf("%lf%lf",&rr,&cc);
        a[ct++]=data(y,x,rr,cc);
    }
    puts(ford()?"YES":"NO");
}
int main(){

    while(scanf("%d%d%d%lf",&n,&m,&s,&v)!=-1) solve();

//    system("pause");
    return 0;
}
