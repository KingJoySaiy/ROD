/*
 * POJ 1502 (×î¶ÌÂ·)
 */
#include<iostream>
#include<cstdlib>
#include<climits>
using namespace std;

const int maxn=105;
int cost[maxn][maxn],d[maxn],n;
bool book[maxn];
char a[5];

void dij(){

    fill(book,book+maxn,false);
    fill(d,d+maxn,INT_MAX);
    d[1]=0;
    while(1){
        int t=-1;
        for(int i=1;i<=n;i++) if(!book[i] and (t==-1 or d[i]<d[t])) t=i;
        if(t==-1) break;
        book[t]=true;
        for(int i=1;i<=n;i++)
            if(cost[t][i]!=INT_MAX) d[i]=min(d[i],d[t]+cost[t][i]);
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
    dij();
    int res=d[1];
    for(int i=2;i<=n;i++) res=max(res,d[i]);
    cout<<res<<endl;

//    system("pause");
    return 0;
}
