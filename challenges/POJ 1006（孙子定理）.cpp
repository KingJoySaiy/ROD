/*
 * @模板题
 * POJ 1006 （中国剩余定理）
 * 题目大意：给定起始日期，三个活跃日期，三个周期，找出第一个共同活跃的日期。
 */
#include<iostream>
#include<cstdio>
typedef long long LL;
using namespace std;

int a[3],m[3]={23,28,33},n=3;

void extgcd(LL a,LL b,LL &x,LL &y){     //扩展欧几里德求逆元

    b?(extgcd(b,a%b,y,x),y-=(a/b)*x):(x=1,y=0);
}
LL crt(){      //中国剩余定理

    LL M=1,res=0,x,y;
    for(int i=0;i<n;i++) M*=m[i];
    for(int i=0;i<n;i++){
        LL mi=M/m[i];
        extgcd(mi,m[i],x,y);
        res=(res+mi*x*a[i])%M;
    }
    if(res<0) res+=M;   //注意res<0的情况
    return res;
}
int main(){

    int ct=0,x;
    while(cin>>a[0]>>a[1]>>a[2]>>x){
        if(a[0]==-1&&a[1]==-1&&a[2]==-1&&x==-1) break;
        int res=crt()-x;
        if(res<=0) res+=21252;
        printf("Case %d: the next triple peak occurs in %d days.\n",++ct,res);
    }

    return 0;
}
