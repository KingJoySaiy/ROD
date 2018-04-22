/*
 * POJ 3723 (最小生成树+并查集)
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

const int maxn=int(2e4+5);
int par[maxn],ran[maxn];
struct edge{

    int from,to,cost;
    edge(int x=0,int y=0,int t=0):from(x),to(y),cost(t){}
};
vector<edge> a;
int n,m,r;

int find(int x){

    return (par[x]==x)?x:(par[x]=find(par[x]));
}
void unite(int x,int y){	//并查集

    x=find(x);
    y=find(y);
    if(x==y) return;
    if(ran[x]<ran[y]) par[x]=y;
    else{
        par[y]=x;
        if(ran[x]==ran[y]) ran[x]++;
    }
}
bool cmp(edge a,edge b){

    return a.cost<b.cost;
}
int kruskal(){

    int res=0;
    sort(a.begin(),a.end(),cmp);
    for(int i=0;i<maxn;i++){    //并查集初始化
        par[i]=i;
        ran[i]=1;
    }
    for(int i=0;i<a.size();i++)
        if(find(a[i].from)!=find(a[i].to)){
            unite(a[i].from,a[i].to);
            res+=a[i].cost;
        }
    return res;
}
int main(){

    int ct,x,y,t;
    cin>>ct;
    while(ct--){
        a.clear();
        cin>>n>>m>>r;
        while(r--){
            scanf("%d%d%d",&x,&y,&t);
            a.push_back(edge(x,n+y,-t));    //对负权求最小生成树
        }
        cout<<10000*(n+m)+kruskal()<<endl;
    }

//    system("pause");
    return 0;
}
