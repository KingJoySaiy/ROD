/*
 * UVA 12169（暴力+拓展欧几里得）
 * 题目大意：略(=_=)
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=105;
const int mod=10001;
int t[maxn],res[2*maxn],ct;

LL gcd(LL a,LL b){

    return b?gcd(b,a%b):a;
}
void extgcd(LL a,LL b,LL &x,LL &y){

    b?(extgcd(b,a%b,y,x),y-=(a/b)*x):(x=1,y=0);
}
int main(){

    cin>>ct;
    for(int i=1;i<=ct;i++)
        scanf("%d",t+i);
    res[1]=t[1];

    for(LL a=0;a<mod;a++){
        LL A=a+1,B=mod,C=t[2]-a*a*t[1],x,y;
        if(C%gcd(A,B)) continue;

        extgcd(A,B,x,y);
        x=x*C;
        for(int i=2;i<=2*ct;i++)
            res[i]=(a*res[i-1]+x)%mod;
        for(int i=1;i<=ct;i++)
            if(t[i]!=res[i*2-1]) goto ed;
        for(int i=1;i<=ct;i++)
            cout<<res[2*i]<<endl;
        break;

        ed:continue;
    }

//    system("pause");
    return 0;
}
