/*
 * HDU 11582（斐波那契）
 * 题目大意：求第a^b个斐波那契数对n取模。
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;

const int maxn=1005;
int fib[maxn][3*maxn];  //记录第j个斐波那契数对i取模
int t[maxn];            //记录周期
LL a,b;

void ini(){         //打个表

    for(int n=2;n<=1000;n++){
        fib[n][0]=0;
        fib[n][1]=1;
        for(int i=2;;i++){
            fib[n][i]=(fib[n][i-2]+fib[n][i-1])%n;
            if(fib[n][i-1]==0&&fib[n][i]==1){
                t[n]=i-1;
                break;
            }
        }
    }
}
int pow_mod(LL x,LL n,int mod){     //快速幂

    int res=1;
    while(n){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
void solve(){

    int mod;
    cin>>a>>b>>mod;
    if(!a||mod==1){     //注意特殊情况
        puts("0");
        return;
    }
    int tt=pow_mod(a%t[mod],b,t[mod]);
    cout<<fib[mod][tt]<<endl;
}
int main(){

    ini();
    int ct;
    cin>>ct;
    while(ct--) solve();

//    system("pause");
    return 0;
}
