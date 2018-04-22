/*
 * @模版题
 * HDU 4651（整数拆分）
 * 题目大意：给定若干整数，求拆分方案数对(1e9+7)取模。
 */
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=1e5+5;
int dp[maxn];     //动规记录拆分方案数

void chaifen(){

    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<maxn;i++)
        for(int j=1,r=1;i-(3*j*j-j)/2>=0;j++,r*=-1){   //加上广义五边形数
            dp[i]=(dp[i]+dp[i-(3*j*j-j)/2]*r)%mod;
            dp[i]=(dp[i]+mod)%mod;
            if(i-(3*j*j+j)/2>=0){
                dp[i]=(dp[i]+dp[i-(3*j*j+j)/2]*r)%mod;
                dp[i]=(dp[i]+mod)%mod;
            }
        }
}
int main(){

    chaifen();
    int ct,x;
    cin>>ct;
    while(ct--){
        scanf("%d",&x);
        printf("%d\n",dp[x]);
    }

    return 0;
}