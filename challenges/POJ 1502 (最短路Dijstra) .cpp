/*
 * POJ 1502 (最短路Dijstra)
 */
 #include<iostream>
#include<climits>
#include<cstdlib>
#include<cstdio>
#include<queue>
using namespace std;

typedef pair<int,int> PP;
const int maxn=105;
int n,cost[maxn][maxn],d[maxn];
char a[5];

void Dijstra(int v){

    fill(d,d+maxn,INT_MAX);
    d[v]=0;

    priority_queue<PP,vector<PP>,greater<PP> > que;
    que.push(make_pair(0,v));    //first->cost second->to 按first升序取出

    while(!que.empty()){
        PP t=que.top(); que.pop();
        int x=t.second;
        if(d[x]<t.first) continue;
        for(int i=1;i<=n;i++)
            if(cost[x][i]!=INT_MAX and d[x]+cost[x][i]<d[i]){
                d[i]=d[x]+cost[x][i];
                que.push(make_pair(d[i],i));
            }
    }
}
int main(){

    cin>>n;
    for(int i=2,t;i<=n;i++)
        for(int j=1;j<i;j++){
            cin>>a;
            if(a[0]=='x') cost[i][j]=cost[j][i]=INT_MAX;
            else{
                t=0;
                for(char *p=a;*p;p++) t=t*10+int(*p-'0');
                cost[i][j]=cost[j][i]=t;
            }
        }
    Dijstra(1);
    int res=d[1];
    for(int i=2;i<=n;i++) res=max(res,d[i]);
    cout<<res<<endl;

//    system("pause");
    return 0;
}
