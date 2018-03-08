/*
 * POJ 3268 (最短路)
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
using namespace std;

const int inf=(INT_MAX>>1)-10;
const int maxn=1005;
int cost[maxn][maxn],d[maxn];
int n,m,to;
bool book[maxn];
vector<int> res(1);

void ini(){

    for(int i=0;i<maxn;i++){
        fill(cost[i],cost[i]+maxn,inf);
        cost[i][i]=0;
    }
    int x,y,t;
    scanf("%d%d%d",&n,&m,&to);
    for(int x,y,t;m--;){
        scanf("%d%d%d",&x,&y,&t);
        cost[x][y]=t;
    }
}
void Dijstra(int x){

    memset(book,false,sizeof(book));
    for(int i=1;i<=n;++i) d[i]=cost[x][i];
    book[x]=true;

    for(int i=1,tmp;i<n;i++){
        tmp=inf;
        for(int j=1;j<=n;j++)
            if(!book[j] and d[j]<tmp){
                tmp=d[j];
                x=j;
            }
        book[x]=true;
        for(int j=1;j<=n;j++)
            d[j]=min(d[j],d[x]+cost[x][j]);
    }
}
int main(){

    ini();
    Dijstra(to);    //to为起点到各点最短距离
    for(int i=1;i<=n;i++){
        res.push_back(d[i]);
        for(int j=i+1;j<=n;j++)
            swap(cost[i][j],cost[j][i]);
    }
    Dijstra(to);    //转置后to为终点
    for(int i=1;i<=n;i++) res[i]+=d[i];
    res.erase(res.begin()+to);
    cout<<*(max_element(res.begin()+1,res.end()))<<endl;

//    system("pause");
    return 0;
}
