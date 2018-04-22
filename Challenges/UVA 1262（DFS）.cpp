/*
 * UVA 1262£¨DFS£©
 */
#include<bits/stdc++.h>
using namespace std;
vector<char> a[6];
char res[6];
int cnt,k;

bool dfs(int step){

    if(step==5){
        if(++cnt==k){
            res[5]='\0';
            puts(res);
            return true;
        }
        return false;
    }
    for(int i=0;i<a[step].size();i++){
        res[step]=a[step][i];
        if(dfs(step+1)) return true;
    }
    return false;
}
void solve(){

    for(int i=0;i<5;i++) a[i].clear();
    char t[2][6][10];
    bool vis[2][26];

    cin>>k;
    for(int i=0;i<2;i++)
        for(int j=0;j<6;j++)
            scanf("%s",t[i][j]);

    for(int s=0;s<5;s++){
        memset(vis,0,sizeof(vis));
        for(int i=0;i<2;i++)
            for(int j=0;j<6;j++)
                vis[i][t[i][j][s]-'A']=true;
        for(int i=0;i<26;i++)
            if(vis[0][i]&&vis[1][i]) a[s].push_back(char(i+'A'));
    }
    cnt=0;
    if(!dfs(0)) puts("NO");
}
int main(){

    int ct;
    cin>>ct;
    while(ct--) solve();
//    system("pause");

    return 0;
}

