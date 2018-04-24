/*
 * POJ 3259 (负环 Bellman-Ford)
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <cstring>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

const int maxn = 505;
const int inf = (INT_MAX>>1) -10;
int cost[maxn][maxn],d[maxn];
int n,m,w,x,y,z;

struct node{

    int from, to, cost;
    node(int x,int y,int z):from(x),to(y),cost(z){}
};
vector<node> edge;

bool Bellman_ford(){

    fill(d,d+maxn,inf);
    d[1] = 0;
    int ct = n;
    while(--ct){
        bool flag = false;
        for(int i = 0; i < edge.size(); i++){
            if(d[edge[i].to] > d[edge[i].from] + edge[i].cost){
                flag = true;
                d[edge[i].to] = d[edge[i].from] + edge[i].cost;
            }
        }
        if(!flag) return false; //无负环
    }
    for(int i = 0; i < edge.size(); i++)
        if(d[edge[i].to] > d[edge[i].from] + edge[i].cost) return true;
    return false;
}
void solve(){

    edge.clear();
    cin>>n>>m>>w;
    for(int i = 0; i < maxn; i++){
        fill(cost[i],cost[i] + maxn,inf);
        cost[i][i] = 0;
    }
    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        edge.push_back(node(x,y,z));
        edge.push_back(node(y,x,z));
    }
    while(w--){
        scanf("%d%d%d",&x,&y,&z);
        edge.push_back(node(x,y,-z));
    }
    puts(Bellman_ford()?"YES":"NO");
}
int main(){

    int ct;
    cin>>ct;
    while(ct--) solve();

//    system("pause");
    return 0;
}