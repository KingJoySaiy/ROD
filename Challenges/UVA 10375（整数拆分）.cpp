/*
 * UVA 10375（整数拆分）
 * 题目大意：求两个大组合数的商。
 */
#include<bits/stdc++.h>
using namespace std;

const int maxn=10005;
int prime[maxn],a[maxn],n;
int p,q,r,s;

void ini(){

    bool book[maxn]={};
    for(int i=2;i<maxn;i++)
        if(!book[i]){
            prime[n++]=i;
            for(int j=i+i;j<maxn;j+=i) book[i]=true;
        }
}
void work(int x,const int &flag){  //分解x!，d为1在分子上，-1在分母上

    for(int i=1;i<=x;i++)
        for(int j=0,t=i;j<n;j++){
            while(t%prime[j]==0){
                t/=prime[j];
                a[j]+=flag;
            }
            if(t==1) break;
        }

}
void solve(){

    memset(a,0,sizeof(a));
    work(p,1);
    work(q,-1);
    work(p-q,-1);
    work(r,-1);
    work(s,1);
    work(r-s,1);
    double res=1;
    for(int i=0;i<n;i++) res*=pow(prime[i],a[i]);
    printf("%.5lf\n",res);

}
int main(){

    ini();
    while(cin>>p>>q>>r>>s) solve();

//    system("pause");
    return 0;
}
/*
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
 */